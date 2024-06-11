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
typename detail::get_expr_bitwise2_and<V1, V2>::type
        bit_and(const any_vec<N,V1>& a,
                const any_vec<N,V2>& b)
{
    using E = detail::get_expr_bitwise2_and<V1, V2>;
    typename E::v1_final_type ra;
    typename E::v2_final_type rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_bit_and(ra, rb);
}

// support scalar arguments
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<unsigned, V>::type
        bit_and(unsigned a, const any_vec<N,V>& b)
{
    using E = detail::get_expr_bitwise2_and<unsigned, V>;
    return detail::insn::i_bit_and(
        detail::make_const_bitwise<typename E::v1_final_type>(detail::cast_int(a)),
        (typename E::v2_final_type)b.wrapped());
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<unsigned long, V>::type
        bit_and(unsigned long a, const any_vec<N,V>& b)
{
    using E = detail::get_expr_bitwise2_and<unsigned long, V>;
    return detail::insn::i_bit_and(
        detail::make_const_bitwise<typename E::v1_final_type>(detail::cast_int(a)),
        (typename E::v2_final_type)b.wrapped());
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<unsigned long long, V>::type
        bit_and(unsigned long long a, const any_vec<N,V>& b)
{
    using E = detail::get_expr_bitwise2_and<unsigned long long, V>;
    return detail::insn::i_bit_and(
        detail::make_const_bitwise<typename E::v1_final_type>(detail::cast_int(a)),
        (typename E::v2_final_type)b.wrapped());
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<int, V>::type
        bit_and(int a, const any_vec<N,V>& b)
{
    using E = detail::get_expr_bitwise2_and<int, V>;
    return detail::insn::i_bit_and(
        detail::make_const_bitwise<typename E::v1_final_type>(detail::cast_int(a)),
        (typename E::v2_final_type)b.wrapped());
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<long, V>::type
        bit_and(long a, const any_vec<N,V>& b)
{
    using E = detail::get_expr_bitwise2_and<long, V>;
    return detail::insn::i_bit_and(
        detail::make_const_bitwise<typename E::v1_final_type>(detail::cast_int(a)),
        (typename E::v2_final_type)b.wrapped());
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<long long, V>::type
        bit_and(long long a, const any_vec<N,V>& b)
{
    using E = detail::get_expr_bitwise2_and<long long, V>;
    return detail::insn::i_bit_and(
        detail::make_const_bitwise<typename E::v1_final_type>(detail::cast_int(a)),
        (typename E::v2_final_type)b.wrapped());
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<V, unsigned>::type
        bit_and(const any_vec<N,V>& a, unsigned b)
{   
    using E = detail::get_expr_bitwise2_and<V, unsigned>;
    return detail::insn::i_bit_and(
        (typename E::v1_final_type)a.wrapped(),
        detail::make_const_bitwise<typename E::v2_final_type>(detail::cast_int(b)));
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<V, unsigned long>::type
        bit_and(const any_vec<N,V>& a, unsigned long b)
{
    using E = detail::get_expr_bitwise2_and<V, unsigned long>;
    return detail::insn::i_bit_and(
        (typename E::v1_final_type)a.wrapped(),
        detail::make_const_bitwise<typename E::v2_final_type>(detail::cast_int(b)));
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<V, unsigned long long>::type
        bit_and(const any_vec<N,V>& a, unsigned long long b)
{
    using E = detail::get_expr_bitwise2_and<V, unsigned long long>;
    return detail::insn::i_bit_and(
        (typename E::v1_final_type)a.wrapped(),
        detail::make_const_bitwise<typename E::v2_final_type>(detail::cast_int(b)));
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<V, int>::type
        bit_and(const any_vec<N,V>& a, int b)
{
    using E = detail::get_expr_bitwise2_and<V, int>;
    return detail::insn::i_bit_and((typename E::v1_final_type)a.wrapped(),
        detail::make_const_bitwise<typename E::v2_final_type>(detail::cast_int(b)));
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<V, long>::type
        bit_and(const any_vec<N,V>& a, long b)
{
    using E = detail::get_expr_bitwise2_and<V, long>;
    return detail::insn::i_bit_and(
        (typename E::v1_final_type)a.wrapped(),
        detail::make_const_bitwise<typename E::v2_final_type>(detail::cast_int(b)));
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<V, long long>::type
        bit_and(const any_vec<N,V>& a, long long b)
{
    using E = detail::get_expr_bitwise2_and<V, long long>;
    return detail::insn::i_bit_and(
        (typename E::v1_final_type)a.wrapped(),
        detail::make_const_bitwise<typename E::v2_final_type>(detail::cast_int(b)));
}


} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

