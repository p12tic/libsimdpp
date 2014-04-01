/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
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
void vec_insert(uint8<N>& a, uint8<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(uint16<N>& a, uint16<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(uint32<N>& a, uint32<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(uint64<N>& a, uint64<M> x, unsigned n) { vec_insert_impl(a, x, n); }

template<unsigned N, unsigned M>
void vec_insert(int8<N>& a, int8<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(int16<N>& a, int16<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(int32<N>& a, int32<M> x, unsigned n) { vec_insert_impl(a, x, n); }
template<unsigned N, unsigned M>
void vec_insert(int64<N>& a, int64<M> x, unsigned n) { vec_insert_impl(a, x, n); }

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
