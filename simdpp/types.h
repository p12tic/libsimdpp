/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_H
#define LIBSIMDPP_SIMDPP_TYPES_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>

#include <simdpp/expr.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int8x16.h>
#include <simdpp/types/int8x32.h>
#include <simdpp/types/int8x64.h>
#include <simdpp/types/int16x8.h>
#include <simdpp/types/int16x16.h>
#include <simdpp/types/int16x32.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/types/int32x8.h>
#include <simdpp/types/int32x16.h>
#include <simdpp/types/int64x2.h>
#include <simdpp/types/int64x4.h>
#include <simdpp/types/int64x8.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/types/float32x16.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/float64x4.h>
#include <simdpp/types/float64x8.h>
#include <simdpp/types/int8.h>
#include <simdpp/types/int16.h>
#include <simdpp/types/int32.h>
#include <simdpp/types/int64.h>
#include <simdpp/types/float32.h>
#include <simdpp/types/float64.h>
#include <simdpp/types/generic.h>
#include <simdpp/types/empty_expr.h>

#define SIMDPP_VEC_ARRAY_IMPL1(RTYPE, OP, V1)                   \
    RTYPE r; for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i)); }                           \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL2(RTYPE, OP, V1, V2)               \
    RTYPE r; for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i), (V2).vec(i)); }              \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL2S(RTYPE, OP, V1, A2)              \
    RTYPE r; for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i), (A2)); }                     \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL3(RTYPE, OP, V1, V2, V3)           \
    RTYPE r; for (unsigned i = 0; i < r.vec_length; ++i) { \
        r.vec(i) = OP((V1).vec(i), (V2).vec(i), (V3).vec(i));   \
    }                                                           \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL_REF1(RTYPE, OP, V1)               \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) {          \
        OP((V1).vec(i)); }

#define SIMDPP_VEC_ARRAY_IMPL_REF2(RTYPE, OP, V1, V2)           \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) {          \
        OP((V1).vec(i), (V2).vec(i)); }

#define SIMDPP_VEC_ARRAY_IMPL_REF3(RTYPE, OP, V1, V2, V3)       \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) {          \
        OP((V1).vec(i), (V2).vec(i), (V3).vec(i)); }

#define SIMDPP_VEC_ARRAY_IMPL_REF4(RTYPE, OP, V1, V2, V3, V4)   \
    for (unsigned i = 0; i < RTYPE::vec_length; ++i) {          \
        OP((V1).vec(i), (V2).vec(i), (V3).vec(i), (V4).vec(i)); }

// Used when the native vector of source vector corresponds to multiple native
// vectors in the destination vector. This happens when a vector type of
// smaller element size is converted to a vector type with larger element size
#define SIMDPP_VEC_ARRAY_IMPL_CONV_INSERT(RTYPE, OP, A)                         \
    RTYPE r; for (unsigned i = 0; i < (A).vec_length; ++i) {                    \
        detail::subvec_insert(r, OP(a.vec(i)), i); }                            \
    return r;

// Used when the native vector of destination vector corresponds to multiple
// native vectors in the source vector. This happens when a vector type of
// larger element size is converted to a vector type with smaller element size.
#define SIMDPP_VEC_ARRAY_IMPL_CONV_EXTRACT(RTYPE, OP, A)                        \
    RTYPE r; for (unsigned i = 0; i < r.vec_length; ++i) {                      \
        r.vec(i) = OP(detail::subvec_extract<RTYPE::base_length>((A), i)); }    \
    return r;

#endif
