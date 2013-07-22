/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_FOREACH_H
#define LIBSIMDPP_NULL_FOREACH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/null/traits.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class R, class V, class C>
R foreach(V v, C c)
{
    R r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = c(v[i]);
    }
    return r;
}

template<class R, class V1, class V2, class C>
R foreach(V1 v1, V2 v2, C c)
{
    R r;
    for (unsigned i = 0; i < traits<V1>::length; i++) {
        r[i] = c(v1[i], v2[i]);
    }
    return r;
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
