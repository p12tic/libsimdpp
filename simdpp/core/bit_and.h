/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_AND_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_AND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_and.h>
#include <simdpp/detail/expr/bit_and.h>
#include <simdpp/detail/get_expr.h>
#include <simdpp/core/detail/get_expr_bitwise.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Computes bitwise AND of integer or floating-point vectors.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @todo: icost
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class V1, class V2>
_PROMOTED_EXPRESSION_ bit_and(const any_vec<N,V1>& a,
                              const any_vec<N,V2>& b);
#else
template<unsigned N, class V1, class V2>
typename detail::get_expr_bitwise2_and<expr_bit_and, V1, V2>::type
        bit_and(const any_vec<N,V1>& a,
                const any_vec<N,V2>& b)
{
    using expr = detail::get_expr_bitwise2_and<expr_bit_and, V1, V2>;
    return { { typename expr::v1_type(a.vec()),
               typename expr::v2_type(b.vec()) }, 0 };
}
#endif

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

