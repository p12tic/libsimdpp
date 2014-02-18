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
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Sign extends the first 4 values of a signed int16x8 vector to 32-bits

    @code
    r0 = (int32_t) a0
    ...
    r3 = (int32_t) a3
    @endcode
    @icost{SSE2-SSSE3, 2}
*/
inline basic_int32x4 to_int32x4(int16x8 a)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = int32_t(a[i]);
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepi16_epi32(a);
#elif SIMDPP_USE_SSE2
    int32x4 r;
    r = zip_lo(int16x8::zero(), a);
    r = shift_r(r, 16);
    return r;
#elif SIMDPP_USE_NEON
    return vmovl_s16(vget_low_s16(a));
#elif SIMDPP_USE_ALTIVEC
    return vec_unpackh((__vector int16_t)a);
#endif
}


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
inline basic_int32x8 to_int32x8(int16x16 a)
{
#if SIMDPP_USE_NULL
    int32x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i/4][i%4] = int32_t(a[0][i]);
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepi16_epi32(_mm256_castsi256_si128(a));
#elif SIMDPP_USE_SSE4_1
    int32x8 r;
    r[0] = to_int32x4(a[0]);
    r[1] = to_int32x4(move_l<4>(a[0]));
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 b0, b1;
    b0 = zip_lo(int16x8::zero(), a[0]);
    b1 = zip_hi(int16x8::zero(), a[0]);
    b0 = shift_r<8>(b0);
    b1 = shift_r<8>(b1);
    return int32x8(b0, b1);
#elif SIMDPP_USE_NEON
    int32x8 r;
    r[0] = vmovl_s16(vget_low_s16(a[0]));
    r[1] = vmovl_s16(vget_high_s16(a[1]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int32x4 b0, b1;
    b0 = vec_unpackh((__vector int16_t)a[0]);
    b1 = vec_unpackl((__vector int16_t)a[0]);
    return {b0, b1};
#endif
}

/** Zero-extends the values of a unsigned int16x8 vector to 32-bits

    @code
    r0 = (uint32_t) a0
    ...
    r3 = (uint32_t) a3
    @endcode
*/
inline basic_int32x4 to_int32x4(uint16x8 a)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = int32_t(a[i]);
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepu16_epi32(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    int32x4 r = zip_lo(a, int16x8::zero());
    return r;
#elif SIMDPP_USE_NEON
    return vmovl_u16(vget_low_u16(a));
#endif
}



/** Zero-extends the first 8 values of a unsigned int16x16 vector to 32-bits

    @code
    r0 = (uint32_t) a0
    ...
    r7 = (uint32_t) a7
    @endcode
    @icost{SSE2-AVX, ALTIVEC, 2}
    @icost{NEON, 2}
*/
inline basic_int32x8 to_int32x8(uint16x16 a)
{
#if SIMDPP_USE_NULL
    uint32x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i/4][i%4] = uint32_t(a[0][i]);
    }
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepu16_epi32(_mm256_castsi256_si128(a));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint32x4 b0, b1;
    b0 = zip_lo(a[0], uint16x8::zero());
    b1 = zip_hi(a[0], uint16x8::zero());
    return uint32x8(b0, b1);
#elif SIMDPP_USE_NEON
    uint32x8 r;
    r[0] = vmovl_u16(vget_low_u16(a[0]));
    r[1] = vmovl_u16(vget_high_u16(a[1]));
    return r;
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
inline basic_int32x4 to_int32x4(float32x4 a)
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

inline basic_int32x8 to_int32x8(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_cvttps_epi32(a);
#else
    return int32x8(to_int32x4(a[0]), to_int32x4(a[1]));
#endif
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
    r2 = 0
    r3 = 0
    @endcode

    @par 256-bit version:
    @code
    r0 = (int32_t) a0
    ...
    r3 = (int32_t) a3
    r4 = 0
    ...
    r7 = 0
    @endcode
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 3}
*/
inline basic_int32x4 to_int32x4(float64x2 a)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    r[0] = int32_t(a[0]);
    r[1] = int32_t(a[1]);
    r[2] = 0;
    r[3] = 0;
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_cvttpd_epi32(a);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> r;
    r[0] = int32_t(a[0]);
    r[1] = int32_t(a[1]);
    r[2] = 0;
    r[3] = 0;
    return r;
#else
    SIMDPP_NOT_IMPLEMENTED1(a); return int32x4();
#endif
}

inline basic_int32x8 to_int32x8(float64x4 a)
{
#if SIMDPP_USE_NULL
    int32x8 r = int32x8::zero();
    r[0][0] = int32_t(a[0][0]);
    r[0][1] = int32_t(a[0][1]);
    r[0][2] = int32_t(a[1][0]);
    r[0][3] = int32_t(a[1][1]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_castsi128_si256(_mm256_cvttpd_epi32(a));
#elif SIMDPP_USE_SSE2
    int32x4 b0 = to_int32x4(a[0]);
    int32x4 b1 = to_int32x4(a[1]);
    return {zip_lo(b0, b1), int32x4::zero()};
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x8> r;
    r[0] = int32_t(a[0][0]);
    r[1] = int32_t(a[0][1]);
    r[2] = int32_t(a[1][0]);
    r[3] = int32_t(a[1][1]);
    r[4] = 0;  r[5] = 0;  r[6] = 0;  r[7] = 0;
    return r;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}
/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

