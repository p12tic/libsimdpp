/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X16_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT16X16_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int16x16.h>
#include <simdpp/detail/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline int16<16>   int16<16>::zero() { return make_uint(0); }
inline uint16<16> uint16<16>::zero() { return make_uint(0); }
inline int16<16>   int16<16>::ones() { return make_uint(0xffff); }
inline uint16<16> uint16<16>::ones() { return make_uint(0xffff); }

inline uint16<16> mask_int16<16>::unmask() const
{
#if SIMDPP_USE_NULL
    return detail::null::unmask_mask<uint16<16>>(*this);
#else
    return uint16<16>(d_);
#endif
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
