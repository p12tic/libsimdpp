/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_ADD_SAT_H
#define LIBSIMDPP_SIMDPP_CORE_I_ADD_SAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_add_sat.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/** Adds and saturates signed 8-bit integer values.

    @code
    r0 = signed_saturate(a0 + b0)
    ...
    rN = signed_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N> SIMDPP_INL
int8<N> add_sat(const int8<N>& a, const int8<N>& b)
{
    return detail::insn::i_add_sat(a.eval(), b.eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC(add_sat, int8, int8)

/** Adds and saturates signed 16-bit integer values.

    @code
    r0 = signed_saturate(a0 + b0)
    ...
    rN = signed_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N> SIMDPP_INL
int16<N> add_sat(const int16<N>& a, const int16<N>& b)
{
    return detail::insn::i_add_sat(a.eval(), b.eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC(add_sat, int16, int16)

/** Adds and saturates unsigned 8-bit integer values.

    @code
    r0 = unsigned_saturate(a0 + b0)
    ...
    rN = unsigned_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N> SIMDPP_INL
uint8<N> add_sat(const uint8<N>& a, const uint8<N>& b)
{
    return detail::insn::i_add_sat(a.eval(), b.eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC(add_sat, uint8, uint8)

/** Adds and saturates unsigned 16-bit integer values.

    @code
    r0 = unsigned_saturate(a0 + b0)
    ...
    rN = unsigned_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N> SIMDPP_INL
uint16<N> add_sat(const uint16<N>& a, const uint16<N>& b)
{
    return detail::insn::i_add_sat(a.eval(), b.eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC(add_sat, uint16, uint16)

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

