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

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_RESULT_OF_ANY_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_RESULT_OF_ANY_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

struct float_tag {};
struct mask_float_tag {};
struct int_tag {};
struct uint_tag {};
struct mask_int_tag {};

template<class T1, class T2, unsigned N, class E> struct result_of_any8;
template<unsigned N, class E> struct result_of_any8<int_tag, int_tag, N, E>             { using type = int8<N,E>; };
template<unsigned N, class E> struct result_of_any8<int_tag, uint_tag, N, E>            { using type = uint8<N,E>; };
template<unsigned N, class E> struct result_of_any8<int_tag, mask_int_tag, N, E>        { using type = int8<N,E>; };
template<unsigned N, class E> struct result_of_any8<uint_tag, int_tag, N, E>            { using type = uint8<N,E>; };
template<unsigned N, class E> struct result_of_any8<uint_tag, uint_tag, N, E>           { using type = uint8<N,E>; };
template<unsigned N, class E> struct result_of_any8<uint_tag, mask_int_tag, N, E>       { using type = uint8<N,E>; };
template<unsigned N, class E> struct result_of_any8<mask_int_tag, int_tag, N, E>        { using type = int8<N,E>; };
template<unsigned N, class E> struct result_of_any8<mask_int_tag, uint_tag, N, E>       { using type = uint8<N,E>; };
template<unsigned N, class E> struct result_of_any8<mask_int_tag, mask_int_tag, N, E>   { using type = mask_int8<N,E>; };

template<class T1, class T2, unsigned N, class E> struct result_of_any16;
template<unsigned N, class E> struct result_of_any16<int_tag, int_tag, N, E>            { using type = int16<N,E>; };
template<unsigned N, class E> struct result_of_any16<int_tag, uint_tag, N, E>           { using type = uint16<N,E>; };
template<unsigned N, class E> struct result_of_any16<int_tag, mask_int_tag, N, E>       { using type = int16<N,E>; };
template<unsigned N, class E> struct result_of_any16<uint_tag, int_tag, N, E>           { using type = uint16<N,E>; };
template<unsigned N, class E> struct result_of_any16<uint_tag, uint_tag, N, E>          { using type = uint16<N,E>; };
template<unsigned N, class E> struct result_of_any16<uint_tag, mask_int_tag, N, E>      { using type = uint16<N,E>; };
template<unsigned N, class E> struct result_of_any16<mask_int_tag, int_tag, N, E>       { using type = int16<N,E>; };
template<unsigned N, class E> struct result_of_any16<mask_int_tag, uint_tag, N, E>      { using type = uint16<N,E>; };
template<unsigned N, class E> struct result_of_any16<mask_int_tag, mask_int_tag, N, E>  { using type = mask_int16<N,E>; };

template<class T1, class T2, unsigned N, class E> struct result_of_any32;
template<unsigned N, class E> struct result_of_any32<int_tag, int_tag, N, E>            { using type = int32<N,E>; };
template<unsigned N, class E> struct result_of_any32<int_tag, uint_tag, N, E>           { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<int_tag, mask_int_tag, N, E>       { using type = int32<N,E>; };
template<unsigned N, class E> struct result_of_any32<int_tag, float_tag, N, E>          { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<int_tag, mask_float_tag, N, E>     { using type = int32<N,E>; };
template<unsigned N, class E> struct result_of_any32<uint_tag, int_tag, N, E>           { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<uint_tag, uint_tag, N, E>          { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<uint_tag, mask_int_tag, N, E>      { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<uint_tag, float_tag, N, E>         { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<uint_tag, mask_float_tag, N, E>    { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_int_tag, int_tag, N, E>       { using type = int32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_int_tag, uint_tag, N, E>      { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_int_tag, mask_int_tag, N, E>  { using type = mask_int32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_int_tag, float_tag, N, E>     { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_int_tag, mask_float_tag, N, E> { using type = mask_float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<float_tag, int_tag, N, E>          { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<float_tag, uint_tag, N, E>         { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<float_tag, mask_int_tag, N, E>     { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<float_tag, float_tag, N, E>        { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<float_tag, mask_float_tag, N, E>   { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_float_tag, int_tag, N, E>     { using type = int32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_float_tag, uint_tag, N, E>    { using type = uint32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_float_tag, mask_int_tag, N, E> { using type = mask_float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_float_tag, float_tag, N, E>   { using type = float32<N,E>; };
template<unsigned N, class E> struct result_of_any32<mask_float_tag, mask_float_tag, N, E> { using type = mask_float32<N,E>; };

template<class T1, class T2, unsigned N, class E> struct result_of_any64;
template<unsigned N, class E> struct result_of_any64<int_tag, int_tag, N, E>            { using type = int64<N,E>; };
template<unsigned N, class E> struct result_of_any64<int_tag, uint_tag, N, E>           { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<int_tag, mask_int_tag, N, E>       { using type = int64<N,E>; };
template<unsigned N, class E> struct result_of_any64<int_tag, float_tag, N, E>          { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<int_tag, mask_float_tag, N, E>     { using type = int64<N,E>; };
template<unsigned N, class E> struct result_of_any64<uint_tag, int_tag, N, E>           { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<uint_tag, uint_tag, N, E>          { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<uint_tag, mask_int_tag, N, E>      { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<uint_tag, float_tag, N, E>         { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<uint_tag, mask_float_tag, N, E>    { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_int_tag, int_tag, N, E>       { using type = int64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_int_tag, uint_tag, N, E>      { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_int_tag, mask_int_tag, N, E>  { using type = mask_int64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_int_tag, float_tag, N, E>     { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_int_tag, mask_float_tag, N, E> { using type = mask_float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<float_tag, int_tag, N, E>          { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<float_tag, uint_tag, N, E>         { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<float_tag, mask_int_tag, N, E>     { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<float_tag, float_tag, N, E>        { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<float_tag, mask_float_tag, N, E>   { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_float_tag, int_tag, N, E>     { using type = int64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_float_tag, uint_tag, N, E>    { using type = uint64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_float_tag, mask_int_tag, N, E> { using type = mask_float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_float_tag, float_tag, N, E>   { using type = float64<N,E>; };
template<unsigned N, class E> struct result_of_any64<mask_float_tag, mask_float_tag, N, E> { using type = mask_float64<N,E>; };

template<class T1, class T2, class V1, class V2> struct result_of_any;


} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
