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

#ifndef LIBSIMDPP_SIMD_MATH_INT_ADV_H
#define LIBSIMDPP_SIMD_MATH_INT_ADV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/types.h>
#include <simdpp/simd/compare.h>
#include <simdpp/simd/math_shift.h>
#include <simdpp/simd/shuffle.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @ingroup simd_math_int
    @{
*/

/// @{
/** Computes minimum of signed 8-bit values.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 8}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline int8x16 min(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epi8(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector int8_t)a, (__vector int8_t)b);
#endif
}

inline int8x32 min(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_min_epi8(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes minimum of the unsigned 8-bit values.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint8x16 min(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vminq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline uint8x32 min(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_min_epu8(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes minimum of the signed 16-bit values.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int16x8 min(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vminq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector int16_t)a, (__vector int16_t)b);
#endif
}

inline int16x16 min(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_min_epi16(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes minimum of the unsigned 16-bit values.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6-7}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12-13}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline uint16x8 min(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epu16(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline uint16x16 min(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_min_epu16(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes minimum of the signed 32-bit values.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 8}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline int32x4 min(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epi32(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector int32_t)a, (__vector int32_t)b);
#endif
}

inline int32x8 min(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_min_epi32(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes minimum of the unsigned 32-bit values.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6-7}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12-13}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline uint32x4 min(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epu32(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline uint32x8 min(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_min_epu32(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maximum of the signed 8-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 8}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline int8x16 max(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epi8(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int8_t)a, (__vector int8_t)b);
#endif
}

inline int8x32 max(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_max_epi8(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maximum of the unsigned 8-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint8x16 max(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline uint8x32 max(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_max_epu8(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maximum of the signed 16-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int16x8 max(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int16_t)a, (__vector int16_t)b);
#endif
}

inline int16x16 max(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_max_epi16(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maximum of the unsigned 16-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6-7}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12-13}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline uint16x8 max(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epu16(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline uint16x16 max(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_max_epu16(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maximum of the signed 32-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 8}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline int32x4 max(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epi32(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int32_t)a, (__vector int32_t)b);
#endif
}


inline int32x8 max(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_max_epi32(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maximum of the unsigned 32-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6-7}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12-13}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
inline uint32x4 max(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epu32(a, b);
#elif SIMDPP_USE_SSE2
    int128 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline uint32x8 max(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_max_epu32(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes rounded average of the unsigned 8-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint8x16 avg(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint8x16>(a, b, [](uint8_t a, uint8_t b){
        return (uint16_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return _mm_avg_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline uint8x32 avg(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_avg_epu8(a, b);
#else
    return {avg(a[0], b[0]), avg(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes rounded average of signed 8-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, ALTIVEC, 2}
*/
inline int8x16 avg(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int8x16>(a, b, [](int8_t a, int8_t b){
        return (int16_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint8x16 a2, b2, bias, r;
    bias = uint8x16::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int8_t)a, (__vector int8_t)b);
#endif
}

inline int8x32 avg(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 a2, b2, bias, r;
    bias = uint8x32::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg(a[0], b[0]), avg(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes rounded average of unsigned 16-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint16x8 avg(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){
        return (uint32_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return _mm_avg_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline uint16x16 avg(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_avg_epu16(a, b);
#else
    return {avg(a[0], b[0]), avg(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes rounded average of signed 16-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, ALTIVEC, 2}
*/
inline int16x8 avg(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){
        return (int32_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint16x8 a2, b2, bias, r;
    bias = uint16x8::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int16_t)a, (__vector int16_t)b);
#endif
}

inline int16x16 avg(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 a2, b2, bias, r;
    bias = uint16x16::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg(a[0], b[0]), avg(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes rounded average of unsigned 32-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6-7}

    @par 256-bit version:
    @icost{SSE2-AVX, 12-13}
    @icost{AVX2, 6-7}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint32x4 avg(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint32x4>(a, b, [](uint32_t a, uint32_t b){
        return (uint64_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    // (x & y) + ((x ^ y) >> 1) + (x ^ y) & 1
    uint32x4 x1, x2, round;
    x1 = bit_and(a, b);
    x2 = bit_xor(a, b);
    round = bit_and(x2, uint32x4::make_const(1));
    x1 = add(x1, shift_r<1>(x2));
    x1 = add(x1, round);
    return x1;
#elif SIMDPP_USE_NEON
    return vrhaddq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline uint32x8 avg(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1) + (x ^ y) & 1
    uint32x8 x1, x2, round;
    x1 = bit_and(a, b);
    x2 = bit_xor(a, b);
    round = bit_and(x2, uint32x8::make_const(1));
    x1 = add(x1, shift_r<1>(x2));
    x1 = add(x1, round);
    return x1;
#else
    return {avg(a[0], b[0]), avg(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes rounded average of signed 32-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 9-10}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 18-19}
    @icost{AVX2, 9-10}
    @icost{NEON, ALTIVEC, 2}
*/
inline int32x4 avg(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int32x4>(a, b, [](int32_t a, int32_t b){
        return (int64_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint32x4 a2, b2, bias, r;
    bias = uint32x4::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int32_t)a, (__vector int32_t)b);
#endif
}

inline int32x8 avg(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 a2, b2, bias, r;
    bias = uint32x8::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg(a[0], b[0]), avg(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of the unsigned 8-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint8x16 avg_trunc(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint8x16>(a, b, [](uint8_t a, uint8_t b){
        return (uint16_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // (x & y) + ((x ^ y) >> 1)
    uint8x16 x1 = bit_and(a, b);
    uint8x16 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#elif SIMDPP_USE_NEON
    return vhaddq_u8(a, b);
#endif
}

inline uint8x32 avg_trunc(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1)
    uint8x32 x1 = bit_and(a, b);
    uint8x32 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of signed 8-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{NEON, ALTIVEC, 2}
*/
inline int8x16 avg_trunc(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int8x16>(a, b, [](int8_t a, int8_t b){
        return (int16_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 a2, b2, bias, r;
    bias = uint8x16::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vhaddq_s8(a, b);
#endif
}

inline int8x32 avg_trunc(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 a2, b2, bias, r;
    bias = uint8x32::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of unsigned 16-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint16x8 avg_trunc(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){
        return (uint32_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // (x & y) + ((x ^ y) >> 1)
    uint16x8 x1 = bit_and(a, b);
    uint16x8 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#elif SIMDPP_USE_NEON
    return vhaddq_u16(a, b);
#endif
}

inline uint16x16 avg_trunc(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1)
    uint16x16 x1 = bit_and(a, b);
    uint16x16 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of signed 16-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{NEON, ALTIVEC, 2}
*/
inline int16x8 avg_trunc(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){
        return (int32_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint16x8 a2, b2, bias, r;
    bias = uint16x8::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vhaddq_s16(a, b);
#endif
}

inline int16x16 avg_trunc(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 a2, b2, bias, r;
    bias = uint16x16::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of unsigned 32-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint32x4 avg_trunc(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint32x4>(a, b, [](uint32_t a, uint32_t b){
        return (uint64_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // (x & y) + ((x ^ y) >> 1)
    uint32x4 x1 = bit_and(a, b);
    uint32x4 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#elif SIMDPP_USE_NEON
    return vhaddq_u32(a, b);
#endif
}

inline uint32x8 avg_trunc(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1)
    uint32x8 x1 = bit_and(a, b);
    uint32x8 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of signed 32-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}
    @icost{ALTIVEC, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{ALTIVEC, 8}
    @icost{NEON, 2}
*/
inline int32x4 avg_trunc(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int32x4>(a, b, [](int32_t a, int32_t b){
        return (int64_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint32x4 a2, b2, bias, r;
    bias = uint32x4::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vhaddq_s32(a, b);
#endif
}

inline int32x8 avg_trunc(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 a2, b2, bias, r;
    bias = uint32x8::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 8-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-4}
*/
inline uint8x16 abs(int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi8(a);
#elif SIMDPP_USE_SSE2
    int8x16 t;
    t = cmp_lt(a, int8x16::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int8x16(vabsq_s8(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint8_t) vec_abs((__vector int8_t)a);
#endif
}

inline uint8x32 abs(int8x32 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_abs_epi8(a);
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 16-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-5}
*/
inline uint16x8 abs(int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi16(a);
#elif SIMDPP_USE_SSE2
    int16x8 t;
    t = cmp_lt(a, int16x8::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int16x8(vabsq_s16(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint16_t) vec_abs((__vector int16_t)a);
#endif
}

inline uint16x16 abs(int16x16 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_abs_epi16(a);
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 32-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-4}
*/
inline uint32x4 abs(int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi32(a);
#elif SIMDPP_USE_SSE2
    int32x4 t;
    t = cmp_lt(a, int32x4::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int32x4(vabsq_s32(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint32_t) vec_abs((__vector int32_t)a);
#endif
}

inline uint32x8 abs(int32x8 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_abs_epi32(a);
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 64-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{NEON, 6}
    @novec{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 10}
    @icost{NEON, 12}
    @icost{AVX2, 4}
    @novec{ALTIVEC}
*/
inline uint64x2 abs(int64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::abs(a);
#elif SIMDPP_USE_SSE2
    float64x2 ta;
    int64x2 t;
    ta = float64x2(shift_r<63>(uint64x2(a)));
    t = cmp_neq(ta, float64x2::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    int32x4 z = shift_r<63>(uint64x2(a));
    z = cmp_eq(z, int32x4::zero());
    z = permute<0,0,2,2>(z);
    z = bit_not(z);
    int64x2 t = z;
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#endif
}

inline uint64x4 abs(int64x4 a)
{
#if SIMDPP_USE_AVX2
    int64x4 t;
    t = _mm256_cmpgt_epi64(int64x4::zero(), a);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Divides one 8-bit unsigned number by another. The precision of the operation
    is configurable: only P least significant bits of both numerator and
    denumerator are considered.

    @code
    r0 = num0 / den0
    ...
    rN = numN / denN
    @endcode
    @par 128-bit version:
    The operations costs at least 9 instructions per bit of precision.

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 10}
    @icost{AVX2, 4}
*/
template<unsigned P>
uint8x16 div_p(uint8x16 num, uint8x16 den)
{
#if SIMDPP_USE_NULL
    return null::div_p<P>(num, den);
#else
    static_assert(P <= 8, "Precision too large");
    uint8x16 r, q, bit_mask;
    r = q = uint8x16::zero();
    bit_mask = uint8x16::make_const(1 << (P-1));

    for (unsigned i = P; i > 0; i--) {
        unsigned bit = i-1;
        uint8x16 n_bit;
        // we'll never shift out any bits, so larger shift doesn't matter
        r = shift_l<1>((uint16x8)r);

        n_bit = bit_and(num, bit_mask);
        n_bit = shift_r((uint16x8)n_bit, bit);
        r = bit_or(r, n_bit);

        uint8x16 cmp, csub, cbit;
        cmp = cmp_lt(r, den);

        csub = bit_andnot(den, cmp);
        cbit = bit_andnot(bit_mask, cmp);
        r = sub(r, csub);
        q = bit_or(q, cbit);

        bit_mask = shift_r<1>((uint16x8)bit_mask);
    }
    return q;

    /*
    The actual algorithm is as follows:
    N - numerator, D - denominator, R - remainder, Q - quetient
    R = 0; Q = 0;
    for (unsigned i = P; i > 0; i--) {
        unsigned bit = i-1;
        R <<= 1;
        R |= (N >> bit) & 1;
        if (R >= D) {
            R = R - D;
            Q |= 1 << bit;
        }
    }*/
#endif
}

template<unsigned P>
uint16x8 div_p(uint16x8 num, uint16x8 den)
{
#if SIMDPP_USE_NULL
    return null::div_p<P>(num, den);
#else
    static_assert(P <= 16, "Precision too large");
    uint16x8 r, q, bit_mask;

    r = q = uint16x8::zero();
    bit_mask = uint16x8::make_const(1 << (P-1));

    for (unsigned i = P; i > 0; i--) {
        unsigned bit = i-1; // TODO precision
        uint16x8 n_bit;
        r = shift_l<1>(r);

        n_bit = bit_and(num, bit_mask);
        n_bit = shift_r(n_bit, bit);
        r = bit_or(r, n_bit);

        uint16x8 cmp, csub, cbit;
        cmp = cmp_lt(r, den);

        csub = bit_andnot(den, cmp);
        cbit = bit_andnot(bit_mask, cmp);
        r = sub(r, csub);
        q = bit_or(q, cbit);

        bit_mask = shift_r<1>(bit_mask);
    }
    return q;
#endif
}
/// @}

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
