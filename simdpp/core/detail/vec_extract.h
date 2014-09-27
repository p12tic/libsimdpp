/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_VEC_EXTRACT_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_VEC_EXTRACT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types.h>
#include <simdpp/core/insert.h>
#include <simdpp/core/extract.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class R, class V>
R vec_extract_impl(V a, unsigned n)
{
    static_assert(R::length >= V::base_length, "Too small vector to extract");

    R r;
    for (unsigned i = 0; i < r.vec_length; ++i) {
        r.vec(i) = a.vec(n*r.vec_length + i);
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
int8<M> vec_extract(int8<N> a, unsigned n) { return vec_extract_impl<int8<M>>(a, n); }
template<unsigned M, unsigned N>
int16<M> vec_extract(int16<N> a, unsigned n) { return vec_extract_impl<int16<M>>(a, n); }
template<unsigned M, unsigned N>
int32<M> vec_extract(int32<N> a, unsigned n) { return vec_extract_impl<int32<M>>(a, n); }
template<unsigned M, unsigned N>
int64<M> vec_extract(int64<N> a, unsigned n) { return vec_extract_impl<int64<M>>(a, n); }

template<unsigned M, unsigned N>
float32<M> vec_extract(float32<N> a, unsigned n) { return vec_extract_impl<float32<M>>(a, n); }
template<unsigned M, unsigned N>
float64<M> vec_extract(float64<N> a, unsigned n) { return vec_extract_impl<float64<M>>(a, n); }


} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
