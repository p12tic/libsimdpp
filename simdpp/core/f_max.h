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

#ifndef LIBSIMDPP_SIMDPP_CORE_F_MAX_H
#define LIBSIMDPP_SIMDPP_CORE_F_MAX_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes maxima of the values of two vectors. If at least one of the values
    is NaN, or both values are zeroes, it is unspecified which value will be
    returned.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 max(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_ps(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 max(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_max_ps(a, b);
#else
    SIMDPP_VEC_ARRAY_IMPL2(float32x8, max, a, b);
#endif
}
/// @}

/// @{
/** Computes maxima of the values of two vectors. If at least one of the values
    is NaN, or both values are zeroes, it is unspecified which value will be
    returned.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 max(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_pd(a, b);
#endif
}

inline float64x4 max(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_max_pd(a, b);
#else
    SIMDPP_VEC_ARRAY_IMPL2(float64x4, max, a, b);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

