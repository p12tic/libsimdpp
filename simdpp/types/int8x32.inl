/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X32_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT8X32_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int8x32.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline int8<32>   int8<32>::zero() { return make_uint(0); }
inline uint8<32> uint8<32>::zero() { return make_uint(0); }
inline int8<32>   int8<32>::ones() { return make_uint(0xff); }
inline uint8<32> uint8<32>::ones() { return make_uint(0xff); }

inline uint8<32> mask_int8<32>::unmask() const
{
#if SIMDPP_USE_NULL
    return null::unmask_mask<uint8<32>>(*this);
#else
    return uint8<32>(d_);
#endif
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
