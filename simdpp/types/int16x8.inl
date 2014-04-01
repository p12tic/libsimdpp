/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X8_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT16X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int16x8.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline int16<8>   int16<8>::zero() { return make_uint(0); }
inline uint16<8> uint16<8>::zero() { return make_uint(0); }
inline int16<8>   int16<8>::ones() { return make_uint(0xffff); }
inline uint16<8> uint16<8>::ones() { return make_uint(0xffff); }

inline uint16<8> mask_int16<8>::unmask() const
{
#if SIMDPP_USE_NULL
    return null::unmask_mask<uint16<8>>(*this);
#else
    return uint16<8>(d_);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
