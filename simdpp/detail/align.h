/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_ALIGN_H
#define LIBSIMDPP_SIMDPP_DETAIL_ALIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

SIMDPP_INL const void* assume_aligned_impl(const void* x, unsigned bytes)
{
#if (__GNUC__ == 4) && (__GNUC_MINOR__ > 7) && !defined(__clang__)
    // since GCC(>4.7.0)
    x = __builtin_assume_aligned(x, bytes);
    return x;
#else
    (void) bytes;
    return x;
#endif
}

template<class T> SIMDPP_INL
T* assume_aligned(T* x, unsigned bytes)
{
    return const_cast<T*>(reinterpret_cast<const T*>(assume_aligned_impl(x, bytes)));
}

template<class T> SIMDPP_INL
const T* assume_aligned(const T* x, unsigned bytes)
{
    return reinterpret_cast<const T*>(assume_aligned_impl(x, bytes));
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

