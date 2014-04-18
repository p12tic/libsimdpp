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
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N,
         template<unsigned, class> class V1, class E1,
         template<unsigned, class> class V2, class E2>
V1<N,void> expr_eval(expr_bit_andnot<V1<N,E1>, V2<N,E2>> q)
{
    return (V1<N,void>) insn::i_bit_andnot(q.a.eval(), q.b.eval());
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
