/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BROADCAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BROADCAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/permute2.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/permute_bytes16.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/detail/null/shuffle.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// forward declarations
template<unsigned s> SIMDPP_INL
uint16x8 i_splat8(const uint16x8& a);
#if SIMDPP_USE_AVX2
template<unsigned s> SIMDPP_INL
uint16x16 i_splat8(const uint16x16& a);
#endif

// -----------------------------------------------------------------------------

template<unsigned s> SIMDPP_INL
uint8x16 i_splat16(const uint8x16& ca)
{
    uint8<16> a = ca;
    SIMDPP_STATIC_ASSERT(s < 16, "Access out of bounds");
#if SIMDPP_USE_NULL
    return detail::null::splat<s>(a);
#elif SIMDPP_USE_AVX2
    a = move16_l<s>(a);
    return _mm_broadcastb_epi8(a);
#elif SIMDPP_USE_SSSE3
    uint8x16 mask = make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                              s,s,s,s,s,s,s,s>(mask);
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_SSE2
    uint16x8 b1, b2;

    if (s % 2 == 1) {
        b1 = _mm_srli_epi16(a, 8);
        b2 = _mm_slli_epi16(b1, 8);
    } else {
        b1 = _mm_slli_epi16(a, 8);
        b2 = _mm_srli_epi16(b1, 8);
    }
    b1 = bit_or(b1, b2);
    return (uint8<16>) i_splat8<s/2>(b1);
#elif SIMDPP_USE_NEON
    if (s < 8) {
        uint8x8_t z = vget_low_u8(a);
        return (uint8x16_t) vdupq_lane_u8(z, (s < 8 ? s : 0));
    } else {
        uint8x8_t z = vget_high_u8(a);
        return (uint8x16_t) vdupq_lane_u8(z, (s < 8 ? 0 : s-8));
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector uint8_t)a, s);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s> SIMDPP_INL
uint8x32 i_splat16(const uint8x32& a)
{
    SIMDPP_STATIC_ASSERT(s < 16, "Access out of bounds");
    uint16x16 b; b = s < 8 ? zip16_lo(a, a) : zip16_hi(a, a);
    return (uint8x32) i_splat8<s%8>(b);
}
#endif

