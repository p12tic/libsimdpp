/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CACHE_H
#define LIBSIMDPP_SIMDPP_CACHE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** @defgroup simd_cache Operations: prefetch
    @{
*/

/** Prefetches data to the lowest level cache for reading.

    @param ptr pointer to the data to prefetch
*/
SIMDPP_INL void prefetch_read(const void* ptr)
{
#if SIMDPP_USE_SSE2
    _mm_prefetch((const char*)ptr, _MM_HINT_T0);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
#if __GNUC__
    __builtin_prefetch(ptr, 0); // should result in PLD or DST
#endif
#endif
    (void) ptr;
}

/** Prefetches data to the lowest level cache for writing.

    @param ptr pointer to the data to prefetch
*/
SIMDPP_INL void prefetch_write(const void* ptr)
{
#if SIMDPP_USE_SSE2
    _mm_prefetch((const char*)ptr, _MM_HINT_T0);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
#if __GNUC__
    __builtin_prefetch(ptr, 1); // should result in PLDW or DSTST
#endif
#endif
    (void) ptr;
}

/// @}


} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

