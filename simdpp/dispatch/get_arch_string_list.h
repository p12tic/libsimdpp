/*  Copyright (C) 2015  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DISPATCH_GET_ARCH_STRING_LIST_H
#define LIBSIMDPP_DISPATCH_GET_ARCH_STRING_LIST_H

#include <vector>
#include <cstring>
#include <simdpp/dispatch/arch.h>
#include <simdpp/setup_arch.h>

namespace simdpp {
namespace detail {
struct ArchDesc {
    const char* id;
    Arch arch;

    ArchDesc(const char* i, Arch a) : id(i), arch(a) {}
};
} // namespace detail

/** Retrieves supported architecture from given string list. The architecture
    names are the same as ids specified in simdpp/detail/insn_id.h
*/
inline Arch get_arch_string_list(const char* const strings[], int count, const char* prefix)
{
    typedef ::simdpp::detail::ArchDesc ArchDesc;

    Arch res = Arch::NONE_NULL;

    if (!prefix)
        prefix = "";

    std::vector<ArchDesc> features;

#if SIMDPP_ARM && SIMDPP_32_BITS
    features.push_back(ArchDesc("neon", Arch::ARM_NEON));
    features.push_back(ArchDesc("neonfltsp", Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP));
#elif SIMDPP_ARM && SIMDPP_64_BITS
    features.push_back(ArchDesc("neon", Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP));
    features.push_back(ArchDesc("neonfltsp", Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP));
#elif SIMDPP_X86
    Arch a_sse2 = Arch::X86_SSE2;
    Arch a_sse3 = a_sse2 | Arch::X86_SSE3;
    Arch a_ssse3 = a_sse3 | Arch::X86_SSSE3;
    Arch a_sse4_1 = a_ssse3 | Arch::X86_SSE4_1;
    Arch a_popcnt = Arch::X86_POPCNT_INSN;
    Arch a_avx = a_sse4_1 | Arch::X86_AVX;
    Arch a_avx2 = a_avx | Arch::X86_AVX2;
    Arch a_fma3 = a_sse3 | Arch::X86_FMA3;
    Arch a_fma4 = a_sse3 | Arch::X86_FMA4;
    Arch a_xop = a_sse3 | Arch::X86_XOP;
    Arch a_avx512f = a_avx2 | Arch::X86_AVX512F;
    Arch a_avx512bw = a_avx512f | Arch::X86_AVX512BW;
    Arch a_avx512dq = a_avx512f | Arch::X86_AVX512DQ;

    features.push_back(ArchDesc("sse2", a_sse2));
    features.push_back(ArchDesc("sse3", a_sse3));
    features.push_back(ArchDesc("ssse3", a_ssse3));
    features.push_back(ArchDesc("sse4p1", a_sse4_1));
    features.push_back(ArchDesc("popcnt", a_popcnt));
    features.push_back(ArchDesc("avx", a_avx));
    features.push_back(ArchDesc("avx2", a_avx2));
    features.push_back(ArchDesc("fma3", a_fma3));
    features.push_back(ArchDesc("fma4", a_fma4));
    features.push_back(ArchDesc("xop", a_xop));
    features.push_back(ArchDesc("avx512f", a_avx512f));
    features.push_back(ArchDesc("avx512bw", a_avx512bw));
    features.push_back(ArchDesc("avx512dq", a_avx512dq));
#elif SIMDPP_PPC
    Arch a_altivec = Arch::POWER_ALTIVEC;
    Arch a_vsx_206 = a_altivec | Arch::POWER_VSX_206;
    Arch a_vsx_207 = a_vsx_206 | Arch::POWER_VSX_207;

    features.push_back(ArchDesc("altivec", a_altivec));
    features.push_back(ArchDesc("vsx_206", a_vsx_206));
    features.push_back(ArchDesc("vsx_207", a_vsx_207));
#elif SIMDPP_MIPS
    features.push_back(ArchDesc("msa", Arch::MIPS_MSA));
#else
    return res;
#endif

    int prefixlen = std::strlen(prefix);
    for (int i = 0; i < count; ++i) {
        const char* s = *strings++;
        int len = std::strlen(s);

        // check if s matches prefix
        if (len < prefixlen)
            continue;
        if (std::strncmp(prefix, s, prefixlen) != 0)
            continue;

        // strip prefix
        s += prefixlen;
        len -= prefixlen;

        // check if any of the architectures match
        for (unsigned j = 0; j < features.size(); ++j) {
            if (std::strcmp(s, features[j].id) == 0)
                res |= features[j].arch;
        }
    }

    return res;
}

} // namespace simdpp

#endif
