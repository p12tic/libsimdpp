/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_FMADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_FMADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_fmadd.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, unsigned N, class E1, class E2, class E3> SIMDPP_INL
float32<N> expr_eval_fmadd(const float32<N,E1>& qa,
                           const float32<N,E2>& qb,
                           const float32<N,E3>& qc)
{
    return insn::i_fmadd(qa.eval(), qb.eval(), qc.eval());
}

template<class R, unsigned N, class E1, class E2, class E3> SIMDPP_INL
float64<N> expr_eval_fmadd(const float64<N,E1>& qa,
                           const float64<N,E2>& qb,
                           const float64<N,E3>& qc)
{
    return insn::i_fmadd(qa.eval(), qb.eval(), qc.eval());
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

