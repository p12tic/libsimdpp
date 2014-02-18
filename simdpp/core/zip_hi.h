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

#ifndef LIBSIMDPP_SIMDPP_CORE_ZIP_HI_H
#define LIBSIMDPP_SIMDPP_CORE_ZIP_HI_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/neon/shuffle.h>
#include <simdpp/null/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Interleaves the higher halves of two vectors.

    @code
        | 0      1      2        3        ... N-2    N-1    |
    r = [ a(N/2) b(N/2) a(N/2+1) b(N/2+1) ... a(N-1) b(N-1) ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint8x16 zip_hi(gint8x16 a, gint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::zip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi8(a, b);
#elif SIMDPP_USE_NEON
    // the compiler will optimize multiple vzip instructions if both zip_hi
    // and zip_hi are used on the same arguments
    return vzipq_u8(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline gint8x32 zip_hi(gint8x32 a, gint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi8(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline gint16x8 zip_hi(gint16x8 a, gint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::zip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u16(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline gint16x16 zip_hi(gint16x16 a, gint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi16(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline gint32x4 zip_hi(gint32x4 a, gint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::zip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u32(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline gint32x8 zip_hi(gint32x8 a, gint32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi32(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline gint64x2 zip_hi(gint64x2 a, gint64x2 b)
{
#if SIMDPP_USE_NULL
    return null::zip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi64(a, b);
#elif SIMDPP_USE_NEON
    return neon::zip_hi(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<1, 3>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

inline gint64x4 zip_hi(gint64x4 a, gint64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi64(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Interleaves the higher halves of two vectors.

    @code
        | 0      1      2        3        ... N-2    N-1    |
    r = [ a(N/2) b(N/2) a(N/2+1) b(N/2+1) ... a(N-1) b(N-1) ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 zip_hi(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::zip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_ps(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_f32(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 zip_hi(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_unpackhi_ps(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline float64x2 zip_hi(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::zip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_castps_pd(_mm_movehl_ps(_mm_castpd_ps(b),
                                       _mm_castpd_ps(a)));
#elif SIMDPP_USE_NEON
    return bit_cast<float64x2>(zip_hi(int64x2(a), int64x2(b)));
#endif
}

inline float64x4 zip_hi(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_unpackhi_pd(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

