/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_CONVERT_H
#define LIBSIMDPP_SIMD_CONVERT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/cast.h>
#include <simdpp/simd/math_shift.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/types.h>
#include <simdpp/simd/detail/mem_block.h>

#if SIMDPP_USE_AVX2
    #include <simdpp/sse/extract_half.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_convert Operations: convert
/// @{

/** Sign extends the first 8 values of a signed int8x16 vector to 16-bits

    @code
    r0 = (int16_t) a0
    ...
    r7 = (int16_t) a7
    @endcode
    @icost{SSE2-SSSE3, 2}
*/
inline basic_int16x8 to_int16x8(int8x16 a)
{
#if SIMDPP_USE_NULL
    int16x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i] = int16_t(a[i]);
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepi8_epi16(a);
#elif SIMDPP_USE_SSE2
    int16x8 r;
    r = zip_lo(int8x16::zero(), a);
    r = shift_r(r, 8);
    return r;
#elif SIMDPP_USE_NEON
    return vmovl_s8(vget_low_s8(a));
#elif SIMDPP_USE_ALTIVEC
    return vec_unpackh((__vector int8_t)a);
#endif
}

/** Sign extends the first 16 values of a signed int8x32 vector to 16-bits

    @code
    r0 = (int16_t) a0
    ...
    r15 = (int16_t) a15
    @endcode

    @icost{SSE4.1-AVX, 3}
    @icost{SSE2-SSSE3, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline basic_int16x16 to_int16x16(int8x32 a)
{
#if SIMDPP_USE_NULL
    int16x16 r;
    for (unsigned i = 0; i < 16; i++) {
        r[i/8][i%8] = int16_t(a[0][i]);
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a));
#elif SIMDPP_USE_SSE4_1
    int16x16 r;
    r[0] = to_int16x8(a[0]);
    r[1] = to_int16x8(move_l<8>(a[0]));
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 b0, b1;
    b0 = zip_lo(int8x16::zero(), a[0]);
    b1 = zip_hi(int8x16::zero(), a[0]);
    b0 = shift_r<8>(b0);
    b1 = shift_r<8>(b1);
    return int16x16(b0, b1);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_s8(vget_low_s8(a[0]));
    r[1] = vmovl_s8(vget_high_s8(a[1]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int16x8 b0, b1;
    b0 = vec_unpackh((__vector int8_t)a[0]);
    b1 = vec_unpackl((__vector int8_t)a[0]);
    return {b0, b1};
#endif
}

/** Extends the first 8 values of a unsigned int8x16 vector to 16-bits

    @code
    r0 = (uint16_t) a0
    ...
    r7 = (uint16_t) a7
    @endcode
*/
inline basic_int16x8 to_int16x8(uint8x16 a)
{
#if SIMDPP_USE_NULL
    uint16x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i] = int16_t(a[i]);
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepu8_epi16(a);
#elif SIMDPP_USE_SSE2
    return zip_lo(a, uint8x16::zero());
#elif SIMDPP_USE_NEON
    return vmovl_u8(vget_low_u8(a));
#elif SIMDPP_USE_ALTIVEC
    return zip_lo(uint8x16::zero(), a);
#endif
}

/** Extends the first 16 values of a unsigned int8x32 vector to 16-bits

    @code
    r0 = (uint16_t) a0
    ...
    r15 = (uint16_t) a15
    @endcode
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int16x16 to_int16x16(uint8x32 a)
{
#if SIMDPP_USE_NULL
    int16x16 r;
    for (unsigned i = 0; i < 16; i++) {
        r[i/8][i%8] = uint16_t(a[0][i]);
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepu8_epi16(_mm256_castsi256_si128(a));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    int16x8 b0, b1;
    b0 = zip_lo(a[0], int8x16::zero());
    b1 = zip_hi(a[0], int8x16::zero());
    return int16x16(b0, b1);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_s8(vget_low_s8(a[0]));
    r[1] = vmovl_s8(vget_high_s8(a[1]));
    return r;
#endif
}

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

/// @{
/** Extends the values of a signed int32x4 vector to 64-bits

    @par 128-bit version:
    @code
    r0 = (int64_t) a0
    r1 = (int64_t) a1
    @endcode

    @icost{SSE2-SSSE3, 2}
    @icost{ALTIVEC, 2-3}

    @par 256-bit version:
    @code
    r0 = (int64_t) a0
    ...
    r3 = (int64_t) a3
    @endcode

    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX, 3}
    @icost{NEON, 2}
    @icost{ALTIVEC, 3-4}
*/
inline basic_int64x2 to_int64x2(int32x4 a)
{
#if SIMDPP_USE_NULL
    int64x2 r;
    r[0] = int64_t(a[0]);
    r[1] = int64_t(a[1]);
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepi32_epi64(a);
#elif SIMDPP_USE_SSE2
    int32x4 u;
    u = shift_r(a, 31);
    a = zip_lo(a, u);
    return a;
#elif SIMDPP_USE_NEON
    return vmovl_s32(vget_low_s32(a));
#elif SIMDPP_USE_ALTIVEC
    int32x4 u;
    u = shift_r(a, 31);
    a = zip_lo(u, a);
    return a;
#endif
}

