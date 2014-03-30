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

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_VEC_EXTRACT_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_VEC_EXTRACT_H

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
R vec_extract_impl(V a, unsigned n)
{
    static_assert(R::length >= a.length / a.vec_length,
                  "Too small vector to extract");

    R r;
    for (unsigned i = 0; i < r.vec_length; ++i) {
        r[i] = a[n*r.vec_length + i];
    }
    return r;

}

// extract a sub-vector consisting of [M*n .. M*(n+1)) elements
template<unsigned M, unsigned N>
uint8<M> vec_extract(uint8<N> a, unsigned n) { return vec_extract_impl<uint8<M>>(a, n); }
template<unsigned M, unsigned N>
uint16<M> vec_extract(uint16<N> a, unsigned n) { return vec_extract_impl<uint16<M>>(a, n); }
template<unsigned M, unsigned N>
uint32<M> vec_extract(uint32<N> a, unsigned n) { return vec_extract_impl<uint32<M>>(a, n); }
template<unsigned M, unsigned N>
uint64<M> vec_extract(uint64<N> a, unsigned n) { return vec_extract_impl<uint64<M>>(a, n); }
template<unsigned M, unsigned N>
float32<M> vec_extract(float32<N> a, unsigned n) { return vec_extract_impl<float32<M>>(a, n); }
template<unsigned M, unsigned N>
float64<M> vec_extract(float64<N> a, unsigned n) { return vec_extract_impl<float64<M>>(a, n); }


} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
