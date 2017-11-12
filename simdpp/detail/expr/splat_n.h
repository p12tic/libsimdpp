/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_BROADCAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_BROADCAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/splat_n.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, unsigned s, unsigned N, class E> SIMDPP_INL
uint8<N> expr_eval_splat16(const uint8<N,E>& qa)
{
    uint8<N> a = qa.eval();
    return insn::i_splat16<s>(a);
}

template<class R, unsigned s, unsigned N, class E> SIMDPP_INL
uint16<N> expr_eval_splat8(const uint16<N,E>& qa)
{
    uint16<N> a = qa.eval();
    return insn::i_splat8<s>(a);
}

template<class R, unsigned s, unsigned N, class E> SIMDPP_INL
uint32<N> expr_eval_splat4(const uint32<N,E>& qa)
{
    uint32<N> a = qa.eval();
    return insn::i_splat4<s>(a);
}

template<class R, unsigned s, unsigned N, class E> SIMDPP_INL
uint64<N> expr_eval_splat2(const uint64<N,E>& qa)
{
    uint64<N> a = qa.eval();
    return insn::i_splat2<s>(a);
}

template<class R, unsigned s, unsigned N, class E> SIMDPP_INL
float32<N> expr_eval_splat4(const float32<N,E>& qa)
{
    float32<N> a = qa.eval();
    return insn::i_splat4<s>(a);
}

template<class R, unsigned s, unsigned N, class E> SIMDPP_INL
float64<N> expr_eval_splat2(const float64<N,E>& qa)
{
    float64<N> a = qa.eval();
    return insn::i_splat2<s>(a);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

