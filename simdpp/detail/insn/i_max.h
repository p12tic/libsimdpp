/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_MAX_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_MAX_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/cmp_gt.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


SIMDPP_INL int8x16 i_max(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epi8(a, b);
#elif SIMDPP_USE_SSE2
    mask_int8x16 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int8x32 i_max(int8x32 a, int8x32 b)
{
    return _mm256_max_epi8(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int8<N> i_max(int8<N> a, int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint8x16 i_max(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_max(uint8x32 a, uint8x32 b)
{
    return _mm256_max_epu8(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_max(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL int16x8 i_max(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int16x16 i_max(int16x16 a, int16x16 b)
{
    return _mm256_max_epi16(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int16<N> i_max(int16<N> a, int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_max(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epu16(a, b);
#elif SIMDPP_USE_SSE2
    mask_int16x8 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16x16 i_max(uint16x16 a, uint16x16 b)
{
    return _mm256_max_epu16(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint16<N> i_max(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL int32x4 i_max(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epi32(a, b);
#elif SIMDPP_USE_SSE2
    mask_int32x4 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int32x8 i_max(int32x8 a, int32x8 b)
{
    return _mm256_max_epi32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL int32<16> i_max(int32<16> a, int32<16> b)
{
    return _mm512_max_epi32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int32<N> i_max(int32<N> a, int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int32<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_max(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epu32(a, b);
#elif SIMDPP_USE_SSE2
    mask_int32x4 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32x8 i_max(uint32x8 a, uint32x8 b)
{
    return _mm256_max_epu32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint32<16> i_max(uint32<16> a, uint32<16> b)
{
    return _mm512_max_epu32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_max(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_max, a, b);
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

