/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_MUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_F_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_mul.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
float32<N> expr_eval_mul(const float32<N,E1>& qa,
                         const float32<N,E2>& qb)
{
    return insn::i_fmul(qa.eval(), qb.eval());
}

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
float64<N> expr_eval_mul(const float64<N,E1>& qa,
                         const float64<N,E2>& qb)
{
    return insn::i_fmul(qa.eval(), qb.eval());
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

