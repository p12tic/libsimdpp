/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_COMPARE_H
#define LIBSIMDPP_NULL_COMPARE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
auto cmp_eq(V a, V b) -> typename traits<V>::int_vector_type
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] == b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

template<class V>
auto cmp_neq(V a, V b) -> typename traits<V>::int_vector_type
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] != b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

template<class V>
auto cmp_lt(V a, V b) -> typename traits<V>::int_vector_type
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] < b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

template<class V>
auto cmp_gt(V a, V b) -> typename traits<V>::int_vector_type
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] > b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
