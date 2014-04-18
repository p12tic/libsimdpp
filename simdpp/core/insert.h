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
#include <simdpp/detail/word_size.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/shuffle1.h>
#include <simdpp/altivec/load1.h>
#include <simdpp/detail/null/set.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

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
template<unsigned id>
uint8x16 insert(uint8x16 a, uint8_t x)
{
    static_assert(id < 16, "Position out of range");
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
template<unsigned id>
uint16x8 insert(uint16x8 a, uint16_t x)
{
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
template<unsigned id>
uint32x4 insert(uint32x4 a, uint32_t x)
{
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
template<unsigned id>
uint64x2 insert(uint64x2 a, uint64_t x)
{
#if SIMDPP_USE_NULL
    a.el(id) = x;
    return a;
#elif SIMDPP_USE_SSE4_1
#if SIMDPP_SSE_32_BITS
    uint32x4 a0 = a;
    a0 = insert<id*2>(a0, uint32_t(x));
    a0 = insert<id*2+1>(a0, uint32_t(x >> 32));
    return a0;
#else
    return _mm_insert_epi64(a.operator __m128i(), x, id);
#endif
#elif SIMDPP_USE_SSE2
#if SIMDPP_SSE_32_BITS
    int32x4 va = _mm_cvtsi32_si128(uint32_t(x));
    int32x4 vb = _mm_cvtsi32_si128(uint32_t(x >> 32));
    int64x2 vx = zip4_lo(va, vb);
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
template<unsigned id>
float32x4 insert(float32x4 a, float x)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
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
    @icost{ALTIVEC, 3}
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

    @icost{AVX2, 1}
    @icost{SSE2-AVX, NEON, ALTIVEC, 0}
*/
template<class E1, class E2>
uint8x32 combine(uint8<16,E1> a, uint8<16,E2> b)
{
#if SIMDPP_USE_AVX2
    uint8x32 r;
    r = _mm256_castsi128_si256(a.eval());
    r = _mm256_inserti128_si256(r, b.eval(), 1);
    return r;
#else
    uint8x32 r;
    r[0] = a.eval();
    r[1] = b.eval();
    return r;
#endif
}


template<class E1, class E2>
uint16x16 combine(uint16<8,E1> a, uint16<8,E2> b)
{
    return uint16x16(combine(uint8x16(a.eval()), uint8x16(b.eval())));
}

template<class E1, class E2>
uint32x8 combine(uint32<4,E1> a, uint32<4,E2> b)
{
    return uint32x8(combine(uint8x16(a.eval()), uint8x16(b.eval())));
}

template<class E1, class E2>
uint64x4 combine(uint64<2,E1> a, uint64<2,E2> b)
{
    return uint64x4(combine(uint8x16(a.eval()), uint8x16(b.eval())));
}

template<class E1, class E2>
int16x16 combine(int16<8,E1> a, int16<8,E2> b)
{
    return int16x16(combine(uint8x16(a.eval()), uint8x16(b.eval())));
}

template<class E1, class E2>
int32x8 combine(int32<4,E1> a, int32<4,E2> b)
{
    return int32x8(combine(uint8x16(a.eval()), uint8x16(b.eval())));
}

template<class E1, class E2>
int64x4 combine(int64<2,E1> a, int64<2,E2> b)
{
    return int64x4(combine(uint8x16(a.eval()), uint8x16(b.eval())));
}

template<class E1, class E2>
float32x8 combine(float32<4,E1> a, float32<4,E2> b)
{
#if SIMDPP_USE_AVX
    float32x8 r;
    r = _mm256_castps128_ps256(a.eval());
    r = _mm256_insertf128_ps(r, b.eval(), 1);
    return r;
#else
    float32x8 r;
    r[0] = a.eval();
    r[1] = b.eval();
    return r;
#endif
}

template<class E1, class E2>
float64x4 combine(float64<2,E1> a, float64<2,E2> b)
{
#if SIMDPP_USE_AVX
    float64x4 r;
    r = _mm256_castpd128_pd256(a.eval());
    r = _mm256_insertf128_pd(r, b.eval(), 1);
    return r;
#else
    float64x4 r;
    r[0] = a.eval();
    r[1] = b.eval();
    return r;
#endif
}

namespace detail {

template<class V, class H>
V v_combine(H a1, H a2)
{
    V r;
    unsigned h = H::vec_length;
    for (unsigned i = 0; i < h; ++i) { r[i] = a1[i]; }
    for (unsigned i = 0; i < h; ++i) { r[i+h] = a2[i]; }
    return r;
}

} // namespace detail

template<unsigned N, class E1, class E2>
uint8<N*2> combine(uint8<N,E1> a1, uint8<N,E2> a2) { return detail::v_combine<uint8<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
uint16<N*2> combine(uint16<N,E1> a1, uint16<N,E2> a2) { return detail::v_combine<uint16<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
uint32<N*2> combine(uint32<N,E1> a1, uint32<N,E2> a2) { return detail::v_combine<uint32<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
uint64<N*2> combine(uint64<N,E1> a1, uint64<N,E2> a2) { return detail::v_combine<uint64<N*2>>(a1.eval(), a2.eval()); }

template<unsigned N, class E1, class E2>
int8<N*2> combine(int8<N,E1> a1, int8<N,E2> a2) { return detail::v_combine<int8<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
int16<N*2> combine(int16<N,E1> a1, int16<N,E2> a2) { return detail::v_combine<int16<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
int32<N*2> combine(int32<N,E1> a1, int32<N,E2> a2) { return detail::v_combine<int32<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
int64<N*2> combine(int64<N,E1> a1, int64<N,E2> a2) { return detail::v_combine<int64<N*2>>(a1.eval(), a2.eval()); }

template<unsigned N, class E1, class E2>
float32<N*2> combine(float32<N,E1> a1, float32<N,E2> a2) { return detail::v_combine<float32<N*2>>(a1.eval(), a2.eval()); }
template<unsigned N, class E1, class E2>
float64<N*2> combine(float64<N,E1> a1, float64<N,E2> a2) { return detail::v_combine<float64<N*2>>(a1.eval(), a2.eval()); }

/// @}

/// @} -- end defgroup

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

/// @}
