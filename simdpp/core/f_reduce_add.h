/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_REDUCE_ADD_H
#define LIBSIMDPP_SIMDPP_CORE_F_REDUCE_ADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_reduce_add.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/** Computes the sum of the elements in the vector.

    @code
    r0 = a0 + a1 + a2 + ...
    @endcode
*/
template<unsigned N> SIMDPP_INL
float reduce_add(const float32<N>& a)
{
    return detail::insn::i_reduce_add(a);
}

template<unsigned N> SIMDPP_INL
double reduce_add(const float64<N>& a)
{
    return detail::insn::i_reduce_add(a);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

