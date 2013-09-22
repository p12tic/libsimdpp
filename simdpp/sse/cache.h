/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SSE_CACHE_H
#define LIBSIMDPP_SSE_CACHE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

