/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BITSELECT_H
#define LIBSIMDPP_SIMDPP_CORE_BITSELECT_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_select.h>
#include <simdpp/detail/get_expr_blend.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    // for each bit
    r0 = (mask0 == 0x1 ) ? on0 : off0
    ...
    rN = (maskN == 0xff ) ? onN : offN
    @endcode

    For an alternative to blend that is faster on some architectures when the mask is either
    all ones or all zeroes for each element, see blend.
*/
template<unsigned N, class V1, class V2, class V3> SIMDPP_INL
    typename detail::get_expr_blend<V1, V2, V3>::type
    bit_select(const any_vec<N,V1>& on, const any_vec<N,V2>& off,
              const any_vec<N,V3>& mask)
{
    using E = typename detail::get_expr_blend<V1, V2, V3>;
    return detail::insn::i_bit_select(typename E::v1_final_type(on.wrapped()),
                                     typename E::v2_final_type(off.wrapped()),
                                     typename E::v3_final_type(mask.wrapped()));
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

