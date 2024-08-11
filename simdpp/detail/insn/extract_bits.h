/*  Copyright (C) 2011-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_EXTRACT_BITS_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_EXTRACT_BITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/extract.h>
#include <simdpp/core/i_shift_l.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/core/make_uint.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/unzip_lo.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL uint16_t i_extract_bits_any(const uint8<16>& ca)
{
    uint8<16> a = ca;
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    for (unsigned i = 0; i < a.length; i++) {
        uint8_t x = ca.el(i);
        x = x & 1;
        r = (r >> 1) | (uint16_t(x) << 15);
    }
    return r;
#elif SIMDPP_USE_SSE2
    // Note that i_extract_bits depends on the exact implementation of this
    // function.
    return _mm_movemask_epi8(a.native());
#elif SIMDPP_USE_NEON
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

    a = bit_and(a, mask);
    uint16<8> a16 = vpaddlq_u8(a.native());
    uint32<4> a32 = vpaddlq_u16(a16.native());
    uint8<16> a8 = vreinterpretq_u8_u64(vpaddlq_u32(a32.native()));
    uint8x8_t r = vzip_u8(vget_low_u8(a8.native()), vget_high_u8(a8.native())).val[0];
    return vget_lane_u16(vreinterpret_u16_u8(r), 0);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);
    a = bit_and(a, mask);
    uint32<4> zero = make_zero();
    uint32x4 s = vec_sum4s(a.native(), zero.native());
    uint32x4 shifts = make_uint(0, 0, 8, 8);
    s = (__vector uint32_t) vec_sl(s.native(), shifts.native());
    s = (int32x4)vec_sums((__vector int32_t)s.native(),
                          (__vector int32_t)zero.native());
#if SIMDPP_BIG_ENDIAN
    return extract<7>(uint16x8(s));
#else
    return extract<6>(uint16x8(s));
#endif
#elif SIMDPP_USE_MSA
    // Note: the implementation of extract_bits depends of the exact behavior
    // of this function
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

    a = bit_and(a, mask);
    uint16<8> a16 = __msa_hadd_u_h(a.native(), a.native());
    uint32<4> a32 = __msa_hadd_u_w(a16.native(), a16.native());
    a = (v16u8) __msa_hadd_u_d(a32.native(), a32.native());
    a = bit_or(a, move16_l<7>(a));
    return extract<0>((uint16<8>)a);
#endif
}

SIMDPP_INL uint32_t i_extract_bits_any(const uint8<32>& ca)
{
#if SIMDPP_USE_AVX2
    return _mm256_movemask_epi8(ca.native());
#else
    uint8<16> lo, hi;
    lo = ca.vec<0>();
    hi = ca.vec<1>();
    return i_extract_bits_any(lo) | (i_extract_bits_any(hi) << 16);
#endif
}

SIMDPP_INL uint8_t i_extract_bits_any(const uint16<8>& ca)
{
#if SIMDPP_USE_NULL
    uint8_t r = 0;
    for (unsigned i = 0; i < ca.length; i++) {
        uint16_t x = ca.el(i);
        x = x & 1;
        r = (r >> 1) | (x << 7);
    }
    return r;
#elif SIMDPP_USE_AVX512BW
    return _mm_movepi16_mask(ca.native());
#elif SIMDPP_USE_SSE2
    uint8<16> zero = make_zero();
    uint8<16> a = unzip16_lo(uint8<16>(ca), zero);
    return _mm_movemask_epi8(a.native());
#elif SIMDPP_USE_NEON
    uint16<8> mask = make_uint(0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080);
    uint16<8> a = bit_and(ca, mask);
    uint32<4> a32 = vpaddlq_u16(a.native());
    uint64x2_t r2 = vpaddlq_u32(a32.native());
    uint64x1_t r = vadd_u64(vget_low_u64(r2), vget_high_u64(r2));
    return vget_lane_u8(vreinterpret_u8_u64(r), 0);
#elif SIMDPP_USE_ALTIVEC
    uint16<8> mask = make_uint(0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080);
    uint16<8> a = bit_and(ca, mask);
    uint32<4> zero = make_zero();
    uint32<4> s = vec_sum4s((__vector uint8_t)a.native(), zero.native());
    s = (int32x4)vec_sums((__vector int32_t)s.native(),
                           (__vector int32_t)zero.native());
#if SIMDPP_BIG_ENDIAN
    return extract<7>(uint16x8(s));
#else
    return extract<6>(uint16x8(s));
#endif
#elif SIMDPP_USE_MSA
    uint16<8> mask = make_uint(0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080);
    uint16<8> a = bit_and(ca, mask);
    uint32<4> a32 = __msa_hadd_u_w(a.native(), a.native());
    a = (v8u16) __msa_hadd_u_d(a32.native(), a32.native());
    a = bit_or(a, move8_l<4>(a));
    return extract<0>(a);
#endif
}

SIMDPP_INL uint16_t i_extract_bits_any(const uint16<16>& ca)
{
#if SIMDPP_USE_AVX512BW
    return _mm256_movepi16_mask(ca.native());
#elif SIMDPP_USE_AVX2
    uint8<32> zero = make_zero();
    uint8<32> a = unzip16_lo(uint8<32>(ca), zero);
    return _mm_movemask_epi8(_mm256_extracti128_si256(_mm256_permute4x64_epi64(a.native(), 0x08), 0));
#else
    uint16<8> lo, hi;
    lo = ca.vec<0>();
    hi = ca.vec<1>();
    return i_extract_bits_any(lo) | (i_extract_bits_any(hi) << 8);
#endif
}

SIMDPP_INL uint8_t i_extract_bits_any(const uint32<4>& ca)
{
    uint32<4> a = ca;
#if SIMDPP_USE_NULL
    uint8_t r = 0;
    for (unsigned i = 0; i < a.length; i++) {
        uint8_t x = ca.el(i);
        x = x & 1;
        r = (r >> 1) | (x << 3);
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_movemask_ps(_mm_castsi128_ps(a.native()));
#elif SIMDPP_USE_NEON
    uint32<4> mask = make_uint(0x1, 0x2, 0x4, 0x8);
    a = bit_and(a, mask);
    uint64x2_t r2 = vpaddlq_u32(a.native());
    uint64x1_t r = vadd_u64(vget_low_u64(r2), vget_high_u64(r2));
    return vget_lane_u8(vreinterpret_u8_u64(r), 0);
#elif SIMDPP_USE_ALTIVEC
    uint32<4> mask = make_uint(0x1, 0x2, 0x4, 0x8);
    a = bit_and(a, mask);
    uint32<4> zero = make_zero();
    uint32<4> s = (int32x4)vec_sums((__vector int32_t)a.native(),
                                    (__vector int32_t)zero.native());
#if SIMDPP_BIG_ENDIAN
    return extract<7>(uint16x8(s));
#else
    return extract<6>(uint16x8(s));
#endif
#elif SIMDPP_USE_MSA
    uint32<4> mask = make_uint(0x1, 0x2, 0x4, 0x8);
    a = bit_and(a, mask);
    a = (v4u32) __msa_hadd_u_d(a.native(), a.native());
    a = bit_or(a, move4_l<2>(a));
    return extract<0>(a);
#endif
}

SIMDPP_INL uint8_t i_extract_bits_any(const uint32<8>& ca)
{
#if SIMDPP_USE_AVX512DQ
    return _mm256_movepi32_mask(ca.native());
#elif SIMDPP_USE_AVX2
    return _mm256_movemask_ps(_mm256_castsi256_ps(ca.native()));
#else
    // FIXME: can be improved
    uint32<4> lo, hi;
    lo = ca.vec<0>();
    hi = ca.vec<1>();
    return i_extract_bits_any(lo) | (i_extract_bits_any(hi) << 4);
#endif
}

template<unsigned id> SIMDPP_INL
uint16_t i_extract_bits(const uint8<16>& ca)
{
    uint8<16> a = ca;
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    for (unsigned i = 0; i < a.length; i++) {
        uint8_t x = ca.el(i);
        x = (x >> id) & 1;
        r = (r >> 1) | (uint16_t(x) << 15);
    }
    return r;
#elif SIMDPP_USE_SSE2
    a = shift_l<7-id>((uint16x8) a);
    return i_extract_bits_any(a);
#elif SIMDPP_USE_NEON
    int8x16 shift_mask = make_int(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                                  4-int(id), 5-int(id), 6-int(id), 7-int(id));

    a = vshlq_u8(a.native(), shift_mask.native());
    return i_extract_bits_any(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 rot_mask = make_int(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                                 4-int(id), 5-int(id), 6-int(id), 7-int(id));
    a = vec_rl(a.native(), rot_mask.native());
    return i_extract_bits_any(a);
#elif SIMDPP_USE_MSA
    int8x16 shifts = make_int(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                              4-int(id), 5-int(id), 6-int(id), 7-int(id));
    uint8<16> a_l = (v16u8) __msa_sll_b((v16i8) a.native(), shifts.native());
    shifts = sub((int8<16>) make_zero(), shifts);
    uint8<16> a_r = (v16u8) __msa_srl_b((v16i8) a.native(), shifts.native());
    a = bit_or(a_l, a_r);
    return i_extract_bits_any(a);
#endif
}

template<unsigned id> SIMDPP_INL
uint32_t i_extract_bits(const uint8<32>& ca)
{
    uint8<32> a = ca;
#if SIMDPP_USE_AVX2
    a = shift_l<7-id>((uint16<16>) a);
    return i_extract_bits_any(a);
#else
    uint8<16> lo, hi;
    split(a, lo, hi);
    return i_extract_bits<id>(lo) | (i_extract_bits<id>(hi) << 16);
#endif
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif


