/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_FMADD_H
#define LIBSIMDPP_SIMDPP_CORE_F_FMADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_fmadd.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Performs a fused multiply-add operation

    @code
    r0 = a0 * b0 + c0
    ...
    rN = aN * bN + cN
    @endcode

    Implemented only on architectures with either @c X86_FMA3 or @c X86_FMA4
    support.
*/
template<unsigned N, class E1, class E2, class E3> SIMDPP_INL
float32<N, expr_empty> fmadd(const float32<N,E1>& a,
                             const float32<N,E2>& b,
                             const float32<N,E3>& c)
{
    return detail::insn::i_fmadd(a.eval(), b.eval(), c.eval());
}

template<unsigned N, class E1, class E2, class E3> SIMDPP_INL
float64<N, expr_empty> fmadd(const float64<N,E1>& a,
                             const float64<N,E2>& b,
                             const float64<N,E3>& c)
{
    return detail::insn::i_fmadd(a.eval(), b.eval(), c.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

