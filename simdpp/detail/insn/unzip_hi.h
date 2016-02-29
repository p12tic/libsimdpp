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
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL uint8x16 i_unzip16_hi(const uint8x16& ca, const uint8x16& cb)
{
    uint8<16> a = ca, b = cb;
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
    return vec_pack((__vector uint16_t)(__vector uint8_t)a, (__vector uint16_t)(__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_unzip16_hi(const uint8x32& ca, const uint8x32& cb)
{
    uint8<32> a = ca, b = cb;
    a = _mm256_srai_epi16(a, 8);
    b = _mm256_srai_epi16(b, 8);
    a = _mm256_packs_epi16(a, b);
    return a;
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_unzip16_hi(const uint8<N>& a, const uint8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_unzip16_hi, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_unzip8_hi(const uint16x8& ca, const uint16x8& cb)
{
    uint16<8> a = ca, b = cb;
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
    return vec_pack((__vector uint32_t)(__vector uint16_t)a, (__vector uint32_t)(__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16x16 i_unzip8_hi(const uint16x16& ca, const uint16x16& cb)
{
    uint16<16> a = ca, b = cb;
    a = _mm256_srai_epi32(a, 16);
    b = _mm256_srai_epi32(b, 16);
    a = _mm256_packs_epi32(a, b);
    return a;
}
#endif

template<unsigned N> SIMDPP_INL
uint16<N> i_unzip8_hi(const uint16<N>& a, const uint16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_unzip8_hi, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_unzip4_hi(const uint32x4& a, const uint32x4& b)
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
SIMDPP_INL uint32x8 i_unzip4_hi(const uint32x8& a, const uint32x8& b)
{
    return shuffle2<1,3,1,3>(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_unzip4_hi(const uint32<16>& a, const uint32<16>& b)
{
    return shuffle2<1,3,1,3>(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_unzip4_hi(const uint32<N>& a, const uint32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_unzip4_hi, a, b)
}

// -----------------------------------------------------------------------------

template<unsigned N> SIMDPP_INL
uint64<N> i_unzip2_hi(const uint64<N>& a, const uint64<N>& b)
{
    return i_zip2_hi(a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL float32x4 i_unzip4_hi(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
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
SIMDPP_INL float32x8 i_unzip4_hi(const float32x8& a, const float32x8& b)
{
    return shuffle2<1,3,1,3>(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_unzip4_hi(const float32<16>& a, const float32<16>& b)
{
    return shuffle2<1,3,1,3>(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_unzip4_hi(const float32<N>& a, const float32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_unzip4_hi, a, b)
}

// -----------------------------------------------------------------------------

template<unsigned N> SIMDPP_INL
float64<N> i_unzip2_hi(const float64<N>& a, const float64<N>& b)
{
    return i_zip2_hi(a, b);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

