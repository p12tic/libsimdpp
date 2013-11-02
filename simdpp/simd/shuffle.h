/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_SHUFFLE_H
#define LIBSIMDPP_SIMD_SHUFFLE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/fwd.h>
#include <simdpp/simd/types.h>
#include <simdpp/simd/bitwise.h>
#include <simdpp/simd/shuffle_generic.h>
#include <simdpp/simd/make_shuffle_bytes_mask.h>
#include <simdpp/simd/detail/shuffle128.h>
#include <simdpp/null/shuffle.h>

#include <iostream>
#include <iomanip>

#if SIMDPP_USE_NEON
    #include <simdpp/neon/shuffle.h>
    #include <simdpp/neon/detail/shuffle.h>
#elif SIMDPP_USE_SSE2
    #include <simdpp/sse/shuffle.h>
    #include <simdpp/sse/extract_half.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @defgroup simd_shuffle Operations: shuffle elements within vectors
    @{
*/

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
inline basic_int8x16 zip_lo(basic_int8x16 a, basic_int8x16 b)
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

inline basic_int8x32 zip_lo(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpacklo_epi8(a, b);
#else
    return {zip_lo(a[0], b[0]), zip_lo(a[1], b[1])};
#endif
}

inline basic_int16x8 zip_lo(basic_int16x8 a, basic_int16x8 b)
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

inline basic_int16x16 zip_lo(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpacklo_epi16(a, b);
#else
    return {zip_lo(a[0], b[0]), zip_lo(a[1], b[1])};
#endif
}

inline basic_int32x4 zip_lo(basic_int32x4 a, basic_int32x4 b)
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

inline basic_int32x8 zip_lo(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpacklo_epi32(a, b);
#else
    return {zip_lo(a[0], b[0]), zip_lo(a[1], b[1])};
#endif
}

inline basic_int64x2 zip_lo(basic_int64x2 a, basic_int64x2 b)
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

inline basic_int64x4 zip_lo(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpacklo_epi64(a, b);
#else
    return {zip_lo(a[0], b[0]), zip_lo(a[1], b[1])};
#endif
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

inline float32x8 zip_lo(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_unpacklo_ps(a, b);
#else
    return {zip_lo(a[0], b[0]), zip_lo(a[1], b[1])};
#endif
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

inline float64x4 zip_lo(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_unpacklo_pd(a, b);
#else
    return {zip_lo(a[0], b[0]), zip_lo(a[1], b[1])};
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

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 zip_hi(basic_int8x16 a, basic_int8x16 b)
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

inline basic_int8x32 zip_hi(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi8(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline basic_int16x8 zip_hi(basic_int16x8 a, basic_int16x8 b)
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

inline basic_int16x16 zip_hi(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi16(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline basic_int32x4 zip_hi(basic_int32x4 a, basic_int32x4 b)
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

inline basic_int32x8 zip_hi(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_unpackhi_epi32(a, b);
#else
    return {zip_hi(a[0], b[0]), zip_hi(a[1], b[1])};
#endif
}

inline basic_int64x2 zip_hi(basic_int64x2 a, basic_int64x2 b)
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

inline basic_int64x4 zip_hi(basic_int64x4 a, basic_int64x4 b)
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

/// @{
/** Moves the elements in an int8x16 vector to the left by @a shift positions.

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ a0  a1   .  a14 a15 ]
     1      r = [ a1  a2   .  a15  0  ]
     2      r = [ a2  a3   .   0   0  ]
      ...    ..   .. ..   ...  ..  .. ..
     14     r = [ a15  0   .   0   0  ]
     15     r = [  0   0   .   0   0  ]
     16     r = [  0   0   .   0   0  ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int8x16 move_l(basic_int8x16 a)
{
    static_assert(shift <= 16, "Selector out of range");
    if (shift == 0) return a;
    if (shift == 16) return uint8x16::zero();

#if SIMDPP_USE_NULL
    uint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int) (16-shift); i++) {
        r[i] = a[i + shift];
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r[i] = 0;
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_srli_si128(a, shift);
#elif SIMDPP_USE_NEON
    int8x16 z = int8x16::zero();
    return neon::detail::align<shift>(a, z);
#elif SIMDPP_USE_ALTIVEC
    // return align<shift>(a, uint8x16::zero());
    return vec_sld((__vector uint8_t)a, (__vector uint8_t)uint8x16::zero(), shift);
#endif
}

template<unsigned shift>
basic_int8x32 move_l(basic_int8x32 a)
{
    static_assert(shift <= 16, "Selector out of range");
    if (shift == 0) return a;
    if (shift == 16) return uint8x32::zero();

#if SIMDPP_USE_AVX2
    return _mm256_srli_si256(a, shift);
#else
    return {move_l<shift>(a[0]), move_l<shift>(a[1])};
#endif
}
/// @}

/// @{
/** Moves the 16-bit elements in a vector to the left by @a shift positions.

    @code
    shift:  pos:| 0  1   . 6  7  |
     0      r = [ a0 a1  . a6 a7 ]
     1      r = [ a1 a2  . a7  0 ]
     2      r = [ a2 a3  .  0  0 ]
      ...    ..   .. .. ... .. ..
     6      r = [ a6 a7  .  0  0 ]
     7      r = [ a7  0  .  0  0 ]
     8      r = [  0  0  .  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int16x8 move_l(basic_int16x8 a)
{
    return move_l<shift*2>(basic_int8x16(a));
}

template<unsigned shift>
basic_int16x16 move_l(basic_int16x16 a)
{
    return move_l<shift*2>(basic_int8x32(a));
}
/// @}

/// @{
/** Moves the 32-bit elements in a vector to the left by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [ a1 a2 a3  0 ]
     2      r = [ a2 a3  0  0 ]
     3      r = [ a3  0  0  0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int32x4 move_l(basic_int32x4 a)
{
    return move_l<shift*4>(basic_int8x16(a));
}

template<unsigned shift>
basic_int32x8 move_l(basic_int32x8 a)
{
    return move_l<shift*4>(basic_int8x32(a));
}
/// @}

/// @{
/** Moves the 64-bit elements in a vector to the left by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [ a1  0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int64x2 move_l(basic_int64x2 a)
{
    return move_l<shift*8>(basic_int8x16(a));
}

template<unsigned shift>
basic_int64x4 move_l(basic_int64x4 a)
{
    return move_l<shift*8>(basic_int8x32(a));
}
/// @}

/// @{
/** Moves the 32-bit elements in a vector to the left by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [ a1 a2 a3  0 ]
     2      r = [ a2 a3  0  0 ]
     3      r = [ a3  0  0  0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float32x4 move_l(float32x4 a)
{
    return float32x4(move_l<shift>(basic_int32x4(a)));
}

template<unsigned shift>
float32x8 move_l(float32x8 a)
{
    return float32x8(move_l<shift>(basic_int32x8(a)));
}
/// @}

/// @{
/** Moves the 64-bit elements in a vector to the left by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [ a1  0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float64x2 move_l(float64x2 a)
{
    return float64x2(move_l<shift>(basic_int64x2(a)));
}

template<unsigned shift>
float64x4 move_l(float64x4 a)
{
    return float64x4(move_l<shift>(basic_int64x4(a)));
}
/// @}

/// @{
/** Moves the 8-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ a0  a1   .  a14 a15 ]
     1      r = [  0  a0   .  a13 a14 ]
     2      r = [  0   0   .  a12 a13 ]
      ...    ..   .. ..   ...  ..  .. ..
     14     r = [  0   0   .  a0  a1  ]
     15     r = [  0   0   .   0  a0  ]
     16     r = [  0   0   .   0   0  ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int8x16 move_r(basic_int8x16 a)
{
    static_assert(shift <= 16, "Selector out of range");
    if (shift == 0) return a;
    if (shift == 16) return uint8x16::zero();

#if SIMDPP_USE_NULL
    basic_int8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)shift; i++) {
        r[i] = 0;
    }
    for (unsigned i = shift; i < 16; i++) {
        r[i] = a[i - shift];
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_slli_si128(a, shift);
#elif SIMDPP_USE_NEON
    int8x16 z = int8x16::zero();
    return neon::detail::align<16-shift>(z, a);
#elif SIMDPP_USE_ALTIVEC
    // return align<16-shift>(uint8x16::zero(), a);
    return vec_sld((__vector uint8_t)uint8x16::zero(), (__vector uint8_t)a, 16-shift);
#endif
}

template<unsigned shift>
basic_int8x32 move_r(basic_int8x32 a)
{
    static_assert(shift <= 16, "Selector out of range");
    if (shift == 0) return a;
    if (shift == 16) return uint8x32::zero();

#if SIMDPP_USE_AVX2
    return _mm256_slli_si256(a, shift);
#else
    return {move_r<shift>(a[0]), move_r<shift>(a[1])};
#endif
}
/// @}

/// @{
/** Moves the 16-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1   . 6  7  |
     0      r = [ a0 a1  . a6 a7 ]
     1      r = [  0 a0  . a5 a6 ]
     2      r = [  0  0  . a4 a5 ]
      ...    ..   .. .. ... .. ..
     6      r = [  0  0  . a0 a1 ]
     7      r = [  0  0  .  0 a0 ]
     8      r = [  0  0  .  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int16x8 move_r(basic_int16x8 a)
{
    return move_r<shift*2>(basic_int8x16(a));
}

template<unsigned shift>
basic_int16x16 move_r(basic_int16x16 a)
{
    return move_r<shift*2>(basic_int8x32(a));
}
/// @}

/// @{
/** Moves the 32-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [  0 a0 a1 a2 ]
     2      r = [  0  0 a0 a1 ]
     3      r = [  0  0  0 a0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int32x4 move_r(basic_int32x4 a)
{
    return move_r<shift*4>(basic_int8x16(a));
}

template<unsigned shift>
basic_int32x8 move_r(basic_int32x8 a)
{
    return move_r<shift*4>(basic_int8x32(a));
}
/// @}

/// @{
/** Moves the 64-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [  0 a0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int64x2 move_r(basic_int64x2 a)
{
    return move_r<shift*8>(basic_int8x16(a));
}

template<unsigned shift>
basic_int64x4 move_r(basic_int64x4 a)
{
    return move_r<shift*8>(basic_int8x32(a));
}
/// @}

/// @{
/** Moves the 32-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [  0 a0 a1 a2 ]
     2      r = [  0  0 a0 a1 ]
     3      r = [  0  0  0 a0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float32x4 move_r(float32x4 a)
{
    return float32x4(move_r<shift>(basic_int32x4(a)));
}

template<unsigned shift>
float32x8 move_r(float32x8 a)
{
    return float32x8(move_r<shift>(basic_int32x8(a)));
}
/// @}

/// @{
/** Moves the 64-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [  0 a0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float64x2 move_r(float64x2 a)
{
    return float64x2(move_r<shift>(basic_int64x2(a)));
}

template<unsigned shift>
float64x4 move_r(float64x4 a)
{
    return float64x4(move_r<shift>(basic_int64x4(a)));
}
/// @}

/// @{
/** Broadcasts the specified 8-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    rN = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 7}
    @icost{SSSE3-AVX, 1-2}
    @icost{AVX2, 2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 14}
    @icost{SSSE3-AVX, 2-3}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
basic_int8x16 broadcast(basic_int8x16 a)
{
    static_assert(s < 16, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_AVX2
    a = move_l<s>(a);
    return _mm_broadcastb_epi8(a);
#elif SIMDPP_USE_SSSE3
    uint8x16 mask = make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                              s,s,s,s,s,s,s,s>(mask);
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_SSE2
    basic_int16x8 b1, b2;

    if (s % 2 == 1) {
        b1 = _mm_srli_epi16(a, 8);
        b2 = _mm_slli_epi16(b1, 8);
    } else {
        b1 = _mm_slli_epi16(a, 8);
        b2 = _mm_srli_epi16(b1, 8);
    }
    b1 = bit_or(b1, b2);
    return broadcast<s/2>(b1);
#elif SIMDPP_USE_NEON
    if (s < 8) {
        uint8x8_t z = vget_low_u8(a);
        return (uint8x16_t) vdupq_lane_u8(z, (s < 8 ? s : 0));
    } else {
        uint8x8_t z = vget_high_u8(a);
        return (uint8x16_t) vdupq_lane_u8(z, (s < 8 ? 0 : s-8));
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector uint8_t)a, s);
#endif
}

template<unsigned s>
basic_int8x32 broadcast(basic_int8x32 a)
{
    static_assert(s < 16, "Access out of bounds");
#if SIMDPP_USE_AVX2
    basic_int16x16 b = s < 8 ? zip_lo(a, a) : zip_hi(a, a);
    return broadcast<s%8>(b);
#else
    return {broadcast<s>(a[0]), broadcast<s>(a[1])};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 16-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    r7 = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{SSSE3-AVX, 1-2}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
template<unsigned s>
basic_int16x8 broadcast(basic_int16x8 a)
{
    static_assert(s < 8, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_AVX2
    a = move_l<s>(a);
    return _mm_broadcastw_epi16(a);
#elif SIMDPP_USE_SSSE3
    uint16x8 mask = make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_SSE2
    // s2 is needed because static_assert fires in branch we don't use
    basic_int64x2 b;
    if (s < 4) {
        constexpr unsigned s2 = s < 4 ? s : s-4;
        b = sse::permute_lo<s2,s2,s2,s2>(a);
        return permute<0,0>(b);
    } else {
        constexpr unsigned s2 = s < 4 ? s : s-4;
        b = sse::permute_hi<s2,s2,s2,s2>(a);
        return permute<1,1>(b);
    }
#elif SIMDPP_USE_NEON
    if (s < 4) {
        uint16x4_t z = vget_low_u16(a);
        return (uint16x8_t) vdupq_lane_u16(z, (s < 4 ? s : 0));
    } else {
        uint16x4_t z = vget_high_u16(a);
        return (uint16x8_t) vdupq_lane_u16(z, (s < 4 ? 0 : s-4));
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector uint16_t)a, s);
#endif
}

template<unsigned s>
basic_int16x16 broadcast(basic_int16x16 a)
{
    static_assert(s < 8, "Access out of bounds");
#if SIMDPP_USE_AVX2
    if (s < 4) {
        constexpr unsigned q = (s < 4) ? s : 0;
        basic_int64x4 h = _mm256_shufflelo_epi16(a, q << 6 | q << 4 | q << 2 | q);
        h = permute<0,0>(h);
        return h;
    } else {
        constexpr unsigned q = (s < 4) ? 0 : s - 4;
        basic_int64x4 h = _mm256_shufflehi_epi16(a, q << 6 | q << 4 | q << 2 | q);
        h = permute<1,1>(h);
        return h;
    }
#else
    return {broadcast<s>(a[0]), broadcast<s>(a[1])};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
basic_int32x4 broadcast(basic_int32x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_SSE2
    return permute<s,s,s,s>(a);
#elif SIMDPP_USE_NEON
    if (s < 2) {
        uint32x2_t z = vget_low_u32(a);
        // Clang implements vdupq_lane_u32 as a macro, thus we must never
        // supply it with s>=2, even if we know the branch will never be executed
        return (uint32x4_t) vdupq_lane_u32(z, (s < 2 ? s : 0));
    } else {
        uint32x2_t z = vget_high_u32(a);
        return (uint32x4_t) vdupq_lane_u32(z, (s < 2 ? 0 : s-2));
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector uint32_t)a, s);
#endif
}

template<unsigned s>
basic_int32x8 broadcast(basic_int32x8 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_AVX2
    return permute<s,s,s,s>(a);
#else
    return {broadcast<s>(a[0]), broadcast<s>(a[1])};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s>
basic_int64x2 broadcast(basic_int64x2 a)
{
    static_assert(s < 2, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_SSE2
    if (s == 0) {
        return permute<0,0>(a);
    } else {
        return permute<1,1>(a);
    }
#elif SIMDPP_USE_NEON
    uint64x1_t z;
    if (s == 0) {
        z = vget_low_u64(a);
    } else {
        z = vget_high_u64(a);
    }
    return (uint64x2_t) vdupq_lane_u64(z, 0);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<s, s>(mask);
    return permute_bytes16(a, mask);
#endif
}

template<unsigned s>
basic_int64x4 broadcast(basic_int64x4 a)
{
    static_assert(s < 2, "Access out of bounds");
#if SIMDPP_USE_AVX2
    return permute<s,s>(a);
#else
    return {broadcast<s>(a[0]), broadcast<s>(a[1])};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned s>
float32x4 broadcast(float32x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_SSE2
    return permute<s,s,s,s>(a);
#elif SIMDPP_USE_NEON
    if (s < 2) {
        float32x2_t z = vget_low_f32(a);
        // Clang implements vdupq_lane_f32 as a macro, thus we must never
        // supply it with s>=2, even if we know the branch will never be executed
        return (float32x4_t) vdupq_lane_f32(z, (s < 2 ? s : 0));
    } else {
        float32x2_t z = vget_high_f32(a);
        return (float32x4_t) vdupq_lane_f32(z, (s < 2 ? 0 : s-2) );
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector float)a, s);
#endif
}

template<unsigned s>
float32x8 broadcast(float32x8 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_AVX
    return permute<s,s,s,s>(a);
#else
    return {broadcast<s>(a[0]), broadcast<s>(a[1])};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s>
float64x2 broadcast(float64x2 a)
{
    static_assert(s < 2, "Access out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_SSE2
    if (s == 0) {
        return permute<0,0>(a);
    } else {
        return permute<1,1>(a);
    }
#elif SIMDPP_USE_NEON
    return float64x2(broadcast<s>(int64x2(a)));
#endif
}

template<unsigned s>
float64x4 broadcast(float64x4 a)
{
    static_assert(s < 2, "Access out of bounds");
#if SIMDPP_USE_AVX
    return permute<s,s>(a);
#else
    return {broadcast<s>(a[0]), broadcast<s>(a[1])};
#endif
}
/// @}


/// @{
/** Broadcasts the specified 8-bit value to all elements within 128-bit lane

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    rN = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
basic_int8x16 broadcast_w(basic_int8x16 a)
{
    return broadcast<s>(a);
}

template<unsigned s>
basic_int8x32 broadcast_w(basic_int8x32 a)
{
    static_assert(s < 32, "Access out of bounds");
#if SIMDPP_USE_AVX2
    basic_int8x16 lo;
    lo = s < 16 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move_l<s % 16>(lo);
    return _mm256_broadcastb_epi8(lo);
#else
    basic_int8x16 p = a[s/16];
    p = broadcast<s%16>(p);
    return {p, p};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 16-bit value to all elements within a int16x8 vector

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    r7 = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
basic_int16x8 broadcast_w(basic_int16x8 a)
{
    return broadcast<s>(a);
}

template<unsigned s>
basic_int16x16 broadcast_w(basic_int16x16 a)
{
    static_assert(s < 16, "Access out of bounds");
#if SIMDPP_USE_AVX2
    basic_int16x8 lo;
    lo = s < 8 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move_l<s % 8>(lo);
    return _mm256_broadcastw_epi16(lo);
#else
    basic_int16x8 p = a[s/8];
    p = broadcast<s%8>(p);
    return {p, p};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within a int32x4 vector

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
basic_int32x4 broadcast_w(basic_int32x4 a)
{
    return broadcast<s>(a);
}

template<unsigned s>
basic_int32x8 broadcast_w(basic_int32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
#if SIMDPP_USE_AVX2
    a = permute<s%4,s%4,s%4,s%4>(a);
    a = detail::shuffle128<s/4, s/4>(a, a);
    return a;
#else
    basic_int32x4 p = a[s/4];
    p = broadcast<s%4>(p);
    return {p, p};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within a int64x2 vector

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 1-2}
*/
template<unsigned s>
basic_int64x2 broadcast_w(basic_int64x2 a)
{
    return broadcast<s>(a);
}

template<unsigned s>
basic_int64x4 broadcast_w(basic_int64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_AVX2
    return permute<s,s,s,s>(a);
#else
    basic_int64x2 p = a[s/2];
    p = broadcast<s%2>(p);
    return {p, p};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within a float32x4 vector

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned s>
float32x4 broadcast_w(float32x4 a)
{
    return broadcast<s>(a);
}

template<unsigned s>
float32x8 broadcast_w(float32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
#if SIMDPP_USE_AVX
    a = detail::shuffle128<s/4,s/4>(a, a);
    return permute<s%4,s%4,s%4,s%4>(a);
#else
    float32x4 p = a[s/4];
    p = broadcast<s%4>(p);
    return {p, p};
#endif
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within a float64x2 vector

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s>
float64x2 broadcast_w(float64x2 a)
{
    return broadcast<s>(a);
}

template<unsigned s>
float64x4 broadcast_w(float64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_AVX2
    return permute<s,s,s,s>(a);
#elif SIMDPP_USE_AVX
    a = detail::shuffle128<s/2,s/2>(a, a);
    a = permute<s%2,s%2>(a);
    return a;
#else
    float64x2 p = a[s/2];
    p = broadcast<s%2>(p);
    return {p, p};
#endif
}
/// @}

/// @{
/** Extracts a int8x16 vector from two concatenated int8x16 vectors

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ l0  l1   .  l14 l15 ]
     1      r = [ l1  l2   .  l15 u0  ]
     2      r = [ l2  l3   .  u0  l1  ]
      ...    ..   .. ..  ... .. ..
     15     r = [ l15 u0   .  u13 u14 ]
     16     r = [ u0  u1   .  u14 u15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int8x16 align(basic_int8x16 lower, basic_int8x16 upper)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return lower;
    if (shift == 16) return upper;

#if SIMDPP_USE_NULL
    basic_int8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)(16-shift); i++) {
        r[i] = lower[i + shift];
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r[i] = upper[i - 16 + shift];
    }
    return r;
#elif SIMDPP_USE_SSSE3
    return _mm_alignr_epi8(upper, lower, shift);
#elif SIMDPP_USE_SSE2
    basic_int8x16 a;
    lower = move_l<shift>(lower);
    upper = move_r<16-shift>(upper);
    a = bit_or(upper, lower);
    return a;
#elif SIMDPP_USE_NEON
    return neon::detail::align<shift>(lower, upper);
#elif SIMDPP_USE_ALTIVEC
    return vec_sld((__vector uint8_t)lower, (__vector uint8_t)upper, (unsigned)shift);
#endif
}

template<unsigned shift>
basic_int8x32 align(basic_int8x32 lower, basic_int8x32 upper)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return lower;
    if (shift == 16) return upper;

#if SIMDPP_USE_AVX2
    return _mm256_alignr_epi8(upper, lower, shift);
#else
    return {align<shift>(lower[0], upper[0]), align<shift>(lower[1], upper[1])};
#endif
}
/// @}

/// @{
/** Extracts a int16x8 vector from two concatenated int16x8 vectors

    @code
    shift:  pos:| 0  1    .  6  7  |
     0      r = [ l0 l1   .  l6 l7 ]
     1      r = [ l1 l2   .  l7 u0 ]
     2      r = [ l2 l3   .  u0 l1 ]
      ...    ..   .. ..  ... .. ..
     7      r = [ l3 u0   .  u5 u6 ]
     8      r = [ u0 u1   .  u6 u7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int16x8 align(basic_int16x8 lower, basic_int16x8 upper)
{
    static_assert(shift <= 8, "Shift out of bounds");
    return align<shift*2>(basic_int8x16(lower), basic_int8x16(upper));
}

template<unsigned shift>
basic_int16x16 align(basic_int16x16 lower, basic_int16x16 upper)
{
    static_assert(shift <= 8, "Shift out of bounds");
    return align<shift*2>(basic_int8x32(lower), basic_int8x32(upper));
}
/// @}

/// @{
/** Extracts a int32x4 vector from two concatenated int32x4 vectors

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ l0 l1 l2 l3 ]
     1      r = [ l1 l2 l3 u0 ]
     2      r = [ l2 l3 u0 u1 ]
     3      r = [ l3 u0 u1 u2 ]
     4      r = [ u0 u1 u2 u3 ]
    @endcode

   @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int32x4 align(basic_int32x4 lower, basic_int32x4 upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    return align<shift*4>(basic_int8x16(lower), basic_int8x16(upper));
}

template<unsigned shift>
basic_int32x8 align(basic_int32x8 lower, basic_int32x8 upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    return align<shift*4>(basic_int8x32(lower), basic_int8x32(upper));
}
/// @}

/// @{
/** Extracts a int64x2 vector from two concatenated int64x2 vectors

    @code
    shift:  pos:| 0  1  |
     0      r = [ l0 l1 ]
     1      r = [ l1 u0 ]
     2      r = [ u0 u1 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
basic_int64x2 align(basic_int64x2 lower, basic_int64x2 upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    return align<shift*8>(basic_int8x16(lower), basic_int8x16(upper));
}

template<unsigned shift>
basic_int64x4 align(basic_int64x4 lower, basic_int64x4 upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    return align<shift*8>(basic_int8x32(lower), basic_int8x32(upper));
}
/// @}

/// @{
/** Extracts a float32x4 vector from two concatenated float32x4 vectors

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ l0 l1 l2 l3 ]
     1      r = [ l1 l2 l3 u0 ]
     2      r = [ l2 l3 u0 u1 ]
     3      r = [ l3 u0 u1 u2 ]
     4      r = [ u0 u1 u2 u3 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-SSE4.1 NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float32x4 align(float32x4 lower, float32x4 upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    return float32x4(align<shift>(basic_int32x4(lower),
                                  basic_int32x4(upper)));
}

template<unsigned shift>
float32x8 align(float32x8 lower, float32x8 upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    return float32x8(align<shift>(basic_int32x8(lower), basic_int32x8(upper)));
}
/// @}

/// @{
/** Extracts a float64x2 vector from two concatenated float64x2 vectors

    @code
    shift:  pos:| 0  1  |
     0      r = [ l0 l1 ]
     1      r = [ l1 u0 ]
     2      r = [ u0 u1 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned shift>
float64x2 align(float64x2 lower, float64x2 upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    return float64x2(align<shift>(basic_int64x2(lower),
                                  basic_int64x2(upper)));
}

template<unsigned shift>
float64x4 align(float64x4 lower, float64x4 upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    return float64x4(align<shift>(basic_int64x4(lower), basic_int64x4(upper)));
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xff ) ? on0 : off0
    ...
    rN = (maskN == 0xff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
    @icost{XOP, 2}
*/
inline basic_int8x16 blend(basic_int8x16 on, basic_int8x16 off, basic_int8x16 mask)
{
#if SIMDPP_USE_NULL
    return null::blend(on, off, mask);
#elif SIMDPP_USE_AVX2
    return _mm_blendv_epi8(off, on, mask);
#elif SIMDPP_USE_XOP
    return _mm_cmov_si128(on, off, mask);
#elif SIMDPP_USE_SSE2
    // _mm_blendv_epi8 needs xmm0 and occupies the shuffle ports, yet saves
    // only one uop
    int128 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON
    return vbslq_u8(mask, on, off);
#elif SIMDPP_USE_ALTIVEC
    return vec_sel((__vector uint8_t)off, (__vector uint8_t)on,
                   (__vector uint8_t)mask);
#endif
}

inline basic_int8x16 blend(basic_int8x16 on, basic_int8x16 off, mask_int8x16 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return blend(uint8x16(on), uint8x16(off), uint8x16(mask));
#endif
}

inline basic_int8x32 blend(basic_int8x32 on, basic_int8x32 off, basic_int8x32 mask)
{
#if SIMDPP_USE_AVX2
    return _mm256_blendv_epi8(off, on, mask);
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}

inline basic_int8x32 blend(basic_int8x32 on, basic_int8x32 off, mask_int8x32 mask)
{
#if SIMDPP_USE_AVX2
    return blend(uint8x32(on), uint8x32(off), uint8x32(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}
/// @}

/// @{
/** Composes vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
inline basic_int16x8 blend(basic_int16x8 on, basic_int16x8 off, basic_int16x8 mask)
{
    return blend((uint8x16)on, (uint8x16)off, (uint8x16)mask);
}

inline basic_int16x16 blend(basic_int16x16 on, basic_int16x16 off, basic_int16x16 mask)
{
#if SIMDPP_USE_AVX2
    return blend(uint8x32(on), uint8x32(off), uint8x32(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}

inline basic_int16x8 blend(basic_int16x8 on, basic_int16x8 off, mask_int16x8 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return blend(uint8x16(on), uint8x16(off), uint8x16(mask));
#endif
}

inline basic_int16x16 blend(basic_int16x16 on, basic_int16x16 off, mask_int16x16 mask)
{
#if SIMDPP_USE_AVX2
    return blend(uint8x32(on), uint8x32(off), uint8x32(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
inline basic_int32x4 blend(basic_int32x4 on, basic_int32x4 off, basic_int32x4 mask)
{
    return blend((uint8x16)on, (uint8x16)off, (uint8x16)mask);
}

inline basic_int32x8 blend(basic_int32x8 on, basic_int32x8 off, basic_int32x8 mask)
{
#if SIMDPP_USE_AVX2
    return blend(uint8x32(on), uint8x32(off), uint8x32(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}

inline basic_int32x4 blend(basic_int32x4 on, basic_int32x4 off, mask_int32x4 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return blend(uint8x16(on), uint8x16(off), uint8x16(mask));
#endif
}

inline basic_int32x8 blend(basic_int32x8 on, basic_int32x8 off, mask_int32x8 mask)
{
#if SIMDPP_USE_AVX2
    return blend(uint8x32(on), uint8x32(off), uint8x32(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
inline basic_int64x2 blend(basic_int64x2 on, basic_int64x2 off, basic_int64x2 mask)
{
    return blend(uint8x16(on), uint8x16(off), uint8x16(mask));
}

inline basic_int64x4 blend(basic_int64x4 on, basic_int64x4 off, basic_int64x4 mask)
{
#if SIMDPP_USE_AVX2
    return _mm256_blendv_epi8(off, on, mask);
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}

inline basic_int64x2 blend(basic_int64x2 on, basic_int64x2 off, mask_int64x2 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return blend(uint8x16(on), uint8x16(off), uint8x16(mask));
#endif
}

inline basic_int64x4 blend(basic_int64x4 on, basic_int64x4 off, mask_int64x4 mask)
{
#if SIMDPP_USE_AVX2
    return blend(uint8x32(on), uint8x32(off), uint8x32(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 3}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 6}
    @icost{NEON, ALTIVEC, 2}
*/
inline float32x4 blend(float32x4 on, float32x4 off, float32x4 mask)
{
#if SIMDPP_USE_NULL
    return null::blend(on, off, mask);
#elif SIMDPP_USE_AVX
    return _mm_blendv_ps(off, on, mask);
#elif SIMDPP_USE_SSE2
    float32x4 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON
    return vbslq_f32(uint32x4(mask), on, off);
#elif SIMDPP_USE_ALTIVEC
    return vec_sel((__vector float)off, (__vector float)on,
                   (__vector float)mask);
#endif
}

inline float32x4 blend(float32x4 on, float32x4 off, int128 mask)
{
    return blend(on, off, bit_cast<float32x4>(mask));
}

inline float32x8 blend(float32x8 on, float32x8 off, float32x8 mask)
{
#if SIMDPP_USE_AVX
    return _mm256_blendv_ps(off, on, mask);
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}

inline float32x8 blend(float32x8 on, float32x8 off, int256 mask)
{
    return blend(on, off, bit_cast<float32x8>(mask));
}


inline float32x4 blend(float32x4 on, float32x4 off, mask_float32x4 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return blend(on, off, uint32x4(mask));
#endif
}

inline float32x8 blend(float32x8 on, float32x8 off, mask_float32x8 mask)
{
#if SIMDPP_USE_AVX
    return blend(on, off, uint32x8(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffffffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffffffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 6}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 blend(float64x2 on, float64x2 off, float64x2 mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::blend(on, off, mask);
#elif SIMDPP_USE_AVX
    return _mm_blendv_pd(off, on, mask);
#elif SIMDPP_USE_SSE2
    float64x2 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#endif
}

inline float64x2 blend(float64x2 on, float64x2 off, int128 mask)
{
    return blend(on, off, bit_cast<float64x2>(mask));
}

inline float64x4 blend(float64x4 on, float64x4 off, float64x4 mask)
{
#if SIMDPP_USE_AVX
    return _mm256_blendv_pd(off, on, mask);
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}

inline float64x4 blend(float64x4 on, float64x4 off, int256 mask)
{
    return blend(on, off, bit_cast<float64x4>(mask));
}

inline float64x2 blend(float64x2 on, float64x2 off, mask_float64x2 mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::blend_mask(on, off, mask);
#else
    return blend(on, off, uint64x2(mask));
#endif
}

inline float64x4 blend(float64x4 on, float64x4 off, mask_float64x4 mask)
{
#if SIMDPP_USE_AVX
    return blend(on, off, uint64x4(mask));
#else
    return {blend(on[0], off[0], mask[0]), blend(on[1], off[1], mask[1])};
#endif
}
/// @}

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
inline basic_int8x16 unzip_hi(basic_int8x16 a, basic_int8x16 b)
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

inline basic_int8x32 unzip_hi(basic_int8x32 a, basic_int8x32 b)
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
inline basic_int16x8 unzip_hi(basic_int16x8 a, basic_int16x8 b)
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

inline basic_int16x16 unzip_hi(basic_int16x16 a, basic_int16x16 b)
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
inline basic_int32x4 unzip_hi(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::unzip_hi(a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return shuffle2<1,3,1,3>(a, b);
#elif SIMDPP_USE_NEON
    return vuzpq_u32(a, b).val[1];
#endif
}

inline basic_int32x8 unzip_hi(basic_int32x8 a, basic_int32x8 b)
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
inline basic_int64x2 unzip_hi(basic_int64x2 a, basic_int64x2 b)
{
    return zip_hi(a, b);
}

inline basic_int64x4 unzip_hi(basic_int64x4 a, basic_int64x4 b)
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
