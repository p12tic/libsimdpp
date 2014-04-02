/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NULL_BITWISE_H
#define LIBSIMDPP_DETAIL_NULL_BITWISE_H
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace null {

/* *_vm variants accept a vector as the first argument and a mask as the second
   *_mm variants accept masks as both arguments
*/

template<class V>
V bit_and(V a, V b)
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

template<class V, class M>
V bit_and_vm(V a, M m)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = m.el(i) ? a.el(i) : 0;
    }
    return r;
}

template<class M>
M bit_and_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = a.el(i) && b.el(i);
    }
    return r;
}


template<class V>
V bit_andnot(V a, V b)
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

template<class V, class M>
V bit_andnot_vm(V a, M m)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = !m.el(i) ? a.el(i) : 0;
    }
    return r;
}

template<class M>
M bit_andnot_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = a.el(i) && !b.el(i);
    }
    return r;
}


template<class V>
V bit_or(V a, V b)
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

template<class M>
M bit_or_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = a.el(i) || b.el(i);
    }
    return r;
}

template<class V>
V bit_xor(V a, V b)
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

template<class M>
M bit_xor_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = (a.el(i) && !b.el(i)) ||
                  (!a.el(i) && b.el(i));
    }
    return r;
}

template<class M>
M bit_not_mm(M a)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r.el(i) = !a.el(i);
    }
    return r;
}

} // namespace null
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
