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

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_XOR_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_XOR_H

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
/** Computes bitwise XOR of integer vectors.

    @code
    r0 = a0 ^ b0
    ...
    rN = aN ^ bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint8x16 bit_xor(gint8x16 a, gint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor(a, gint8x16(b));
#elif SIMDPP_USE_SSE2
    return _mm_xor_si128(a, b);
#elif SIMDPP_USE_NEON
    return veorq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32 bit_xor(gint8x32 a, gint8x32 b)
{
    return _mm256_xor_si256(a, b);
}
#endif

template<unsigned N>
inline gint8<N> bit_xor(gint8<N> a, gint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint8x32, bit_xor, a, b)
}

template<unsigned N>
gint8<N> bit_xor(gint8<N> a, gint16<N/2> b) { return bit_xor(uint8<N>(a), uint8<N>(b)); }
template<unsigned N>
gint8<N> bit_xor(gint8<N> a, gint32<N/4> b) { return bit_xor(uint8<N>(a), uint8<N>(b)); }
template<unsigned N>
gint8<N> bit_xor(gint8<N> a, gint64<N/8> b) { return bit_xor(uint8<N>(a), uint8<N>(b)); }
template<unsigned N>
gint16<N> bit_xor(gint16<N> a, gint8<N*2> b) { return bit_xor(uint8<N*2>(a), uint8<N*2>(b)); }
template<unsigned N>
gint16<N> bit_xor(gint16<N> a, gint16<N> b) { return bit_xor(uint8<N*2>(a), uint8<N*2>(b)); }
template<unsigned N>
gint16<N> bit_xor(gint16<N> a, gint32<N/2> b) { return bit_xor(uint8<N*2>(a), uint8<N*2>(b)); }
template<unsigned N>
gint16<N> bit_xor(gint16<N> a, gint64<N/4> b) { return bit_xor(uint8<N*2>(a), uint8<N*2>(b)); }
template<unsigned N>
gint32<N> bit_xor(gint32<N> a, gint8<N*4> b) { return bit_xor(uint8<N*4>(a), uint8<N*4>(b)); }
template<unsigned N>
gint32<N> bit_xor(gint32<N> a, gint16<N/2> b) { return bit_xor(uint8<N*4>(a), uint8<N*4>(b)); }
template<unsigned N>
gint32<N> bit_xor(gint32<N> a, gint32<N> b) { return bit_xor(uint8<N*4>(a), uint8<N*4>(b)); }
template<unsigned N>
gint32<N> bit_xor(gint32<N> a, gint64<N*2> b) { return bit_xor(uint8<N*4>(a), uint8<N*4>(b)); }
template<unsigned N>
gint64<N> bit_xor(gint64<N> a, gint8<N*8> b) { return bit_xor(uint8<N*8>(a), uint8<N*8>(b)); }
template<unsigned N>
gint64<N> bit_xor(gint64<N> a, gint16<N/4> b) { return bit_xor(uint8<N*8>(a), uint8<N*8>(b)); }
template<unsigned N>
gint64<N> bit_xor(gint64<N> a, gint32<N/2> b) { return bit_xor(uint8<N*8>(a), uint8<N*8>(b)); }
template<unsigned N>
gint64<N> bit_xor(gint64<N> a, gint64<N> b) { return bit_xor(uint8<N*8>(a), uint8<N*8>(b)); }

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

#if SIMDPP_USE_AVX2
inline mask_int8x32  bit_xor(mask_int8x32 a,  mask_int8x32 b)  { return bit_xor(uint8x32(a), uint8x32(b)); }
inline mask_int16x16 bit_xor(mask_int16x16 a, mask_int16x16 b) { return bit_xor(uint8x32(a), uint8x32(b)); }
inline mask_int32x8  bit_xor(mask_int32x8 a,  mask_int32x8 b)  { return bit_xor(uint8x32(a), uint8x32(b)); }
inline mask_int64x4  bit_xor(mask_int64x4 a,  mask_int64x4 b)  { return bit_xor(uint8x32(a), uint8x32(b)); }
#endif

template<unsigned N>
mask_int8<N> bit_xor(mask_int8<N> a, mask_int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, bit_xor, a, b)
}

template<unsigned N>
mask_int16<N> bit_xor(mask_int16<N> a, mask_int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, bit_xor, a, b)
}

template<unsigned N>
mask_int32<N> bit_xor(mask_int32<N> a, mask_int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, bit_xor, a, b)
}

template<unsigned N>
mask_int64<N> bit_xor(mask_int64<N> a, mask_int64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int64<N>, bit_xor, a, b)
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

#if SIMDPP_USE_AVX
inline float32x8 bit_xor(float32x8 a, float32x8 b)
{
    return _mm256_xor_ps(a, b);
}
#endif

template<unsigned N>
float32<N> bit_xor(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, bit_xor, a, b)
}

template<unsigned N>
float32<N> bit_xor(float32<N> a, gint32<N> b)
{
    return bit_xor(a, float32<N>(b));
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

#if SIMDPP_USE_AVX
inline float64x4 bit_xor(float64x4 a, float64x4 b)
{
    return _mm256_xor_pd(a, b);
}
#endif

template<unsigned N>
float64<N> bit_xor(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, bit_xor, a, b)
}

template<unsigned N>
float64<N> bit_xor(float64<N> a, gint64<N> b)
{
    return bit_xor(a, float64<N>(b));
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

#if SIMDPP_USE_AVX
inline mask_float32x8 bit_xor(mask_float32x8 a, mask_float32x8 b)
{
    return bit_xor(float32x8(a), float32x8(b));
}
#endif

template<unsigned N>
mask_float32<N> bit_xor(mask_float32<N> a, mask_float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, bit_xor, a, b)
}

#if SIMDPP_USE_AVX
inline mask_float64x4 bit_xor(mask_float64x4 a, mask_float64x4 b)
{
    return bit_xor(float64x4(a), float64x4(b));
}
#endif

template<unsigned N>
mask_float64<N> bit_xor(mask_float64<N> a, mask_float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, bit_xor, a, b)
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


