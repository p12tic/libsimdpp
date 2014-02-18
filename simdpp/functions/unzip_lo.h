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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_UNZIP_LO_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_UNZIP_LO_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/functions/bit_and.h>
#include <simdpp/functions/shuffle2.h>
#include <simdpp/functions/zip_lo.h>
#include <simdpp/null/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** De-interleaves the odd(lower) elements of two int8x16 vectors

    @code
        | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  |
    r = [ a0  a2  a4  a6  a8  a10 a12 a14 b0  b2  b4  b6  b8  b10 b12 b14 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 8-9}
    @icost{NEON, 2}
    @icost{AVX2, 4-5}
    @icost{ALTIVEC, 2-3}

*/
inline basic_int8x16 unzip_lo(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_lo(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, r;
    mask = int128::ones();
    mask = _mm_srli_epi16(mask, 8);
    a = bit_and(a, mask);
    b = bit_and(b, mask);
    r = _mm_packus_epi16(a, b);
    return r;
#elif SIMDPP_USE_NEON
    return vuzpq_u8(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    uint8x16 mask = make_shuffle_bytes16_mask<0,2,4,6,8,10,12,14,
                                              16,18,20,22,24,26,28,30>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

inline basic_int8x32 unzip_lo(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 mask, r;
    mask = int256::ones();
    mask = _mm256_srli_epi16(mask, 8);
    a = bit_and(a, mask);
    b = bit_and(b, mask);
    r = _mm256_packus_epi16(a, b);
    return r;
#else
    return {unzip_lo(a[0], b[0]), unzip_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the odd(lower) elements of two int16x8 vectors

    @code
        | 0  1  2  3  4  5  6  7  |
    r = [ a0 a2 a4 a6 b0 b2 b4 b6 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX2, 4-5}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
inline basic_int16x8 unzip_lo(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_lo(a, b);
#elif SIMDPP_USE_SSE4_1
    uint32x4 mask, r;
    mask = int128::ones();
    mask = _mm_srli_epi32(mask, 16);
    a = bit_and(a, mask);
    b = bit_and(b, mask);
    r = _mm_packus_epi32(a, b);
    return r;
#elif SIMDPP_USE_SSE2
    uint32x4 r;
    a = _mm_slli_epi32(a, 16);
    b = _mm_slli_epi32(b, 16);
    a = _mm_srai_epi32(a, 16);
    b = _mm_srai_epi32(b, 16);
    r = _mm_packs_epi32(a, b);
    return r;
#elif SIMDPP_USE_NEON
    return vuzpq_u16(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    uint16x8 mask = make_shuffle_bytes16_mask<0,2,4,6,8,10,12,14>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

inline basic_int16x16 unzip_lo(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 mask, r;
    mask = int256::ones();
    mask = _mm256_srli_epi32(mask, 16);
    a = bit_and(a, mask);
    b = bit_and(b, mask);
    r = _mm256_packus_epi32(a, b);
    return r;
#else
    return {unzip_lo(a[0], b[0]), unzip_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the odd(lower) elements of two int32x4 vectors

    @code
        | 0  1  2  3  |
    r = [ a0 a2 b0 b2 ]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline basic_int32x4 unzip_lo(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return shuffle2<0,2,0,2>(a,b);
#elif SIMDPP_USE_NEON
    return vuzpq_u32(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    uint32x4 mask = make_shuffle_bytes16_mask<0,2,4,6>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

inline basic_int32x8 unzip_lo(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return shuffle2<0,2,0,2>(a,b);
#else
    return {unzip_lo(a[0], b[0]), unzip_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the odd(lower) elements of two int64x2 vectors

    @code
        | 0  1  |
    r = [ a0 b0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int64x2 unzip_lo(basic_int64x2 a, basic_int64x2 b)
{
    return zip_lo(a, b);
}

inline basic_int64x4 unzip_lo(basic_int64x4 a, basic_int64x4 b)
{
    return zip_lo(a, b);
}
/// @}

/// @{
/** De-interleaves the odd(lower) elements of two float32x4 vectors

    @code
        | 0  1  2  3  |
    r = [ a0 a2 b0 b2 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 unzip_lo(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_lo(a, b);
#elif SIMDPP_USE_SSE2
    return shuffle2<0,2,0,2>(a,b);
#elif SIMDPP_USE_NEON
    return vuzpq_f32(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    uint32x4 mask = make_shuffle_bytes16_mask<0,2,4,6>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

inline float32x8 unzip_lo(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return shuffle2<0,2,0,2>(a,b);
#else
    return {unzip_lo(a[0], b[0]), unzip_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** De-interleaves the odd(lower) elements of two float64x2 vectors

    @code
        | 0  1  |
    r = [ a0 b0 ]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @novec{NEON, ALTIVEC}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline float64x2 unzip_lo(float64x2 a, float64x2 b)
{
    return zip_lo(a, b);
}

inline float64x4 unzip_lo(float64x4 a, float64x4 b)
{
    return zip_lo(a, b);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

