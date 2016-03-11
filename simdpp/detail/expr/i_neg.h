/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_NEG_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {


template<class R, class E> SIMDPP_INL
int8<16> expr_eval(const expr_neg<int8<16,E>>& q)
{
    int8<16> a = q.a.eval();
#if SIMDPP_USE_NULL
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(0, a);
#elif SIMDPP_USE_NEON
    return vnegq_s8(a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
int8<32> expr_eval(const expr_neg<int8<32,E>>& q)
{
    int8<32> a = q.a.eval();
    return sub(0, a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
int8<N> expr_eval(const expr_neg<int8<N,E>>& q)
{
    int8<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int8<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
int16<8> expr_eval(const expr_neg<int16<8,E>>& q)
{
    int16<8> a = q.a.eval();
#if SIMDPP_USE_NULL
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(0, a);
#elif SIMDPP_USE_NEON
    return vnegq_s16(a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
int16<16> expr_eval(const expr_neg<int16<16,E>>& q)
{
    int16<16> a = q.a.eval();
    return sub(0, a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
int16<N> expr_eval(const expr_neg<int16<N,E>>& q)
{
    int16<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int16<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
int32<4> expr_eval(const expr_neg<int32<4,E>>& q)
{
    int32<4> a = q.a.eval();
#if SIMDPP_USE_NULL
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(0, a);
#elif SIMDPP_USE_NEON
    return vnegq_s32(a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
int32<8> expr_eval(const expr_neg<int32<8,E>>& q)
{
    int32<8> a = q.a.eval();
    return sub(0, a);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E> SIMDPP_INL
int32<16> expr_eval(const expr_neg<int32<16,E>>& q)
{
    int32<16> a = q.a.eval();
    return sub(0, a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
int32<N> expr_eval(const expr_neg<int32<N,E>>& q)
{
    int32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int32<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
int64<2> expr_eval(const expr_neg<int64<2,E>>& q)
{
    int64<2> a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    return sub(0, a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
uint64<4> expr_eval(const expr_neg<int64<4,E>>& q)
{
    int64<4> a = q.a.eval();
    return sub(0, a);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E> SIMDPP_INL
uint64<8> expr_eval(const expr_neg<int64<8,E>>& q)
{
    int64<8> a = q.a.eval();
    return sub(0, a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
uint64<N> expr_eval(const expr_neg<int64<N,E>>& q)
{
    int64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int64<N>, neg, a);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

