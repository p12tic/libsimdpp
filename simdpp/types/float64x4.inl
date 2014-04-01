/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/float64x4.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX

inline float64<4> float64<4>::zero() { return make_uint(0); }

inline float64<4> mask_float64<4>::unmask() const
{
#if SIMDPP_USE_NULL
    return null::unmask_mask<float64<4>>(*this);
#else
    return float64<4>(d_);
#endif
}

#endif // SIMDPP_USE_AVX

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
