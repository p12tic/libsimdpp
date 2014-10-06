/*  Copyright (C) 2011  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_CACHE_H
#define LIBSIMDPP_SSE_CACHE_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace sse {

/** @defgroup simd_cache
    @{
*/

/** Prefetches data to level 1 cache
    @param ptr pointer to the data to prefetch
*/
SIMDPP_INL void prefetch_l1(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_T0);
}

/** Prefetches data to level 2 cache
    @param ptr pointer to the data to prefetch
*/
SIMDPP_INL void prefetch_l2(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_T1);
}

/** Prefetches data to level 3 cache
    @param ptr pointer to the data to prefetch
*/
SIMDPP_INL void prefetch_l3(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_T2);
}

/** Prefetches data to a non-temporary buffer to be read once
    @param ptr pointer to the data to prefetch
*/
SIMDPP_INL void prefetch_nt(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_NTA);
}

/// @}

} // namespace sse
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif

