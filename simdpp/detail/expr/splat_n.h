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
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N, unsigned s, class E>
uint8<N> expr_eval(expr_splat16<s,uint8<N,E>> q)
{
    uint8<N> a = q.a.eval();
    return insn::i_splat16<s>(a);
}

template<unsigned N, unsigned s, class E>
uint16<N> expr_eval(expr_splat8<s,uint16<N,E>> q)
{
    uint16<N> a = q.a.eval();
    return insn::i_splat8<s>(a);
}

template<unsigned N, unsigned s, class E>
uint32<N> expr_eval(expr_splat4<s,uint32<N,E>> q)
{
    uint32<N> a = q.a.eval();
    return insn::i_splat4<s>(a);
}

template<unsigned N, unsigned s, class E>
uint64<N> expr_eval(expr_splat2<s,uint64<N,E>> q)
{
    uint64<N> a = q.a.eval();
    return insn::i_splat2<s>(a);
}

template<unsigned N, unsigned s, class E>
float32<N> expr_eval(expr_splat4<s,float32<N,E>> q)
{
    float32<N> a = q.a.eval();
    return insn::i_splat4<s>(a);
}

template<unsigned N, unsigned s, class E>
float64<N> expr_eval(expr_splat2<s,float64<N,E>> q)
{
    float64<N> a = q.a.eval();
    return insn::i_splat2<s>(a);
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

