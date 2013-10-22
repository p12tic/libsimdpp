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

#ifndef LIBSIMDPP_NULL_MEMORY_H
#define LIBSIMDPP_NULL_MEMORY_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

template<class V>
V load(V& a, const void* p)
{
    using T = typename V::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        a[i] = *pt++;
    }
    return a;
}

template<class V>
void load_packed2(V& a, V& b, const void* p)
{
    using T = typename V::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        a[i] = *pt++;
        b[i] = *pt++;
    }
}

template<class V>
void load_packed3(V& a, V& b, V& c, const void* p)
{
    using T = typename V::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        a[i] = *pt++;
        b[i] = *pt++;
        c[i] = *pt++;
    }
}

template<class V>
void load_packed4(V& a, V& b, V& c, V& d, const void* p)
{
    using T = typename V::element_type;
    const T* pt = reinterpret_cast<const T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        a[i] = *pt++;
        b[i] = *pt++;
        c[i] = *pt++;
        d[i] = *pt++;
    }
}

template<class V>
void store(void* p, V a)
{
    using T = typename V::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        *pt++ = a[i];
    }
}

template<class V>
void store_first(void* p, V a, unsigned n)
{
    using T = typename V::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < V::length && i < n; i++) {
        *pt++ = a[i];
    }
}

template<class V>
void store_last(void* p, V a, unsigned n)
{
    using T = typename V::element_type;
    T* pt = reinterpret_cast<T*>(p);
    pt += V::length - n;
    for (unsigned i = V::length - n; i < V::length; i++) {
        *pt++ = a[i];
    }
}

template<class V>
void store_packed2(void* p, V& a, V& b)
{
    using T = typename V::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        *pt++ = a[i];
        *pt++ = b[i];
    }
}

template<class V>
void store_packed3(void* p, V& a, V& b, V& c)
{
    using T = typename V::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        *pt++ = a[i];
        *pt++ = b[i];
        *pt++ = c[i];
    }
}

template<class V>
void store_packed4(void* p, V& a, V& b, V& c, V& d)
{
    using T = typename V::element_type;
    T* pt = reinterpret_cast<T*>(p);
    for (unsigned i = 0; i < V::length; i++) {
        *pt++ = a[i];
        *pt++ = b[i];
        *pt++ = c[i];
        *pt++ = d[i];
    }
}

} // namespace null
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
