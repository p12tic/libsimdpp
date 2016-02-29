/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_WIDTH_H
#define LIBSIMDPP_SIMDPP_DETAIL_WIDTH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

struct vec128_impl {
    typedef  int8x16 i8 ;
    typedef uint8x16 u8 ;
    typedef  int16x8 i16;
    typedef uint16x8 u16;
    typedef  int32x4 i32;
    typedef uint32x4 u32;
    typedef  int64x2 i64;
    typedef uint64x2 u64;
    typedef float32x4 f32;
    typedef float64x2 f64;
};

struct vec256_impl {
    typedef  int8x32 i8 ;
    typedef uint8x32 u8 ;
    typedef  int16x16 i16;
    typedef uint16x16 u16;
    typedef int32x8 i32;
    typedef uint32x8 u32;
    typedef int64x4 i64;
    typedef uint64x4 u64;
    typedef float32x8 f32;
    typedef float64x4 f64;
};

template<class T> struct same_width;
template<> struct same_width<int8x16  > : vec128_impl {};
template<> struct same_width<uint8x16 > : vec128_impl {};
template<> struct same_width<int16x8  > : vec128_impl {};
template<> struct same_width<uint16x8 > : vec128_impl {};
template<> struct same_width<int32x4  > : vec128_impl {};
template<> struct same_width<uint32x4 > : vec128_impl {};
template<> struct same_width<int64x2  > : vec128_impl {};
template<> struct same_width<uint64x2 > : vec128_impl {};
template<> struct same_width<float32x4> : vec128_impl {};
template<> struct same_width<float64x2> : vec128_impl {};

template<> struct same_width< int8x32 > : vec256_impl {};
template<> struct same_width<uint8x32 > : vec256_impl {};
template<> struct same_width< int16x16> : vec256_impl {};
template<> struct same_width<uint16x16> : vec256_impl {};
template<> struct same_width< int32x8 > : vec256_impl {};
template<> struct same_width<uint32x8 > : vec256_impl {};
template<> struct same_width< int64x4 > : vec256_impl {};
template<> struct same_width<uint64x4 > : vec256_impl {};
template<> struct same_width<float32x8> : vec256_impl {};
template<> struct same_width<float64x4> : vec256_impl {};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
