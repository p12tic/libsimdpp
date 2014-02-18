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

#ifndef LIBSIMDPP_SIMDPP_CORE_ZIP_LO_H
#define LIBSIMDPP_SIMDPP_CORE_ZIP_LO_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/shuffle.h>
#include <simdpp/neon/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Interleaves the lower halves of two vectors.

    @code
        | 0  1  2  3  4  5  ... N-2      N-1      |
    r = [ a0 b0 a1 b1 a2 b2 ... a(N/2-1) b(N/2-1) ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint8x16 zip_lo(gint8x16 a, gint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::zip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi8(a, b);
#elif SIMDPP_USE_NEON
    // the compiler will optimize multiple vzip instructions if both zip_lo
    // and zip_hi are used on the same arguments
    return vzipq_u8(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32 zip_lo(gint8x32 a, gint8x32 b)
{
    return _mm256_unpacklo_epi8(a, b);
}
#endif

template<unsigned N>
gint8<N> zip_lo(gint8<N> a, gint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint8<N>, zip_lo, a, b)
}

inline gint16x8 zip_lo(gint16x8 a, gint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::zip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u16(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint16x16 zip_lo(gint16x16 a, gint16x16 b)
{
    return _mm256_unpacklo_epi16(a, b);
}
#endif

template<unsigned N>
gint16<N> zip_lo(gint16<N> a, gint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint16<N>, zip_lo, a, b)
}

inline gint32x4 zip_lo(gint32x4 a, gint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::zip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u32(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint32x8 zip_lo(gint32x8 a, gint32x8 b)
{
    return _mm256_unpacklo_epi32(a, b);
}
#endif

template<unsigned N>
gint32<N> zip_lo(gint32<N> a, gint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint32<N>, zip_lo, a, b)
}

inline gint64x2 zip_lo(gint64x2 a, gint64x2 b)
{
#if SIMDPP_USE_NULL
    return null::zip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi64(a, b);
#elif SIMDPP_USE_NEON
    return neon::zip_lo(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<0, 2>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

#if SIMDPP_USE_AVX2
inline gint64x4 zip_lo(gint64x4 a, gint64x4 b)
{
    return _mm256_unpacklo_epi64(a, b);
}
#endif

template<unsigned N>
gint64<N> zip_lo(gint64<N> a, gint64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint64<N>, zip_lo, a, b)
}
/// @}

/// @{
/** Interleaves the lower halves of two vectors.

    @code
        | 0  1  2  3  4  5  ... N-2      N-1      |
    r = [ a0 b0 a1 b1 a2 b2 ... a(N/2-1) b(N/2-1) ]
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline float32x4 zip_lo(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::zip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_ps(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_f32(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 zip_lo(float32x8 a, float32x8 b)
{
    return _mm256_unpacklo_ps(a, b);
}
#endif

template<unsigned N>
float32<N> zip_lo(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, zip_lo, a, b)
}

inline float64x2 zip_lo(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::zip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_castps_pd(_mm_movelh_ps(_mm_castpd_ps(a),
                                       _mm_castpd_ps(b)));
#elif SIMDPP_USE_NEON
    return bit_cast<float64x2>(zip_lo(int64x2(a), int64x2(b)));
#endif
}

#if SIMDPP_USE_AVX
inline float64x4 zip_lo(float64x4 a, float64x4 b)
{
    return _mm256_unpacklo_pd(a, b);
}
#endif

template<unsigned N>
float64<N> zip_lo(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, zip_lo, a, b)
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
