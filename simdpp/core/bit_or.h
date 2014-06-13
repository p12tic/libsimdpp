/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_OR_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_OR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_or.h>
#include <simdpp/detail/expr/bit_or.h>
#include <simdpp/core/detail/get_expr_bitwise.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Computes bitwise OR of integer vectors.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @todo icost
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class V1, class V2>
_PROMOTED_EXPRESSION_ bit_or(const any_vec<N,V1>& a,
                             const any_vec<N,V2>& b);
#else
template<unsigned N, class V1, class V2>
typename detail::get_expr_bit_or<V1, V2>::type
        bit_or(const any_vec<N,V1>& a, const any_vec<N,V2>& b)
{
    using expr = detail::get_expr_bit_or<V1, V2>;
    return { { typename expr::v12_type(a.wrapped()),
               typename expr::v12_type(b.wrapped()) }, 0 };
}
#endif

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


