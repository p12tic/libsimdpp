/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_BITWISE_H
#define LIBSIMDPP_NULL_BITWISE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>
#include <simdpp/simd/cast.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
V bit_and(V a, V b)
{
    V r;
    using E = typename traits<V>::element_type;
    using U = typename traits<V>::unsigned_element_type;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 & b1);
    }
    return r;
}

template<class V>
V bit_andnot(V a, V b)
{
    V r;
    using E = typename traits<V>::element_type;
    using U = typename traits<V>::unsigned_element_type;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 & ~b1);
    }
    return r;
}

template<class V>
V bit_or(V a, V b)
{
    V r;
    using E = typename traits<V>::element_type;
    using U = typename traits<V>::unsigned_element_type;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 | b1);
    }
    return r;
}

template<class V>
V bit_xor(V a, V b)
{
    V r;
    using E = typename traits<V>::element_type;
    using U = typename traits<V>::unsigned_element_type;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 ^ b1);
    }
    return r;
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
