/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DISPATCH_GET_ARCH_RAW_CPUID_H
#define LIBSIMDPP_DISPATCH_GET_ARCH_RAW_CPUID_H

#if (__i386__ || __amd64__) && (__clang__ || __GNUC__ || __INTEL_COMPILER || _MSC_VER)
#define SIMDPP_HAS_GET_ARCH_RAW_CPUID 1

#include <simdpp/dispatch/arch.h>
#include <stdint.h>

#if __GNUC__
#include <cpuid.h>
#endif

namespace simdpp {
namespace detail {

inline void get_cpuid(unsigned level, unsigned subleaf, unsigned* eax, unsigned* ebx,
                      unsigned* ecx, unsigned* edx)
{
#if __clang__ || __INTEL_COMPILER
    // Older versions of clang don't support subleafs, which leads to inability
    // to detect AVX2 for example. On ICC there's no proper cpuid intrinsic.
#if __i386__
    __asm("cpuid" : "=a"(*eax), "=b" (*ebx), "=c"(*ecx), "=d"(*edx) \
                  : "0"(level), "2"(subleaf));
#else
// x86-64 uses %rbx as the base register, so preserve it. */
    __asm("xchgq  %%rbx,%q1\n" \
          "cpuid\n" \
          "xchgq  %%rbx,%q1" \
            : "=a"(*eax), "=b" (*ebx), "=c"(*ecx), "=d"(*edx) \
            : "0"(level), "2"(subleaf));
#endif
#elif __GNUC__
    __cpuid_count(level, subleaf, *eax, *ebx, *ecx, *edx);
#elif _MSC_VER
    uint32_t regs[4];
    __cpuidex((int*) regs, subleaf, level);
    *eax = regs[0];
    *ebx = regs[1];
    *ecx = regs[2];
    *edx = regs[3];
#else
    #error "unsupported compiler"
#endif
}

inline uint64_t get_xcr(unsigned level)
{
#if (defined (_MSC_FULL_VER) && _MSC_FULL_VER >= 160040000) || (defined (__INTEL_COMPILER) && __INTEL_COMPILER >= 1200) // Microsoft or Intel compiler supporting _xgetbv intrinsic
    return _xgetbv(level);
#elif defined(__GNUC__) || defined(__clang__)
    uint32_t eax, edx;
    __asm("xgetbv" : "=a"(eax),"=d"(edx) : "c"(level) : );
    return eax | (uint64_t(edx) << 32);
#else
    return 0;
#endif
}

} // namespace detail

/** Retrieves supported architecture using the CPUID instruction. Works only on
    x86.
*/
inline Arch get_arch_raw_cpuid()
{
    Arch arch_info = Arch::NONE_NULL;

    uint32_t eax, ebx, ecx, edx;
    bool xsave_xrstore_avail = false;

    simdpp::detail::get_cpuid(0, 0, &eax, &ebx, &ecx, &edx);
    unsigned max_cpuid_level = eax;

    simdpp::detail::get_cpuid(0x80000000, 0, &eax, &ebx, &ecx, &edx);
    unsigned max_ex_cpuid_level = eax;

    if (max_cpuid_level >= 0x00000001) {
        simdpp::detail::get_cpuid(0x00000001, 0, &eax, &ebx, &ecx, &edx);

        if (edx & (1 << 26))
            arch_info |= Arch::X86_SSE2;
        if (ecx & (1 << 0))
            arch_info |= Arch::X86_SSE3;
        if (ecx & (1 << 9))
            arch_info |= Arch::X86_SSSE3;
        if (ecx & (1 << 19))
            arch_info |= Arch::X86_SSE4_1;
        if (ecx & (1 << 12))
            arch_info |= Arch::X86_FMA3;
        if (ecx & (1 << 26)) {
            // XSAVE/XRSTORE available on hardware, now check OS support
            uint64_t xcr = simdpp::detail::get_xcr(0);
            if ((xcr & 6) == 6)
                xsave_xrstore_avail = true;
        }

        if (ecx & (1 << 28) && xsave_xrstore_avail)
            arch_info |= Arch::X86_AVX;
    }
    if (max_ex_cpuid_level >= 0x80000001) {
        simdpp::detail::get_cpuid(0x80000001, 0, &eax, &ebx, &ecx, &edx);
        if (ecx & (1 << 16))
            arch_info |= Arch::X86_FMA4;
        if (ecx & (1 << 11))
            arch_info |= Arch::X86_XOP;
    }

    if (max_cpuid_level >= 0x00000007) {
        simdpp::detail::get_cpuid(0x00000007, 0, &eax, &ebx, &ecx, &edx);
        if (ebx & (1 << 5) && xsave_xrstore_avail)
            arch_info |= Arch::X86_AVX2;
        if (ebx & (1 << 16) && xsave_xrstore_avail)
            arch_info |= Arch::X86_AVX512F;
    }

    return arch_info;
}

} // namespace simdpp

#endif // #if (__i386__ || __amd64__) && ...

#endif
