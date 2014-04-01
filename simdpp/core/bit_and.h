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

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes bitwise AND of integer or floating-point vectors.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @todo: icost
*/
template<unsigned N, class V1, class V2>
typename detail::get_expr2<V1, V2, void>::empty
    bit_and(const any_vec<N,V1>& a, const any_vec<N,V2>& b)
{
    typename detail::get_expr2_nosign<V1, V2, void>::type ra, rb;
    ra = a.vec().eval();
    rb = b.vec().eval();
    return detail::insn::i_bit_and(ra, rb);
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

