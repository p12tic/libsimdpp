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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/detail/mem_unpack.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Loads a 128-bit or 256-bit integer, 32-bit or 64-bit float vector
    from an aligned memory location.

    @par 128-bit version:

    @code
    a[0..127] = *(p)
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:

    @code
    a[0..255] = *(p)
    @endcode
    @a p must be aligned to 32 bytes.

    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
    @icost{AVX (integer vectors), 2}
*/
inline int128 load(int128& a, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_si128(reinterpret_cast<const __m128i*>(p));
    return a;
#elif SIMDPP_USE_NEON
    a = vreinterpretq_u32_u64(vld1q_u64(reinterpret_cast<const uint64_t*>(p)));
    return a;
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, reinterpret_cast<const uint8_t*>(p));
    return a;
#endif
}

inline int256 load(int256& a, const void* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX2
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p));
    return a;
#else
    const char* q = reinterpret_cast<const char*>(p);
    a = gint8x32{load(a[0], q), load(a[1], q+16)};
    return a;
#endif
}

inline float32x4 load(float32x4& a, const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_ps(p);
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_f32(p);
    return a;
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, p);
    return a;
#endif
}

inline float32x8 load(float32x8& a, const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    a = _mm256_load_ps(p);
    return a;
#else
    a = float32x8{load(a[0], p), load(a[1], p+4)};
    return a;
#endif
}

inline float64x2 load(float64x2& a, const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_pd(p);
    return a;
#endif
}

inline float64x4 load(float64x4& a, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    a = _mm256_load_pd(p);
    return a;
#else
    a = float64x4{load(a[0], p), load(a[1], p+2)};
    return a;
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

