/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_COPYSIGN_H
#define LIBSIMDPP_SIMDPP_CORE_F_COPYSIGN_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_select.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Copies sign of one number to another number

    @code
    r0 = std::copysign(m0, s0)
    ...
    rN = std::copysign(mN, sN)
    @endcode
*/
template<unsigned N> SIMDPP_INL
    float32<N> copysign(const float32<N>& m, const float32<N>& s)
{
    uint32<N> mask = make_uint(0x80000000);
    return bit_select(s, m, mask);
}

template<unsigned N> SIMDPP_INL
    float64<N> copysign(const float64<N>& m, const float64<N>& s)
{
    uint64<N> mask = make_uint(0x8000000000000000);
    return bit_select(s, m, mask);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

