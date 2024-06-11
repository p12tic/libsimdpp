/*  Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_VECTOR_ARRAY_MACROS_H
#define LIBSIMDPP_SIMDPP_DETAIL_VECTOR_ARRAY_MACROS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<unsigned I, unsigned End>
struct vec_array_impl {
    template<class R, class V, class Op>
    static SIMDPP_INL void apply1(R& dst, const V& src, Op&& op)
    {
        dst.template vec<I>() = op(src.template vec<I>());
        vec_array_impl<I + 1, End>::apply1(dst, src, op);
    }

    template<class R, class V1, class V2, class Op>
    static SIMDPP_INL void apply2(R& dst, const V1& src1, const V2& src2, Op&& op)
    {
        dst.template vec<I>() = op(src1.template vec<I>(), src2.template vec<I>());
        vec_array_impl<I + 1, End>::apply2(dst, src1, src2, op);
    }

    template<class R, class V1, class S2, class Op>
    static SIMDPP_INL void apply2_scalar(R& dst, const V1& src1, const S2& src2, Op&& op)
    {
        dst.template vec<I>() = op(src1.template vec<I>(), src2);
        vec_array_impl<I + 1, End>::apply2_scalar(dst, src1, src2, op);
    }

    template<class R, class V1, class V2, class V3, class Op>
    static SIMDPP_INL void apply3(R& dst, const V1& src1, const V2& src2, const V3& src3, Op&& op)
    {
        dst.template vec<I>() = op(src1.template vec<I>(),
                                   src2.template vec<I>(),
                                   src3.template vec<I>());
        vec_array_impl<I + 1, End>::apply3(dst, src1, src2, src3, op);
    }

    template<class V1, class V2, class Op>
    static SIMDPP_INL void apply2_ref(V1& v1, V2& v2, Op&& op)
    {
        op(v1.template vec<I>(), v2.template vec<I>());
        vec_array_impl<I + 1, End>::apply2_ref(v1, v2, op);
    }

    template<class V1, class V2, class V3, class V4, class Op>
    static SIMDPP_INL void apply4_ref(V1& v1, V2& v2, V3& v3, V4& v4, Op&& op)
    {
        op(v1.template vec<I>(), v2.template vec<I>(), v3.template vec<I>(), v4.template vec<I>());
        vec_array_impl<I + 1, End>::apply4_ref(v1, v2, v3, v4, op);
    }
};

template<unsigned End>
struct vec_array_impl<End, End> {
    template<class R, class V, class Op>
    static SIMDPP_INL void apply1(R&, const V&, Op&&) {}

    template<class R, class V1, class V2, class Op>
    static SIMDPP_INL void apply2(R&, const V1&, const V2&, Op&&) {}

    template<class R, class V1, class S2, class Op>
    static SIMDPP_INL void apply2_scalar(R&, const V1&, const S2&, Op&&) {}

    template<class R, class V1, class V2, class V3, class Op>
    static SIMDPP_INL void apply3(R&, const V1&, const V2&, const V3&, Op&&) {}

    template<class V1, class V2, class Op>
    static SIMDPP_INL void apply2_ref(V1&, V2&, Op&&) {}

    template<class V1, class V2, class V3, class V4, class Op>
    static SIMDPP_INL void apply4_ref(V1&, V2&, V3&, V4&, Op&&) {}
};

#define SIMDPP_VEC_ARRAY_IMPL1(RTYPE, VTYPE, OP, V1)                                    \
    RTYPE r;                                                                            \
    detail::vec_array_impl<0, VTYPE::vec_length>::apply1(                               \
        r, V1, [](const auto& v) { return OP(v); });                                    \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL2(RTYPE, VTYPE, OP, V1, V2)                                \
    RTYPE r;                                                                            \
    detail::vec_array_impl<0, VTYPE::vec_length>::apply2(                               \
        r, V1, V2, [](const auto& v1, const auto& v2) { return OP(v1, v2); });          \
    return r;


#define SIMDPP_VEC_ARRAY_IMPL2S(RTYPE, VTYPE, OP, V1, S2)                               \
    RTYPE r;                                                                            \
    detail::vec_array_impl<0, VTYPE::vec_length>::apply2_scalar(                        \
        r, V1, S2, [](const auto& v1, const auto& v2) { return OP(v1, v2); });          \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL3(RTYPE, VTYPE, OP, V1, V2, V3)                            \
    RTYPE r;                                                                            \
    detail::vec_array_impl<0, VTYPE::vec_length>::apply3(                               \
        r, V1, V2, V3, [](const auto& v1, const auto& v2, const auto& v3)               \
                       { return OP(v1, v2, v3); });                                     \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL_REF2(RTYPE, VTYPE, OP, V1, V2)                            \
    detail::vec_array_impl<0, VTYPE::vec_length>::apply2_ref(                           \
        V1, V2, [](auto& v1, auto& v2) { OP(v1, v2); });

#define SIMDPP_VEC_ARRAY_IMPL_REF4(RTYPE, VTYPE, OP, V1, V2, V3, V4)                    \
    detail::vec_array_impl<0, VTYPE::vec_length>::apply4_ref(                           \
        V1, V2, V3, V4, [](auto& v1, auto& v2, auto& v3, auto& v4) { OP(v1, v2, v3, v4); });

} // namespace detail
} // SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
