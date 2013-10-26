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

#ifndef LIBSIMDPP_NULL_BITWISE_H
#define LIBSIMDPP_NULL_BITWISE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/cast.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

/* *_vm variants accept a vector as the first argument and a mask as the second
   *_mm variants accept masks as both arguments
*/

template<class V>
V bit_and(V a, V b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 & b1);
    }
    return r;
}

template<class V, class M>
V bit_and_vm(V a, M m)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = m[i] ? a[i] : 0;
    }
    return r;
}

template<class M>
M bit_and_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r[i] = a[i] && b[i];
    }
    return r;
}


template<class V>
V bit_andnot(V a, V b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 & ~b1);
    }
    return r;
}

template<class V, class M>
V bit_andnot_vm(V a, M m)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = !m[i] ? a[i] : 0;
    }
    return r;
}

template<class M>
M bit_andnot_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r[i] = a[i] && !b[i];
    }
    return r;
}


template<class V>
V bit_or(V a, V b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 | b1);
    }
    return r;
}

template<class M>
M bit_or_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r[i] = a[i] || b[i];
    }
    return r;
}

template<class V>
V bit_xor(V a, V b)
{
    V r;
    using E = typename V::element_type;
    using U = typename V::uint_element_type;
    for (unsigned i = 0; i < V::length; i++) {
        U a1 = bit_cast<U, E>(a[i]);
        U b1 = bit_cast<U, E>(b[i]);
        r[i] = bit_cast<E, U>(a1 ^ b1);
    }
    return r;
}

template<class M>
M bit_xor_mm(M a, M b)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r[i] = (a[i] && !b[i]) || (!a[i] && b[i]);
    }
    return r;
}

template<class M>
M bit_not_mm(M a)
{
    M r;
    for (unsigned i = 0; i < M::length; i++) {
        r[i] = !a[i];
    }
    return r;
}

} // namespace null
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
