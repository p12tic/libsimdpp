/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_TRAITS_H
#define LIBSIMDPP_SIMDPP_TYPES_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <type_traits>
namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// Allows detection whether specific type is a simdpp vector
template<class T>
struct is_vector : std::false_type {};

template<unsigned N, class E> struct is_vector<float32<N,E>>   : std::true_type {};
template<unsigned N, class E> struct is_vector<float64<N,E>>   : std::true_type {};
template<unsigned N, class E> struct is_vector<int8<N,E>>      : std::true_type {};
template<unsigned N, class E> struct is_vector<int16<N,E>>     : std::true_type {};
template<unsigned N, class E> struct is_vector<int32<N,E>>     : std::true_type {};
template<unsigned N, class E> struct is_vector<int64<N,E>>     : std::true_type {};
template<unsigned N, class E> struct is_vector<uint8<N,E>>     : std::true_type {};
template<unsigned N, class E> struct is_vector<uint16<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_vector<uint32<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_vector<uint64<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int8<N,E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int16<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int32<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int64<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_float32<N,E>>  : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_float64<N,E>>  : std::true_type {};

/// Allows detection whether specific type is a simdpp mask
template<class T>
struct is_mask : std::false_type {};

template<unsigned N, class E> struct is_mask<mask_int8<N,E>>    : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_int16<N,E>>   : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_int32<N,E>>   : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_int64<N,E>>   : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_float32<N,E>> : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_float64<N,E>> : std::true_type {};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
