/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMD_THIS_COMPILE_ARCH_H
#define LIBSIMDPP_SIMD_THIS_COMPILE_ARCH_H

#include <simdpp/dispatch/arch.h>

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

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
#if SIMDPP_USE_NEON
    res |= Arch::ARM_NEON;
#endif
#if SIMDPP_USE_NEON_FLT_SP
    res |= Arch::ARM_NEON_FLT_SP;
#endif
    return res;
}

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

