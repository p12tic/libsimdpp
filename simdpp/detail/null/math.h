/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NULL_MATH_H
#define LIBSIMDPP_DETAIL_NULL_MATH_H
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/cast.h>

#include <cmath>
#include <cstdlib>
#include <limits>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace null {

template<class V>
typename V::mask_vector_type isnan(V a)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = std::isnan(a.el(i)) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_vector_type isnan2(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (std::isnan(a.el(i)) || std::isnan(b.el(i))) ? 1 : 0;
    }
    return r;
}

template<class V>
V abs(V a)
{
    for (unsigned i = 0; i < V::length; i++) {
        a.el(i) = std::abs(a.el(i));
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
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) + b.el(i);
    }
    return r;
}

template<class V>
V add_sat(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = saturate<typename V::element_type>(int32_t(a.el(i)) + b.el(i));
    }
    return r;
}

template<class V>
V sub(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) - b.el(i);
    }
    return r;
}

template<class V>
V sub_sat(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = saturate<typename V::element_type>(int32_t(a.el(i)) - b.el(i));
    }
    return r;
}

template<class V>
V neg(V a)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = -a.el(i);
    }
    return r;
}

template<class V>
V mul(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) * b.el(i);
    }
    return r;
}

template<class V>
V fmadd(V a, V b, V c)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = std::fma(a.el(i), b.el(i), c.el(i));
    }
    return r;
}

template<class V>
V fmsub(V a, V b, V c)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = std::fma(a.el(i), b.el(i), -c.el(i));
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
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) & mask) / (b.el(i) & mask);
        r.el(i) &= mask;
    }
    return r;
}


template<class V>
V shift_r(V a, unsigned shift)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) >> shift;
    }
    return r;
}

template<class V>
V shift_l(V a, unsigned shift)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) << shift;
    }
    return r;
}

template<class V>
V min(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) <= b.el(i) ? a.el(i) : b.el(i);
    }
    return r;
}

template<class V>
V max(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = a.el(i) >= b.el(i) ? a.el(i) : b.el(i);
    }
    return r;
}

} // namespace null
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
