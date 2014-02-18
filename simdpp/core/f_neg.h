/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_CORE_F_NEG_H
#define LIBSIMDPP_SIMDPP_CORE_F_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Negates the values of a float32x4 vector

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, 2-3}
    @icost{AVX-AVX2, NEON, 2}
*/
inline float32x4 neg(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // reversion of the sign bit required even for NaNs and zeros
    int32x4 zero = int32x4::make_const(0x80000000);
    return bit_xor(a, zero);
#elif SIMDPP_USE_NEON_FLT_SP
    return vnegq_f32(a);
#endif
}

inline float32x8 neg(float32x8 a)
{
#if SIMDPP_USE_AVX
    int32x8 zero = int32x8::make_const(0x80000000);
    return bit_xor(a, zero);
#else
    SIMDPP_VEC_ARRAY_IMPL1(float32x8, neg, a);
#endif
}
/// @}

/// @{
/** Negates the values of a vector

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 1-2}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX-AVX2, 1-2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 neg(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    int64x2 zero = int64x2::make_const(0x8000000000000000);
    return bit_xor(a, zero);
#endif
}

inline float64x4 neg(float64x4 a)
{
#if SIMDPP_USE_AVX
    int64x4 zero = int64x4::make_const(0x8000000000000000);
    return bit_xor(a, zero);
#else
    SIMDPP_VEC_ARRAY_IMPL1(float64x4, neg, a);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

