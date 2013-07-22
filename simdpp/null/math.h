/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_MATH_H
#define LIBSIMDPP_NULL_MATH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>
#include <simdpp/simd/cast.h>

#include <cmath>
#include <cstdlib>
#include <limits>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
V abs(V a)
{
    for (unsigned i = 0; i < traits<V>::length; i++) {
        a[i] = std::abs(a[i]);
    }
    return a;
}

template<class T, class U>
T saturate(U t)
{
    U min = std::numeric_limits<T>::min();
    U max = std::numeric_limits<T>::max();
    t = t < min ? min : t;
    t = t > max ? max : t;
    return t;
}

template<class V>
V add(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] + b[i];
    }
    return r;
}

template<class V>
V adds(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = saturate<typename traits<V>::element_type>(int32_t(a[i]) + b[i]);
    }
    return r;
}

template<class V>
V sub(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] - b[i];
    }
    return r;
}

template<class V>
V subs(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = saturate<typename traits<V>::element_type>(int32_t(a[i]) - b[i]);
    }
    return r;
}

template<class V>
V neg(V a)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = -a[i];
    }
    return r;
}

template<class V>
V mul(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] * b[i];
    }
    return r;
}

template<unsigned P, class V>
V div_p(V a, V b)
{
    // the least P significant bits of the mask are set.
    uint64_t mask = 0;
    mask = ~mask;
    mask <<= P;
    mask = ~mask;

    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] & mask) / (b[i] & mask);
        r[i] &= mask;
    }
    return r;
}


template<class V>
V shift_r(V a, unsigned shift)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] >> shift;
    }
    return r;
}

template<class V>
V shift_l(V a, unsigned shift)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] << shift;
    }
    return r;
}

template<class V>
V min(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] <= b[i] ? a[i] : b[i];
    }
    return r;
}

template<class V>
V max(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = a[i] >= b[i] ? a[i] : b[i];
    }
    return r;
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
