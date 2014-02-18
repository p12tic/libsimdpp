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
#include <simdpp/null/shuffle.h>
#include <simdpp/sse/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// forward declarations
template<unsigned s>
gint16x8 i_broadcast(gint16x8 a);

// -----------------------------------------------------------------------------

template<unsigned s>
gint8x16 i_broadcast(gint8x16 a)
{
    static_assert(s < 16, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_AVX2
    a = move_l<s>(a);
    return _mm_broadcastb_epi8(a);
#elif SIMDPP_USE_SSSE3
    uint8x16 mask = make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                              s,s,s,s,s,s,s,s>(mask);
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_SSE2
    gint16x8 b1, b2;

    if (s % 2 == 1) {
        b1 = _mm_srli_epi16(a, 8);
        b2 = _mm_slli_epi16(b1, 8);
    } else {
        b1 = _mm_slli_epi16(a, 8);
        b2 = _mm_srli_epi16(b1, 8);
    }
    b1 = bit_or(b1, b2);
    return (gint8<16>) i_broadcast<s/2>(b1);
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
template<unsigned s>
gint8x32 i_broadcast(gint8x32 a)
{
    static_assert(s < 16, "Access out of bounds");
    gint16x16 b = s < 8 ? zip_lo(a, a) : zip_hi(a, a);
    return i_broadcast<s%8>(b);
}
#endif

template<unsigned s, unsigned N>
gint8<N> i_broadcast(gint8<N> a)
{
    static_assert(s < 16, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(gint8<N>, i_broadcast<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint16x8 i_broadcast(gint16x8 a)
{
    static_assert(s < 8, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_AVX2
    a = move_l<s>(a);
    return _mm_broadcastw_epi16(a);
#elif SIMDPP_USE_SSSE3
    uint16x8 mask = make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_SSE2
    // s2 is needed because static_assert fires in branch we don't use
    gint64x2 b;
    if (s < 4) {
        constexpr unsigned s2 = s < 4 ? s : s-4;
        b = sse::permute_lo<s2,s2,s2,s2>(a);
        return (gint16<8>) permute2<0,0>(b);
    } else {
        constexpr unsigned s2 = s < 4 ? s : s-4;
        b = sse::permute_hi<s2,s2,s2,s2>(a);
        return (gint16<8>) permute2<1,1>(b);
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
template<unsigned s>
gint16x16 i_broadcast(gint16x16 a)
{
    static_assert(s < 8, "Access out of bounds");
    if (s < 4) {
        constexpr unsigned q = (s < 4) ? s : 0;
        gint64x4 h = _mm256_shufflelo_epi16(a, q << 6 | q << 4 | q << 2 | q);
        h = permute2<0,0>(h);
        return h;
    } else {
        constexpr unsigned q = (s < 4) ? 0 : s - 4;
        gint64x4 h = _mm256_shufflehi_epi16(a, q << 6 | q << 4 | q << 2 | q);
        h = permute2<1,1>(h);
        return h;
    }
}
#endif

template<unsigned s, unsigned N>
gint16<N> i_broadcast(gint16<N> a)
{
    static_assert(s < 8, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(gint16<N>, i_broadcast<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint32x4 i_broadcast(gint32x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
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
template<unsigned s>
gint32x8 i_broadcast(gint32x8 a)
{
    static_assert(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N>
gint32<N> i_broadcast(gint32<N> a)
{
    static_assert(s < 4, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(gint32x8, i_broadcast<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint64x2 i_broadcast(gint64x2 a)
{
    static_assert(s < 2, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
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
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<s, s>(mask);
    return permute_bytes16(a, mask);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint64x4 i_broadcast(gint64x4 a)
{
    static_assert(s < 2, "Access out of bounds");
    return permute2<s,s>(a);
}
#endif

template<unsigned s, unsigned N>
gint64<N> i_broadcast(gint64<N> a)
{
    static_assert(s < 2, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(gint64<N>, i_broadcast<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
float32x4 i_broadcast(float32x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_NULL
    return null::broadcast_w<s>(a);
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
template<unsigned s>
float32x8 i_broadcast(float32x8 a)
{
    static_assert(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N>
float32<N> i_broadcast(float32<N> a)
{
    static_assert(s < 4, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_broadcast<s>, a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
float64x2 i_broadcast(float64x2 a)
{
    static_assert(s < 2, "Access out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::broadcast_w<s>(a);
#elif SIMDPP_USE_SSE2
    if (s == 0) {
        return permute2<0,0>(a);
    } else {
        return permute2<1,1>(a);
    }
#elif SIMDPP_USE_NEON
    return float64x2(i_broadcast<s>(int64x2(a)));
#endif
}

#if SIMDPP_USE_AVX
template<unsigned s>
float64x4 i_broadcast(float64x4 a)
{
    static_assert(s < 2, "Access out of bounds");
    return permute2<s,s>(a);
}
#endif

template<unsigned s, unsigned N>
float64<N> i_broadcast(float64<N> a)
{
    static_assert(s < 2, "Access out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, i_broadcast<s>, a);
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

