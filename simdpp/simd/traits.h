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

#ifndef LIBSIMDPP_SIMD_TRAITS_H
#define LIBSIMDPP_SIMD_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// Allows detection whether specific type is a simdpp vector
template<class T>
struct is_vector { static constexpr bool value = false; };

template<> class is_vector<float32x4>   { static constexpr bool value = true; };
template<> class is_vector<float64x2>   { static constexpr bool value = true; };
template<> class is_vector<float32x8>   { static constexpr bool value = true; };
template<> class is_vector<float64x4>   { static constexpr bool value = true; };
template<> class is_vector<int128>      { static constexpr bool value = true; };
template<> class is_vector<int256>      { static constexpr bool value = true; };
template<> class is_vector<int8x16>     { static constexpr bool value = true; };
template<> class is_vector<int16x8>     { static constexpr bool value = true; };
template<> class is_vector<int32x4>     { static constexpr bool value = true; };
template<> class is_vector<int64x2>     { static constexpr bool value = true; };
template<> class is_vector<int8x32>     { static constexpr bool value = true; };
template<> class is_vector<int16x16>    { static constexpr bool value = true; };
template<> class is_vector<int32x8>     { static constexpr bool value = true; };
template<> class is_vector<int64x4>     { static constexpr bool value = true; };
template<> class is_vector<uint8x16>    { static constexpr bool value = true; };
template<> class is_vector<uint16x8>    { static constexpr bool value = true; };
template<> class is_vector<uint32x4>    { static constexpr bool value = true; };
template<> class is_vector<uint64x2>    { static constexpr bool value = true; };
template<> class is_vector<uint8x32>    { static constexpr bool value = true; };
template<> class is_vector<uint16x16>   { static constexpr bool value = true; };
template<> class is_vector<uint32x8>    { static constexpr bool value = true; };
template<> class is_vector<uint64x4>    { static constexpr bool value = true; };
template<> class is_vector<basic_int8x16>   { static constexpr bool value = true; };
template<> class is_vector<basic_int16x8>   { static constexpr bool value = true; };
template<> class is_vector<basic_int32x4>   { static constexpr bool value = true; };
template<> class is_vector<basic_int64x2>   { static constexpr bool value = true; };
template<> class is_vector<basic_int8x32>   { static constexpr bool value = true; };
template<> class is_vector<basic_int16x16>  { static constexpr bool value = true; };
template<> class is_vector<basic_int32x8>   { static constexpr bool value = true; };
template<> class is_vector<basic_int64x4>   { static constexpr bool value = true; };

/// Allows detection whether specific type is a simdpp mask
template<class T>
struct is_mask { static constexpr bool value = false; };

template<> class is_mask<mask_int8x16>  { static constexpr bool value = true; };
template<> class is_mask<mask_int8x32>  { static constexpr bool value = true; };
template<> class is_mask<mask_int16x8>  { static constexpr bool value = true; };
template<> class is_mask<mask_int16x16> { static constexpr bool value = true; };
template<> class is_mask<mask_int32x4>  { static constexpr bool value = true; };
template<> class is_mask<mask_int32x8>  { static constexpr bool value = true; };
template<> class is_mask<mask_int64x2>  { static constexpr bool value = true; };
template<> class is_mask<mask_int64x4>  { static constexpr bool value = true; };
template<> class is_mask<mask_float32x4> { static constexpr bool value = true; };
template<> class is_mask<mask_float32x8> { static constexpr bool value = true; };
template<> class is_mask<mask_float64x2> { static constexpr bool value = true; };
template<> class is_mask<mask_float64x4> { static constexpr bool value = true; };

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
