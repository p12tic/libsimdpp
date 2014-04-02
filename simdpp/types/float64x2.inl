/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64X2_INL
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64X2_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/float64x2.h>
#include <simdpp/detail/mem_block.h>
#include <simdpp/detail/word_size.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/permute2.h>
#include <simdpp/detail/null/mask.h>
#include <simdpp/detail/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline float64<2> float64<2>::zero() { return make_uint(0); }

inline float64<2> mask_float64<2>::unmask() const
{
#if SIMDPP_USE_NULL
    return detail::null::unmask_mask<float64<2>>(*this);
#else
    return float64<2>(d_);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
