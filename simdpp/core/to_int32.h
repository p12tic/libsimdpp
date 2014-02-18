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

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_INT32_H
#define LIBSIMDPP_SIMDPP_CORE_TO_INT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/insert.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Sign extends the first 8 values of a signed int16x16 vector to 32-bits

    @code
    r0 = (int32_t) a0
    ...
    r7 = (int32_t) a7
    @endcode
    @icost{SSE4.1-AVX, 3}
    @icost{SSE2-SSSE3, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline gint32x8 to_int32(int16x8 a)
{
#if SIMDPP_USE_NULL
    int32x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i/4].el(i%4) = int32_t(a[0].el(i));
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepi16_epi32(a);
#elif SIMDPP_USE_SSE4_1
    int32x8 r;
    r[0] = _mm_cvtepi16_epi32(a);
    r[1] = _mm_cvtepi16_epi32(move_l<4>(a).eval());
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 b0, b1, sign;
    sign = shift_r<16>(a);
    b0 = zip_lo(a, sign);
    b1 = zip_hi(a, sign);
    return gint32x8(combine(b0, b1));
#elif SIMDPP_USE_NEON
    int32x8 r;
    r[0] = vmovl_s16(vget_low_s16(a[0]));
    r[1] = vmovl_s16(vget_high_s16(a[1]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int32x4 b0, b1;
    b0 = vec_unpackh((__vector int16_t)a[0]);
    b1 = vec_unpackl((__vector int16_t)a[0]);
    return combine(b0, b1);
#endif
}

/// @{
/** Converts the values of a float32x4 vector into signed int32_t
    representation using truncation if only an inexact conversion can be
    performed. The behavior is undefined if the value can not be represented in
    the result type.

    SSE specific:
    If the value can not be represented by int32_t, @c 0x80000000 is returned
    TODO: NaN handling

    NEON, ALTIVEC specific:
    If the value can not be represented by int32_t, either @c 0x80000000 or @c
    0x7fffffff is returned depending on the sign of the operand (saturation
    occurs). Conversion of NaNs results in @a 0.

    @code
    r0 = (int32_t) a0
    ...
    rN = (int32_t) aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline gint32x4 to_int32(float32x4 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<int32x4>(a, [](float x) { return int32_t(x); });
#elif SIMDPP_USE_SSE2
    return _mm_cvttps_epi32(a);
#elif SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP
    detail::mem_block<float32x4> mf(a);
    detail::mem_block<int32x4> mi;
    mi[0] = int(mf[0]);
    mi[1] = int(mf[1]);
    mi[2] = int(mf[2]);
    mi[3] = int(mf[3]);
    return mi;
#elif SIMDPP_USE_NEON_FLT_SP
    return vcvtq_s32_f32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_cts((__vector float)a, 0);
#endif
}

#if SIMDPP_USE_AVX2
inline gint32x8 to_int32x8(float32x8 a)
{
    return _mm256_cvttps_epi32(a);
}
#endif

template<unsigned N>
gint32<N> to_int32x8(float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(gint32<N>, to_int32, a);
}
/// @}

/// @{
/** Converts the values of a doublex2 vector into int32_t representation using
    truncation. The behavior is undefined if the value can not be represented
    in the result type.

    SSE specific:
    If the value can not be represented by int32_t, @c 0x80000000 is returned
    @todo NaN handling

    NEON VFP specific:
    If the value can not be represented by int32_t, either @c 0x80000000 or @c
    0x7fffffff is returned depending on the sign of the operand. Conversion of
    NaNs results in @a 0.

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @code
    r0 = (int32_t) a0
    r1 = (int32_t) a1
    r2 = (int32_t) a2
    r3 = (int32_t) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
*/
inline gint32x4 to_int32(float64x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> r;
    r[0] = int32_t(a[0].el(0));
    r[1] = int32_t(a[0].el(1));
    r[2] = int32_t(a[1].el(0));
    r[3] = int32_t(a[1].el(1));
    return r;
#elif SIMDPP_USE_SSE2
    gint32x4 r1, r2;
    float64x2 a1, a2;
    split(a, a1, a2);
    r1 = _mm_cvttpd_epi32(a1);
    r2 = _mm_cvttpd_epi32(a2);
    r2 = move_l<2>(r2);
    return bit_or(r1, r2);
#else
    SIMDPP_NOT_IMPLEMENTED1(a); return int32x4();
#endif
}

// TODO support arbitrary length vectors

/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

