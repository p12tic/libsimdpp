/*  libsimdpp
    Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INSERT_H
#define LIBSIMDPP_SIMD_INSERT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/cast.h>

#if SIMDPP_USE_NULL
    #include <simdpp/null/set.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** Inserts an element into int8x16 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    ...
    r15 = (id == 15) ? x : a15
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 4}
*/
template<unsigned id>
basic_int8x16 insert(basic_int8x16 a, uint8_t x)
{
#if SIMDPP_USE_NULL
    a[id] = x;
    return a;
#elif SIMDPP_USE_SSE4_1
    return _mm_insert_epi8(a, x, id);
#elif SIMDPP_USE_SSE2
    uint16_t r = _mm_extract_epi16(a, id/2);
    if (id % 2 == 1) {
        r = (r & 0x00ff) | (x << 8);
    } else {
        r = (r & 0xff00) | x;
    }
    a = _mm_insert_epi16(a, r, id/2);
    return a;
#elif SIMDPP_USE_NEON
    return vsetq_lane_u8(x, a, id);
#endif
}

/** Inserts an element into int16x8 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    ...
    r7 = (id == 7) ? x : a7
    @endcode

    This function may have very high latency.
*/
template<unsigned id>
basic_int16x8 insert(basic_int16x8 a, uint16_t x)
{
#if SIMDPP_USE_NULL
    a[id] = x;
    return a;
#elif SIMDPP_USE_SSE2
    return _mm_insert_epi16(a, x, id);
#elif SIMDPP_USE_NEON
    return vsetq_lane_u16(x, a, id);
#endif
}

/** Inserts an element into int32x4 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    r2 = (id == 2) ? x : a2
    r3 = (id == 3) ? x : a3
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 4}
*/
template<unsigned id>
int128 insert(basic_int32x4 a, uint32_t x)
{
#if SIMDPP_USE_NULL
    a[id] = x;
    return a;
#elif SIMDPP_USE_SSE4_1
    return _mm_insert_epi32(a, x, id);
#elif SIMDPP_USE_SSE2
    uint16_t lo = x & 0xffff;
    uint16_t hi = x >> 16;
    basic_int16x8 a1 = a;
    a1 = insert<id*2>(a1, lo);
    a1 = insert<id*2+1>(a1, hi);
    return a1;
#elif SIMDPP_USE_NEON
    return vsetq_lane_u32(x, a, id);
#endif
}

/** Inserts an element into int64x2 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 2}
*/
template<unsigned id>
int128 insert(basic_int64x2 a, uint64_t x)
{
#if SIMDPP_USE_NULL
    a[id] = x;
    return a;
#elif SIMDPP_USE_SSE4_1
    return _mm_insert_epi64(a, x, id);
#elif SIMDPP_USE_SSE2
    int64x2 vx = _mm_cvtsi64_si128(x);
    if (id == 0) {
        a = shuffle1<0,1>(vx, a);
    } else {
        a = shuffle1<0,0>(a, vx);
    }
    return a;
#elif SIMDPP_USE_NEON
    return vsetq_lane_u64(x, a, id);
#endif
}

/** Inserts an element into float32x4 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    r2 = (id == 2) ? x : a2
    r3 = (id == 3) ? x : a3
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 4}
*/
template<unsigned id>
float32x4 insert(float32x4 a, float x)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return float32x4(insert<id>(int32x4(a), bit_cast<uint32_t>(x)));
#elif SIMDPP_USE_NEON
    return vsetq_lane_f32(x, a, id);
#endif
}

/** Inserts an element into float64x2 vector at the position identified by @a id.

    This function potentially
    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 2}
*/
template<unsigned id>
float64x2 insert(float64x2 a, double x)
{
    return float64x2(insert<id>(int64x2(a), bit_cast<int64_t>(x)));
}

/// @{
/** Combines two 128-bit vectors into a 256-bit vector

    @code
    r = [ a, b ]
    @endcode
*/
inline int256 combine(int128 a, int128 b)
{
#if SIMDPP_USE_AVX2
    int256 r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
#else
    return {a, b};
#endif
}

inline float32x8 combine(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_AVX
    float32x8 r;
    r = _mm256_castps128_ps256(a);
    r = _mm256_insertf128_ps(r, b, 1);
    return r;
#else
    return {a, b};
#endif
}

inline float64x4 combine(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_AVX
    float64x4 r;
    r = _mm256_castpd128_pd256(a);
    r = _mm256_insertf128_pd(r, b, 1);
    return r;
#else
    return {a, b};
#endif
}

/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif

/// @}
