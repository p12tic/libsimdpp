/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_OR_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_OR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_or.h>
#include <simdpp/detail/expr/bit_or.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Computes bitwise OR of integer vectors.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @todo icost
*/
template<unsigned N, class V1, class V2>
typename detail::get_expr2<V1, V2, void>::empty
        bit_or(const any_vec<N,V1>& a, const any_vec<N,V2>& b)
{
    typename detail::get_expr2_nosign<V1, V2, void>::type ra, rb;
    ra = a.vec().eval();
    rb = b.vec().eval();
    return detail::insn::i_bit_or(ra, rb);
}

/* FIXME
template<unsigned N, class E1, class E2>
uint32<N, expr_bit_or<uint32<N,E1>,
                      mask_int32<N,E2>>> bit_or(uint32<N,E1> a,
                                                mask_int32<N,E2> b)
{
    return { { a, b }, 0 };
}

template<unsigned N, class E1, class E2>
uint64<N, expr_bit_or<uint64<N,E1>,
                      mask_int64<N,E2>>> bit_or(uint64<N,E1> a,
                                                mask_int64<N,E2> b)
{
    return { { a, b }, 0 };
}

template<unsigned N, class E1, class E2>
float32<N, expr_bit_or<float32<N,E1>,
                       mask_float32<N,E2>>>
        bit_or(float32<N,E1> a, mask_float32<N,E2> b)
{
    return { { a, b }, 0 };
}

template<unsigned N, class E1, class E2>
float64<N, expr_bit_or<float64<N,E1>,
                       mask_float64<N,E2>>> bit_or(float64<N,E1> a, mask_float64<N,E2> b)
{
    return { { a, b }, 0 };
}
*/
/// @}
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


