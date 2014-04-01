/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_MIN_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_MIN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline int8x16 i_min(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epi8(a, b);
#elif SIMDPP_USE_SSE2
    mask_int8x16 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int8x32 i_min(int8x32 a, int8x32 b)
{
    return _mm256_min_epi8(a, b);
}
#endif

template<unsigned N>
int8<N> i_min(int8<N> a, int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

inline uint8x16 i_min(uint8x16 a, uint8x16 b)
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

#if SIMDPP_USE_AVX2
inline uint8x32 i_min(uint8x32 a, uint8x32 b)
{
    return _mm256_min_epu8(a, b);
}
#endif

template<unsigned N>
uint8<N> i_min(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

inline int16x8 i_min(int16x8 a, int16x8 b)
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

#if SIMDPP_USE_AVX2
inline int16x16 i_min(int16x16 a, int16x16 b)
{
    return _mm256_min_epi16(a, b);
}
#endif

template<unsigned N>
int16<N> i_min(int16<N> a, int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

inline uint16x8 i_min(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epu16(a, b);
#elif SIMDPP_USE_SSE2
    mask_int16x8 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint16x16 i_min(uint16x16 a, uint16x16 b)
{
    return _mm256_min_epu16(a, b);
}
#endif

template<unsigned N>
uint16<N> i_min(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

inline int32x4 i_min(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epi32(a, b);
#elif SIMDPP_USE_SSE2
    mask_int32x4 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int32x8 i_min(int32x8 a, int32x8 b)
{
    return _mm256_min_epi32(a, b);
}
#endif

template<unsigned N>
int32<N> i_min(int32<N> a, int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int32<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

inline uint32x4 i_min(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_min_epu32(a, b);
#elif SIMDPP_USE_SSE2
    mask_int32x4 mask = cmp_lt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vminq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint32x8 i_min(uint32x8 a, uint32x8 b)
{
    return _mm256_min_epu32(a, b);
}
#endif

template<unsigned N>
uint32<N> i_min(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_min, a, b);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

