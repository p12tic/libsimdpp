/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_REDUCE_MUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_REDUCE_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/extract.h>
#include <simdpp/core/f_mul.h>
#include <simdpp/core/i_mul.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/make_uint.h>
#include <simdpp/detail/mem_block.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// -----------------------------------------------------------------------------

SIMDPP_INL uint32_t i_reduce_mul(const uint16x8& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r *= a.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    uint32x4 ca = (uint32x4)a;
    // shift data zeroing out bits
    uint32x4 al = shift_r<16>(ca);
    uint32x4 ah = shift_l<16>(ca);
    // due to zeroing bits in previous steps, the result can be OR'ed
    uint32x4 lo = _mm_mullo_epi16(ca, al);
    uint32x4 hi = _mm_mulhi_epu16(ca, ah);
    uint32x4 r = bit_or(lo, hi);
    r = _mm_mul_epu32(r, move4_l<1>(r).eval());
    r = _mm_mul_epu32(r, move4_l<2>(r).eval());
    return extract<0>(r);
#elif SIMDPP_USE_NEON
    uint32x4 r = vmull_u16(vget_low_u16(a), vget_high_u16(a));
    r = mul_lo(r, move4_l<2>(r));
    r = mul_lo(r, move4_l<1>(r));
    return extract<0>(r);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 a2 = move8_l<1>(a);
    uint32x4 r = vec_mule((__vector uint16_t)a2, (__vector uint16_t)a);
    mem_block<uint32x4> b = r;
    return b[0] * b[1] * b[2] * b[3];
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32_t i_reduce_mul(const uint16x16& a)
{
    uint32x8 ca = (uint32x8) a;
    // shift data zeroing out bits
    uint32x8 al = shift_r<16>(ca);
    uint32x8 ah = shift_l<16>(ca);
    // due to zoreing bits in previous steps, the result can be OR'ed
    uint32x8 lo = _mm256_mullo_epi16(ca, al);
    uint32x8 hi = _mm256_mulhi_epu16(ca, ah);
    uint32x8 r = bit_or(lo, hi);
    r = _mm256_mul_epu32(r, move4_l<1>(r).eval());
    uint32x4 r2 = _mm_mul_epu32(detail::extract128<0>(r), detail::extract128<1>(r));
    r2 = _mm_mul_epu32(r2, move4_l<2>(r2).eval());
    return extract<0>(r2);
}
#endif

template<unsigned N>
SIMDPP_INL uint32_t i_reduce_mul(const uint16<N>& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = 1;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r *= a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_AVX2
    uint32x8 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x8 ca = (uint32x8) a.vec(j);
        // shift data zeroing out bits
        uint32x8 al = shift_r<16>(ca);
        uint32x8 ah = shift_l<16>(ca);
        // due to zoreing bits in previous steps, the result can be OR'ed
        uint32x8 lo = _mm256_mullo_epi16(ca, al);
        uint32x8 hi = _mm256_mulhi_epu16(ca, ah);
        uint32x8 iprod = bit_or(lo, hi);
        iprod = _mm256_mul_epu32(iprod, move4_l<1>(iprod).eval());
        prod = _mm256_mul_epu32(prod, iprod);
    }
    uint32x4 r2 = _mm_mul_epu32(detail::extract128<0>(prod), detail::extract128<1>(prod));
    r2 = _mm_mul_epu32(r2, move4_l<2>(r2).eval());
    return extract<0>(r2);
#elif SIMDPP_USE_SSE2
    uint32x4 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x4 ca = (uint32x4) a.vec(j);
        // shift data zeroing out bits
        uint32x4 al = shift_r<16>(ca);
        uint32x4 ah = shift_l<16>(ca);
        // due to zoreing bits in previous steps, the result can be OR'ed
        uint32x4 lo = _mm_mullo_epi16(ca, al);
        uint32x4 hi = _mm_mulhi_epu16(ca, ah);
        uint32x4 r = bit_or(lo, hi);
        r = _mm_mul_epu32(r, move4_l<1>(r).eval());
        prod = _mm_mul_epu32(prod, r);
    }
    prod = _mm_mul_epu32(prod, move4_l<2>(prod).eval());
    return extract<0>(prod);
