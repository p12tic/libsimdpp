/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_FMADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_FMADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>
#include <simdpp/detail/not_implemented.h>


namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class E1, class E2, class E3>
float32<4> expr_eval(expr_fmadd<float32<4,E1>,
                                           float32<4,E2>,
                                           float32<4,E3>> q)
{
    float32<4> a = q.a.eval();
    float32<4> b = q.b.eval();
    float32<4> c = q.c.eval();
#if SIMDPP_USE_NULL
    return null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_macc_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

#if SIMDPP_USE_AVX
template<class E1, class E2, class E3>
float32<8> expr_eval(expr_fmadd<float32<8,E1>,
                                           float32<8,E2>,
                                           float32<8,E3>> q)
{
    float32<8> a = q.a.eval();
    float32<8> b = q.b.eval();
    float32<8> c = q.c.eval();
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_macc_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}
#endif

template<unsigned N, class E1, class E2, class E3>
float32<N> expr_eval(expr_fmadd<float32<N,E1>,
                                float32<N,E2>,
                                float32<N,E3>> q)
{
    float32<N> a = q.a.eval();
    float32<N> b = q.b.eval();
    float32<N> c = q.c.eval();
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, fmadd, a, b, c);
}


// -----------------------------------------------------------------------------

template<class E1, class E2, class E3>
float64<2> expr_eval(expr_fmadd<float64<2,E1>,
                                float64<2,E2>,
                                float64<2,E3>> q)
{
    float64<2> a = q.a.eval();
    float64<2> b = q.b.eval();
    float64<2> c = q.c.eval();
#if SIMDPP_USE_NULL
    return null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_macc_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

#if SIMDPP_USE_AVX
template<class E1, class E2, class E3>
float64<4> expr_eval(expr_fmadd<float64<4,E1>,
                                float64<4,E2>,
                                float64<4,E3>> q)
{
    float64<4> a = q.a.eval();
    float64<4> b = q.b.eval();
    float64<4> c = q.c.eval();
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_macc_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}
#endif

template<unsigned N, class E1, class E2, class E3>
float64<N> expr_eval(expr_fmadd<float64<N,E1>,
                                float64<N,E2>,
                                float64<N,E3>> q)
{
    float64<N> a = q.a.eval();
    float64<N> b = q.b.eval();
    float64<N> c = q.c.eval();
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, fmadd, a, b, c);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

