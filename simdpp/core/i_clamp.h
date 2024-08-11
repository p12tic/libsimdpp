/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_CLAMP_H
#define LIBSIMDPP_SIMDPP_CORE_I_CLAMP_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_min.h>
#include <simdpp/core/i_max.h>

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
    uint8<N> clamp(const uint8<N>& v, const uint8<N>& lo, const uint8<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    int8<N> clamp(const int8<N>& v, const int8<N>& lo, const int8<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    uint16<N> clamp(const uint16<N>& v, const uint16<N>& lo, const uint16<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    int16<N> clamp(const int16<N>& v, const int16<N>& lo, const int16<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    uint32<N> clamp(const uint32<N>& v, const uint32<N>& lo, const uint32<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    int32<N> clamp(const int32<N>& v, const int32<N>& lo, const int32<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    uint64<N> clamp(const uint64<N>& v, const uint64<N>& lo, const uint64<N>& hi)
{
    return max(min(v, hi), lo);
}

template<unsigned N> SIMDPP_INL
    int64<N> clamp(const int64<N>& v, const int64<N>& lo, const int64<N>& hi)
{
    return max(min(v, hi), lo);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

