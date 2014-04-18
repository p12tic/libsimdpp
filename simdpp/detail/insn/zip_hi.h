/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP_HI_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP_HI_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/neon/shuffle.h>
#include <simdpp/detail/null/shuffle.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline uint8x16 i_zip16_hi(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip16_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi8(a, b);
#elif SIMDPP_USE_NEON
    // the compiler will optimize multiple vzip instructions if both zip_hi
    // and zip_hi are used on the same arguments
    return vzipq_u8(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 i_zip16_hi(uint8x32 a, uint8x32 b)
{
    return _mm256_unpackhi_epi8(a, b);
}
#endif

template<unsigned N>
uint8<N> i_zip16_hi(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_zip16_hi, a, b)
}

// -----------------------------------------------------------------------------

inline uint16x8 i_zip8_hi(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip8_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u16(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint16x16 i_zip8_hi(uint16x16 a, uint16x16 b)
{
    return _mm256_unpackhi_epi16(a, b);
}
#endif

template<unsigned N>
uint16<N> i_zip8_hi(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_zip8_hi, a, b)
}

// -----------------------------------------------------------------------------

inline uint32x4 i_zip4_hi(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip4_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_u32(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint32x8 i_zip4_hi(uint32x8 a, uint32x8 b)
{
    return _mm256_unpackhi_epi32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
inline uint32<16> i_zip4_hi(uint32<16> a, uint32<16> b)
{
    return _mm512_unpackhi_epi32(a, b);
}
#endif

template<unsigned N>
uint32<N> i_zip4_hi(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_zip4_hi, a, b)
}

// -----------------------------------------------------------------------------

inline uint64x2 i_zip2_hi(uint64x2 a, uint64x2 b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip2_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_epi64(a, b);
#elif SIMDPP_USE_NEON
    return neon::zip2_hi(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<1, 3>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

#if SIMDPP_USE_AVX2
inline uint64x4 i_zip2_hi(uint64x4 a, uint64x4 b)
{
    return _mm256_unpackhi_epi64(a, b);
}
#endif

#if SIMDPP_USE_AVX512
inline uint64<8> i_zip2_hi(uint64<8> a, uint64<8> b)
{
    return _mm512_unpackhi_epi64(a, b);
}
#endif

template<unsigned N>
uint64<N> i_zip2_hi(uint64<N> a, uint64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, i_zip2_hi, a, b)
}

// -----------------------------------------------------------------------------

inline float32x4 i_zip4_hi(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::zip4_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_unpackhi_ps(a, b);
#elif SIMDPP_USE_NEON
    return vzipq_f32(a, b).val[1];
#elif SIMDPP_USE_ALTIVEC
    return vec_mergel((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_zip4_hi(float32x8 a, float32x8 b)
{
    return _mm256_unpackhi_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512
inline float32<16> i_zip4_hi(float32<16> a, float32<16> b)
{
    return _mm512_unpackhi_ps(a, b);
}
#endif

template<unsigned N>
float32<N> i_zip4_hi(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_zip4_hi, a, b)
}

// -----------------------------------------------------------------------------

inline float64x2 i_zip2_hi(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::zip2_hi(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_castps_pd(_mm_movehl_ps(_mm_castpd_ps(b),
                                       _mm_castpd_ps(a)));
#elif SIMDPP_USE_NEON
    return bit_cast<float64x2>(zip2_hi(int64x2(a), int64x2(b)));
#endif
}

#if SIMDPP_USE_AVX
inline float64x4 i_zip2_hi(float64x4 a, float64x4 b)
{
    return _mm256_unpackhi_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512
inline float64<8> i_zip2_hi(float64<8> a, float64<8> b)
{
    return _mm512_unpackhi_pd(a, b);
}
#endif

template<unsigned N>
float64<N> i_zip2_hi(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_zip2_hi, a, b)
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

