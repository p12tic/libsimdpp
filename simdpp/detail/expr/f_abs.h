/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_ABS_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_ABS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/make_int.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class E>
float32<4> expr_eval(expr_abs<float32<4,E>> q)
{
    float32<4> a = q.a.eval();
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return detail::null::abs(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    int32<4> mask = make_int(0x7fffffff);
    return bit_and(a, mask);
#elif SIMDPP_USE_NEON_FLT_SP
    return vabsq_f32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_abs((__vector float)a);
#endif
}

#if SIMDPP_USE_AVX
template<class E>
float32<8> expr_eval(expr_abs<float32<8,E>> q)
{
    float32<8> a = q.a.eval();
    int32<8> mask = make_int(0x7fffffff);
    return bit_and(a, mask);
}
#endif

#if SIMDPP_USE_AVX512
template<class E>
float32<16> expr_eval(expr_abs<float32<16,E>> q)
{
    // TODO: maybe cmp_lt is better, but what to do with negative zero?
    float32<16> a = q.a.eval();
    int32<16> mask = make_int(0x7fffffff);
    return bit_and(a, mask);
}
#endif

template<unsigned N, class E>
float32<N> expr_eval(expr_abs<float32<N,E>> q)
{
    float32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class E>
float64x2 expr_eval(expr_abs<float64<2,E>> q)
{
    float64x2 a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::abs(a);
#elif SIMDPP_USE_SSE2
    int64<2> mask = make_int(0x7fffffffffffffff);
    return bit_and(a, mask);
#endif
}

#if SIMDPP_USE_AVX
template<class E>
float64x4 expr_eval(expr_abs<float64<4,E>> q)
{
    float64x4 a = q.a.eval();
    int64<4> mask = make_int(0x7fffffffffffffff);
    return bit_and(a, mask);
}
#endif

#if SIMDPP_USE_AVX512
template<class E>
float64<8> expr_eval(expr_abs<float64<8,E>> q)
{
    // TODO: maybe cmp_lt is better, but what to do with negative zero?
    float64<8> a = q.a.eval();
    int64<8> mask = make_int(0x7fffffffffffffff);
    return bit_and(a, mask);
}
#endif

template<unsigned N, class E>
float64<N> expr_eval(expr_abs<float64<N,E>> q)
{
    float64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, abs, a);
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

