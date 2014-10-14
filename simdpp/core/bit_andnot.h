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
    return { { typename expr::v1_type(a.wrapped()),
               typename expr::v2_type(b.wrapped()) }, 0 };
}

// support scalar arguments
// support scalar arguments
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(uint32_t a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::make_const<detail::get_expr_nomask<V>::type>(a), b);
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(uint64_t a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::make_const<detail::get_expr_nomask<V>::type>(a), b);
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(int32_t a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::make_const<detail::get_expr_nomask<V>::type>(uint32_t(a)), b);
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(int64_t a, const any_vec<N,V>& b)
{
    return bit_andnot(detail::make_const<detail::get_expr_nomask<V>::type>(a), b);
}

template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, uint32_t b)
{
    return bit_andnot(a, detail::make_const<typename detail::get_expr_nomask<V>::type>(b));
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, uint64_t b)
{
    return bit_andnot(a, detail::make_const<typename detail::get_expr_nomask<V>::type>(b));
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, int32_t b)
{
    return bit_andnot(a, detail::make_const<typename detail::get_expr_nomask<V>::type>(uint32_t(b)));
}
template<unsigned N, class V> SIMDPP_INL
typename detail::get_expr_bitwise2_and<expr_bit_andnot, typename detail::get_expr_nomask<V>::type, V>::type
        bit_andnot(const any_vec<N,V>& a, int64_t b)
{
    return bit_andnot(a, detail::make_const<typename detail::get_expr_nomask<V>::type>(b));
}


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

