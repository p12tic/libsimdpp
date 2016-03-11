/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/core/cast.h>

#include <cstring>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

enum {
    CAST_MASK_MEMCPY,
    CAST_MASK_UNMASK,
    CAST_MASK_REMASK
};
// defined in cast.inl
template<bool IsRMask, bool IsLMask, unsigned MaskCastOverride> struct cast_wrapper;


} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
