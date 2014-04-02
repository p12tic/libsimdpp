/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_UNZIP_HI_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_UNZIP_HI_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/detail/null/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

inline uint8x16 i_unzip16_hi(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return detail::null::unzip16_hi(a, b);
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

#if SIMDPP_USE_AVX2
inline uint8x32 i_unzip16_hi(uint8x32 a, uint8x32 b)
{
    a = _mm256_srai_epi16(a, 8);
    b = _mm256_srai_epi16(b, 8);
    a = _mm256_packs_epi16(a, b);
    return a;
}
#endif

template<unsigned N>
uint8<N> i_unzip16_hi(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_unzip16_hi, a, b)
}

// -----------------------------------------------------------------------------

inline uint16x8 i_unzip8_hi(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return detail::null::unzip8_hi(a, b);
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

#if SIMDPP_USE_AVX2
inline uint16x16 i_unzip8_hi(uint16x16 a, uint16x16 b)
{
    a = _mm256_srai_epi32(a, 16);
    b = _mm256_srai_epi32(b, 16);
    a = _mm256_packs_epi32(a, b);
    return a;
}
#endif

template<unsigned N>
uint16<N> i_unzip8_hi(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_unzip8_hi, a, b)
}

// -----------------------------------------------------------------------------

inline uint32x4 i_unzip4_hi(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::unzip4_hi(a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return shuffle2<1,3,1,3>(a, b);
#elif SIMDPP_USE_NEON
    return vuzpq_u32(a, b).val[1];
#endif
}

#if SIMDPP_USE_AVX2
inline uint32x8 i_unzip4_hi(uint32x8 a, uint32x8 b)
{
    return shuffle2<1,3,1,3>(a, b);
}
#endif

template<unsigned N>
uint32<N> i_unzip4_hi(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_unzip4_hi, a, b)
}

// -----------------------------------------------------------------------------

template<unsigned N>
uint64<N> i_unzip2_hi(uint64<N> a, uint64<N> b)
{
    return i_zip2_hi(a, b);
}

// -----------------------------------------------------------------------------

inline float32x4 i_unzip4_hi(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::unzip4_hi(a, b);
#elif SIMDPP_USE_SSE2
    return shuffle2<1,3,1,3>(a,b);
#elif SIMDPP_USE_NEON
    return vuzpq_f32(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return float32x4(i_unzip4_hi((uint32x4)a, (uint32x4)b));
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_unzip4_hi(float32x8 a, float32x8 b)
{
    return shuffle2<1,3,1,3>(a, b);
}
#endif

template<unsigned N>
float32<N> i_unzip4_hi(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_unzip4_hi, a, b)
}

// -----------------------------------------------------------------------------

template<unsigned N>
float64<N> i_unzip2_hi(float64<N> a, float64<N> b)
{
    return i_zip2_hi(a, b);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

