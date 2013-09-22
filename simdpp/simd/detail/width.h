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

#ifndef LIBSIMDPP_SIMD_DETAIL_WIDTH_H
#define LIBSIMDPP_SIMD_DETAIL_WIDTH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

struct vec128_impl {
    using i8  =  int8x16;
    using u8  = uint8x16;
    using b8  = basic_int8x16;
    using i16 =  int16x8;
    using u16 = uint16x8;
    using b16 = basic_int16x8;
    using i32 =  int32x4;
    using u32 = uint32x4;
    using b32 = basic_int32x4;
    using i64 =  int64x2;
    using u64 = uint64x2;
    using b64 = basic_int64x2;
    using f32 = float32x4;
    using f64 = float64x2;
};

struct vec256_impl {
    using i8  =  int8x32;
    using u8  = uint8x32;
    using b8  = basic_int8x32;
    using i16 =  int16x16;
    using u16 = uint16x16;
    using b16 = basic_int16x16;
    using i32 = int32x8;
    using u32 = uint32x8;
    using b32 = basic_int32x8;
    using i64 = int64x4;
    using u64 = uint64x4;
    using b64 = basic_int64x4;
    using f32 = float32x8;
    using f64 = float64x4;
};

template<class T> struct same_width;
template<> struct same_width<int8x16  > : vec128_impl {};
template<> struct same_width<uint8x16 > : vec128_impl {};
template<> struct same_width<basic_int8x16 > : vec128_impl {};
template<> struct same_width<int16x8  > : vec128_impl {};
template<> struct same_width<uint16x8 > : vec128_impl {};
template<> struct same_width<basic_int16x8 > : vec128_impl {};
template<> struct same_width<int32x4  > : vec128_impl {};
template<> struct same_width<uint32x4 > : vec128_impl {};
template<> struct same_width<basic_int32x4 > : vec128_impl {};
template<> struct same_width<int64x2  > : vec128_impl {};
template<> struct same_width<uint64x2 > : vec128_impl {};
template<> struct same_width<basic_int64x2 > : vec128_impl {};
template<> struct same_width<float32x4> : vec128_impl {};
template<> struct same_width<float64x2> : vec128_impl {};

template<> struct same_width< int8x32 > : vec256_impl {};
template<> struct same_width<uint8x32 > : vec256_impl {};
template<> struct same_width<basic_int8x32 > : vec256_impl {};
template<> struct same_width< int16x16> : vec256_impl {};
template<> struct same_width<uint16x16> : vec256_impl {};
template<> struct same_width<basic_int16x16> : vec256_impl {};
template<> struct same_width< int32x8 > : vec256_impl {};
template<> struct same_width<uint32x8 > : vec256_impl {};
template<> struct same_width<basic_int32x8 > : vec256_impl {};
template<> struct same_width< int64x4 > : vec256_impl {};
template<> struct same_width<uint64x4 > : vec256_impl {};
template<> struct same_width<basic_int64x4 > : vec256_impl {};
template<> struct same_width<float32x8> : vec256_impl {};
template<> struct same_width<float64x4> : vec256_impl {};

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
