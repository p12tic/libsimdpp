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

#ifndef LIBSIMDPP_SIMDPP_CORE_UNZIP_HI_H
#define LIBSIMDPP_SIMDPP_CORE_UNZIP_HI_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/null/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** De-interleaves the even(higher) elements of two int8x16 vectors

    @code
        | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  |
    r = [ a1  a3  a5  a7  a9  a11 a13 a15 b1  b3  b5  b7  b9  b11 b13 b15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
    @icost{AVX2, 3}

*/
inline gint8x16 unzip_hi(gint8x16 a, gint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_hi(a, b);
#elif SIMDPP_USE_SSE2
    a = _mm_srai_epi16(a, 8);
    b = _mm_srai_epi16(b, 8);
    a = _mm_packs_epi16(a, b);
    return a;
#elif SIMDPP_USE_NEON
    return vuzpq_u8(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_pack((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline gint8x32 unzip_hi(gint8x32 a, gint8x32 b)
{
#if SIMDPP_USE_AVX2
    a = _mm256_srai_epi16(a, 8);
    b = _mm256_srai_epi16(b, 8);
    a = _mm256_packs_epi16(a, b);
    return a;
#else
    return {unzip_hi(a[0], b[0]), unzip_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the even(higher) elements of two int16x8 vectors

    @code
        | 0  1  2  3  4  5  6  7  |
    r = [ a1 a3 a5 a7 b1 b3 b5 b7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
    @icost{AVX2, 3}
*/
inline gint16x8 unzip_hi(gint16x8 a, gint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_hi(a, b);
#elif SIMDPP_USE_SSE2
    a = _mm_srai_epi32(a, 16);
    b = _mm_srai_epi32(b, 16);
    a = _mm_packs_epi32(a, b);
    return a;
#elif SIMDPP_USE_NEON
    return vuzpq_u16(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_pack((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline gint16x16 unzip_hi(gint16x16 a, gint16x16 b)
{
#if SIMDPP_USE_AVX2
    a = _mm256_srai_epi32(a, 16);
    b = _mm256_srai_epi32(b, 16);
    a = _mm256_packs_epi32(a, b);
    return a;
#else
    return {unzip_hi(a[0], b[0]), unzip_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the even(higher) elements of two int32x4 vectors

    @code
        | 0  1  2  3  |
    r = [ a1 a3 b1 b3 ]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{ALTIVEC, 2-3}
    @icost{SSE2-AVX, NEON, 2}
*/
inline gint32x4 unzip_hi(gint32x4 a, gint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_hi(a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return shuffle2<1,3,1,3>(a, b);
#elif SIMDPP_USE_NEON
    return vuzpq_u32(a, b).val[1];
#endif
}

inline gint32x8 unzip_hi(gint32x8 a, gint32x8 b)
{
#if SIMDPP_USE_AVX2
    return shuffle2<1,3,1,3>(a, b);
#else
    return {unzip_hi(a[0], b[0]), unzip_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the even(higher) elements of two int64x2 vectors

    @code
        | 0  1  |
    r = [ a1 b1 ]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{ALTIVEC, 2-3}
    @icost{SSE2-AVX, NEON, 2}
*/
inline gint64x2 unzip_hi(gint64x2 a, gint64x2 b)
{
    return zip_hi(a, b);
}

inline gint64x4 unzip_hi(gint64x4 a, gint64x4 b)
{
    return zip_hi(a, b);
}
/// @}

/// @{
/** De-interleaves the even(higher) elements of two float32x4 vectors

    @code
        | 0  1  2  3  |
    r = [ a1 a3 b1 b3 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 unzip_hi(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_hi(a, b);
#elif SIMDPP_USE_SSE2
    return shuffle2<1,3,1,3>(a,b);
#elif SIMDPP_USE_NEON
    return vuzpq_f32(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return float32x4(unzip_hi((uint32x4)a, (uint32x4)b));
#endif
}

inline float32x8 unzip_hi(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return shuffle2<1,3,1,3>(a, b);
#else
    return {unzip_hi(a[0], b[0]), unzip_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the even(higher) elements of two float64x2 vectors

    @code
        | 0  1  |
    r = [ a1 b1 ]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @novec{NEON, ALTIVEC}
    @icost{SSE2-AVX, 2}


*/
inline float64x2 unzip_hi(float64x2 a, float64x2 b)
{
    return zip_hi(a, b);
}

inline float64x4 unzip_hi(float64x4 a, float64x4 b)
{
    return zip_hi(a, b);
}
/// @}
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

