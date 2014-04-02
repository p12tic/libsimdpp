/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT64X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int64x4.h>
#include <simdpp/types/float64x4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline int64<4>   int64<4>::zero() { return make_uint(0); }
inline uint64<4> uint64<4>::zero() { return make_uint(0); }
inline int64<4>   int64<4>::ones() { return make_uint(0xffffffffffffffff); }
inline uint64<4> uint64<4>::ones() { return make_uint(0xffffffffffffffff); }

inline uint64<4> mask_int64<4>::unmask() const
{
#if SIMDPP_USE_NULL
    return detail::null::unmask_mask<uint64<4>>(*this);
#else
    return uint64<4>(d_);
#endif
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
