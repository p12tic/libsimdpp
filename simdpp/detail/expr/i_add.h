/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_add.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint8<N> expr_eval_add(const uint8<N,E1>& qa,
                       const uint8<N,E2>& qb)
{
    return insn::i_iadd(qa.eval(), qb.eval());
}

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval_add(const uint16<N,E1>& qa,
                        const uint16<N,E2>& qb)
{
    return insn::i_iadd(qa.eval(), qb.eval());
}

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint32<N> expr_eval_add(const uint32<N,E1>& qa,
                        const uint32<N,E2>& qb)
{
    return insn::i_iadd(qa.eval(), qb.eval());
}

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint64<N> expr_eval_add(const uint64<N,E1>& qa,
                        const uint64<N,E2>& qb)
{
    return insn::i_iadd(qa.eval(), qb.eval());
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

