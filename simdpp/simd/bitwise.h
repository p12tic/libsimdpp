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

#ifndef LIBSIMDPP_SIMD_BITWISE_H
#define LIBSIMDPP_SIMD_BITWISE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/bitwise.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @defgroup simd_bitwise Operations: bitwise
    @{
*/

/// @{
/** Computes bitwise AND of integer vectors.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 bit_and(basic_int8x16 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and(uint8x16(a), uint8x16(b));
#elif SIMDPP_USE_SSE2
    return _mm_and_si128(a, b);
#elif SIMDPP_USE_NEON
    return vandq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_and((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline basic_int16x8 bit_and(basic_int16x8 a, int128 b) { return bit_and(uint8x16(a), uint8x16(b)); }
inline basic_int32x4 bit_and(basic_int32x4 a, int128 b) { return bit_and(uint8x16(a), uint8x16(b)); }
inline basic_int64x2 bit_and(basic_int64x2 a, int128 b) { return bit_and(uint8x16(a), uint8x16(b)); }

inline basic_int8x32 bit_and(basic_int8x32 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_and_si256(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline basic_int16x16 bit_and(basic_int16x16 a, int256 b) { return bit_and(uint8x32(a), uint8x32(b)); }
inline basic_int32x8 bit_and(basic_int32x8 a, int256 b)   { return bit_and(uint8x32(a), uint8x32(b)); }
inline basic_int64x4 bit_and(basic_int64x4 a, int256 b)   { return bit_and(uint8x32(a), uint8x32(b)); }

// -----------------------------------------------------------------------------

inline basic_int8x16 bit_and(basic_int8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(a, uint8x16(b));
#endif
}

inline basic_int16x8 bit_and(basic_int16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

inline basic_int32x4 bit_and(basic_int32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

inline basic_int64x2 bit_and(basic_int64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

// -----------------------------------------------------------------------------

inline basic_int8x32 bit_and(basic_int8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(a, uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline basic_int16x16 bit_and(basic_int16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint8x32(a), uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline basic_int32x8 bit_and(basic_int32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint8x32(a), uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline basic_int64x4 bit_and(basic_int64x4 a, mask_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint8x32(a), uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

// -----------------------------------------------------------------------------

inline mask_int8x16 bit_and(mask_int8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_mm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

inline mask_int16x8 bit_and(mask_int16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_mm(a, b);
#else
    return bit_and(uint16x8(a), uint16x8(b));
#endif
}

inline mask_int32x4 bit_and(mask_int32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_mm(a, b);
#else
    return bit_and(uint32x4(a), uint32x4(b));
#endif
}

inline mask_int64x2 bit_and(mask_int64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_mm(a, b);
#else
    return bit_and(uint64x2(a), uint64x2(b));
#endif
}

inline mask_int8x32 bit_and(mask_int8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint8x32(a), uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline mask_int16x16 bit_and(mask_int16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint16x16(a), uint16x16(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline mask_int32x8 bit_and(mask_int32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint32x8(a), uint32x8(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline mask_int64x4 bit_and(mask_int64x4 a, mask_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint64x4(a), uint64x4(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise AND of floating-point vectors.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 bit_and(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_and_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32(a),
                                           vreinterpretq_u32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_and((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 bit_and(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_and_ps(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline float32x4 bit_and(float32x4 a, int128 b)
{
    return bit_and(a, bit_cast<float32x4>(b));
}

inline float32x8 bit_and(float32x8 a, int256 b)
{
    return bit_and(a, bit_cast<float32x8>(b));
}

inline float32x4 bit_and(float32x4 a, mask_float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(a, float32x4(b));
#endif
}

inline float32x8 bit_and(float32x8 a, mask_float32x8 b)
{
#if SIMDPP_USE_AVX
    return bit_and(a, float32x8(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline mask_float32x4 bit_and(mask_float32x4 a, mask_float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_mm(a, b);
#else
    return bit_and(float32x4(a), float32x4(b));
#endif
}

inline mask_float32x8 bit_and(mask_float32x8 a, mask_float32x8 b)
{
#if SIMDPP_USE_AVX
    return bit_and(float32x8(a), float32x8(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

// -----------------------------------------------------------------------------

inline float64x2 bit_and(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_and(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_and_pd(a, b);
#endif
}

inline float64x4 bit_and(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_and_pd(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline float64x2 bit_and(float64x2 a, int128 b)
{
    return bit_and(a, bit_cast<float64x2>(b));
}

inline float64x4 bit_and(float64x4 a, int256 b)
{
    return bit_and(a, bit_cast<float64x4>(b));
}

inline float64x2 bit_and(float64x2 a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_and_vm(a, b);
#else
    return bit_and(a, float64x2(b));
#endif
}

inline float64x4 bit_and(float64x4 a, mask_float64x4 b)
{
#if SIMDPP_USE_AVX
    return bit_and(a, float64x4(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline mask_float64x2 bit_and(mask_float64x2 a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_and_mm(a, b);
#else
    return bit_and(float64x2(a), float64x2(b));
#endif
}

inline mask_float64x4 bit_and(mask_float64x4 a, mask_float64x4 b)
{
#if SIMDPP_USE_AVX
    return bit_and(float64x4(a), float64x4(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

/// @}

/// @{
/** Computes bitwise AND NOT of integer vectors.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 bit_andnot(basic_int8x16 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot(uint8x16(a), uint8x16(b));
#elif SIMDPP_USE_SSE2
    return _mm_andnot_si128(b, a);
#elif SIMDPP_USE_NEON
    return vbicq_u8(a, b);;
#elif SIMDPP_USE_ALTIVEC
    return vec_andc((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline basic_int16x8 bit_andnot(basic_int16x8 a, int128 b) { return bit_andnot(uint8x16(a), uint8x16(b)); }
inline basic_int32x4 bit_andnot(basic_int32x4 a, int128 b) { return bit_andnot(uint8x16(a), uint8x16(b)); }
inline basic_int64x2 bit_andnot(basic_int64x2 a, int128 b) { return bit_andnot(uint8x16(a), uint8x16(b)); }

inline basic_int8x32 bit_andnot(basic_int8x32 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_andnot_si256(b, a);
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}
inline basic_int16x16 bit_andnot(basic_int16x16 a, int256 b) { return bit_andnot(uint8x32(a), uint8x32(b)); }
inline basic_int32x8 bit_andnot(basic_int32x8 a, int256 b)   { return bit_andnot(uint8x32(a), uint8x32(b)); }
inline basic_int64x4 bit_andnot(basic_int64x4 a, int256 b)   { return bit_andnot(uint8x32(a), uint8x32(b)); }

// -----------------------------------------------------------------------------

inline basic_int8x16 bit_andnot(basic_int8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_vm(a, b);
#else
    return bit_andnot(a, uint8x16(b));
#endif
}

inline basic_int16x8 bit_andnot(basic_int16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_vm(a, b);
#else
    return bit_andnot(uint8x16(a), uint8x16(b));
#endif
}

inline basic_int32x4 bit_andnot(basic_int32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_vm(a, b);
#else
    return bit_andnot(uint8x16(a), uint8x16(b));
#endif
}

inline basic_int64x2 bit_andnot(basic_int64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_vm(a, b);
#else
    return bit_andnot(uint8x16(a), uint8x16(b));
#endif
}

// -----------------------------------------------------------------------------

inline basic_int8x32 bit_andnot(basic_int8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(a, uint8x32(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline basic_int16x16 bit_andnot(basic_int16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint8x32(a), uint8x32(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline basic_int32x8 bit_andnot(basic_int32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint8x32(a), uint8x32(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline basic_int64x4 bit_andnot(basic_int64x4 a, mask_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint8x32(a), uint8x32(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

// -----------------------------------------------------------------------------

inline mask_int8x16 bit_andnot(mask_int8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_mm(a, b);
#else
    return bit_andnot(uint8x16(a), uint8x16(b));
#endif
}

inline mask_int16x8 bit_andnot(mask_int16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_mm(a, b);
#else
    return bit_andnot(uint16x8(a), uint16x8(b));
#endif
}

inline mask_int32x4 bit_andnot(mask_int32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_mm(a, b);
#else
    return bit_andnot(uint32x4(a), uint32x4(b));
#endif
}

inline mask_int64x2 bit_andnot(mask_int64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_mm(a, b);
#else
    return bit_andnot(uint64x2(a), uint64x2(b));
#endif
}

inline mask_int8x32 bit_andnot(mask_int8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint8x32(a), uint8x32(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline mask_int16x16 bit_andnot(mask_int16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint16x16(a), uint16x16(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline mask_int32x8 bit_andnot(mask_int32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint32x8(a), uint32x8(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline mask_int64x4 bit_andnot(mask_int64x4 a, mask_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_andnot(uint64x4(a), uint64x4(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise AND NOT of floating-point vectors.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline float32x4 bit_andnot(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_ps(b, a);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(a),
                                           vreinterpretq_u32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_andc((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 bit_andnot(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_andnot_ps(b, a);
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline float32x4 bit_andnot(float32x4 a, int128 b)
{
    return bit_andnot(a, bit_cast<float32x4>(b));
}

inline float32x8 bit_andnot(float32x8 a, int256 b)
{
    return bit_andnot(a, bit_cast<float32x8>(b));
}

inline float32x4 bit_andnot(float32x4 a, mask_float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_vm(a, b);
#else
    return bit_andnot(a, float32x4(b));
#endif
}

inline float32x8 bit_andnot(float32x8 a, mask_float32x8 b)
{
#if SIMDPP_USE_AVX
    return bit_andnot(a, float32x8(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline mask_float32x4 bit_andnot(mask_float32x4 a, mask_float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot_mm(a, b);
#else
    return bit_andnot(float32x4(a), float32x4(b));
#endif
}

inline mask_float32x8 bit_andnot(mask_float32x8 a, mask_float32x8 b)
{
#if SIMDPP_USE_AVX
    return bit_andnot(float32x8(a), float32x8(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

// -----------------------------------------------------------------------------

inline float64x2 bit_andnot(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_pd(b, a);
#endif
}

inline float64x4 bit_andnot(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_andnot_pd(b, a);
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline float64x2 bit_andnot(float64x2 a, int128 b)
{
    return bit_andnot(a, bit_cast<float64x2>(b));
}

inline float64x4 bit_andnot(float64x4 a, int256 b)
{
    return bit_andnot(a, bit_cast<float64x4>(b));
}

inline float64x2 bit_andnot(float64x2 a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_andnot_vm(a, b);
#else
    return bit_andnot(a, float64x2(b));
#endif
}

inline float64x4 bit_andnot(float64x4 a, mask_float64x4 b)
{
#if SIMDPP_USE_AVX
    return bit_andnot(a, float64x4(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline mask_float64x2 bit_andnot(mask_float64x2 a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_andnot_mm(a, b);
#else
    return bit_andnot(float64x2(a), float64x2(b));
#endif
}

inline mask_float64x4 bit_andnot(mask_float64x4 a, mask_float64x4 b)
{
#if SIMDPP_USE_AVX
    return bit_andnot(float64x4(a), float64x4(b));
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise OR of integer vectors.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 bit_or(basic_int8x16 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or(a, basic_int8x16(b));
#elif SIMDPP_USE_SSE2
    return _mm_or_si128(a, b);
#elif SIMDPP_USE_NEON
    return vorrq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline basic_int16x8 bit_or(basic_int16x8 a, int128 b) { return bit_or(uint8x16(a), uint8x16(b)); }
inline basic_int32x4 bit_or(basic_int32x4 a, int128 b) { return bit_or(uint8x16(a), uint8x16(b)); }
inline basic_int64x2 bit_or(basic_int64x2 a, int128 b) { return bit_or(uint8x16(a), uint8x16(b)); }

inline basic_int8x32 bit_or(basic_int8x32 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_or_si256(a, b);
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline basic_int16x16 bit_or(basic_int16x16 a, int256 b) { return bit_or(uint8x32(a), uint8x32(b)); }
inline basic_int32x8 bit_or(basic_int32x8 a, int256 b)   { return bit_or(uint8x32(a), uint8x32(b)); }
inline basic_int64x4 bit_or(basic_int64x4 a, int256 b)   { return bit_or(uint8x32(a), uint8x32(b)); }


inline mask_int8x16 bit_or(mask_int8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or_mm(a, b);
#else
    return bit_or(uint8x16(a), uint8x16(b));
#endif
}

inline mask_int16x8 bit_or(mask_int16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or_mm(a, b);
#else
    return bit_or(uint16x8(a), uint16x8(b));
#endif
}

inline mask_int32x4 bit_or(mask_int32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or_mm(a, b);
#else
    return bit_or(uint32x4(a), uint32x4(b));
#endif
}

inline mask_int64x2 bit_or(mask_int64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or_mm(a, b);
#else
    return bit_or(uint64x2(a), uint64x2(b));
#endif
}

inline mask_int8x32 bit_or(mask_int8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_or(uint8x32(a), uint8x32(b));
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline mask_int16x16 bit_or(mask_int16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_or(uint16x16(a), uint16x16(b));
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline mask_int32x8 bit_or(mask_int32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_or(uint32x8(a), uint32x8(b));
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline mask_int64x4 bit_or(mask_int64x4 a, mask_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_or(uint64x4(a), uint64x4(b));
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise OR of floating-point vectors

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 bit_or(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_or_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(a), vreinterpretq_s32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 bit_or(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_or_ps(a, b);
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline float32x4 bit_or(float32x4 a, int128 b)
{
    return bit_or(a, bit_cast<float32x4>(b));
}

inline float32x8 bit_or(float32x8 a, int256 b)
{
    return bit_or(a, bit_cast<float32x8>(b));
}

// -----------------------------------------------------------------------------

inline float64x2 bit_or(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_or(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_or_pd(a, b);
#endif
}

inline float64x4 bit_or(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_or_pd(a, b);
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline float64x2 bit_or(float64x2 a, int128 b)
{
    return bit_or(a, bit_cast<float64x2>(b));
}

inline float64x4 bit_or(float64x4 a, int256 b)
{
    return bit_or(a, bit_cast<float64x4>(b));
}

// -----------------------------------------------------------------------------

inline mask_float32x4 bit_or(mask_float32x4 a, mask_float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or_mm(a, b);
#else
    return bit_or(float32x4(a), float32x4(b));
#endif
}

inline mask_float64x2 bit_or(mask_float64x2 a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_or_mm(a, b);
#else
    return bit_or(float64x2(a), float64x2(b));
#endif
}

inline mask_float32x8 bit_or(mask_float32x8 a, mask_float32x8 b)
{
#if SIMDPP_USE_AVX
    return bit_or(float32x8(a), float32x8(b));
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline mask_float64x4 bit_or(mask_float64x4 a, mask_float64x4 b)
{
#if SIMDPP_USE_AVX
    return bit_or(float64x4(a), float64x4(b));
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise XOR of integer vectors.

    @code
    r0 = a0 ^ b0
    ...
    rN = aN ^ bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 bit_xor(basic_int8x16 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor(a, basic_int8x16(b));
#elif SIMDPP_USE_SSE2
    return _mm_xor_si128(a, b);
#elif SIMDPP_USE_NEON
    return veorq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline basic_int16x8 bit_xor(basic_int16x8 a, int128 b) { return bit_xor(uint8x16(a), uint8x16(b)); }
inline basic_int32x4 bit_xor(basic_int32x4 a, int128 b) { return bit_xor(uint8x16(a), uint8x16(b)); }
inline basic_int64x2 bit_xor(basic_int64x2 a, int128 b) { return bit_xor(uint8x16(a), uint8x16(b)); }

inline basic_int8x32 bit_xor(basic_int8x32 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_xor_si256(a, b);
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline basic_int16x16 bit_xor(basic_int16x16 a, int256 b) { return bit_xor(uint8x32(a), uint8x32(b)); }
inline basic_int32x8 bit_xor(basic_int32x8 a, int256 b)   { return bit_xor(uint8x32(a), uint8x32(b)); }
inline basic_int64x4 bit_xor(basic_int64x4 a, int256 b)   { return bit_xor(uint8x32(a), uint8x32(b)); }

// -----------------------------------------------------------------------------

inline mask_int8x16 bit_xor(mask_int8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor_mm(a, b);
#else
    return bit_xor(uint8x16(a), uint8x16(b));
#endif
}

inline mask_int16x8 bit_xor(mask_int16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor_mm(a, b);
#else
    return bit_xor(uint16x8(a), uint16x8(b));
#endif
}

inline mask_int32x4 bit_xor(mask_int32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor_mm(a, b);
#else
    return bit_xor(uint32x4(a), uint32x4(b));
#endif
}

inline mask_int64x2 bit_xor(mask_int64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor_mm(a, b);
#else
    return bit_xor(uint64x2(a), uint64x2(b));
#endif
}

inline mask_int8x32 bit_xor(mask_int8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_xor(uint8x32(a), uint8x32(b));
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline mask_int16x16 bit_xor(mask_int16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_xor(uint16x16(a), uint16x16(b));
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline mask_int32x8 bit_xor(mask_int32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_xor(uint32x8(a), uint32x8(b));
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline mask_int64x4 bit_xor(mask_int64x4 a, mask_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_xor(uint64x4(a), uint64x4(b));
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

/// @}

/// @{
/** Computes bitwise XOR of floating-point vectors

    @code
    r0 = a0 ^ b0
    ...
    rN = aN ^ bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 bit_xor(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(a), vreinterpretq_s32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 bit_xor(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_xor_ps(a, b);
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline float32x4 bit_xor(float32x4 a, int128 b)
{
    return bit_xor(a, bit_cast<float32x4>(b));
}

inline float32x8 bit_xor(float32x8 a, int256 b)
{
    return bit_xor(a, bit_cast<float32x8>(b));
}

// -----------------------------------------------------------------------------

inline float64x2 bit_xor(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_pd(a, b);
#endif
}

inline float64x4 bit_xor(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_xor_pd(a, b);
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline float64x2 bit_xor(float64x2 a, int128 b)
{
    return bit_xor(a, bit_cast<float64x2>(b));
}

inline float64x4 bit_xor(float64x4 a, int256 b)
{
    return bit_xor(a, bit_cast<float64x4>(b));
}

// -----------------------------------------------------------------------------

inline mask_float32x4 bit_xor(mask_float32x4 a, mask_float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor_mm(a, b);
#else
    return bit_xor(float32x4(a), float32x4(b));
#endif
}

inline mask_float64x2 bit_xor(mask_float64x2 a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_xor_mm(a, b);
#else
    return bit_xor(float64x2(a), float64x2(b));
#endif
}

inline mask_float32x8 bit_xor(mask_float32x8 a, mask_float32x8 b)
{
#if SIMDPP_USE_AVX
    return bit_xor(float32x8(a), float32x8(b));
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline mask_float64x4 bit_xor(mask_float64x4 a, mask_float64x4 b)
{
#if SIMDPP_USE_AVX
    return bit_xor(float64x4(a), float64x4(b));
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise NOT of an integer vector

    @code
    r = ~a
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 bit_not(basic_int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<basic_int8x16>(a, [](uint64_t a){ return ~a; });
#elif SIMDPP_USE_SSE2
    basic_int8x16 ones = basic_int8x16::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return vmvnq_u8(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector uint8_t)a, (__vector uint8_t)a);
#endif
}

inline basic_int16x8 bit_not(basic_int16x8 a) { return bit_not(uint8x16(a)); }
inline basic_int32x4 bit_not(basic_int32x4 a) { return bit_not(uint8x16(a)); }
inline basic_int64x2 bit_not(basic_int64x2 a) { return bit_not(uint8x16(a)); }

inline basic_int8x32 bit_not(basic_int8x32 a)
{
#if SIMDPP_USE_AVX2
    basic_int8x32 ones = basic_int8x32::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline basic_int16x16 bit_not(basic_int16x16 a) { return bit_not(uint8x32(a)); }
inline basic_int32x8 bit_not(basic_int32x8 a)   { return bit_not(uint8x32(a)); }
inline basic_int64x4 bit_not(basic_int64x4 a)   { return bit_not(uint8x32(a)); }

// -----------------------------------------------------------------------------

inline mask_int8x16 bit_not(mask_int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint8x16(a));
#endif
}

inline mask_int16x8 bit_not(mask_int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint16x8(a));
#endif
}

inline mask_int32x4 bit_not(mask_int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint32x4(a));
#endif
}

inline mask_int64x2 bit_not(mask_int64x2 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint64x2(a));
#endif
}

inline mask_int8x32 bit_not(mask_int8x32 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint8x32(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_int16x16 bit_not(mask_int16x16 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint16x16(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_int32x8 bit_not(mask_int32x8 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint32x8(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_int64x4 bit_not(mask_int64x4 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint64x4(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise NOT of a floating-point vector

    @code
    r = ~a
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
inline float32x4 bit_not(float32x4 a)
{
#if SIMDPP_USE_NULL
    return float32x4(bit_not(uint32x4(a)));
#elif SIMDPP_USE_SSE2
    uint32x4 ones = uint32x4::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return (float32x4) vmvnq_u32((uint32x4)a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector float)a, (__vector float)a);
#endif
}

inline float64x2 bit_not(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return float64x2(bit_not(uint64x2(a)));
#elif SIMDPP_USE_SSE2
    uint64x2 ones = uint64x2::ones();
    return bit_xor(a, ones);
#endif
}

inline float32x8 bit_not(float32x8 a)
{
#if SIMDPP_USE_AVX
    uint32x8 ones = uint32x8::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline float64x4 bit_not(float64x4 a)
{
#if SIMDPP_USE_AVX
    uint64x4 ones = uint64x4::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

// -----------------------------------------------------------------------------

inline mask_float32x4 bit_not(mask_float32x4 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(float32x4(a));
#endif
}

inline mask_float64x2 bit_not(mask_float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_not_mm(a);
#else
    return bit_not(float64x2(a));
#endif
}

inline mask_float32x8 bit_not(mask_float32x8 a)
{
#if SIMDPP_USE_AVX
    return bit_not(float32x8(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_float64x4 bit_not(mask_float64x4 a)
{
#if SIMDPP_USE_AVX
    return bit_not(float64x4(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}
/// @}

/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
