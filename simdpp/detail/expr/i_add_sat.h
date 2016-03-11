/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_SAT_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_SAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/expr.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E1, class E2> SIMDPP_INL
int8<16> expr_eval(const expr_add_sat<int8<16,E1>,
                                      int8<16,E2>>& q)
{
    int8<16> a = q.a.eval();
    int8<16> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::add_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int8<32> expr_eval(const expr_add_sat<int8<32,E1>,
                                      int8<32,E2>>& q)
{
    int8<32> a = q.a.eval();
    int8<32> b = q.b.eval();
    return _mm256_adds_epi8(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int8<N> expr_eval(const expr_add_sat<int8<N,E1>,
                                     int8<N,E2>>& q)
{
    int8<N> a = q.a.eval();
    int8<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, add_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
int16<8> expr_eval(const expr_add_sat<int16<8,E1>,
                                      int16<8,E2>>& q)
{
    int16<8> a = q.a.eval();
    int16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::add_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int16<16> expr_eval(const expr_add_sat<int16<16,E1>,
                                       int16<16,E2>>& q)
{
    int16<16> a = q.a.eval();
    int16<16> b = q.b.eval();
    return _mm256_adds_epi16(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int16<N> expr_eval(const expr_add_sat<int16<N,E1>,
                                      int16<N,E2>>& q)
{
    int16<N> a = q.a.eval();
    int16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, add_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint8<16> expr_eval(const expr_add_sat<uint8<16,E1>,
                                       uint8<16,E2>>& q)
{
    uint8<16> a = q.a.eval();
    uint8<16> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::add_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint8<32> expr_eval(const expr_add_sat<uint8<32,E1>,
                                       uint8<32,E2>>& q)
{
    uint8<32> a = q.a.eval();
    uint8<32> b = q.b.eval();
    return _mm256_adds_epu8(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint8<N> expr_eval(const expr_add_sat<uint8<N,E1>,
                                      uint8<N,E2>>& q)
{
    uint8<N> a = q.a.eval();
    uint8<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, add_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval(const expr_add_sat<uint16<8,E1>,
                                       uint16<8,E2>>& q)
{
    uint16<8> a = q.a.eval();
    uint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::add_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval(const expr_add_sat<uint16<16,E1>,
                                        uint16<16,E2>>& q)
{
    uint16<16> a = q.a.eval();
    uint16<16> b = q.b.eval();
    return _mm256_adds_epu16(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval(const expr_add_sat<uint16<N,E1>,
                                       uint16<N,E2>>& q)
{
    uint16<N> a = q.a.eval();
    uint16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, add_sat, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

