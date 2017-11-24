/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_UTILS_ELEMENT_TYPE_H
#define LIBSIMDPP_TEST_UTILS_ELEMENT_TYPE_H

#include <simdpp/simd.h>
#include <cstdint>

// Types of vector elements
enum ElementType : uint8_t {
    TYPE_INT8 = 0,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_UINT32,
    TYPE_INT32,
    TYPE_UINT64,
    TYPE_INT64,
    TYPE_FLOAT32,
    TYPE_FLOAT64
};

// Returns size of the element of a vector of given type
static inline std::size_t element_size_for_type(ElementType t)
{
    switch (t) {
    case TYPE_INT8:
    case TYPE_UINT8: return 1;
    case TYPE_INT16:
    case TYPE_UINT16: return 2;
    case TYPE_UINT32:
    case TYPE_INT32: return 4;
    case TYPE_UINT64:
    case TYPE_INT64: return 8;
    case TYPE_FLOAT32: return 4;
    case TYPE_FLOAT64: return 8;
    }
    std::abort();
    return 0;
}

template<class V> struct GetElementType {
    static_assert(sizeof(V) <= 8, "Unsupported element size");
    static const ElementType value = sizeof(V) == 1 ? TYPE_UINT8 :
                                     sizeof(V) == 2 ? TYPE_UINT16 :
                                     sizeof(V) == 4 ? TYPE_UINT32 : TYPE_UINT64;
};
template<unsigned N, class E>
struct GetElementType<simdpp::uint8<N,E>> { static const ElementType value = TYPE_UINT8; };
template<unsigned N, class E>
struct GetElementType<simdpp::int8<N,E>> { static const ElementType value = TYPE_INT8; };
template<unsigned N, class E>
struct GetElementType<simdpp::uint16<N,E>> { static const ElementType value = TYPE_UINT16; };
template<unsigned N, class E>
struct GetElementType<simdpp::int16<N,E>> { static const ElementType value = TYPE_INT16; };
template<unsigned N, class E>
struct GetElementType<simdpp::uint32<N,E>> { static const ElementType value = TYPE_UINT32; };
template<unsigned N, class E>
struct GetElementType<simdpp::int32<N,E>> { static const ElementType value = TYPE_INT32; };
template<unsigned N, class E>
struct GetElementType<simdpp::float32<N,E>> { static const ElementType value = TYPE_FLOAT32; };
template<unsigned N, class E>
struct GetElementType<simdpp::uint64<N,E>> { static const ElementType value = TYPE_UINT64; };
template<unsigned N, class E>
struct GetElementType<simdpp::int64<N,E>> { static const ElementType value = TYPE_INT64; };
template<unsigned N, class E>
struct GetElementType<simdpp::float64<N,E>> { static const ElementType value = TYPE_FLOAT64; };

template<> struct GetElementType<uint8_t>  { static const ElementType value = TYPE_UINT8; };
template<> struct GetElementType<int8_t>   { static const ElementType value = TYPE_INT8; };
template<> struct GetElementType<uint16_t> { static const ElementType value = TYPE_UINT16; };
template<> struct GetElementType<int16_t>  { static const ElementType value = TYPE_INT16; };
template<> struct GetElementType<uint32_t> { static const ElementType value = TYPE_UINT32; };
template<> struct GetElementType<int32_t>  { static const ElementType value = TYPE_INT32; };
template<> struct GetElementType<float>    { static const ElementType value = TYPE_FLOAT32; };
template<> struct GetElementType<uint64_t> { static const ElementType value = TYPE_UINT64; };
template<> struct GetElementType<int64_t>  { static const ElementType value = TYPE_INT64; };
template<> struct GetElementType<double>   { static const ElementType value = TYPE_FLOAT64; };

#endif
