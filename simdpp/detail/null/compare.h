/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NULL_COMPARE_H
#define LIBSIMDPP_DETAIL_NULL_COMPARE_H
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/detail/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace null {

template<class V>
typename V::mask_vector_type cmp_eq(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) == b.el(i)) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_vector_type cmp_neq(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) != b.el(i)) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_vector_type cmp_lt(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) < b.el(i)) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_vector_type cmp_le(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) <= b.el(i)) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_vector_type cmp_gt(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) > b.el(i)) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_vector_type cmp_ge(V a, V b)
{
    typename V::mask_vector_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = (a.el(i) >= b.el(i)) ? 1 : 0;
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
