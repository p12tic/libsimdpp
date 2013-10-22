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

#ifndef LIBSIMDPP_NULL_SET_H
#define LIBSIMDPP_NULL_SET_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

template<class V>
V set_broadcast(V& a, typename V::element_type x)
{
    for (unsigned i = 0; i < V::length; i++) {
        a[i] = x;
    }
    return a;
}

template<class V, class E = typename V::element_type>
V make_vec(E v0)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = v0;
    }
    return r;
}

template<class V, class E = typename V::element_type>
V make_vec(E v0, E v1)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=2) {
        r[i] = v0;
        r[i+1] = v1;
    }
    return r;
}

template<class V, class E = typename V::element_type>
V make_vec(E v0, E v1, E v2, E v3)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=4) {
        r[i] = v0;
        r[i+1] = v1;
        r[i+2] = v2;
        r[i+3] = v3;
    }
    return r;
}

template<class V, class E = typename V::element_type>
V make_vec(E v0, E v1, E v2, E v3, E v4, E v5, E v6, E v7)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=8) {
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

template<class V, class E = typename V::element_type>
V make_vec(E v0, E v1, E v2, E v3, E v4, E v5, E v6, E v7,
           E v8, E v9, E v10, E v11, E v12, E v13, E v14, E v15)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=16) {
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
