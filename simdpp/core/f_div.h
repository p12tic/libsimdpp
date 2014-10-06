/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_DIV_H
#define LIBSIMDPP_SIMDPP_CORE_F_DIV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_div.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Divides the values of two vectors.

    @code
    r0 = a0 / b0
    ...
    rN = aN / bN
    @endcode

    @icost{NEON, 6}
    @icost{ALTIVEC, 10}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 12}
    @icost{ALTIVEC, 19}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
float32<N, _DETAIL_> div(float32<N,E1> a,
                         float32<N,E2> b);
#else
template<unsigned N, class E1, class E2> SIMDPP_INL
float32<N, float32<N>> div(float32<N,E1> a, float32<N,E2> b)
{
    return detail::insn::i_div(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(div, float32, float32)

/** Divides the values of two vectors

    @code
    r0 = a0 / b0
    ...
    rN = aN / bN
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
float64<N, _DETAIL_> div(float64<N,E1> a,
                         float64<N,E2> b);
#else
template<unsigned N, class E1, class E2> SIMDPP_INL
float64<N, float64<N>> div(float64<N,E1> a, float64<N,E2> b)
{
    return detail::insn::i_div(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(div, float64, float64)

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