template<unsigned s, unsigned N> SIMDPP_INL
uint8<N> i_splat16(const uint8<N>& a)
{
    SIMDPP_STATIC_ASSERT(s < 16, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_splat16<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s> SIMDPP_INL
uint16x8 i_splat8(const uint16x8& a)
{
    SIMDPP_STATIC_ASSERT(s < 8, "Access out of bounds");
#if SIMDPP_USE_NULL
    return detail::null::splat<s>(a);
#elif SIMDPP_USE_AVX2
    uint16<8> b = move8_l<s>(a);
    return _mm_broadcastw_epi16(b);
#elif SIMDPP_USE_SSSE3
    uint16x8 mask = make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_SSE2
    // s2 is needed because SIMDPP_STATIC_ASSERT fires in branch we don't use
    uint64x2 b;
    if (s < 4) {
        const unsigned s2 = s < 4 ? s : s-4;
        b = _mm_shufflelo_epi16(a, _MM_SHUFFLE(s2,s2,s2,s2));
        return (uint16<8>) permute2<0,0>(b);
    } else {
        const unsigned s2 = s < 4 ? s : s-4;
        b = _mm_shufflehi_epi16(a, _MM_SHUFFLE(s2,s2,s2,s2));
        return (uint16<8>) permute2<1,1>(b);
    }
#elif SIMDPP_USE_NEON
    if (s < 4) {
        uint16x4_t z = vget_low_u16(a);
        return (uint16x8_t) vdupq_lane_u16(z, (s < 4 ? s : 0));
    } else {
        uint16x4_t z = vget_high_u16(a);
        return (uint16x8_t) vdupq_lane_u16(z, (s < 4 ? 0 : s-4));
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector uint16_t)a, s);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s> SIMDPP_INL
uint16x16 i_splat8(const uint16x16& a)
{
    SIMDPP_STATIC_ASSERT(s < 8, "Access out of bounds");
    if (s < 4) {
        const unsigned q = (s < 4) ? s : 0;
        uint64x4 h = _mm256_shufflelo_epi16(a, q << 6 | q << 4 | q << 2 | q);
        h = permute2<0,0>(h);
        return uint16x16(h);
    } else {
        const unsigned q = (s < 4) ? 0 : s - 4;
        uint64x4 h = _mm256_shufflehi_epi16(a, q << 6 | q << 4 | q << 2 | q);
        h = permute2<1,1>(h);
        return uint16x16(h);
    }
}
#endif

template<unsigned s, unsigned N> SIMDPP_INL
uint16<N> i_splat8(const uint16<N>& a)
{
    SIMDPP_STATIC_ASSERT(s < 8, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint16<N>, i_splat8<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s> SIMDPP_INL
uint32x4 i_splat4(const uint32x4& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
#if SIMDPP_USE_NULL
    return detail::null::splat<s>(a);
#elif SIMDPP_USE_SSE2
    return permute4<s,s,s,s>(a);
#elif SIMDPP_USE_NEON
    if (s < 2) {
        uint32x2_t z = vget_low_u32(a);
        // Clang implements vdupq_lane_u32 as a macro, thus we must never
        // supply it with s>=2, even if we know the branch will never be executed
        return (uint32x4_t) vdupq_lane_u32(z, (s < 2 ? s : 0));
    } else {
        uint32x2_t z = vget_high_u32(a);
        return (uint32x4_t) vdupq_lane_u32(z, (s < 2 ? 0 : s-2));
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector uint32_t)a, s);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s> SIMDPP_INL
uint32x8 i_splat4(const uint32x8& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif\

#if SIMDPP_USE_AVX512F
template<unsigned s> SIMDPP_INL
uint32<16> i_splat4(const uint32<16>& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N> SIMDPP_INL
uint32<N> i_splat4(const uint32<N>& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, i_splat4<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s> SIMDPP_INL
uint64x2 i_splat2(const uint64x2& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::splat<s>(a);
#elif SIMDPP_USE_SSE2
    if (s == 0) {
        return permute2<0,0>(a);
    } else {
        return permute2<1,1>(a);
    }
#elif SIMDPP_USE_NEON
    uint64x1_t z;
    if (s == 0) {
        z = vget_low_u64(a);
    } else {
        z = vget_high_u64(a);
    }
    return (uint64x2_t) vdupq_lane_u64(z, 0);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s> SIMDPP_INL
uint64x4 i_splat2(const uint64x4& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
    return permute2<s,s>(a);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned s> SIMDPP_INL
uint64<8> i_splat2(const uint64<8>& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
    return permute2<s,s>(a);
}
#endif

template<unsigned s, unsigned N> SIMDPP_INL
uint64<N> i_splat2(const uint64<N>& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, i_splat2<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s> SIMDPP_INL
float32x4 i_splat4(const float32x4& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::splat<s>(a);
#elif SIMDPP_USE_SSE2
    return permute4<s,s,s,s>(a);
#elif SIMDPP_USE_NEON
    if (s < 2) {
        float32x2_t z = vget_low_f32(a);
        // Clang implements vdupq_lane_f32 as a macro, thus we must never
        // supply it with s>=2, even if we know the branch will never be executed
        return (float32x4_t) vdupq_lane_f32(z, (s < 2 ? s : 0));
    } else {
        float32x2_t z = vget_high_f32(a);
        return (float32x4_t) vdupq_lane_f32(z, (s < 2 ? 0 : s-2) );
    }
#elif SIMDPP_USE_ALTIVEC
    return vec_splat((__vector float)a, s);
#endif
}

#if SIMDPP_USE_AVX
template<unsigned s> SIMDPP_INL
float32x8 i_splat4(const float32x8& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned s> SIMDPP_INL
float32<16> i_splat4(const float32<16>& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N> SIMDPP_INL
float32<N> i_splat4(const float32<N>& a)
{
    SIMDPP_STATIC_ASSERT(s < 4, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_splat4<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s> SIMDPP_INL
float64x2 i_splat2(const float64x2& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON32
    return detail::null::splat<s>(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON64
    return permute2<s,s>(a);
#endif
}

#if SIMDPP_USE_AVX
template<unsigned s> SIMDPP_INL
float64x4 i_splat2(const float64x4& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
    return permute2<s,s>(a);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned s> SIMDPP_INL
float64<8> i_splat2(const float64<8>& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
    return permute2<s,s>(a);
}
#endif

template<unsigned s, unsigned N> SIMDPP_INL
float64<N> i_splat2(const float64<N>& a)
{
    SIMDPP_STATIC_ASSERT(s < 2, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, i_splat2<s>, a);
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

