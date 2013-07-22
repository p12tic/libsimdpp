/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_CACHE_H
#define LIBSIMDPP_SSE_CACHE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace sse {

#ifdef SIMDPP_USE_SSE2
/** @defgroup simd_cache
    @{
*/

/** Prefetches data to level 1 cache
    @param ptr pointer to the data to prefetch
*/
inline void prefetch_l1(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_T0);
}

/** Prefetches data to level 2 cache
    @param ptr pointer to the data to prefetch
*/
inline void prefetch_l2(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_T1);
}

/** Prefetches data to level 3 cache
    @param ptr pointer to the data to prefetch
*/
inline void prefetch_l3(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_T2);
}

/** Prefetches data to a non-temporary buffer to be read once
    @param ptr pointer to the data to prefetch
*/
inline void prefetch_nt(const void* ptr)
{
    _mm_prefetch((const char*)ptr, _MM_HINT_NTA);
}

/// @}
#endif

} // namespace sse
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif

