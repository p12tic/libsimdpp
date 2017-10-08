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
float32<4> expr_eval_fmadd(const float32<4,E1>& qa,
                           const float32<4,E2>& qb,
                           const float32<4,E3>& qc)
{
    float32<4> a = qa.eval();
    float32<4> b = qb.eval();
    float32<4> c = qc.eval();
#if SIMDPP_USE_NULL
    return detail::null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_ps(a.native(), b.native(), c.native());
#elif SIMDPP_USE_FMA4
    return _mm_macc_ps(a.native(), b.native(), c.native());
#elif SIMDPP_USE_NEON64
    // FIXME: also in vfpv4
    return vfmaq_f32(a.native(), b.native(), c.native());
#elif SIMDPP_USE_MSA
    return __msa_fmadd_w(c.native(), a.native(), b.native());
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2, class E3> SIMDPP_INL
float32<8> expr_eval_fmadd(const float32<8,E1>& qa,
                           const float32<8,E2>& qb,
                           const float32<8,E3>& qc)
{
    float32<8> a = qa.eval();
    float32<8> b = qb.eval();
    float32<8> c = qc.eval();
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_ps(a.native(), b.native(), c.native());
#elif SIMDPP_USE_FMA4
    return _mm256_macc_ps(a.native(), b.native(), c.native());
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2, class E3> SIMDPP_INL
float32<16> expr_eval_fmadd(const float32<16,E1>& qa,
                            const float32<16,E2>& qb,
                            const float32<16,E3>& qc)
{
    float32<16> a = qa.eval();
    float32<16> b = qb.eval();
    float32<16> c = qc.eval();
    return _mm512_fmadd_ps(a.native(), b.native(), c.native());
}
#endif

template<class R, unsigned N, class E1, class E2, class E3> SIMDPP_INL
float32<N> expr_eval_fmadd(const float32<N,E1>& qa,
                           const float32<N,E2>& qb,
                           const float32<N,E3>& qc)
{
    float32<N> a = qa.eval();
    float32<N> b = qb.eval();
    float32<N> c = qc.eval();
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, fmadd, a, b, c);
}


// -----------------------------------------------------------------------------

template<class R, class E1, class E2, class E3> SIMDPP_INL
float64<2> expr_eval_fmadd(const float64<2,E1>& qa,
                           const float64<2,E2>& qb,
                           const float64<2,E3>& qc)
{
    float64<2> a = qa.eval();
    float64<2> b = qb.eval();
    float64<2> c = qc.eval();
#if SIMDPP_USE_NULL
    return detail::null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_pd(a.native(), b.native(), c.native());
#elif SIMDPP_USE_FMA4
    return _mm_macc_pd(a.native(), b.native(), c.native());
#elif SIMDPP_USE_NEON64
    // FIXME: also in vfpv4
    return vfmaq_f64(a.native(), b.native(), c.native());
#elif SIMDPP_USE_MSA
    return __msa_fmadd_d(c.native(), a.native(), b.native());
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
template<class R, class E1, class E2, class E3> SIMDPP_INL
float64<4> expr_eval_fmadd(const float64<4,E1>& qa,
                           const float64<4,E2>& qb,
                           const float64<4,E3>& qc)
{
    float64<4> a = qa.eval();
    float64<4> b = qb.eval();
    float64<4> c = qc.eval();
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_pd(a.native(), b.native(), c.native());
#elif SIMDPP_USE_FMA4
    return _mm256_macc_pd(a.native(), b.native(), c.native());
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(R, a, b, c);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2, class E3> SIMDPP_INL
float64<8> expr_eval_fmadd(const float64<8,E1>& qa,
                           const float64<8,E2>& qb,
                           const float64<8,E3>& qc)
{
    float64<8> a = qa.eval();
    float64<8> b = qb.eval();
    float64<8> c = qc.eval();
    return _mm512_fmadd_pd(a.native(), b.native(), c.native());
}
#endif

template<class R, unsigned N, class E1, class E2, class E3> SIMDPP_INL
float64<N> expr_eval_fmadd(const float64<N,E1>& qa,
                           const float64<N,E2>& qb,
                           const float64<N,E3>& qc)
{
    float64<N> a = qa.eval();
    float64<N> b = qb.eval();
    float64<N> c = qc.eval();
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, fmadd, a, b, c);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

