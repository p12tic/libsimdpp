
/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_CACHE_H
#define LIBSIMDPP_SIMD_CACHE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @defgroup simd_cache Operations: prefetch
    @{
*/

/** Prefetches data to the lowest level cache for reading.

    Currently supported instruction sets:

    * SSE2-AVX2
    * NEON (GCC)

    If the current architecture is not supported, the function does not have
    any effects.

    @param ptr pointer to the data to prefetch
*/
inline void prefetch_read(const void* ptr)
{
#if SIMDPP_USE_SSE2
    _mm_prefetch((const char*)ptr, _MM_HINT_T0);
#elif SIMDPP_USE_NEON
#if __GNUC__
    __builtin_prefetch(ptr, 0); // should result in PLD
#endif
#endif
    (void) ptr;
}

/** Prefetches data to the lowest level cache for writing.

    Currently supported instruction sets:

    * SSE2-AVX2
    * NEON (GCC)

    If the current architecture is not supported, the function does not have
    any effects.

    @param ptr pointer to the data to prefetch
*/
inline void prefetch_write(const void* ptr)
{
#if SIMDPP_USE_SSE2
    _mm_prefetch((const char*)ptr, _MM_HINT_T0);
#elif SIMDPP_USE_NEON
#if __GNUC__
    __builtin_prefetch(ptr, 1); // should result in PLDW
#endif
#endif
    (void) ptr;
}

/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

