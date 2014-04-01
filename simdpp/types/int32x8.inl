/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X8_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int32x8.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline int32<8> int32<8>::zero() { return make_uint(0); }
inline uint32<8> uint32<8>::zero() { return make_uint(0); }
inline int32<8> int32<8>::ones() { return make_uint(0xffffffff); }
inline uint32<8> uint32<8>::ones() { return make_uint(0xffffffff); }

inline uint32<8> mask_int32<8>::unmask() const
{
#if SIMDPP_USE_NULL
    return null::unmask_mask<uint32<8>>(*this);
#else
    return uint32<8>(d_);
#endif
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
