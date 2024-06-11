/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_ISFINITE_H
#define LIBSIMDPP_SIMDPP_CORE_ISFINITE_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>
#include <simdpp/detail/vector_array_macros.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Checks whether elements in @a a are IEEE754 NaN or infinity.

    @code
    r0 = isnan(a0) || isinf(a0) ? 0xffffffff : 0
    ...
    rN = isnan(aN) || isinf(aN) ? 0xffffffff : 0
    @endcode
*/
template<unsigned N> SIMDPP_INL
    mask_float32<N> isfinite(const float32<N>& a)
{
#if SIMDPP_USE_NULL
    SIMDPP_VEC_ARRAY_IMPL1(mask_float32<N>, float32<N>, detail::null::isfinite, a);
#else
    return (a - a) == make_zero<float32<N>>();
#endif
}

/** Checks whether elements in @a a are IEEE754 NaN.

    @code
    r0 = isnan(a0) || isinf(a0) ? 0xffffffff'ffffffff : 0
    ...
    rN = isnan(aN) || isinf(aN) ? 0xffffffff'ffffffff : 0
    @endcode
*/
template<unsigned N> SIMDPP_INL
    mask_float64<N> isfinite(const float64<N>& a)
{
#if SIMDPP_USE_NULL
    SIMDPP_VEC_ARRAY_IMPL1(mask_float64<N>, float64<N>, detail::null::isfinite, a);
#else
    return (a - a) == make_zero<float64<N>>();
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

