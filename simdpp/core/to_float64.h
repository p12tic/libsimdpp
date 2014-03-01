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

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_FLOAT64_H
#define LIBSIMDPP_SIMDPP_CORE_TO_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/mem_block.h>
#include <simdpp/core/move_l.h>
#include <simdpp/sse/extract_half.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Converts the 32-bit integer values to 64-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is rounded to the
    nearest representable value.

    @par 256-bit version:
    @code
    r0 = (double) a0
    ...
    r3 = (double) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
inline float64x4 to_float64(int32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> ax(a);
    float64x4 r;
    r[0].el(0) = double(ax[0]);
    r[0].el(1) = double(ax[1]);
    r[1].el(0) = double(ax[2]);
    r[1].el(1) = double(ax[3]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_cvtepi32_pd(a);
#elif SIMDPP_USE_SSE2
    float64x2 r1, r2;
    r1 = _mm_cvtepi32_pd(a);
    r2 = _mm_cvtepi32_pd(move4_r<2>(a).eval());
    return combine(r1, r2);
#endif
}

#if SIMDPP_USE_AVX2
inline float64<8> to_float64(float32x8 a)
{
    float64x4 r1, r2;
    float32x4 a1, a2;
    split(a, a1, a2);
    r1 = _mm256_cvtepi32_pd(a1);
    r2 = _mm256_cvtepi32_pd(a2);
    return combine(r1, r2);
}
#endif
/// @}

// TODO support arbitrary length vectors

/// @{
/** Converts the 32-bit float values to 64-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is rounded to the
    nearest representable value.

    @par 256-bit version:
    @code
    r0 = (double) a0
    ...
    r3 = (double) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
inline float64x4 to_float64(float32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> ax(a);
    float64x4 r;
    r[0].el(0) = double(ax[0]);
    r[0].el(1) = double(ax[1]);
    r[1].el(0) = double(ax[2]);
    r[1].el(1) = double(ax[3]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_cvtps_pd(a);
#elif SIMDPP_USE_SSE2
    float64x2 r1, r2;
    r1 = _mm_cvtps_pd(a);
    r2 = _mm_cvtps_pd(move4_r<2>(a).eval());
    return combine(r1, r2);
#endif
}

#if SIMDPP_USE_AVX
inline float64<8> to_float64(float32x8 a)
{
    float64x2 r1, r2;
    float32x4 a1, a2;
    split(a, a1, a2);
    r1 = _mm256_cvtps_pd(a1);
    r2 = _mm256_cvtps_pd(a2);
    return combine(r1, r2);
}
#endif

// TODO support arbitrary length vectors

/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

