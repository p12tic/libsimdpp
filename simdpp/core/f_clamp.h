/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_CLAMP_H
#define LIBSIMDPP_SIMDPP_CORE_F_CLAMP_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/f_min.h>
#include <simdpp/core/f_max.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/** Clamps value to a range.
    Effectively applies std::clamp(v, lo, hi) for each element in the vector

    @code
    r0 = clamp(v0, lo0, hi0)
    ...
    rN = clamp(vN, loN, hiN)
    @endcode
*/
template<unsigned N> SIMDPP_INL
    float32<N> clamp(const float32<N>& v, const float32<N>& lo, const float32<N>& hi)
{
    return max(min(v, hi), lo);
}
template<unsigned N> SIMDPP_INL
    float64<N> clamp(const float64<N>& v, const float64<N>& lo, const float64<N>& hi)
{
    return max(min(v, hi), lo);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

