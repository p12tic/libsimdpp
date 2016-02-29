/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_FMADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_FMADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>
#include <simdpp/detail/not_implemented.h>


namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E1, class E2, class E3> SIMDPP_INL
float32<4> expr_eval(const expr_fmadd<float32<4,E1>,
                                      float32<4,E2>,
                                      float32<4,E3> >& q)
{
    float32<4> a = q.a.eval();
    float32<4> b = q.b.eval();
    float32<4> c = q.c.eval();
#if SIMDPP_USE_NULL
    return detail::null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_macc_ps(a, b, c);
#elif SIMDPP_USE_NEON64
    // FIXME: also in vfpv4
    return vfmaq_f32(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2, class E3> SIMDPP_INL
float32<8> expr_eval(const expr_fmadd<float32<8,E1>,
                                      float32<8,E2>,
                                      float32<8,E3> >& q)
{
    float32<8> a = q.a.eval();
    float32<8> b = q.b.eval();
    float32<8> c = q.c.eval();
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_macc_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2, class E3> SIMDPP_INL
float32<16> expr_eval(const expr_fmadd<float32<16,E1>,
                                       float32<16,E2>,
                                       float32<16,E3> >& q)
{
    float32<16> a = q.a.eval();
    float32<16> b = q.b.eval();
    float32<16> c = q.c.eval();
    return _mm512_fmadd_ps(a, b, c);
}
#endif

template<class R, unsigned N, class E1, class E2, class E3> SIMDPP_INL
float32<N> expr_eval(const expr_fmadd<float32<N,E1>,
                                      float32<N,E2>,
                                      float32<N,E3> >& q)
{
    float32<N> a = q.a.eval();
    float32<N> b = q.b.eval();
    float32<N> c = q.c.eval();
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, fmadd, a, b, c);
}


// -----------------------------------------------------------------------------

template<class R, class E1, class E2, class E3> SIMDPP_INL
float64<2> expr_eval(const expr_fmadd<float64<2,E1>,
                                      float64<2,E2>,
                                      float64<2,E3> >& q)
{
    float64<2> a = q.a.eval();
    float64<2> b = q.b.eval();
    float64<2> c = q.c.eval();
#if SIMDPP_USE_NULL
    return detail::null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_macc_pd(a, b, c);
#elif SIMDPP_USE_NEON64
    // FIXME: also in vfpv4
    return vfmaq_f64(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2, class E3> SIMDPP_INL
float64<4> expr_eval(const expr_fmadd<float64<4,E1>,
                                      float64<4,E2>,
                                      float64<4,E3> >& q)
{
    float64<4> a = q.a.eval();
    float64<4> b = q.b.eval();
    float64<4> c = q.c.eval();
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_macc_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2, class E3> SIMDPP_INL
float64<8> expr_eval(const expr_fmadd<float64<8,E1>,
                                      float64<8,E2>,
                                      float64<8,E3> >& q)
{
    float64<8> a = q.a.eval();
    float64<8> b = q.b.eval();
    float64<8> c = q.c.eval();
    return _mm512_fmadd_pd(a, b, c);
}
#endif

template<class R, unsigned N, class E1, class E2, class E3> SIMDPP_INL
float64<N> expr_eval(const expr_fmadd<float64<N,E1>,
                                      float64<N,E2>,
                                      float64<N,E3> >& q)
{
    float64<N> a = q.a.eval();
    float64<N> b = q.b.eval();
    float64<N> c = q.c.eval();
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, fmadd, a, b, c);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

