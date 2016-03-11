/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_MUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_mull.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/unzip_hi.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {


template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval(const expr_mul_lo<uint16<8,E1>,
                                      uint16<8,E2>>& q)
{
    uint16<8> a = q.a.eval();
    uint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mullo_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vmulq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_mladd((__vector uint16_t)a, (__vector uint16_t)b,
                     (__vector uint16_t)(uint16x8) make_zero());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval(const expr_mul_lo<uint16<16,E1>,
                                       uint16<16,E2>>& q)
{
    uint16<16> a = q.a.eval();
    uint16<16> b = q.b.eval();
    return _mm256_mullo_epi16(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval(const expr_mul_lo<uint16<N,E1>,
                                      uint16<N,E2>>& q)
{
    uint16<N> a = q.a.eval();
    uint16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, mul_lo, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
int16<8> expr_eval(const expr_mul_hi<int16<8,E1>,
                                     int16<8,E2>>& q)
{
    int16<8> a = q.a.eval();
    int16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    uint16<8> r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = (int32_t(a.el(i)) * b.el(i)) >> 16;
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epi16(a, b);
#elif SIMDPP_USE_NEON
    int32x4 lo = vmull_s16(vget_low_s16(a), vget_low_s16(b));
    int32x4 hi = vmull_s16(vget_high_s16(a), vget_high_s16(b));
    return unzip8_hi(int16x8(lo), int16x8(hi));
#elif SIMDPP_USE_ALTIVEC
    int16<16> ab;
    ab = mull(a, b);
    return unzip8_lo(ab.vec(0), ab.vec(1));
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int16<16> expr_eval(const expr_mul_hi<int16<16,E1>,
                                      int16<16,E2>>& q)
{
    int16<16> a = q.a.eval();
    int16<16> b = q.b.eval();
    return _mm256_mulhi_epi16(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int16<N> expr_eval(const expr_mul_hi<int16<N,E1>,
                                     int16<N,E2>>& q)
{
    int16<N> a = q.a.eval();
    int16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, mul_hi, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval(const expr_mul_hi<uint16<8,E1>,
                                      uint16<8,E2>>& q)
{
    uint16<8> a = q.a.eval();
    uint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    uint16<8> r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = (uint32_t(a.el(i)) * b.el(i)) >> 16;
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epu16(a, b);
#elif SIMDPP_USE_NEON
    uint32x4 lo = vmull_u16(vget_low_u16(a), vget_low_u16(b));
    uint32x4 hi = vmull_u16(vget_high_u16(a), vget_high_u16(b));
    return unzip8_hi(uint16x8(lo), uint16x8(hi));
#elif SIMDPP_USE_ALTIVEC
    uint16<16> ab;
    ab = mull(a, b);
    return unzip8_lo(ab.vec(0), ab.vec(1));
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval(const expr_mul_hi<uint16<16,E1>,
                                       uint16<16,E2>>& q)
{
    uint16<16> a = q.a.eval();
    uint16<16> b = q.b.eval();
    return _mm256_mulhi_epu16(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval(const expr_mul_hi<uint16<N,E1>,
                                      uint16<N,E2>>& q)
{
    uint16<N> a = q.a.eval();
    uint16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, mul_hi, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint32<4> expr_eval(const expr_mul_lo<uint32<4,E1>,
                                      uint32<4,E2>>& q)
{
    uint32<4> a = q.a.eval();
    uint32<4> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::mul(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_mullo_epi32(a, b);
#elif SIMDPP_USE_SSE2
    uint32x4 a1, b1;
    a1 = move4_l<1>(a);
    b1 = move4_l<1>(b);
    a = _mm_mul_epu32(a, b);
    a1 = _mm_mul_epu32(a1, b1);
    a = shuffle2<0,2,0,2>(a, a1); // additional latency unavoidable
    a = permute4<0,2,1,3>(a);
    return a;
#elif SIMDPP_USE_NEON
    return vmulq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    // implement in terms of 16-bit multiplies
    //   *  ah  al
    //      bh  bl
    //      ======
    //   + (al*bl) <-  l_ab
    //+ (ah*bl)    <-  h_ab
    //+ (al*bh)    <-  h_ba

    uint16<8> ra = a, rb = b;
    uint16<8> sa = move8_l<1>(ra);
    uint16<8> sb = move8_l<1>(rb);

    uint32<4> l_ab = vec_mulo((__vector uint16_t) ra, (__vector uint16_t) rb);
    uint32<4> h_ab = vec_mulo((__vector uint16_t) ra, (__vector uint16_t) sb);
    uint32<4> h_ba = vec_mulo((__vector uint16_t) sa, (__vector uint16_t) rb);

    h_ab = shift_l<16>(add(h_ab, h_ba));
    h_ab = add(h_ab, l_ab);
    return h_ab;
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint32<8> expr_eval(const expr_mul_lo<uint32<8,E1>,
                                      uint32<8,E2>>& q)
{
    uint32<8> a = q.a.eval();
    uint32<8> b = q.b.eval();
    return _mm256_mullo_epi32(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
uint32<16> expr_eval(const expr_mul_lo<uint32<16,E1>,
                                       uint32<16,E2>>& q)
{
    uint32<16> a = q.a.eval();
    uint32<16> b = q.b.eval();
    return _mm512_mullo_epi32(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint32<N> expr_eval(const expr_mul_lo<uint32<N,E1>,
                                      uint32<N,E2>>& q)
{
    uint32<N> a = q.a.eval();
    uint32<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, mul_lo, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

