/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>
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

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_VEC_INSERT_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_VEC_INSERT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types.h>

#include <cstring>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class R, class V>
void vec_insert_impl(R& a, V x, unsigned n)
{
    static_assert(x.length > a.length / a.vec_length,
                  "Too small vector to insert");

    for (unsigned i = 0; i < x.vec_length; ++i) {
        a[n*x.vec_length + i] = x[i]; //TODO combine or split as needed
    }
}

// Sets the elements [M*n .. M*(n+1)) of @a a to the contents of @a x
template<unsigned N, unsigned M>
void vec_insert(gint8<N>& a, gint8<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(gint16<N>& a, gint16<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(gint32<N>& a, gint32<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(gint64<N>& a, gint64<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(float32<N>& a, float32<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(float64<N>& a, float64<M> x, unsigned n) { vec_insert_impl(a, x, n); }

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
