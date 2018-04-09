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
#include <assert.h> 

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class T> SIMDPP_INL
T* assume_aligned(T* x, unsigned bytes)
{
#if (__GNUC__ == 4) && (__GNUC_MINOR__ > 7) && !defined(__clang__)
    // since GCC(>4.7.0)
    return reinterpret_cast<T*>(__builtin_assume_aligned(x, bytes));
#else
    (void) bytes;
    return x;
#endif
}

template<class T> SIMDPP_INL
const T* assume_aligned(const T* x, unsigned bytes)
{
#if (__GNUC__ == 4) && (__GNUC_MINOR__ > 7) && !defined(__clang__)
    // since GCC(>4.7.0)
    return reinterpret_cast<const T*>(__builtin_assume_aligned(x, bytes));
#else
    (void) bytes;
    return x;
#endif
}

SIMDPP_INL bool is_aligned(const void* ptr, std::size_t alignment) noexcept
{
    assert(((alignment & (alignment - 1)) == 0));
    return ((std::size_t)ptr & (alignment - 1)) == 0; //from boost\align\detail\is_aligned.hpp
}

SIMDPP_INL bool is_aligned(std::size_t val, std::size_t alignment) noexcept
{
    assert(((alignment & (alignment - 1)) == 0));
    return (val & (alignment - 1)) == 0; //from boost\align\detail\is_aligned.hpp
}

template<typename T>
SIMDPP_INL T* reach_next_aligned(T* ptr, std::size_t alignment) noexcept
{    
    assert(((alignment & (alignment - 1)) == 0));
    return reinterpret_cast<T*>(((std::size_t)ptr + alignment - 1) &~(alignment - 1)); //from boost\align\detail\align_up.hpp
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

