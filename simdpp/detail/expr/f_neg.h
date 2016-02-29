/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_NEG_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E> SIMDPP_INL
float32<4> expr_eval(const expr_neg<float32<4,E> >& q)
{
    float32<4> a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // reversion of the sign bit required even for NaNs and zeros
    return bit_xor(a, 0x80000000);
#elif SIMDPP_USE_NEON_FLT_SP
    return vnegq_f32(a);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E> SIMDPP_INL
float32<8> expr_eval(const expr_neg<float32<8,E> >& q)
{
    float32<8> a = q.a.eval();
    return bit_xor(a, 0x80000000);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E> SIMDPP_INL
float32<16> expr_eval(const expr_neg<float32<16,E> >& q)
{
    // FIXME: check whether we can simply use sub
    float32<16> a = q.a.eval();
    return bit_xor(a, 0x80000000);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
float32<N> expr_eval(const expr_neg<float32<N,E> >& q)
{
    float32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
float64x2 expr_eval(const expr_neg<float64<2,E> >& q)
{
    float64x2 a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2
    return bit_xor(a, 0x8000000000000000);
#elif SIMDPP_USE_NEON64
    return vnegq_f64(a);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E> SIMDPP_INL
float64x4 expr_eval(const expr_neg<float64<4,E> >& q)
{
    float64x4 a = q.a.eval();
    return bit_xor(a, 0x8000000000000000);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E> SIMDPP_INL
float64<8> expr_eval(const expr_neg<float64<8,E> >& q)
{
    // FIXME: check whether we can simply use sub
    float64<8> a = q.a.eval();
    return bit_xor(a, 0x8000000000000000);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
float64<N> expr_eval(const expr_neg<float64<N,E> >& q)
{
    float64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, neg, a);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

