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

#if SIMDPP_USE_NULL
    #include <simdpp/null/compare.h>
#elif SIMDPP_USE_NEON
    #include <simdpp/neon/detail/vfp_float64x2.h>
#endif

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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int8x16 cmp_eq(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s8(a, b);
#endif
}

inline basic_int8x32 cmp_eq(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi8(a, b);
#else
    return basic_int8x32(cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int16x8 cmp_eq(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s16(a, b);
#endif
}

inline basic_int16x16 cmp_eq(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi16(a, b);
#else
    return basic_int16x16(cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 cmp_eq(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpeq_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vceqq_s32(a, b);
#endif
}

inline basic_int32x8 cmp_eq(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpeq_epi32(a, b);
#else
    return basic_int32x8(cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1]));
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
    @icost{SSE2-SSE4.1, NEON, 2}
*/
inline basic_int32x4 cmp_eq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_AVX
    return int32x4(_mm_cmp_ps(a, b, _CMP_EQ_OQ));
#elif SIMDPP_USE_SSE2
    return int32x4(_mm_cmpeq_ps(a, b));
#elif SIMDPP_USE_NEON
    return vceqq_f32(a, b);
#endif
}

inline basic_int32x8 cmp_eq(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return int32x8(_mm256_cmp_ps(a, b, _CMP_EQ_OQ));
#else
    return basic_int32x8(cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1]));
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline basic_int64x2 cmp_eq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_eq(a, b);
#elif SIMDPP_USE_AVX
    return int64x2(_mm_cmp_pd(a, b, _CMP_EQ_OQ));
#elif SIMDPP_USE_SSE2
    return int64x2(_mm_cmpeq_pd(a, b));
#elif SIMDPP_USE_NEON
    return neon::detail::cmp_eq(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline basic_int64x4 cmp_eq(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return int64x4(_mm256_cmp_pd(a, b, _CMP_EQ_OQ));
#else
    return basic_int64x4(cmp_eq(a[0], b[0]), cmp_eq(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, 4}
    @icost{AVX2, 2}
*/
inline basic_int8x16 cmp_neq(basic_int8x16 a, basic_int8x16 b)
{
    int128 r;
    r = cmp_eq(a, b);
    r = bit_not(r);
    return r;
}

inline basic_int8x32 cmp_neq(basic_int8x32 a, basic_int8x32 b)
{
    int256 r;
    r = cmp_eq(a, b);
    r = bit_not(r);
    return r;
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
    @icost{SSE2-AVX, NEON, 2}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, 4}
    @icost{AVX2, 2}
*/
inline basic_int16x8 cmp_neq(basic_int16x8 a, basic_int16x8 b)
{
    int128 r;
    r = cmp_eq(a, b);
    r = bit_not(r);
    return r;
}

inline basic_int16x16 cmp_neq(basic_int16x16 a, basic_int16x16 b)
{
    int256 r;
    r = cmp_eq(a, b);
    r = bit_not(r);
    return r;
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
    @icost{SSE2-AVX, NEON, 2}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, 4}
    @icost{AVX2, 2}
*/
inline basic_int32x4 cmp_neq(basic_int32x4 a, basic_int32x4 b)
{
    int128 r;
    r = cmp_eq(a, b);
    r = bit_not(r);
    return r;
}

inline basic_int32x8 cmp_neq(basic_int32x8 a, basic_int32x8 b)
{
    int256 r;
    r = cmp_eq(a, b);
    r = bit_not(r);
    return r;
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
    @icost{NEON, 2}

    @par 256-bit version
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 4}
*/
inline basic_int32x4 cmp_neq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return int32x4(_mm_cmp_ps(a, b, _CMP_NEQ_UQ));
#elif SIMDPP_USE_SSE2
    return int32x4(_mm_cmpneq_ps(a, b));
#elif SIMDPP_USE_NEON
    return bit_not(vceqq_f32(a, b));
#endif
}

inline basic_int32x8 cmp_neq(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return int32x8(_mm256_cmp_ps(a, b, _CMP_NEQ_UQ));
#else
    return basic_int32x8(cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]));
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline basic_int64x2 cmp_neq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return int64x2(_mm_cmp_pd(a, b, _CMP_NEQ_UQ));
#elif SIMDPP_USE_SSE2
    return int64x2(_mm_cmpneq_pd(a, b));
#elif SIMDPP_USE_NEON
    return neon::detail::cmp_neq(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline basic_int64x4 cmp_neq(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return int64x4(_mm256_cmp_pd(a, b, _CMP_NEQ_UQ));
#else
    return basic_int64x4(cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int8x16 cmp_gt(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s8(a, b);
#endif
}

inline basic_int8x32 cmp_gt(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi8(a, b);
#else
    return basic_int8x32(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-AVX, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{NEON, 2}
*/
inline basic_int8x16 cmp_gt(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    uint8x16 bias = uint8x16::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u8(a, b);
#endif
}

inline basic_int8x32 cmp_gt(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 bias = uint8x32::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi8(a, b);
#else
    return basic_int8x32(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int16x8 cmp_gt(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s16(a, b);
#endif
}

inline basic_int16x16 cmp_gt(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi16(a, b);
#else
    return basic_int16x16(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-AVX, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{NEON, 2}
*/
inline basic_int16x8 cmp_gt(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 bias = uint16x8::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u16(a, b);
#endif
}

inline basic_int16x16 cmp_gt(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 bias = uint16x16::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi16(a, b);
#else
    return basic_int16x16(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 cmp_gt(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s32(a, b);
#endif
}

inline basic_int32x8 cmp_gt(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    return int32x8(_mm256_cmpgt_epi32(a, b));
#else
    return basic_int32x8(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-AVX, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{NEON, 2}
*/
inline basic_int32x4 cmp_gt(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    int32x4 bias = int32x4::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u32(a, b);
#endif
}

inline basic_int32x8 cmp_gt(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 bias = uint32x8::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi32(a, b);
#else
    return basic_int32x8(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-SSE4.1, NEON, 2}
*/
inline basic_int32x4 cmp_gt(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_AVX
    return int32x4(_mm_cmp_ps(a, b, _CMP_GT_OQ));
#elif SIMDPP_USE_SSE2
    return int32x4(_mm_cmpgt_ps(a, b));
#elif SIMDPP_USE_NEON
    return vcgtq_f32(a, b);
#endif
}

inline basic_int32x8 cmp_gt(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return int32x8(_mm256_cmp_ps(a, b, _CMP_GT_OQ));
#else
    return basic_int32x8(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline basic_int64x2 cmp_gt(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_AVX
    return int64x2(_mm_cmp_pd(a, b, _CMP_GT_OQ));
#elif SIMDPP_USE_SSE2
    return int64x2(_mm_cmpgt_pd(a, b));
#elif SIMDPP_USE_NEON
    return neon::detail::cmp_gt(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline basic_int64x4 cmp_gt(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return int64x4(_mm256_cmp_pd(a, b, _CMP_GT_OQ));
#else
    return basic_int64x4(cmp_gt(a[0], b[0]), cmp_gt(a[1], b[1]));
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
    @icost{SSE2-SSE4.1, NEON, 2}
*/
inline basic_int32x4 cmp_ge(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_ge(a, b);
#elif SIMDPP_USE_AVX
    return int32x4(_mm_cmp_ps(a, b, _CMP_GE_OQ));
#elif SIMDPP_USE_SSE2
    return int32x4(_mm_cmpge_ps(a, b));
#elif SIMDPP_USE_NEON
    return vcgeq_f32(a, b);
#endif
}

inline basic_int32x8 cmp_ge(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return int32x8(_mm256_cmp_ps(a, b, _CMP_GE_OQ));
#else
    return basic_int32x8(cmp_ge(a[0], b[0]), cmp_ge(a[1], b[1]));
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline basic_int64x2 cmp_ge(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_ge(a, b);
#elif SIMDPP_USE_AVX
    return int64x2(_mm_cmp_pd(a, b, _CMP_GE_OQ));
#elif SIMDPP_USE_SSE2
    return int64x2(_mm_cmpge_pd(a, b));
#elif SIMDPP_USE_NEON
    return neon::detail::cmp_ge(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline basic_int64x4 cmp_ge(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return int64x4(_mm256_cmp_pd(a, b, _CMP_GE_OQ));
#else
    return basic_int64x4(cmp_ge(a[0], b[0]), cmp_ge(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int8x16 cmp_lt(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s8(a, b);
#endif
}

inline basic_int8x32 cmp_lt(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi8(b, a);
#else
    return basic_int8x32(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{NEON, 2}
*/
inline basic_int8x16 cmp_lt(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    uint8x16 bias = uint8x16::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u8(a, b);
#endif
}

inline basic_int8x32 cmp_lt(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 bias = uint8x32::make_const(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi8(b, a);
#else
    return basic_int8x32(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int16x8 cmp_lt(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s16(a, b);
#endif
}

inline basic_int16x16 cmp_lt(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi16(b, a);
#else
    return basic_int16x16(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{NEON, 2}
*/
inline basic_int16x8 cmp_lt(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 bias = uint16x8::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u16(a, b);
#endif
}

inline basic_int16x16 cmp_lt(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 bias = uint16x16::make_const(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi16(b, a);
#else
    return basic_int16x16(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 cmp_lt(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s32(a, b);
#endif
}

inline basic_int32x8 cmp_lt(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_cmpgt_epi32(b, a);
#else
    return basic_int32x8(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{NEON, 2}
*/
inline basic_int32x4 cmp_lt(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    uint32x4 bias = uint32x4::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u32(a, b);
#endif
}

inline basic_int32x8 cmp_lt(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 bias = uint32x8::make_const(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi32(b, a);
#else
    return basic_int32x8(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 cmp_lt(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_AVX
    return int32x4(_mm_cmp_ps(a, b, _CMP_LT_OQ));
#elif SIMDPP_USE_SSE2
    return int32x4(_mm_cmplt_ps(a, b));
#elif SIMDPP_USE_NEON
    return vcltq_f32(a, b);
#endif
}

inline basic_int32x8 cmp_lt(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return int32x8(_mm256_cmp_ps(a, b, _CMP_LT_OQ));
#else
    return basic_int32x8(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline basic_int64x2 cmp_lt(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_lt(a, b);
#elif SIMDPP_USE_AVX
    return int64x2(_mm_cmp_pd(a, b, _CMP_LT_OQ));
#elif SIMDPP_USE_SSE2
    return int64x2(_mm_cmplt_pd(a, b));
#elif SIMDPP_USE_NEON
    return neon::detail::cmp_lt(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline basic_int64x4 cmp_lt(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return int64x4(_mm256_cmp_pd(a, b, _CMP_LT_OQ));
#else
    return basic_int64x4(cmp_lt(a[0], b[0]), cmp_lt(a[1], b[1]));
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
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 cmp_le(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_le(a, b);
#elif SIMDPP_USE_AVX
    return int32x4(_mm_cmp_ps(a, b, _CMP_LE_OQ));
#elif SIMDPP_USE_SSE2
    return int32x4(_mm_cmple_ps(a, b));
#elif SIMDPP_USE_NEON
    return vcleq_f32(a, b);
#endif
}

inline basic_int32x8 cmp_le(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return int32x8(_mm256_cmp_ps(a, b, _CMP_LE_OQ));
#else
    return basic_int32x8(cmp_le(a[0], b[0]), cmp_le(a[1], b[1]));
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline basic_int64x2 cmp_le(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_le(a, b);
#elif SIMDPP_USE_AVX
    return int64x2(_mm_cmp_pd(a, b, _CMP_LE_OQ));
#elif SIMDPP_USE_SSE2
    return int64x2(_mm_cmple_pd(a, b));
#elif SIMDPP_USE_NEON
    return neon::detail::cmp_le(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline basic_int64x4 cmp_le(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return int64x4(_mm256_cmp_pd(a, b, _CMP_LE_OQ));
#else
    return basic_int64x4(cmp_le(a[0], b[0]), cmp_le(a[1], b[1]));
#endif
}
/// @}

/// @} -- end compare

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
