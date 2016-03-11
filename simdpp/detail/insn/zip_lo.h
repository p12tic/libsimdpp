/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP_LO_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP_LO_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/shuffle_bytes16.h>
#include <simdpp/detail/null/shuffle.h>
#include <simdpp/detail/neon/shuffle.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL uint8x16 i_zip16_lo(const uint8x16& a, const uint8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip16_lo(a, b);
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

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_zip16_lo(const uint8x32& a, const uint8x32& b)
{
    return _mm256_unpacklo_epi8(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_zip16_lo(const uint8<N>& a, const uint8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_zip16_lo, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_zip8_lo(const uint16x8& a, const uint16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip8_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u16(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16x16 i_zip8_lo(const uint16x16& a, const uint16x16& b)
{
    return _mm256_unpacklo_epi16(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint16<N> i_zip8_lo(const uint16<N>& a, const uint16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_zip8_lo, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_zip4_lo(const uint32x4& a, const uint32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip4_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u32(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32x8 i_zip4_lo(const uint32x8& a, const uint32x8& b)
{
    return _mm256_unpacklo_epi32(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_zip4_lo(const uint32<16>& a, const uint32<16>& b)
{
    return _mm512_unpacklo_epi32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_zip4_lo(const uint32<N>& a, const uint32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_zip4_lo, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint64x2 i_zip2_lo(const uint64x2& a, const uint64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::zip2_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_epi64(a, b);
#elif SIMDPP_USE_NEON
    return neon::zip2_lo(a, b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64x4 i_zip2_lo(const uint64x4& a, const uint64x4& b)
{
    return _mm256_unpacklo_epi64(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_zip2_lo(const uint64<8>& a, const uint64<8>& b)
{
    return _mm512_unpacklo_epi64(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint64<N> i_zip2_lo(const uint64<N>& a, const uint64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, i_zip2_lo, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL float32x4 i_zip4_lo(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::zip4_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpacklo_ps(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_f32(a, b).val[0];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergeh((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_zip4_lo(const float32x8& a, const float32x8& b)
{
    return _mm256_unpacklo_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_zip4_lo(const float32<16>& a, const float32<16>& b)
{
    return _mm512_unpacklo_ps(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_zip4_lo(const float32<N>& a, const float32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_zip4_lo, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL float64x2 i_zip2_lo(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON32
    return detail::null::zip2_lo(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_castps_pd(_mm_movelh_ps(_mm_castpd_ps(a),
                                       _mm_castpd_ps(b)));
#elif SIMDPP_USE_NEON64
    return vtrn1q_f64(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64x4 i_zip2_lo(const float64x4& a, const float64x4& b)
{
    return _mm256_unpacklo_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_zip2_lo(const float64<8>& a, const float64<8>& b)
{
    return _mm512_unpacklo_pd(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_zip2_lo(const float64<N>& a, const float64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_zip2_lo, a, b)
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
