/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_AND_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_AND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_and.h>
#include <simdpp/detail/expr/bit_and.h>
#include <simdpp/detail/get_expr.h>
#include <simdpp/core/detail/get_expr_bitwise.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Computes bitwise AND of integer or floating-point vectors.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @todo: icost
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V1, V2>::type
        bit_and(const any_vec<N,V1>& a,
                const any_vec<N,V2>& b)
{
    expr_bit_and<V1, V2> ret = { a.wrapped(), b.wrapped() };
    return ret;
}

// support scalar arguments
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, unsigned, V>::type
        bit_and(const unsigned& a, const any_vec<N,V>& b)
{
    expr_bit_and<unsigned, V> ret = { a, b.wrapped() };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, unsigned long, V>::type
        bit_and(const unsigned long& a, const any_vec<N,V>& b)
{
    expr_bit_and<unsigned long, V> ret = { a, b.wrapped() };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, unsigned long long, V>::type
        bit_and(const unsigned long long& a, const any_vec<N,V>& b)
{
    expr_bit_and<unsigned long long, V> ret = { a, b.wrapped() };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, int, V>::type
        bit_and(const int& a, const any_vec<N,V>& b)
{
    expr_bit_and<int, V> ret = { a, b.wrapped() };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, long, V>::type
        bit_and(const long& a, const any_vec<N,V>& b)
{
    expr_bit_and<long, V> ret = { a, b.wrapped() };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, long long, V>::type
        bit_and(const long long& a, const any_vec<N,V>& b)
{
    expr_bit_and<long long, V> ret = { a, b.wrapped() };
    return ret;
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V, unsigned>::type
        bit_and(const any_vec<N,V>& a, const unsigned& b)
{
    expr_bit_and<V, unsigned> ret = { a.wrapped(), b };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V, unsigned long>::type
        bit_and(const any_vec<N,V>& a, const unsigned long& b)
{
    expr_bit_and<V, unsigned long> ret = { a.wrapped(), b };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V, unsigned long long>::type
        bit_and(const any_vec<N,V>& a, const unsigned long long& b)
{
    expr_bit_and<V, unsigned long long> ret = { a.wrapped(), b };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V, int>::type
        bit_and(const any_vec<N,V>& a, const int& b)
{
    expr_bit_and<V, int> ret = { a.wrapped(), b };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V, long>::type
        bit_and(const any_vec<N,V>& a, const long& b)
{
    expr_bit_and<V, long> ret = { a.wrapped(), b };
    return ret;
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_and, V, long long>::type
        bit_and(const any_vec<N,V>& a, const long long& b)
{
    expr_bit_and<V, long long> ret = { a.wrapped(), b };
    return ret;
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

