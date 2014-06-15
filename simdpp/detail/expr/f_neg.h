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
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class E>
float32<4> expr_eval(expr_neg<float32<4,E>> q)
{
    float32<4> a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // reversion of the sign bit required even for NaNs and zeros
    int32x4 zero = make_int(0x80000000);
    return bit_xor(a, zero);
#elif SIMDPP_USE_NEON_FLT_SP
    return vnegq_f32(a);
#endif
}

#if SIMDPP_USE_AVX
template<class E>
float32<8> expr_eval(expr_neg<float32<8,E>> q)
{
    float32<8> a = q.a.eval();
    int32x8 zero = make_int(0x80000000);
    return bit_xor(a, zero);
}
#endif

#if SIMDPP_USE_AVX512
template<class E>
float32<16> expr_eval(expr_neg<float32<16,E>> q)
{
    // FIXME: check whether we can simply use sub
    float32<16> a = q.a.eval();
    int32<16> zero = make_int(0x80000000);
    return bit_xor(a, zero);
}
#endif

template<unsigned N, class E>
float32<N> expr_eval(expr_neg<float32<N,E>> q)
{
    float32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class E>
float64x2 expr_eval(expr_neg<float64<2,E>> q)
{
    float64x2 a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2
    int64x2 zero = make_int(0x8000000000000000);
    return bit_xor(a, zero);
#endif
}

#if SIMDPP_USE_AVX
template<class E>
float64x4 expr_eval(expr_neg<float64<4,E>> q)
{
    float64x4 a = q.a.eval();
    int64x4 zero = make_int(0x8000000000000000);
    return bit_xor(a, zero);
}
#endif

#if SIMDPP_USE_AVX512
template<class E>
float64<8> expr_eval(expr_neg<float64<8,E>> q)
{
    // FIXME: check whether we can simply use sub
    float64<8> a = q.a.eval();
    int64<8> zero = make_int(0x8000000000000000);
    return bit_xor(a, zero);
}
#endif

template<unsigned N, class E>
float64<N> expr_eval(expr_neg<float64<N,E>> q)
{
    float64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, neg, a);
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

