/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_TRAITS_H
#define LIBSIMDPP_SIMDPP_TYPES_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <type_traits>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// Allows detection whether specific type is a simdpp vector
template<class T>
struct is_vector : std::false_type {};

template<unsigned N, class E> struct is_vector<float32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<float64<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<int8<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<int16<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<int32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<int64<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<uint8<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<uint16<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<uint32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<uint64<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int8<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int16<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_int64<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_float32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_vector<mask_float64<N, E>> : std::true_type {};

/// Allows detection whether specific type is a simdpp value (i.e. not expression) vector
template<class V>
struct is_value_vector : std::false_type {};

template<unsigned N> struct is_value_vector<float32<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<float64<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<int8<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<int16<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<int32<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<int64<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<uint8<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<uint16<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<uint32<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<uint64<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<mask_int8<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<mask_int16<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<mask_int32<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<mask_int64<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<mask_float32<N>> : std::true_type {};
template<unsigned N> struct is_value_vector<mask_float64<N>> : std::true_type {};

/// Allows detection whether specific type is a simdpp mask
template<class T>
struct is_mask : std::false_type {};

template<unsigned N, class E> struct is_mask<mask_int8<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_int16<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_int32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_int64<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_float32<N, E>> : std::true_type {};
template<unsigned N, class E> struct is_mask<mask_float64<N, E>> : std::true_type {};


/// Define simd_traits  
template<class valuetype>
struct simd_traits
{
    static const size_t alignment = std::alignment_of<valuetype>::value; 
};

template<>
struct simd_traits <int8_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT8_SIZE;
    using simd_type = int8<fast_size>;
    using simd_mask_type = mask_int8<fast_size>;
    static const size_t alignment = fast_size;
};

template<>
struct simd_traits <uint8_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT8_SIZE;
    using simd_type = uint8<fast_size>;
    using simd_mask_type = mask_int8<fast_size>;
    static const size_t alignment = fast_size;
};

template<>
struct simd_traits <int16_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT16_SIZE;
    using simd_type = int16<fast_size>;
    using simd_mask_type = mask_int16<fast_size>;
    static const size_t alignment = fast_size * 2;
};

template<>
struct simd_traits <uint16_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT16_SIZE;
    using simd_type = uint16<fast_size>;
    using simd_mask_type = mask_int16<fast_size>;
    static const size_t alignment = fast_size * 2;
};

template<>
struct simd_traits <int32_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT32_SIZE;
    using simd_type = int32<fast_size>;
    using simd_mask_type = mask_int32<fast_size>;
    static const size_t alignment = fast_size * 4;
};

template<>
struct simd_traits <uint32_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT32_SIZE;
    using simd_type = uint32<fast_size>;
    using simd_mask_type = mask_int32<fast_size>;
    static const size_t alignment = fast_size * 4;
};

template<>
struct simd_traits <int64_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT64_SIZE;
    using simd_type = int64<fast_size>;
    using simd_mask_type = mask_int64<fast_size>;
    static const size_t alignment = fast_size * 8;
};

template<>
struct simd_traits <uint64_t>
{
    static const size_t fast_size = SIMDPP_FAST_INT64_SIZE;
    using simd_type = uint64<fast_size>;
    using simd_mask_type = mask_int64<fast_size>;
    static const size_t alignment = fast_size * 8;
};

template<>
struct simd_traits <float>
{
    static const size_t fast_size = SIMDPP_FAST_FLOAT32_SIZE;
    using simd_type = float32<fast_size>;
    using simd_mask_type = mask_float32<fast_size>;
    static const size_t alignment = fast_size * 4;
};


template<>
struct simd_traits <double>
{
    static const size_t fast_size = SIMDPP_FAST_FLOAT64_SIZE;
    using simd_type = float64<fast_size>;
    using simd_mask_type = mask_float64<fast_size>;
    static const size_t alignment = fast_size * 8;
};

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
