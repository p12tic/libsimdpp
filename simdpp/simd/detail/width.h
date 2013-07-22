/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_DETAIL_WIDTH_H
#define LIBSIMDPP_SIMD_DETAIL_WIDTH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
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
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
