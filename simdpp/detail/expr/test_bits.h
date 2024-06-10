/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_TEST_BITS_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_TEST_BITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/expr.h>
#include <simdpp/detail/insn/test_bits.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<unsigned N, class V> SIMDPP_INL
bool e_test_bits_any(const any_vec<N,V>& a)
{
    typename detail::get_expr_nosign<V>::type ra;
    ra = a.wrapped().eval();
    return insn::i_test_bits_any(ra);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
