/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_GET_EXPR_H
#define LIBSIMDPP_SIMDPP_DETAIL_GET_EXPR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/expr.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/tag.h>
#include <simdpp/expr.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

/*  The tag values are selected specifically to make this class template
    simpler.

    See simdpp/types/tag.h

    Note that B refers to the number of elements in the resulting vector. Since
    get_expr2 always selects elements with smaller number of (wider) elements,
    one only needs to ensure that B refers to the function argument with widest
    elements among the function arguments.
*/

template<unsigned Tag, unsigned B, class E> struct type_of_tag;
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_INT + SIMDPP_TAG_SIZE8, B, E>     { typedef int8<B,E> type;       typedef int8<B,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_INT + SIMDPP_TAG_SIZE16, B, E>    { typedef int16<B/2,E> type;    typedef int16<B/2,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_INT + SIMDPP_TAG_SIZE32, B, E>    { typedef int32<B/4,E> type;    typedef int32<B/4,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_INT + SIMDPP_TAG_SIZE64, B, E>    { typedef int64<B/8,E> type;    typedef int64<B/8,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_UINT + SIMDPP_TAG_SIZE8, B, E>    { typedef uint8<B,E> type;      typedef uint8<B,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_UINT + SIMDPP_TAG_SIZE16, B, E>   { typedef uint16<B/2,E> type;   typedef uint16<B/2,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_UINT + SIMDPP_TAG_SIZE32, B, E>   { typedef uint32<B/4,E> type;   typedef uint32<B/4,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_UINT + SIMDPP_TAG_SIZE64, B, E>   { typedef uint64<B/8,E> type;   typedef uint64<B/8,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_MASK_INT + SIMDPP_TAG_SIZE8, B, E>    { typedef mask_int8<B,E> type;    typedef mask_int8<B,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_MASK_INT + SIMDPP_TAG_SIZE16, B, E>   { typedef mask_int16<B/2,E> type; typedef mask_int16<B/2,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_MASK_INT + SIMDPP_TAG_SIZE32, B, E>   { typedef mask_int32<B/4,E> type; typedef mask_int32<B/4,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_MASK_INT + SIMDPP_TAG_SIZE64, B, E>   { typedef mask_int64<B/8,E> type; typedef mask_int64<B/8,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_FLOAT + SIMDPP_TAG_SIZE32, B, E>      { typedef float32<B/4,E> type;    typedef float32<B/4,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_FLOAT + SIMDPP_TAG_SIZE64, B, E>      { typedef float64<B/8,E> type;    typedef float64<B/8,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_MASK_FLOAT + SIMDPP_TAG_SIZE32, B, E> { typedef mask_float32<B/4,E> type; typedef mask_float32<B/4,expr_empty> empty; };
template<unsigned B, class E> struct type_of_tag<SIMDPP_TAG_MASK_FLOAT + SIMDPP_TAG_SIZE64, B, E> { typedef mask_float64<B/8,E> type; typedef mask_float64<B/8,expr_empty> empty; };

template<class V1, class V2>
struct expr2_maybe_scalar_tags {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<int, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<long, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<long long, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<unsigned, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<unsigned long, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<unsigned long long, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<float, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V2>
struct expr2_maybe_scalar_tags<double, V2> {
    static const unsigned v1_type_tag = V2::type_tag;
    static const unsigned v1_size_tag = V2::size_tag;
    static const unsigned v2_type_tag = V2::type_tag;
    static const unsigned v2_size_tag = V2::size_tag;
    static const unsigned length_bytes = V2::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, int> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, long> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, long long> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, unsigned> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, unsigned long> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, unsigned long long> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, float> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V1>
struct expr2_maybe_scalar_tags<V1, double> {
    static const unsigned v1_type_tag = V1::type_tag;
    static const unsigned v1_size_tag = V1::size_tag;
    static const unsigned v2_type_tag = V1::type_tag;
    static const unsigned v2_size_tag = V1::size_tag;
    static const unsigned length_bytes = V1::length_bytes;
};

template<class V, class E = void>
class get_expr {
public:
    typedef typename type_of_tag<V::type_tag + V::size_tag, V::length_bytes, E>::type type;
    typedef typename type_of_tag<V::type_tag + V::size_tag, V::length_bytes, E>::empty empty;
};

template<class V, class E = void>
class get_expr_nomask {
    static const unsigned type_tag = (V::type_tag == SIMDPP_TAG_MASK_FLOAT) ? SIMDPP_TAG_FLOAT :
                                     (V::type_tag == SIMDPP_TAG_MASK_INT) ? SIMDPP_TAG_UINT : V::type_tag;
public:
    typedef typename type_of_tag<type_tag + V::size_tag, V::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + V::size_tag, V::length_bytes, E>::empty empty;
};

template<class V, class E = void>
class get_expr_nosign {
    static const unsigned type_tag = (V::type_tag == SIMDPP_TAG_INT) ? SIMDPP_TAG_UINT : V::type_tag;
public:
    typedef typename type_of_tag<type_tag + V::size_tag, V::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + V::size_tag, V::length_bytes, E>::empty empty;
};

template<class V, class E = void>
class get_expr_nomask_nosign {
    static const unsigned type_tag = (V::type_tag == SIMDPP_TAG_MASK_FLOAT) ? SIMDPP_TAG_FLOAT :
                                     (V::type_tag == SIMDPP_TAG_INT) ? SIMDPP_TAG_UINT :
                                     (V::type_tag == SIMDPP_TAG_MASK_INT) ? SIMDPP_TAG_UINT : V::type_tag;
public:
    typedef typename type_of_tag<type_tag + V::size_tag, V::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + V::size_tag, V::length_bytes, E>::empty empty;
};

template<class V1, class V2>
class get_expr2_same {
    typedef expr2_maybe_scalar_tags<V1, V2> tags;
public:
    typedef typename type_of_tag<tags::v1_type_tag + tags::v1_size_tag,
                                 tags::length_bytes, void>::type v1_final_type;
    typedef typename type_of_tag<tags::v2_type_tag + tags::v2_size_tag,
                                 tags::length_bytes, void>::type v2_final_type;
};

template<class V1, class V2, class E = void>
class get_expr2 {
    static const bool is_mask_op = (V1::type_tag == SIMDPP_TAG_MASK_FLOAT || V1::type_tag == SIMDPP_TAG_MASK_INT) &&
                                   (V2::type_tag == SIMDPP_TAG_MASK_FLOAT || V2::type_tag == SIMDPP_TAG_MASK_INT);
    static const unsigned size_tag = V1::size_tag > V2::size_tag ? V1::size_tag : V2::size_tag;
    static const unsigned type_tag = (is_mask_op && V1::size_tag != V2::size_tag) ? SIMDPP_TAG_UINT :
                                                  (V1::type_tag > V2::type_tag ? V1::type_tag : V2::type_tag);

public:
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::empty empty;
};



template<class V1, class V2, class E = void>
class get_expr2_nomask {
    static const unsigned type_tag_t1 = V1::type_tag > V2::type_tag ? V1::type_tag : V2::type_tag;

    static const unsigned size_tag = V1::size_tag > V2::size_tag ? V1::size_tag : V2::size_tag;
    static const unsigned type_tag = (type_tag_t1 == SIMDPP_TAG_MASK_FLOAT) ? SIMDPP_TAG_FLOAT :
                                        (type_tag_t1 == SIMDPP_TAG_MASK_INT) ? SIMDPP_TAG_UINT : type_tag_t1;

public:
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::empty empty;
};

template<class V1, class V2, class E = void>
class get_expr2_nosign {
    static const unsigned type_tag_t1 = V1::type_tag > V2::type_tag ? V1::type_tag : V2::type_tag;

public:
    static const unsigned size_tag = V1::size_tag > V2::size_tag ? V1::size_tag : V2::size_tag;
    static const unsigned type_tag = (type_tag_t1 == SIMDPP_TAG_INT) ? SIMDPP_TAG_UINT : type_tag_t1;

    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::empty empty;
};


template<class V1, class V2, class E = void>
class get_expr2_nomask_nosign {
    static const unsigned type_tag_t1 = V1::type_tag > V2::type_tag ? V1::type_tag : V2::type_tag;
    static const bool is_mask_op = type_tag_t1 == SIMDPP_TAG_MASK_FLOAT || type_tag_t1 == SIMDPP_TAG_MASK_INT;

    static const unsigned size_tag = V1::size_tag > V2::size_tag ? V1::size_tag : V2::size_tag;
    static const unsigned type_tag = (is_mask_op && V1::size_tag != V2::size_tag) ? SIMDPP_TAG_UINT :
                                     (type_tag_t1 == SIMDPP_TAG_INT) ? SIMDPP_TAG_UINT : type_tag_t1;

public:
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::type type;
    typedef typename type_of_tag<type_tag + size_tag, V1::length_bytes, E>::empty empty;
};


} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
