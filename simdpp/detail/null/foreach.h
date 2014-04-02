/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NULL_FOREACH_H
#define LIBSIMDPP_DETAIL_NULL_FOREACH_H
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace null {

template<class R, class V, class C>
R foreach(V v, C c)
{
    R r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = c(v.el(i));
    }
    return static_cast<R>(r);
}

template<class R, class V1, class V2, class C>
R foreach(V1 v1, V2 v2, C c)
{
    R r;
    for (unsigned i = 0; i < V1::length; i++) {
        r.el(i) = c(v1.el(i), v2.el(i));
    }
    return static_cast<R>(r);
}

} // namespace null
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
