/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_MEMORY_H
#define LIBSIMDPP_NULL_MEMORY_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
V load(V& a, const void* p)
{
    using T = typename traits<V>::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        a[i] = *pt++;
    }
    return a;
}

template<class V>
void load_packed2(V& a, V& b, const void* p)
{
    using T = typename traits<V>::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        a[i] = *pt++;
        b[i] = *pt++;
    }
}

template<class V>
void load_packed3(V& a, V& b, V& c, const void* p)
{
    using T = typename traits<V>::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        a[i] = *pt++;
        b[i] = *pt++;
        c[i] = *pt++;
    }
}

template<class V>
void load_packed4(V& a, V& b, V& c, V& d, const void* p)
{
    using T = typename traits<V>::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        a[i] = *pt++;
        b[i] = *pt++;
        c[i] = *pt++;
        d[i] = *pt++;
    }
}

template<class V>
void store(void* p, V a)
{
    using T = typename traits<V>::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        *pt++ = a[i];
    }
}

template<class V>
void store_first(void* p, V a, unsigned n)
{
    using T = typename traits<V>::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < traits<V>::length && i < n; i++) {
        *pt++ = a[i];
    }
}

template<class V>
void store_last(void* p, V a, unsigned n)
{
    using T = typename traits<V>::element_type;
    T* pt = reinterpret_cast<T*>(p);
    pt += traits<V>::length - n;
    for (unsigned i = traits<V>::length - n; i < traits<V>::length; i++) {
        *pt++ = a[i];
    }
}

template<class V>
void store_packed2(void* p, V& a, V& b)
{
    using T = typename traits<V>::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        *pt++ = a[i];
        *pt++ = b[i];
    }
}

template<class V>
void store_packed3(void* p, V& a, V& b, V& c)
{
    using T = typename traits<V>::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        *pt++ = a[i];
        *pt++ = b[i];
        *pt++ = c[i];
    }
}

template<class V>
void store_packed4(void* p, V& a, V& b, V& c, V& d)
{
    using T = typename traits<V>::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < traits<V>::length; i++) {
        *pt++ = a[i];
        *pt++ = b[i];
        *pt++ = c[i];
        *pt++ = d[i];
    }
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