#elif SIMDPP_USE_NEON
    uint32x4 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x4 r = vmull_u16(vget_low_u16(a.vec(j)), vget_high_u16(a.vec(j)));
        prod = mul_lo(prod, r);
    }
    prod = mul_lo(prod, move4_l<2>(prod));
    prod = mul_lo(prod, move4_l<1>(prod));
    return extract<0>(prod);
#elif SIMDPP_USE_ALTIVEC
    uint32_t r = i_reduce_mul(a.vec(0));
    for (unsigned j = 1; j < a.vec_length; ++j) {
        r *= i_reduce_mul(a.vec(j));
    }
    return r;
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL int32_t i_reduce_mul(const int16x8& a)
{
#if SIMDPP_USE_NULL
    int32_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r *= a.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    uint32x4 ca = (uint32x4) a;
    // shift data zeroing out bits
    uint32x4 al = shift_r<16>(ca);
    uint32x4 ah = shift_l<16>(ca);
    // due to zoreing bits in previous steps, the result can be OR'ed
    uint32x4 lo = _mm_mullo_epi16(ca, al);
    uint32x4 hi = _mm_mulhi_epi16(ca, ah);
    uint32x4 r = bit_or(lo, hi);
    r = _mm_mul_epu32(r, move4_l<1>(r).eval());
    r = _mm_mul_epu32(r, move4_l<2>(r).eval());
    return extract<0>(r);
#elif SIMDPP_USE_NEON
    int32x4 r = vmull_s16(vget_low_s16(a), vget_high_s16(a));
    r = mul_lo(r, move4_l<2>(r));
    r = mul_lo(r, move4_l<1>(r));
    return extract<0>(r);
#elif SIMDPP_USE_ALTIVEC
    int16x8 a2 = move8_l<1>(a);
    int32x4 r = vec_mule((__vector int16_t)a2, (__vector int16_t)a);
    mem_block<int32x4> b = r;
    return b[0] * b[1] * b[2] * b[3];
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int32_t i_reduce_mul(const int16x16& a)
{
    uint32x8 ca = (uint32x8) a;
    // shift data zeroing out bits
    uint32x8 al = shift_r<16>(ca);
    uint32x8 ah = shift_l<16>(ca);
    // due to zoreing bits in previous steps, the result can be OR'ed
    uint32x8 lo = _mm256_mullo_epi16(ca, al);
    uint32x8 hi = _mm256_mulhi_epi16(ca, ah);
    uint32x8 r = bit_or(lo, hi);
    r = _mm256_mul_epu32(r, move4_l<1>(r).eval());
    uint32x4 r2 = _mm_mul_epu32(detail::extract128<0>(r), detail::extract128<1>(r));
    r2 = _mm_mul_epu32(r2, move4_l<2>(r2).eval());
    return extract<0>(r2);
}
#endif

template<unsigned N>
SIMDPP_INL int32_t i_reduce_mul(const int16<N>& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = 1;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r *= a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_AVX2
    uint32x8 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x8 ca = (uint32x8) a.vec(j);
        // shift data zeroing out bits
        uint32x8 al = shift_r<16>(ca);
        uint32x8 ah = shift_l<16>(ca);
        // due to zoreing bits in previous steps, the result can be OR'ed
        uint32x8 lo = _mm256_mullo_epi16(ca, al);
        uint32x8 hi = _mm256_mulhi_epi16(ca, ah);
        uint32x8 iprod = bit_or(lo, hi);
        iprod = _mm256_mul_epu32(iprod, move4_l<1>(iprod).eval());
        prod = _mm256_mul_epu32(prod, iprod);
    }
    uint32x4 r2 = _mm_mul_epu32(detail::extract128<0>(prod), detail::extract128<1>(prod));
    r2 = _mm_mul_epu32(r2, move4_l<2>(r2).eval());
    return extract<0>(r2);
#elif SIMDPP_USE_SSE2
    uint32x4 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x4 ca = (uint32x4) a.vec(j);
        // shift data zeroing out bits
        uint32x4 al = shift_r<16>(ca);
        uint32x4 ah = shift_l<16>(ca);
        // due to zoreing bits in previous steps, the result can be OR'ed
        uint32x4 lo = _mm_mullo_epi16(ca, al);
        uint32x4 hi = _mm_mulhi_epi16(ca, ah);
        uint32x4 r = bit_or(lo, hi);
        r = _mm_mul_epu32(r, move4_l<1>(r).eval());
        prod = _mm_mul_epu32(prod, r);
    }
    prod = _mm_mul_epu32(prod, move4_l<2>(prod).eval());
    return extract<0>(prod);
