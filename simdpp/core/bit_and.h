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

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_AND_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_AND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/foreach.h>
#include <simdpp/null/bitwise.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

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
inline gint8x16 bit_and(gint8x16 a, int128 b)
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

inline gint8x32 bit_and(gint8x32 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_and_si256(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

template<unsigned N>
gint16<N> bit_and(gint16<N> a, int_bits<N*2> b) { return bit_and(uint8<N*2>(a), uint8<N*2>(b)); }
template<unsigned N>
gint32<N> bit_and(gint32<N> a, int_bits<N*4> b) { return bit_and(uint8<N*4>(a), uint8<N*4>(b)); }
template<unsigned N>
gint64<N> bit_and(gint64<N> a, int_bits<N*8> b) { return bit_and(uint8<N*8>(a), uint8<N*8>(b)); }

// -----------------------------------------------------------------------------

inline gint8x16 bit_and(gint8x16 a, mask_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(a, uint8x16(b));
#endif
}

inline gint16x8 bit_and(gint16x8 a, mask_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

inline gint32x4 bit_and(gint32x4 a, mask_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

inline gint64x2 bit_and(gint64x2 a, mask_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and_vm(a, b);
#else
    return bit_and(uint8x16(a), uint8x16(b));
#endif
}

// -----------------------------------------------------------------------------

inline gint8x32 bit_and(gint8x32 a, mask_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(a, uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline gint16x16 bit_and(gint16x16 a, mask_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint8x32(a), uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline gint32x8 bit_and(gint32x8 a, mask_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_and(uint8x32(a), uint8x32(b));
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline gint64x4 bit_and(gint64x4 a, mask_int64x4 b)
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

