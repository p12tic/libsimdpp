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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_TRAITS_H
#define LIBSIMDPP_SIMDPP_DETAIL_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

/*  Normalizes vector type. Removes sign from a vector type.
 */
template<class V> struct remove_sign { using type = V; using expr = V; };

template<unsigned N, class E> struct remove_sign<int8<N,E>> { using type = uint8<N>;   using expr = uint8<N,E>; };
template<unsigned N, class E> struct remove_sign<int16<N,E>> { using type = uint16<N>; using expr = uint16<N,E>; };
template<unsigned N, class E> struct remove_sign<int32<N,E>> { using type = uint32<N>; using expr = uint32<N,E>; };
template<unsigned N, class E> struct remove_sign<int64<N,E>> { using type = uint64<N>; using expr = uint64<N,E>; };

/*  Normalizes vector type. Removes sign from a vector type. Result type is a
    value type, not an expression.
 */
template<class V> struct remove_mask { using type = V; using expr = V; };

template<unsigned N, class E> struct remove_mask<mask_int8<N,E>> { using type = uint8<N>;   using expr = uint8<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_int16<N,E>> { using type = uint16<N>; using expr = uint16<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_int32<N,E>> { using type = uint32<N>; using expr = uint32<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_int64<N,E>> { using type = uint64<N>; using expr = uint64<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_float32<N,E>> { using type = float32<N>; using expr = float32<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_float64<N,E>> { using type = float64<N>; using expr = float64<N,E>; };

/*
template<class V> struct remove_mask { using type = V; using expr = V; };

template<unsigned N, class E> struct remove_mask<mask_int8<N,E>> { using type = uint8<N>;   using expr = uint8<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_int16<N,E>> { using type = uint16<N>; using expr = uint16<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_int32<N,E>> { using type = uint32<N>; using expr = uint32<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_int64<N,E>> { using type = uint64<N>; using expr = uint64<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_float32<N,E>> { using type = float32<N>; using expr = float32<N,E>; };
template<unsigned N, class E> struct remove_mask<mask_float64<N,E>> { using type = float64<N>; using expr = float64<N,E>; };

*/


} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
