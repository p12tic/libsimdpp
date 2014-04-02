/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int32x4.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/permute4.h>
#include <simdpp/detail/null/mask.h>
#include <simdpp/detail/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline int32<4> int32<4>::zero() { return make_uint(0); }
inline uint32<4> uint32<4>::zero() { return make_uint(0); }
inline int32<4> int32<4>::ones() { return make_uint(0xffffffff); }
inline uint32<4> uint32<4>::ones() { return make_uint(0xffffffff); }

inline uint32<4> mask_int32<4>::unmask() const
{
#if SIMDPP_USE_NULL
    return detail::null::unmask_mask<uint32<4>>(*this);
#else
    return uint32<4>(d_);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
