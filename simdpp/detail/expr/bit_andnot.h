/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_BIT_ANDNOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_BIT_ANDNOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_andnot.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N, class E1, class E2>
uint32<N> expr_eval(expr_bit_andnot<uint32<N,E1>,
                                    mask_int32<N,E2>> q)
{
    uint32<N> a = q.a.eval();
    mask_int32<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

template<unsigned N, class E1, class E2>
uint64<N> expr_eval(expr_bit_andnot<uint64<N,E1>,
                                    mask_int64<N,E2>> q)
{
    uint64<N> a = q.a.eval();
    mask_int64<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

template<unsigned N, class E1, class E2>
float32<N> expr_eval(expr_bit_andnot<float32<N,E1>,
                                     mask_float32<N,E2>> q)
{
    float32<N> a = q.a.eval();
    mask_float32<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

template<unsigned N, class E1, class E2>
float64<N> expr_eval(expr_bit_andnot<float64<N,E1>,
                                     mask_float64<N,E2>> q)
{
    float64<N> a = q.a.eval();
    mask_float64<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
