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
#include <simdpp/detail/null/math.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


SIMDPP_INL int8x16 i_min(const int8x16& a, const int8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::min(a, b);
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
SIMDPP_INL int8x32 i_min(const int8x32& a, const int8x32& b)
{
    return _mm256_min_epi8(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int8<N> i_min(const int8<N>& a, const int8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint8x16 i_min(const uint8x16& a, const uint8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vminq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_min(const uint8x32& a, const uint8x32& b)
{
    return _mm256_min_epu8(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_min(const uint8<N>& a, const uint8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL int16x8 i_min(const int16x8& a, const int16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vminq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int16x16 i_min(const int16x16& a, const int16x16& b)
{
    return _mm256_min_epi16(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int16<N> i_min(const int16<N>& a, const int16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_min(const uint16x8& a, const uint16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::min(a, b);
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
SIMDPP_INL uint16x16 i_min(const uint16x16& a, const uint16x16& b)
{
    return _mm256_min_epu16(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint16<N> i_min(const uint16<N>& a, const uint16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL int32x4 i_min(const int32x4& a, const int32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::min(a, b);
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
SIMDPP_INL int32x8 i_min(const int32x8& a, const int32x8& b)
{
    return _mm256_min_epi32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL int32<16> i_min(const int32<16>& a, const int32<16>& b)
{
    return _mm512_min_epi32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int32<N> i_min(const int32<N>& a, const int32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int32<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_min(const uint32x4& a, const uint32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::min(a, b);
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
SIMDPP_INL uint32x8 i_min(const uint32x8& a, const uint32x8& b)
{
    return _mm256_min_epu32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint32<16> i_min(const uint32<16>& a, const uint32<16>& b)
{
    return _mm512_min_epu32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_min(const uint32<N>& a, const uint32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_min, a, b);
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

