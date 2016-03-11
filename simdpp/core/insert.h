/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INSERT_H
#define LIBSIMDPP_SIMD_INSERT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/shuffle1.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/detail/altivec/load1.h>
#include <simdpp/detail/null/set.h>
#include <simdpp/detail/insn/combine.h>
#include <simdpp/detail/mem_block.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @defgroup simd_insert_extract Operations: insert or extract a single element from a vector
/// @{

/// @{
/** Inserts an element into int8x16 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    ...
    r15 = (id == 15) ? x : a15
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 4-5}
    @icost{ALTIVEC, 3}
*/
template<unsigned id> SIMDPP_INL
uint8x16 insert(const uint8x16& ca, uint8_t x)
{
    uint8<16> a = ca;
    SIMDPP_STATIC_ASSERT(id < 16, "Position out of range");
#if SIMDPP_USE_NULL
    a.el(id) = x;
    return a;
#elif SIMDPP_USE_SSE4_1
    return _mm_insert_epi8(a.operator __m128i(), x, id);
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
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint8x16> ax(a);
    ax[id] = x;
    a = ax;
    return a;
#endif
}

/** Inserts an element into int16x8 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    ...
    r7 = (id == 7) ? x : a7
    @endcode

    This function may have very high latency.

    @icost{ALTIVEC, 3}
*/
template<unsigned id> SIMDPP_INL
uint16x8 insert(const uint16x8& ca, uint16_t x)
{
    uint16<8> a = ca;
#if SIMDPP_USE_NULL
    a.el(id) = x;
    return a;
#elif SIMDPP_USE_SSE2
    return _mm_insert_epi16(a, x, id);
#elif SIMDPP_USE_NEON
    return vsetq_lane_u16(x, a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint16x8> ax(a);
    ax[id] = x;
    a = ax;
    return a;
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
    @icost{ALTIVEC, 3}
*/
template<unsigned id> SIMDPP_INL
uint32x4 insert(const uint32x4& ca, uint32_t x)
{
    uint32<4> a = ca;
#if SIMDPP_USE_NULL
    a.el(id) = x;
    return a;
#elif SIMDPP_USE_SSE4_1
    return _mm_insert_epi32(a.operator __m128i(), x, id);
#elif SIMDPP_USE_SSE2
    uint16_t lo = x & 0xffff;
    uint16_t hi = x >> 16;
    uint16x8 a1 = uint16<8>(a);
    a1 = insert<id*2>(a1, lo);
    a1 = insert<id*2+1>(a1, hi);
    return uint32<4>(a1);
#elif SIMDPP_USE_NEON
    return vsetq_lane_u32(x, a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint32x4> ax(a);
    ax[id] = x;
    a = ax;
    return a;
#endif
}

/** Inserts an element into int64x2 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 2}
    @icost{SSE4_1, 1}
    @icost{SSE2_32bit, SSE3_32bit, SSSE3_32bit, 4}
    @icost{SSE4_1_32bit, 2}
    @icost{ALTIVEC, 3}
*/
template<unsigned id> SIMDPP_INL
uint64x2 insert(const uint64x2& ca, uint64_t x)
{
    uint64<2> a = ca;
#if SIMDPP_USE_NULL
    a.el(id) = x;
    return a;
#elif SIMDPP_USE_SSE4_1
#if SIMDPP_32_BITS
    uint32x4 a0 = (uint32x4) a;
    a0 = insert<id*2>(a0, uint32_t(x));
    a0 = insert<id*2+1>(a0, uint32_t(x >> 32));
    return (uint64x2) a0;
#else
    return _mm_insert_epi64(a.operator __m128i(), x, id);
#endif
#elif SIMDPP_USE_SSE2
#if SIMDPP_32_BITS
    int32x4 va = _mm_cvtsi32_si128(uint32_t(x));
    int32x4 vb = _mm_cvtsi32_si128(uint32_t(x >> 32));
    int64x2 vx = (int64x2) zip4_lo(va, vb);
    if (id == 0) {
        a = shuffle1<0,1>(vx, a);
    } else {
        a = shuffle1<0,0>(a, vx);
    }
    return a;
#else
    int64x2 vx = _mm_cvtsi64_si128(x);
    if (id == 0) {
        a = shuffle1<0,1>(vx, a);
    } else {
        a = shuffle1<0,0>(a, vx);
    }
    return a;
#endif
#elif SIMDPP_USE_NEON
    return vsetq_lane_u64(x, a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint64x2> ax(a);
    ax[id] = x;
    a = ax;
    return a;
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
    @icost{ALTIVEC, 3}
*/
template<unsigned id> SIMDPP_INL
float32x4 insert(const float32x4& a, float x)
{
#if SIMDPP_USE_NEON_FLT_SP
    return vsetq_lane_f32(x, a, id);
#else
    return float32x4(insert<id>(int32x4(a), bit_cast<uint32_t>(x)));
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
    @icost{ALTIVEC, 3}
*/
template<unsigned id> SIMDPP_INL
float64x2 insert(const float64x2& a, double x)
{
    return float64x2(insert<id>(int64x2(a), bit_cast<int64_t>(x)));
}

/// @} -- end defgroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

/// @}
