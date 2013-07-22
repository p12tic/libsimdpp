/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_SHUFFLE_H
#define LIBSIMDPP_NULL_SHUFFLE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
V zip_lo(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length/2; i++) {
        r[i*2] = a[i];
        r[i*2+1] = b[i];
    }
    return r;
}

template<class V>
V zip_hi(V a, V b)
{
    V r;
    constexpr unsigned half = traits<V>::length/2;
    for (unsigned i = 0; i < half; i++) {
        r[i*2] = a[half+i];
        r[i*2+1] = b[half+i];
    }
    return r;
}

template<unsigned pos, class V>
V broadcast(V v)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = v[pos];
    }
    return r;
}

template<unsigned shift, class V>
V align(V lo, V hi)
{
    V r;
    for (unsigned i = 0; i < 16-shift; i++) {
        r[i] = lo[i + shift];
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r[i] = hi[i - 16 + shift];
    }
    return r;
}

template<class V>
V unzip_lo(V a, V b)
{
    V r;
    unsigned half = traits<V>::length/2;
    for (unsigned i = 0; i < half; i++) {
        r[i] = a[i*2];
        r[i + half] = b[i*2];
    }
    return r;
}

template<class V>
V unzip_hi(V a, V b)
{
    V r;
    unsigned half = traits<V>::length/2;
    for (unsigned i = 0; i < half; i++) {
        r[i] = a[i*2+1];
        r[i + half] = b[i*2+1];
    }
    return r;
}

template<class V>
V blend(V on, V off, V mask)
{
    V r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
}

template<unsigned s0, unsigned s1, class V>
V permute(V a)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=2) {
        r[i] =   a[i + s0];
        r[i+1] = a[i + s1];
    }
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
V permute(V a)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=4) {
        r[i] =   a[i + s0];
        r[i+1] = a[i + s1];
        r[i+2] = a[i + s2];
        r[i+3] = a[i + s3];
    }
    return r;
}

template<unsigned s0, unsigned s1, class V>
V shuffle1(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=2) {
        r[i] =   a[i + s0];
        r[i+1] = b[i + s1];
    }
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
V shuffle2(V a, V b)
{
    V r;
    for (unsigned i = 0; i < traits<V>::length; i+=4) {
        r[i] =   a[i + s0];
        r[i+1] = a[i + s1];
        r[i+2] = b[i + s2];
        r[i+3] = b[i + s3];
    }
    return r;
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
