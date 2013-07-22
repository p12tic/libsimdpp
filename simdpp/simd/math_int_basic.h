/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_MATH_INT_BASIC_H
#define LIBSIMDPP_SIMD_MATH_INT_BASIC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/transpose.h>

#if SIMDPP_USE_NULL
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** @defgroup simd_math_int
    @{
*/

/// @{
/** Adds 8-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int8x16 add(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u8(a, b);
#endif
}

inline basic_int8x32 add(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi8(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds 16-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int16x8 add(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u16(a, b);
#endif
}

inline basic_int16x16 add(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi16(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds 32-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 add(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u32(a, b);
#endif
}

inline basic_int32x8 add(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi32(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds 64-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int128 add(basic_int64x2 a, basic_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi64(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u64(a, b);
#endif
}

inline basic_int64x4 add(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi64(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates signed 8-bit integer values.

    @code
    r0 = signed_saturate(a0 + b0)
    ...
    rN = signed_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int8x16 adds(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_s8(a, b);
#endif
}

inline int8x32 adds(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epi8(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates signed 16-bit integer values.

    @code
    r0 = signed_saturate(a0 + b0)
    ...
    rN = signed_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int16x8 adds(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_s16(a, b);
#endif
}

inline int16x16 adds(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epi16(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates unsigned 8-bit integer values.

    @code
    r0 = unsigned_saturate(a0 + b0)
    ...
    rN = unsigned_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline uint8x16 adds(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_u8(a, b);
#endif
}

inline uint8x32 adds(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epu8(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates unsigned 16-bit integer values.

    @code
    r0 = unsigned_saturate(a0 + b0)
    ...
    rN = unsigned_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline uint16x8 adds(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_u16(a, b);
#endif
}

inline uint16x16 adds(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epi8(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts 8-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int8x16 sub(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u8(a, b);
#endif
}

inline basic_int8x32 sub(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_sub_epi8(a, b);
#else
    return {sub(a[0], b[0]), sub(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts 16-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int16x8 sub(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u16(a, b);
#endif
}

inline basic_int16x16 sub(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_sub_epi16(a, b);
#else
    return {sub(a[0], b[0]), sub(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts 32-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int32x4 sub(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u32(a, b);
#endif
}

inline basic_int32x8 sub(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_sub_epi32(a, b);
#else
    return {sub(a[0], b[0]), sub(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts 64-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int64x2 sub(basic_int64x2 a, basic_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi64(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u64(a, b);
#endif
}

inline basic_int64x4 sub(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_sub_epi64(a, b);
#else
    return {sub(a[0], b[0]), sub(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts and saturaters signed 8-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int8x16 subs(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_s8(a, b);
#endif
}

inline int8x32 subs(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_subs_epi8(a, b);
#else
    return {subs(a[0], b[0]), subs(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts and saturaters signed 16-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int16x8 subs(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_s16(a, b);
#endif
}

inline int16x16 subs(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_subs_epi16(a, b);
#else
    return {subs(a[0], b[0]), subs(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts and saturaters unsigned 8-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline uint8x16 subs(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_u8(a, b);
#endif
}

inline uint8x32 subs(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_subs_epu8(a, b);
#else
    return {subs(a[0], b[0]), subs(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts and saturaters unsigned 16-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline uint16x8 subs(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_u16(a, b);
#endif
}

inline uint16x16 subs(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_subs_epu16(a, b);
#else
    return {subs(a[0], b[0]), subs(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Negates signed 8-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int8x16 neg(int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    return sub(int8x16::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s8(a);
#endif
}

inline int8x32 neg(int8x32 a)
{
#if SIMDPP_USE_AVX2
    return sub(int8x32::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates signed 16-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int16x8 neg(int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    return sub(int16x8::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s16(a);
#endif
}

inline int16x16 neg(int16x16 a)
{
#if SIMDPP_USE_AVX2
    return sub(int16x16::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates signed 32-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int32x4 neg(int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    return sub(int32x4::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s32(a);
#endif
}

inline int32x8 neg(int32x8 a)
{
#if SIMDPP_USE_AVX2
    return sub(int32x8::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates signed 64-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2}
*/
inline int64x2 neg(int64x2 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    return sub(int64x2::zero(), a);
#endif
}

inline int64x4 neg(int64x4 a)
{
#if SIMDPP_USE_AVX2
    return sub(int64x4::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

// no 8 bit multiplications in SSE
/// @{
/** Multiplies 16-bit values and returns the lower part of the multiplication

    @code
    r0 = low(a0 * b0)
    ...
    rN = low(aN * bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline basic_int16x8 mul_lo(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mullo_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vmulq_s16(a, b);
#endif
}

inline basic_int16x16 mul_lo(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mullo_epi16(a, b);
#else
    return {mul_lo(a[0], b[0]), mul_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 16-bit values and returns the higher half of the result.

    @code
    r0 = high(a0 * b0)
    ...
    rN = high(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{NEON, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 6}
*/
inline int16x8 mul_hi(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){ return (int32_t(a) * b) >> 16; });
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epi16(a, b);
#elif SIMDPP_USE_NEON
    int16x8 lo = int128(vmull_s16(vget_low_s16(a), vget_low_s16(b)));
    int16x8 hi = int128(vmull_s16(vget_high_s16(a), vget_high_s16(b)));
    return unzip_hi(lo, hi);
#endif
}

inline int16x16 mul_hi(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mulhi_epi16(a, b);
#else
    return {mul_hi(a[0], b[0]), mul_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 16-bit values and returns the higher half of the result.

    @code
    r0 = high(a0 * b0)
    ...
    rN = high(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{NEON, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 6}
*/
inline uint16x8 mul_hi(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){ return (int64_t(a) * b) >> 16; });
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epu16(a, b);
#elif SIMDPP_USE_NEON
    uint16x8 lo = int128(vmull_u16(vget_low_u16(a), vget_low_u16(b)));
    uint16x8 hi = int128(vmull_u16(vget_high_u16(a), vget_high_u16(b)));
    return unzip_hi(lo, hi);
#endif
}

inline uint16x16 mul_hi(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mulhi_epu16(a, b);
#else
    return {mul_hi(a[0], b[0]), mul_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies 32-bit values and returns the lower half of the result.

    @code
    r0 = low(a0 * b0)
    ...
    rN = low(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 3}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 6}
    @icost{SSE4.1-AVX, NEON 2}
*/
inline int128 mul_lo(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::mul(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_mullo_epi32(a, b);
#elif SIMDPP_USE_SSE2
    basic_int32x4 a1, b1;
    a1 = move_l<1>(a);
    b1 = move_l<1>(b);
    a = _mm_mul_epu32(a, b);
    a1 = _mm_mul_epu32(a1, b1);
    a = shuffle2<0,2,0,2>(a, a1); // additional latency unavoidable
    a = permute<0,2,1,3>(a);
    return a;
#elif SIMDPP_USE_NEON
    return vmulq_s32(a, b);
#endif
}

inline basic_int32x8 mul_lo(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mulhi_epu16(a, b);
#else
    return {mul_lo(a[0], b[0]), mul_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 16-bit values in the lower halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    ...
    r3 = a3 * b3
    @endcode

    @icost{SSE2-AVX, 2}

    @par 256-bit version:

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 4}
    @icost{AVX2, NEON, 2}
    @note Use with mull_hi on the same arguments to save instructions.
*/
inline int32x4 mull_lo(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = int32_t(a[i]) * b[i];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epi16(a, b);
    return zip_lo(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_s16(vget_low_s16(a), vget_low_s16(b));
#endif
}

inline int32x8 mull_lo(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    int16x16 lo = _mm256_mullo_epi16(a, b);
    int16x16 hi = _mm256_mulhi_epi16(a, b);
    return zip_lo(lo, hi);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 16-bit values in the lower halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    ...
    r3 = a3 * b3
    @endcode

    @icost{SSE2-AVX, 2}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 4}
    @icost{AVX2, NEON, 2}
    @note Use with mull_hi on the same arguments to save instructions.
*/
inline uint32x4 mull_lo(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    uint32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = uint32_t(a[i]) * b[i];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epu16(a, b);
    return zip_lo(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_u16(vget_low_u16(a), vget_low_u16(b));
#endif
}

inline uint32x8 mull_lo(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 lo = _mm256_mullo_epi16(a, b);
    uint16x16 hi = _mm256_mulhi_epu16(a, b);
    return zip_lo(lo, hi);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 16-bit values in the higher halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a4 * b4
    ...
    r3 = a7 * b7
    @endcode

    @icost{SSE2-AVX, 2}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 4}
    @icost{AVX2, NEON, 2}
    @note Use with mull_lo on the same arguments to save instructions.
*/
inline int32x4 mull_hi(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = int32_t(a[i+4]) * b[i+4];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epi16(a, b);
    return zip_hi(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_s16(vget_high_s16(a), vget_high_s16(b));
#endif
}

inline int32x8 mull_hi(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    int16x16 lo = _mm256_mullo_epi16(a, b);
    int16x16 hi = _mm256_mulhi_epi16(a, b);
    return zip_hi(lo, hi);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 16-bit values in the higher halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a4 * b4
    ...
    r3 = a7 * b7
    @endcode

    @icost{SSE2-AVX, 2}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 4}
    @icost{AVX2, NEON, 2}
    @note Use with mull_lo on the same arguments to save instructions.
*/
inline uint32x4 mull_hi(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    uint32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = uint32_t(a[i+4]) * b[i+4];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epu16(a, b);
    return zip_hi(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_u16(vget_high_u16(a), vget_high_u16(b));
#endif
}

inline uint32x8 mull_hi(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 lo = _mm256_mullo_epi16(a, b);
    uint16x16 hi = _mm256_mulhi_epu16(a, b);
    return zip_hi(lo, hi);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 32-bit values in the lower halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    r1 = a1 * b1
    @endcode
    @icost{SSE4.1-AVX, 3}
    @unimp{SSE2-SSSE3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE4.1-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
    @unimp{SSE2-SSSE3}
*/
inline int64x2 mull_lo(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    int64x2 r;
    r[0] = int64_t(a[2]) * b[2];
    r[1] = int64_t(a[3]) * b[3];
    return r;
#elif SIMDPP_USE_SSE4_1
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm_mul_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_s32(vget_low_s32(a), vget_low_s32(b));
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline int64x4 mull_lo(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm256_mul_epi32(a, b);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 32-bit values in the lower halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    r1 = a1 * b1
    @endcode
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
*/
inline uint64x2 mull_lo(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    uint64x2 r;
    r[0] = uint64_t(a[0]) * b[0];
    r[1] = uint64_t(a[1]) * b[1];
    return r;
#elif SIMDPP_USE_SSE2
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm_mul_epu32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_u32(vget_low_u32(a), vget_low_u32(b));
#endif
}

inline uint64x4 mull_lo(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm256_mul_epu32(a, b);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 32-bit values in the higher halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    r1 = a1 * b1
    @endcode
    @icost{SSE4.1-AVX, 3}
    @unimp{SSE2-SSSE3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE4.1-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
    @unimp{SSE2-SSSE3}
*/
inline int64x2 mull_hi(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    int64x2 r;
    r[0] = int64_t(a[2]) * b[2];
    r[1] = int64_t(a[3]) * b[3];
    return r;
#elif SIMDPP_USE_SSE4_1
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm_mul_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_s32(vget_high_s32(a), vget_high_s32(b));
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline int64x4 mull_hi(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm256_mul_epi32(a, b);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 32-bit values in the higher halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    r1 = a1 * b1
    @endcode
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
*/
inline uint64x2 mull_hi(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    uint64x2 r;
    r[0] = uint64_t(a[2]) * b[2];
    r[1] = uint64_t(a[3]) * b[3];
    return r;
#elif SIMDPP_USE_SSE2
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm_mul_epu32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_u32(vget_high_u32(a), vget_high_u32(b));
#endif
}

inline uint64x4 mull_hi(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm256_mul_epu32(a, b);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
