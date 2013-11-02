/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_COMPARE_H
#define LIBSIMDPP_SIMD_COMPARE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/bitwise.h>
#include <simdpp/simd/math_int_basic.h>
#include <simdpp/simd/make_shuffle_bytes_mask.h>

#include <simdpp/null/compare.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// note 64-bit integer compare operations are not available neither on NEON nor
// on SSE

/// @defgroup simd_compare Operations: compare
/// @{

/// @{
/** Compares 8-bit values for equality.

    @code
    r0 = (a0 == b0) ? 0xff : 0x0
    ...
    rN = (aN == bN) ? 0xff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int8x16 cmp_eq(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline mask_int8x32 cmp_eq(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi8(a, b);
#else
    return {cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares 16-bit values for equality.

    @code
    r0 = (a0 == b0) ? 0xffff : 0x0
    ...
    rN = (aN == bN) ? 0xffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int16x8 cmp_eq(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline mask_int16x16 cmp_eq(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi16(a, b);
#else
    return {cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two int32x4 vectors for equality

    @code
    r0 = (a0 == b0) ? 0xffffffff : 0x0
    ...
    rN = (aN == bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int32x4 cmp_eq(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline mask_int32x8 cmp_eq(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi32(a, b);
#else
    return {cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two int64x2 vectors for equality

    @code
    r0 = (a0 == b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN == bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 5}
    @icost{XOP, 1}
    @icost{NEON, 3}
    @icost{ALTIVEC, 3-4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, AVX, 10}
    @icost{XOP, SSE4.1, 2}
    @icost{NEON, 6}
    @icost{ALTIVEC, 6-7}
*/
inline mask_int64x2 cmp_eq(basic_int64x2 a, basic_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comeq_epi64(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_cmpeq_epi64(a, b);
#elif SIMDPP_USE_SSE2
    uint64x2 r32, r32s;
    r32 = cmp_eq(uint32x4(a), uint32x4(b));
    // swap the 32-bit halves
    r32s = bit_or(shift_l<32>(r32), shift_r<32>(r32));
    // combine the results. Each 32-bit half is ANDed with the neighbouring pair
    r32 = bit_and(r32, r32s);
    return r32;
#elif SIMDPP_USE_NEON
    uint32x4 r32, r32s;
    r32 = cmp_eq(uint32x4(a), uint32x4(b));
    r32s = r32;
    // swap the 32-bit halves
    transpose2(r32, r32s);
    // combine the results. Each 32-bit half is ANDed with the neighbouring pair
    r32 = bit_and(r32, r32s);
    return uint64x2(r32);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 mask = make_shuffle_bytes16_mask<0, 2, 1, 3>(mask);
    uint32x4 a0, b0, r;
    a0 = a;  b0 = b;
    r = cmp_eq(a, b);
    r = permute_bytes16(uint16x8(a), mask);
    r = cmp_eq(r, uint32x4::zero();
    return r;
#endif
}

inline mask_int64x4 cmp_eq(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi64(a, b);
#else
    return {cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for equality

    @code
    r0 = (a0 == b0) ? 0xffffffff : 0x0
    ...
    rN = (aN == bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline mask_float32x4 cmp_eq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_EQ_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_ps(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpeq((__vector float)a, (__vector float)b);
#endif
}

inline mask_float32x8 cmp_eq(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_EQ_OQ);
#else
    return {cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float64x2 vectors for equality

    @code
    r0 = (a0 == b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN == bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_eq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_EQ_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline mask_float64x4 cmp_eq(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_EQ_OQ);
#else
    return {cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two int8x16 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xff : 0x0
    ...
    rN = (aN != bN) ? 0xff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
inline mask_int8x16 cmp_neq(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi8(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_int8x32 cmp_neq(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return { cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]) };
#endif
}
/// @}

/// @{
/** Compares the values of two int16x8 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffff : 0x0
    ...
    rN = (aN != bN) ? 0xffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
inline mask_int16x8 cmp_neq(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi16(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_int16x16 cmp_neq(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return { cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]) };
#endif
}
/// @}

/// @{
/** Compares the values of two int32x4 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
inline mask_int32x4 cmp_neq(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi32(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_int32x8 cmp_neq(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return { cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]) };
#endif
}
/// @}

/// @{
/** Compares the values of two int64x2 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1, AVX, 2}
    @icost{XOP, 1}
    @icost{NEON, 4}
    @icost{ALTIVEC, 3-5}

    @par 256-bit version:
    @icost{SSE2-SSSE3, AVX, 10}
    @icost{SSE4.1, NEON, 4}
    @icost{AVX2, XOP, 2}
    @icost{NEON, 8}
    @icost{ALTIVEC, 6-8}
*/
inline mask_int64x2 cmp_neq(basic_int64x2 a, basic_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi64(a, b);
#elif SIMDPP_USE_SSE4_1 || SIMDPP_USE_NEON
    return bit_not(cmp_eq(a, b));
#elif SIMDPP_USE_SSE2
    uint64x2 r32, r32s;
    r32 = cmp_eq(uint32x4(a), uint32x4(b));
    // swap the 32-bit halves
    r32s = bit_or(shift_l<32>(r32), shift_r<32>(r32));
    // combine the results. Each 32-bit half is ORed with the neighbouring pair
    r32 = bit_or(r32, r32s);
    return r32;
#elif SIMDPP_USE_ALTIVEC
    uint16x8 mask = make_shuffle_bytes16_mask<0, 2, 1, 3>(mask);
    uint32x4 a0, b0, r, ones;
    ones = int128::ones();

    a0 = a;  b0 = b;
    r = cmp_eq(a, b);
    r = permute_bytes16(uint16x8(a), mask);
    r = cmp_eq(r, ones);
    return r;
#endif
}

inline mask_int64x4 cmp_neq(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return {cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 2}

    @par 256-bit version
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, ALTIVEC, 4}
*/
inline mask_float32x4 cmp_neq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_ps(a, b);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_float32x8 cmp_neq(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_NEQ_UQ);
#else
    return {cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float64x2 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_neq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline mask_float64x4 cmp_neq(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_NEQ_UQ);
#else
    return {cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two signed int16x8 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xff : 0x0
    ...
    rN = (aN > bN) ? 0xff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int8x16 cmp_gt(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector int8_t)a, (__vector int8_t)b);
#endif
}

inline mask_int8x32 cmp_gt(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi8(a, b);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two unsigned int16x8 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xff : 0x0
    ...
    rN = (aN > bN) ? 0xff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6-7}
    @icost{AVX2, 3-4}
    @icost{XOP, 2}
    @icost{NEON, ALTIVEC, 2}
*/
inline mask_int8x16 cmp_gt(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comgt_epu8(a, b);
#elif SIMDPP_USE_SSE2
    uint8x16 bias = uint8x16::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline mask_int8x32 cmp_gt(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 bias = uint8x32::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi8(a, b);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two signed int16x8 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xffff : 0x0
    ...
    rN = (aN > bN) ? 0xffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int16x8 cmp_gt(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector int16_t)a, (__vector int16_t)b);
#endif
}

inline mask_int16x16 cmp_gt(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi16(a, b);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two unsigned int16x8 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xffff : 0x0
    ...
    rN = (aN > bN) ? 0xffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6-7}
    @icost{AVX2, 3-4}
    @icost{XOP, NEON, ALTIVEC, 2}
*/
inline mask_int16x8 cmp_gt(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comgt_epu16(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 bias = uint16x8::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline mask_int16x16 cmp_gt(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 bias = uint16x16::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi16(a, b);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two signed int32x4 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xffffffff : 0x0
    ...
    rN = (aN > bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int32x4 cmp_gt(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector int32_t)a, (__vector int32_t)b);
#endif
}

inline mask_int32x8 cmp_gt(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi32(a, b);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two unsigned int32x4 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xffffffff : 0x0
    ...
    rN = (aN > bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6-7}
    @icost{AVX2, 3-4}
    @icost{XOP, NEON, ALTIVEC, 2}
*/
inline mask_int32x4 cmp_gt(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comgt_epu32(a, b);
#elif SIMDPP_USE_SSE2
    int32x4 bias = int32x4::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline mask_int32x8 cmp_gt(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 bias = uint32x8::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi32(a, b);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xffffffff : 0x0
    ...
    rN = (aN > bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline mask_float32x4 cmp_gt(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_GT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_ps(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector float)a, (__vector float)b);
#endif
}

inline mask_float32x8 cmp_gt(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_GT_OQ);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @}
/** Compares the values of two float64x2 vectors for greater-than

    @code
    r0 = (a0 > b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN > bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_gt(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_GT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline mask_float64x4 cmp_gt(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_GT_OQ);
#else
    return {cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for greater-than or equal

    @code
    r0 = (a0 >= b0) ? 0xffffffff : 0x0
    ...
    rN = (aN >= bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline mask_float32x4 cmp_ge(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_ge(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_GE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpge_ps(a, b);
#elif SIMDPP_USE_NEON
    return vcgeq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpge((__vector float)a, (__vector float)b);
#endif
}

inline mask_float32x8 cmp_ge(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_GE_OQ);
#else
    return {cmp_ge(a[0], b[0]), cmp_ge(a[1], b[1])};
#endif
}
/// @}

/// @}
/** Compares the values of two float64x2 vectors for greater-than

    @code
    r0 = (a0 >= b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN >= bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_ge(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_ge(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_GE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpge_pd(a, b);
#endif
}

inline mask_float64x4 cmp_ge(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_GE_OQ);
#else
    return {cmp_ge(a[0], b[0]), cmp_ge(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two signed int8x16 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xff : 0x0
    ...
    rN = (aN < bN) ? 0xff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int8x16 cmp_lt(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector int8_t)a, (__vector int8_t)b);
#endif
}

inline mask_int8x32 cmp_lt(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi8(b, a);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two unsigned int8x16 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xff : 0x0
    ...
    rN = (aN < bN) ? 0xff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6-7}
    @icost{AVX2, 3-4}
    @icost{XOP, NEON, ALTIVEC, 2}
*/
inline mask_int8x16 cmp_lt(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comlt_epu8(a, b);
#elif SIMDPP_USE_SSE2
    uint8x16 bias = uint8x16::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline mask_int8x32 cmp_lt(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 bias = uint8x32::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi8(b, a);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two signed int16x8 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xffff : 0x0
    ...
    rN = (aN < bN) ? 0xffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int16x8 cmp_lt(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector int16_t)a, (__vector int16_t)b);
#endif
}

inline mask_int16x16 cmp_lt(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi16(b, a);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two unsigned int16x8 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xffff : 0x0
    ...
    rN = (aN < bN) ? 0xffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6-7}
    @icost{AVX2, 3-4}
    @icost{XOP, NEON, ALTIVEC, 2}
*/
inline mask_int16x8 cmp_lt(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comlt_epu16(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 bias = uint16x8::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline mask_int16x16 cmp_lt(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 bias = uint16x16::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi16(b, a);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two signed int32x4 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xffffffff : 0x0
    ...
    rN = (aN < bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_int32x4 cmp_lt(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector int32_t)a, (__vector int32_t)b);
#endif
}

inline mask_int32x8 cmp_lt(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi32(b, a);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two unsigned int32x4 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xffffffff : 0x0
    ...
    rN = (aN < bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6-7}
    @icost{AVX2, 3-4}
    @icost{XOP, NEON, ALTIVEC, 2}
*/
inline mask_int32x4 cmp_lt(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comlt_epu32(a, b);
#elif SIMDPP_USE_SSE2
    uint32x4 bias = uint32x4::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline mask_int32x8 cmp_lt(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 bias = uint32x8::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi32(b, a);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xffffffff : 0x0
    ...
    rN = (aN < bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_float32x4 cmp_lt(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_LT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_ps(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector float)a, (__vector float)b);
#endif
}

inline mask_float32x8 cmp_lt(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_LT_OQ);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float64x2 vectors for less-than

    @code
    r0 = (a0 < b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN < bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_lt(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_LT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_pd(a, b);
#endif
}

inline mask_float64x4 cmp_lt(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_LT_OQ);
#else
    return {cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for less-than or equal

    @code
    r0 = (a0 <= b0) ? 0xffffffff : 0x0
    ...
    rN = (aN <= bN) ? 0xffffffff : 0x0
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline mask_float32x4 cmp_le(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_le(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_LE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmple_ps(a, b);
#elif SIMDPP_USE_NEON
    return vcleq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmple((__vector float)a, (__vector float)b);
#endif
}

inline mask_float32x8 cmp_le(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_LE_OQ);
#else
    return {cmp_le(a[0], b[0]), cmp_le(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float64x2 vectors for less-than or equal

    @code
    r0 = (a0 <= b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN <= bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_le(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_le(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_LE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmple_pd(a, b);
#endif
}

inline mask_float64x4 cmp_le(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_LE_OQ);
#else
    return {cmp_le(a[0], b[0]), cmp_le(a[1], b[1])};
#endif
}
/// @}

/// @} -- end compare

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
