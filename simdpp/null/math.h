/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_NULL_MATH_H
#define LIBSIMDPP_NULL_MATH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/cast.h>
#include <simdpp/simd/detail/mem_block.h>

#include <cmath>
#include <cstdlib>
#include <limits>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

template<class V>
typename V::mask_type isnan(V a)
{
    typename V::mask_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = std::isnan(a[i]) ? 1 : 0;
    }
    return r;
}

template<class V>
typename V::mask_type isnan2(V a, V b)
{
    typename V::mask_type r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = (std::isnan(a[i]) || std::isnan(b[i])) ? 1 : 0;
    }
    return r;
}

template<class V>
V abs(V a)
{
    detail::mem_block<V> ax(a);
    for (unsigned i = 0; i < V::length; i++) {
        ax[i] = std::abs(ax[i]);
    }
    return ax;
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
        r[i] = a[i] + b[i];
    }
    return r;
}

template<class V>
V adds(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = saturate<typename V::element_type>(int32_t(a[i]) + b[i]);
    }
    return r;
}

template<class V>
V sub(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = a[i] - b[i];
    }
    return r;
}

template<class V>
V subs(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = saturate<typename V::element_type>(int32_t(a[i]) - b[i]);
    }
    return r;
}

template<class V>
V neg(V a)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = -a[i];
    }
    return r;
}

template<class V>
V mul(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = a[i] * b[i];
    }
    return r;
}

template<class V>
V fmadd(V a, V b, V c)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = std::fma(a[i], b[i], c[i]);
    }
    return r;
}

template<class V>
V fmsub(V a, V b, V c)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = std::fma(a[i], b[i], -c[i]);
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
        r[i] = (a[i] & mask) / (b[i] & mask);
        r[i] &= mask;
    }
    return r;
}


template<class V>
V shift_r(V a, unsigned shift)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = a[i] >> shift;
    }
    return r;
}

template<class V>
V shift_l(V a, unsigned shift)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = a[i] << shift;
    }
    return r;
}

template<class V>
V min(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = a[i] <= b[i] ? a[i] : b[i];
    }
    return r;
}

template<class V>
V max(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = a[i] >= b[i] ? a[i] : b[i];
    }
    return r;
}

} // namespace null
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
