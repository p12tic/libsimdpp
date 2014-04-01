/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/float32x4.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/splat.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline float32<4> float32<4>::zero() { return make_uint(0); }

inline float32<4> mask_float32<4>::unmask() const
{
#if SIMDPP_USE_NULL
    return null::unmask_mask<float32<4>>(*this);
#else
    return float32<4>(d_);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
