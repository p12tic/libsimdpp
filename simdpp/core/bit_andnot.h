/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_ANDNOT_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_ANDNOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_andnot.h>
#include <simdpp/detail/expr/bit_andnot.h>
#include <simdpp/detail/cast_expr.h>
#include <simdpp/core/detail/get_expr_bitwise.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Computes bitwise AND NOT of two integer or floating-point vectors.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @todo: icost
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, V1, V2>::type
        bit_andnot(const any_vec<N,V1>& a, const any_vec<N,V2>& b)
{
    using expr = typename detail::get_expr_bitwise2_and<expr_bit_andnot, V1, V2>;
    return { { detail::cast_expr<typename expr::v1_type>(a.wrapped()),
               detail::cast_expr<typename expr::v2_type>(b.wrapped()) }, 0 };
}

// support scalar arguments
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint32_t>>::type, V>::type
        bit_andnot(const uint32_t& a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint32_t>>::type>(a), b);
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint64_t>>::type, V>::type
        bit_andnot(const uint64_t& a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint64_t>>::type>(a), b);
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<int32_t>>::type, V>::type
        bit_andnot(const int32_t& a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<int32_t>>::type>(a), b);
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<int64_t>>::type, V>::type
        bit_andnot(const int64_t& a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<int64_t>>::type>(a), b);
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint32_t>>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, const uint32_t& b)
{
    return bit_andnot(a, detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint32_t>>::type>(b));
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint64_t>>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, const uint64_t& b)
{
    return bit_andnot(a, detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<uint64_t>>::type>(b));
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<int32_t>>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, const int32_t& b)
{
    return bit_andnot(a, detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<int32_t>>::type>(b));
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V, expr_scalar_bitwise<int64_t>>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, const int64_t& b)
{
    return bit_andnot(a, detail::cast_expr<typename detail::get_expr_nomask<V, expr_scalar_bitwise<int64_t>>::type>(b));
}


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

