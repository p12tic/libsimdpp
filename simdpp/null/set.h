/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_SET_H
#define LIBSIMDPP_NULL_SET_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
V set_broadcast(V& a, typename traits<V>::element_type x)
{
    for (unsigned i = 0; i < traits<V>::length; i++) {
        a[i] = x;
    }
    return a;
}

template<class V, class E = typename traits<V>::element_type>
V make_vec(E v0)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = v0;
    }
    return r;
}

template<class V, class E = typename traits<V>::element_type>
V make_vec(E v0, E v1)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=2) {
        r[i] = v0;
        r[i+1] = v1;
    }
    return r;
}

template<class V, class E = typename traits<V>::element_type>
V make_vec(E v0, E v1, E v2, E v3)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=4) {
        r[i] = v0;
        r[i+1] = v1;
        r[i+2] = v2;
        r[i+3] = v3;
    }
    return r;
}

template<class V, class E = typename traits<V>::element_type>
V make_vec(E v0, E v1, E v2, E v3, E v4, E v5, E v6, E v7)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=8) {
        r[i] = v0;
        r[i+1] = v1;
        r[i+2] = v2;
        r[i+3] = v3;
        r[i+4] = v4;
        r[i+5] = v5;
        r[i+6] = v6;
        r[i+7] = v7;
    }
    return r;
}

template<class V, class E = typename traits<V>::element_type>
V make_vec(E v0, E v1, E v2, E v3, E v4, E v5, E v6, E v7,
           E v8, E v9, E v10, E v11, E v12, E v13, E v14, E v15)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=16) {
        r[i] = v0;
        r[i+1] = v1;
        r[i+2] = v2;
        r[i+3] = v3;
        r[i+4] = v4;
        r[i+5] = v5;
        r[i+6] = v6;
        r[i+7] = v7;
        r[i+8] = v8;
        r[i+9] = v9;
        r[i+10] = v10;
        r[i+11] = v11;
        r[i+12] = v12;
        r[i+13] = v13;
        r[i+14] = v14;
        r[i+15] = v15;
    }
    return r;
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
