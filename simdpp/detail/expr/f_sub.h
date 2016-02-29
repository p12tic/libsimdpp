/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_SUB_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_SUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E1, class E2> SIMDPP_INL
float32<4> expr_eval(const expr_sub<float32<4,E1>,
                                    float32<4,E2>>& q)
{
    float32<4> a = q.a.eval();
    float32<4> b = q.b.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_ps(a,b);
#elif SIMDPP_USE_NEON_FLT_SP
    return vsubq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2> SIMDPP_INL
float32<8> expr_eval(const expr_sub<float32<8,E1>,
                                    float32<8,E2>>& q)
{
    float32<8> a = q.a.eval();
    float32<8> b = q.b.eval();
    return _mm256_sub_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
float32<16> expr_eval(const expr_sub<float32<16,E1>,
                                     float32<16,E2>>& q)
{
    float32<16> a = q.a.eval();
    float32<16> b = q.b.eval();
    return _mm512_sub_ps(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
float32<N> expr_eval(const expr_sub<float32<N,E1>,
                                    float32<N,E2>>& q)
{
    float32<N> a = q.a.eval();
    float32<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, sub, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
float64<2> expr_eval(const expr_sub<float64<2,E1>,
                                    float64<2,E2>>& q)
{
    float64<2> a = q.a.eval();
    float64<2> b = q.b.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::sub(a, b);
#elif SIMDPP_USE_NEON64
    return vsubq_f64(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_pd(a, b);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2> SIMDPP_INL
float64<4> expr_eval(const expr_sub<float64<4,E1>,
                                    float64<4,E2>>& q)
{
    float64<4> a = q.a.eval();
    float64<4> b = q.b.eval();
    return _mm256_sub_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
float64<8> expr_eval(const expr_sub<float64<8,E1>,
                                    float64<8,E2>>& q)
{
    float64<8> a = q.a.eval();
    float64<8> b = q.b.eval();
    return _mm512_sub_pd(a, b);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
float64<N> expr_eval(const expr_sub<float64<N,E1>,
                                    float64<N,E2>>& q)
{
    float64<N> a = q.a.eval();
    float64<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, sub, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

