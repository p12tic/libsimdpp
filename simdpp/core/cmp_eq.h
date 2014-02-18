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

#ifndef LIBSIMDPP_SIMDPP_CORE_CMP_EQ_H
#define LIBSIMDPP_SIMDPP_CORE_CMP_EQ_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_shift_l.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/compare.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


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
inline mask_int8x16 cmp_eq(gint8x16 a, gint8x16 b)
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

inline mask_int8x32 cmp_eq(gint8x32 a, gint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi8(a, b);
#else
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8x32, cmp_eq, a, b);
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
inline mask_int16x8 cmp_eq(gint16x8 a, gint16x8 b)
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

inline mask_int16x16 cmp_eq(gint16x16 a, gint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi16(a, b);
#else
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16x16, cmp_eq, a, b);
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
inline mask_int32x4 cmp_eq(gint32x4 a, gint32x4 b)
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

inline mask_int32x8 cmp_eq(gint32x8 a, gint32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi32(a, b);
#else
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32x8, cmp_eq, a, b);
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
inline mask_int64x2 cmp_eq(gint64x2 a, gint64x2 b)
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

inline mask_int64x4 cmp_eq(gint64x4 a, gint64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi64(a, b);
#else
    SIMDPP_VEC_ARRAY_IMPL2(mask_int64x4, cmp_eq, a, b);
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
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32x8, cmp_eq, a, b);
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
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64x4, cmp_eq, a, b);
#endif
}
/// @}
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