#elif SIMDPP_USE_NEON
    int32x4 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int32x4 r = vmull_s16(vget_low_s16(a.vec(j)), vget_high_s16(a.vec(j)));
        prod = mul_lo(prod, r);
    }
    prod = mul_lo(prod, move4_l<2>(prod));
    prod = mul_lo(prod, move4_l<1>(prod));
    return extract<0>(prod);
#elif SIMDPP_USE_ALTIVEC
    int32_t r = i_reduce_mul(a.vec(0));
    for (unsigned j = 1; j < a.vec_length; ++j) {
        r *= i_reduce_mul(a.vec(j));
    }
    return r;
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32_t i_reduce_mul(const uint32x4& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r *= a.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    uint32x4 r = _mm_mul_epu32(a, move4_l<1>(a).eval());
    r = _mm_mul_epu32(r, move4_l<2>(r).eval());
    return extract<0>(r);
#elif SIMDPP_USE_NEON
    uint32x4 r = a;
    r = mul_lo(r, move4_l<2>(r));
    r = mul_lo(r, move4_l<1>(r));
    return extract<0>(r);
#elif SIMDPP_USE_ALTIVEC
    mem_block<uint32x4> b = a;
    return b[0] * b[1] * b[2] * b[3];
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32_t i_reduce_mul(const uint32x8& a)
{
    uint32x8 ra = _mm256_mul_epu32(a, move4_l<1>(a).eval());
    uint32x4 r = _mm_mul_epu32(detail::extract128<0>(ra), detail::extract128<1>(ra));
    r = _mm_mul_epu32(r, move4_l<2>(r).eval());
    return extract<0>(r);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32_t i_reduce_mul(const uint32<16>& a)
{
#if SIMDPP_WORKAROUND_AVX512F_NO_REDUCE
    return i_reduce_mul(mul_lo(extract256<0>(a), extract256<1>(a)));
#else
    return _mm512_reduce_mul_epi32(a);
#endif
}
#endif

template<unsigned N>
SIMDPP_INL uint32_t i_reduce_mul(const uint32<N>& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = 1;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r *= a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_AVX2
    uint32x8 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x8 ai = a.vec(j);
        uint32x8 ra = _mm256_mul_epu32(ai, move4_l<1>(ai).eval());
        prod = _mm256_mul_epu32(prod, ra);
    }
    uint32x4 r = _mm_mul_epu32(detail::extract128<0>(prod), detail::extract128<1>(prod));
    r = _mm_mul_epu32(r, move4_l<2>(r).eval());
    return extract<0>(r);
#elif SIMDPP_USE_SSE2
    uint32x4 r = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x4 ai = a.vec(j);
        uint32x4 ra = _mm_mul_epu32(ai, move4_l<1>(ai).eval());
        r = _mm_mul_epu32(r, ra);
    }
    r = _mm_mul_epu32(r, move4_l<2>(r).eval());
    return extract<0>(r);
#elif SIMDPP_USE_NEON
    uint32x4 prod = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        prod = mul_lo(prod, a.vec(j));
    }
    prod = mul_lo(prod, move4_l<2>(prod));
    prod = mul_lo(prod, move4_l<1>(prod));
    return extract<0>(prod);
#elif SIMDPP_USE_ALTIVEC
    uint32_t r = i_reduce_mul(a.vec(0));
    for (unsigned j = 1; j < a.vec_length; ++j) {
        r *= i_reduce_mul(a.vec(j));
    }
    return r;
#endif
}

// -----------------------------------------------------------------------------


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

