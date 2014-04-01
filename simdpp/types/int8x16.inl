/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X16_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT8X16_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int8x16.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/altivec/load1.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline int8<16>   int8<16>::zero() { return make_uint(0); }
inline uint8<16> uint8<16>::zero() { return make_uint(0); }
inline int8<16>   int8<16>::ones() { return make_uint(0xff); }
inline uint8<16> uint8<16>::ones() { return make_uint(0xff); }

inline uint8<16> mask_int8<16>::unmask() const
{
#if SIMDPP_USE_NULL
    return null::unmask_mask<uint8<16>>(*this);
#else
    return uint8<16>(d_);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
