/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NULL_BITWISE_H
#define LIBSIMDPP_DETAIL_NULL_BITWISE_H
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/null/mask.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace null {

/* *_vm variants accept a vector as the first argument and a mask as the second
   *_mm variants accept masks as both arguments
*/

template<class V> SIMDPP_INL
V bit_and(const V& a, const V& b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a.el(i));
        U b1 = bit_cast<U, E>(b.el(i));
        r.el(i) = bit_cast<E, U>(a1 & b1);
    }
    return r;
}

template<class V, class M> SIMDPP_INL
V bit_and_vm(const V& a, const M& m)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = m.el(i) ? a.el(i) : 0;
    }
    return r;
}

template<class M> SIMDPP_INL
M bit_and_mm(const M& a, const M& b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = a.el(i) && b.el(i);
    }
    return r;
}


template<class V> SIMDPP_INL
V bit_andnot(const V& a, const V& b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a.el(i));
        U b1 = bit_cast<U, E>(b.el(i));
        r.el(i) = bit_cast<E, U>(a1 & ~b1);
    }
    return r;
}

template<class V, class M> SIMDPP_INL
V bit_andnot_vm(const V& a, const M& m)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = !m.el(i) ? a.el(i) : 0;
    }
    return r;
}

template<class M> SIMDPP_INL
M bit_andnot_mm(const M& a, const M& b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = a.el(i) && !b.el(i);
    }
    return r;
}


template<class V> SIMDPP_INL
V bit_or(const V& a, const V& b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a.el(i));
        U b1 = bit_cast<U, E>(b.el(i));
        r.el(i) = bit_cast<E, U>(a1 | b1);
    }
    return r;
}

template<class M> SIMDPP_INL
M bit_or_mm(const M& a, const M& b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = a.el(i) || b.el(i);
    }
    return r;
}

template<class V> SIMDPP_INL
V bit_xor(const V& a, const V& b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a.el(i));
        U b1 = bit_cast<U, E>(b.el(i));
        r.el(i) = bit_cast<E, U>(a1 ^ b1);
    }
    return r;
}

template<class M> SIMDPP_INL
M bit_xor_mm(const M& a, const M& b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = (a.el(i) && !b.el(i)) ||
                  (!a.el(i) && b.el(i));
    }
    return r;
}

template<class M> SIMDPP_INL
M bit_not_mm(const M& a)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = !a.el(i);
    }
    return r;
}

template<class V> SIMDPP_INL
bool test_bits_any(const V& a)
{
    using U = typename V::uint_element_type;
    U r = 0;
    for (unsigned i = 0; i < a.length; ++i) {
        r |= bit_cast<U>(a.el(i));
    }
    return r != 0;
}

} // namespace null
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