inline basic_int64x4 to_int64x4(int32x8 a)
{
#if SIMDPP_USE_NULL
    int64x4 r;
    r[0][0] = int64_t(a[0][0]);
    r[0][1] = int64_t(a[0][1]);
    r[1][0] = int64_t(a[0][2]);
    r[1][1] = int64_t(a[0][3]);
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepi32_epi64(sse::extract_lo(a));
#elif SIMDPP_USE_SSE2
    return int64x4(to_int64x2(a[0]), to_int64x2(move_l<2>(a[0])));
#elif SIMDPP_USE_NEON
    int64x4 r;
    r[0] = vmovl_s32(vget_low_s32(a[0]));
    r[1] = vmovl_s32(vget_high_s32(a[0]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int32x4 a0 = a[0];
    int32x4 u = shift_r(a0, 31);
    int64x2 b0, b1;
    b0 = zip_lo(u, a0);
    b1 = zip_hi(u, a0);
    return { b0, b1 };
#endif
}

/// @{
/** Extends the values of an unsigned int32x4 vector to 64-bits

    @par 128-bit version:
    @code
    r0 = (uint64_t) a0
    r1 = (uint64_t) a1
    @endcode

    @par 256-bit version:
    @code
    r0 = (uint64_t) a0
    ...
    r3 = (uint64_t) a3
    @endcode

    @icost{SSE2-AVX, 3}
    @icost{NEON, ALTIVEC, 2}
*/
inline basic_int64x2 to_int64x2(uint32x4 a)
{
#if SIMDPP_USE_NULL
    int64x2 r;
    r[0] = int64_t(a[0]);
    r[1] = int64_t(a[1]);
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepu32_epi64(a);
#elif SIMDPP_USE_SSE2
    return zip_lo(a, uint32x4::zero());
#elif SIMDPP_USE_NEON
    return vmovl_u32(vget_low_u32(a));
#elif SIMDPP_USE_ALTIVEC
    return zip_lo(uint32x4::zero(), a);
#endif
}

inline basic_int64x4 to_int64x4(uint32x8 a)
{
#if SIMDPP_USE_NULL
    int64x4 r;
    r[0][0] = int64_t(a[0][0]);
    r[0][1] = int64_t(a[0][1]);
    r[1][0] = int64_t(a[0][2]);
    r[1][1] = int64_t(a[0][3]);
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepu32_epi64(sse::extract_lo(a));
#elif SIMDPP_USE_SSE2
    uint32x4 u1 = move_l<2>(a[0]);
    return int64x4(to_int64x2(a[0]), u1);
#elif SIMDPP_USE_NEON
    uint64x4 r;
    r[0] = vmovl_u32(vget_low_u32(a[0]));
    r[1] = vmovl_u32(vget_high_u32(a[0]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    return { zip_lo(uint32x4::zero(), a[0]), zip_hi(uint32x4::zero(), a[1]) };
#endif
}
/// @}

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

/// @{
/** Converts the 32-bit integer values to 64-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is rounded to the
    nearest representable value.

    @par 128-bit version:
    @code
    r0 = (double) a0
    r1 = (double) a1
    @endcode

    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @code
    r0 = (double) a0
    ...
    r3 = (double) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 to_float64x2(int32x4 a)
{
#if SIMDPP_USE_NULL
    float64x2 r;
    r[0] = double(a[0]);
    r[1] = double(a[1]);
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_cvtepi32_pd(a);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> ax(a);
    float64x2 r;
    r[0] = double(ax[0]);
    r[1] = double(ax[1]);
    return r;
#endif
}

inline float64x4 to_float64x4(int32x8 a)
{
#if SIMDPP_USE_NULL
    float64x4 r;
    r[0][0] = double(a[0][0]);
    r[0][1] = double(a[0][1]);
    r[1][0] = double(a[0][2]);
    r[1][1] = double(a[0][3]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_cvtepi32_pd(sse::extract_lo(a));
#elif SIMDPP_USE_SSE2
    return float64x4(to_float64x2(a[0]), to_float64x2(move_l<2>(a[0])));
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    float64x4 r;
    detail::mem_block<int32x8> ax(a);
    r[0][0] = double(ax[0]);
    r[0][1] = double(ax[1]);
    r[1][0] = double(ax[2]);
    r[1][1] = double(ax[3]);
    return r;
#endif
}
/// @}

/// @{
/** Converts the 32-bit float values to 64-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is rounded to the
    nearest representable value.

    @par 128-bit version:
    @code
    r0 = (double) a0
    r1 = (double) a1
    @endcode

    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @code
    r0 = (double) a0
    ...
    r3 = (double) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 to_float64x2(float32x4 a)
{
#if SIMDPP_USE_NULL
    float64x2 r;
    r[0] = double(a[0]);
    r[1] = double(a[1]);
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_cvtps_pd(a);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> ax(a);
    float64x2 r;
    r[0] = double(ax[0]);
    r[1] = double(ax[1]);
    return r;
#endif
}

inline float64x4 to_float64x4(float32x8 a)
{
#if SIMDPP_USE_NULL
    float64x4 r;
    r[0][0] = double(a[0][0]);
    r[0][1] = double(a[0][1]);
    r[1][0] = double(a[0][2]);
    r[1][1] = double(a[0][3]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_cvtps_pd(sse::extract_lo(a));
#elif SIMDPP_USE_SSE2
    return float64x4(to_float64x2(a[0]), to_float64x2(move_l<2>(a[0])));
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x8> ax(a);
    float64x4 r;
    r[0][0] = double(ax[0]);
    r[0][1] = double(ax[1]);
    r[1][0] = double(ax[2]);
    r[1][1] = double(ax[3]);
    return r;
#endif
}
/// @}

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
