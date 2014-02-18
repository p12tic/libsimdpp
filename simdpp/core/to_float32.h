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

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_FLOAT32_H
#define LIBSIMDPP_SIMDPP_CORE_TO_FLOAT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Converts 32-bit integer values to 32-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the current rounding mode is
    used.

    NEON, ALTIVEC specific:

    If only inexact conversion can be performed, round to nearest mode is used.

    @code
    r0 = (float) a0
    ...
    rN = (float) aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 to_float32x4(int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<float32x4>(a, [](int32_t x) { return float(x); });
#elif SIMDPP_USE_SSE2
    return _mm_cvtepi32_ps(a);
#elif SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP
    detail::mem_block<int32x4> mi(a);
    detail::mem_block<float32x4> mf;
    mf[0] = float(mi[0]);
    mf[1] = float(mi[1]);
    mf[2] = float(mi[2]);
    mf[3] = float(mi[3]);
    return mf;
#elif SIMDPP_USE_NEON_FLT_SP
    return vcvtq_f32_s32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_ctf((__vector int32_t)a, 0);
#endif
}

inline float32x8 to_float32x8(int32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_cvtepi32_ps(a);
#else
    return float32x8(to_float32x4(a[0]), to_float32x4(a[1]));
#endif
}
/// @}

/// @{
/** Converts 64-bit float values to 32-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is truncated.

    @par 128-bit version:
    @code
    r0 = (float) a0
    r1 = (float) a1
    r2 = 0.0f
    r3 = 0.0f
    @endcode

    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @code
    r0 = (float) a0
    ...
    r3 = (float) a3
    r4 = 0.0f
    ...
    r7 = 0.0f
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
inline float32x4 to_float32x4(float64x2 a)
{
#if SIMDPP_USE_NULL
    float32x4 r;
    r[0] = float(a[0]);
    r[1] = float(a[1]);
    r[2] = 0.0;
    r[3] = 0.0;
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_cvtpd_ps(a);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> r;
    r[0] = float(a[0]);
    r[1] = float(a[1]);
    r[2] = 0;
    r[3] = 0;
    return r;
#endif
}

inline float32x8 to_float32x8(float64x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> r;
    r[0] = float(a[0][0]);
    r[1] = float(a[0][1]);
    r[2] = float(a[1][0]);
    r[3] = float(a[1][1]);
    return float32x8(r, float32x4::zero());
#elif SIMDPP_USE_AVX
    return _mm256_castps128_ps256(_mm256_cvtpd_ps(a));
#elif SIMDPP_USE_SSE2
    return float32x8(to_float32x4(a[0]), to_float32x4(move_l<2>(a[0])));
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

