/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BLEND_H
#define LIBSIMDPP_SIMDPP_CORE_BLEND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/eval_scalar.h>
#include <simdpp/detail/insn/blend.h>
#include <simdpp/detail/get_expr_blend.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    The result is undefined if the above requirement is not met.

    @code
    r0 = (mask0 == 0xff ) ? on0 : off0
    ...
    rN = (maskN == 0xff ) ? onN : offN
    @endcode

    For an alternative to blend that does not require all bits to be either set or not set,
    see bit_select.

    @todo icost

    @par int16

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}

    @par int32

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}

    @par int64

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}

    @par float32

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 3}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 6}
    @icost{NEON, ALTIVEC, 2}

    @par float64

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 6}
    @novec{NEON, ALTIVEC}
*/
template<unsigned N, class V1, class V2, class V3> SIMDPP_INL
typename detail::get_expr_blend<V1, V2, V3>::type
        blend(const any_vec<N,V1>& on, const any_vec<N,V2>& off,
              const any_vec<N,V3>& mask)
{
    using E = typename detail::get_expr_blend<V1, V2, V3>;
    return detail::insn::i_blend(
        detail::eval_maybe_scalar<typename E::v1_final_type, V1>::eval(on.wrapped()),
        detail::eval_maybe_scalar<typename E::v2_final_type, V2>::eval(off.wrapped()),
        detail::eval_maybe_scalar<typename E::v3_final_type, V3>::eval(mask.wrapped()));
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

