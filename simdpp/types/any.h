/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_ANY_H
#define LIBSIMDPP_SIMDPP_TYPES_ANY_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/fwd.h>
#include <stdint.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @ingroup simd_vec_any
/// @{

/** Represents any vector that has @a B bytes of data. The exact vector type is
    @a V.
*/
template<unsigned B, class V>
struct any_vec {
    static const unsigned length_bytes = B;
    typedef V type;

    /// @{
    /// Returns the wrapped vector
    SIMDPP_INL V& wrapped() { return static_cast<V&>(*this); }
    SIMDPP_INL const V& wrapped() const { return static_cast<const V&>(*this); }
    /// @}
};

template<unsigned N, class V> struct any_vec8 : any_vec<N, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE8;
};
template<unsigned N, class V> struct any_vec16 : any_vec<N*2, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE16;
};
template<unsigned N, class V> struct any_vec32 : any_vec<N*4, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE32;
};
template<unsigned N, class V> struct any_vec64 : any_vec<N*8, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE64;
};

template<unsigned N, class V>
struct any_float32 : any_vec32<N, V>
{
    static const unsigned length = N;
    static const unsigned base_length = SIMDPP_FAST_FLOAT32_SIZE;
    static const unsigned vec_length = (N + SIMDPP_FAST_FLOAT32_SIZE - 1) / SIMDPP_FAST_FLOAT32_SIZE;
    typedef float element_type;
    typedef uint32_t uint_element_type;
    typedef int32<N> int_vector_type;
    typedef uint32<N> uint_vector_type;
    typedef mask_float32<N> mask_vector_type;
    static const unsigned num_bits = 32;
    static const uint_element_type all_bits = 0xffffffff;
};

template<unsigned N, class V>
struct any_float64 : any_vec64<N, V>
{
    static const unsigned length = N;
    static const unsigned base_length = SIMDPP_FAST_FLOAT64_SIZE;
    static const unsigned vec_length = (N + SIMDPP_FAST_FLOAT64_SIZE - 1) / SIMDPP_FAST_FLOAT64_SIZE;
    typedef double element_type;
    typedef uint64_t uint_element_type;
    typedef int64<N> int_vector_type;
    typedef uint64<N> uint_vector_type;
    typedef mask_float64<N> mask_vector_type;
    static const unsigned num_bits = 64;
    static const uint_element_type all_bits = 0xffffffffffffffff;
};

template<unsigned N, class V>
struct any_int8 : any_vec8<N, V>
{
    static const unsigned length = N;
    static const unsigned base_length = SIMDPP_FAST_INT8_SIZE;
    static const unsigned vec_length = (N + SIMDPP_FAST_INT8_SIZE - 1) / SIMDPP_FAST_INT8_SIZE;
    typedef uint8_t uint_element_type;
    typedef int8<N> int_vector_type;
    typedef uint8<N> uint_vector_type;
    typedef mask_int8<N> mask_vector_type;

    static const unsigned num_bits = 8;
    static const uint_element_type all_bits = 0xff;
};

template<unsigned N, class V>
struct any_int16 : any_vec16<N, V>
{
    static const unsigned length = N;
    static const unsigned base_length = SIMDPP_FAST_INT16_SIZE;
    static const unsigned vec_length = (N + SIMDPP_FAST_INT16_SIZE - 1) / SIMDPP_FAST_INT16_SIZE;
    typedef uint16_t uint_element_type;
    typedef int16<N> int_vector_type;
    typedef uint16<N> uint_vector_type;
    typedef mask_int16<N> mask_vector_type;

    static const unsigned num_bits = 16;
    static const uint_element_type all_bits = 0xffff;
};

template<unsigned N, class V>
struct any_int32 : any_vec32<N, V>
{
    static const unsigned length = N;
    static const unsigned base_length = SIMDPP_FAST_INT32_SIZE;
    static const unsigned vec_length = (N + SIMDPP_FAST_INT32_SIZE - 1) / SIMDPP_FAST_INT32_SIZE;
    typedef uint32_t uint_element_type;
    typedef int32<N> int_vector_type;
    typedef uint32<N> uint_vector_type;
    typedef mask_int32<N> mask_vector_type;

    static const unsigned num_bits = 32;
    static const uint_element_type all_bits = 0xffffffff;
};

template<unsigned N, class V>
struct any_int64 : any_vec64<N, V>
{
    static const unsigned length = N;
    static const unsigned base_length = SIMDPP_FAST_INT64_SIZE;
    static const unsigned vec_length = (N + SIMDPP_FAST_INT64_SIZE - 1) / SIMDPP_FAST_INT64_SIZE;
    typedef uint64_t uint_element_type;
    typedef int64<N> int_vector_type;
    typedef uint64<N> uint_vector_type;
    typedef mask_int64<N> mask_vector_type;

    static const unsigned num_bits = 64;
    static const uint_element_type all_bits = 0xffffffffffffffff;
};

/// @} -- end ingroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
