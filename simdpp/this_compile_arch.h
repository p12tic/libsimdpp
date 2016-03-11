/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_THIS_COMPILE_ARCH_H
#define LIBSIMDPP_SIMD_THIS_COMPILE_ARCH_H

#include <simdpp/dispatch/arch.h>

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** @defgroup simd_dispatcher Dispatching support
    @{
*/

/** Returns the instruction set flags that will be required by the currently
    compiled code
*/
inline Arch this_compile_arch()
{
    Arch res = Arch::NONE_NULL;
#if SIMDPP_USE_SSE2
    res |= Arch::X86_SSE2;
#endif
#if SIMDPP_USE_SSE3
    res |= Arch::X86_SSE3;
#endif
#if SIMDPP_USE_SSSE3
    res |= Arch::X86_SSSE3;
#endif
#if SIMDPP_USE_SSE4_1
    res |= Arch::X86_SSE4_1;
#endif
#if SIMDPP_USE_AVX
    res |= Arch::X86_AVX;
#endif
#if SIMDPP_USE_AVX2
    res |= Arch::X86_AVX2;
#endif
#if SIMDPP_USE_FMA3
    res |= Arch::X86_FMA3;
#endif
#if SIMDPP_USE_FMA4
    res |= Arch::X86_FMA4;
#endif
#if SIMDPP_USE_XOP
    res |= Arch::X86_XOP;
#endif
#if SIMDPP_USE_AVX512F
    res |= Arch::X86_AVX512F;
#endif
#if SIMDPP_USE_NEON
    res |= Arch::ARM_NEON;
#endif
#if SIMDPP_USE_NEON_FLT_SP
    res |= Arch::ARM_NEON_FLT_SP;
#endif
    return res;
}

/// @} -- end defgroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

