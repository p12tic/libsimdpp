/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ABS_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ABS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_abs.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, unsigned N, class E> SIMDPP_INL
uint8<N> expr_eval_abs(const int8<N,E>& qa)
{
    return insn::i_iabs(qa.eval());
}

template<class R, unsigned N, class E> SIMDPP_INL
uint16<N> expr_eval_abs(const int16<N,E>& qa)
{
    return insn::i_iabs(qa.eval());
}

template<class R, unsigned N, class E> SIMDPP_INL
uint32<N> expr_eval_abs(const int32<N,E>& qa)
{
    return insn::i_iabs(qa.eval());
}

template<class R, unsigned N, class E> SIMDPP_INL
uint64<N> expr_eval_abs(const int64<N,E>& qa)
{
    return insn::i_iabs(qa.eval());
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

