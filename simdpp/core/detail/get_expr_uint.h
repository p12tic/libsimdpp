/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_GET_EXPR_UINT_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_GET_EXPR_UINT_H

#include <simdpp/detail/get_expr.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {


/*  We want to reduce the number of overloads that need to be created in order
    to match a specific case of an expression tree containing various integer
    operation nodes, such as add(int), mul_lo(int), etc. For particular
    vector size each of these operations are equivalent regardless of the
    argument types. Thus we simply convert the arguments of the expression to
    uint expressions of certain configuration.

    As a result, the following tuples of types will appear as the arguments
     of the returned expression:

      * uint8, uint8
      * uint16, uint16
      * uint32, uint32
      * uint64, uint64
*/

template<template<class, class> class E, class V1, class V2>
class get_expr_uint {

#if SIMDPP_EXPR_DEBUG
    SIMDPP_STATIC_ASSERT(V1::size_tag == V2::size_tag, "Mismatching vector sizes");
    SIMDPP_STATIC_ASSERT(V1::type_tag == SIMDPP_TAG_MASK_INT ||
                  V1::type_tag == SIMDPP_TAG_UINT ||
                  V1::type_tag == SIMDPP_TAG_INT, "Incorrect type parameter");
    SIMDPP_STATIC_ASSERT(V2::type_tag == SIMDPP_TAG_MASK_INT ||
                  V2::type_tag == SIMDPP_TAG_UINT ||
                  V2::type_tag == SIMDPP_TAG_INT, "Incorrect type parameter");
#endif

    // the size tag of the expression
    static const unsigned size_tag = V1::size_tag;

    // (type_tag) get the type tag of the expression. Pretty much the same as
    // get_expr2_nomask does
    static const unsigned type_tag_t1 = V1::type_tag > V2::type_tag ? V1::type_tag : V2::type_tag;
    static const unsigned type_tag = (type_tag_t1 == SIMDPP_TAG_MASK_INT) ? SIMDPP_TAG_UINT : type_tag_t1;

    // strip signed integer types and masks
    static const unsigned v1_type_tag = SIMDPP_TAG_UINT;
    static const unsigned v2_type_tag = SIMDPP_TAG_UINT;

public:
    typedef typename type_of_tag<v1_type_tag + size_tag, V1::length_bytes,
                                         typename wrap_vector_expr<V1>::type>::type v1_type;
    typedef typename type_of_tag<v2_type_tag + size_tag, V1::length_bytes,
                                         typename wrap_vector_expr<V2>::type>::type v2_type;

    typedef E<v1_type, v2_type> expr_type;

    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes,
                                 E<v1_type, v2_type> >::type type;
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
