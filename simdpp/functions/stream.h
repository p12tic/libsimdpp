/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_STREAM_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_STREAM_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/detail/align.h>
#include <simdpp/functions/store.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Stores a 128-bit or 256-bit integer, 32-bit or 64-bit floating point vector
    to memory without polluting the caches, if possible.

    @par 128-bit version:

    @code
    *(p) = a[0..127]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:

    @code
    *(p) = a[0..255]
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
    @icost{AVX (integer vectors), 2}
*/
inline void stream(void* p, int128 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    store(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(p));
#endif
}

inline void stream(void* p, int256 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX2
    _mm256_stream_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    stream(q, a[0]);
    stream(q+16, a[1]);
#endif
}

inline void stream(float* p, float32x4 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_ps(p, a);
#elif SIMDPP_USE_NEON
    store(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector float)a, 0, p);
#endif
}

inline void stream(float* p, float32x8 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    _mm256_stream_ps(p, a);
#else
    stream(p, a[0]);
    stream(p+4, a[1]);
#endif
}

inline void stream(double* p, float64x2 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_pd(p, a);
#endif
}

inline void stream(double* p, float64x4 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    _mm256_stream_pd(p, a);
#else
    stream(p, a[0]);
    stream(p+2, a[1]);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

