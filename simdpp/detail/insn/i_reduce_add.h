/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_REDUCE_ADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_REDUCE_ADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/extract.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/make_uint.h>
#include <simdpp/detail/mem_block.h>
#include <simdpp/detail/extract128.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL uint16_t i_reduce_add(const uint8x16& a)
{
#if SIMDPP_USE_NULL
    uint16_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r += a.el(i);
    }
    return r;
#elif SIMDPP_USE_XOP
    uint16x8 sum = _mm_haddq_epu8(a);
    return extract<0>(sum) + extract<4>(sum);
#elif SIMDPP_USE_SSE2
    uint16x8 sum = _mm_sad_epu8(a, _mm_setzero_si128());
    return extract<0>(sum) + extract<4>(sum);
#elif SIMDPP_USE_NEON
    uint16x8 a2 = vpaddlq_u8(a);
    uint32x4 a3 = vpaddlq_u16(a2);
    uint64x2 a4 = vpaddlq_u32(a3);
    a3 = a4;
    uint32x2_t r = vadd_u32(vget_low_u32(a3), vget_high_u32(a3));
    return vget_lane_u32(r, 0);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 sum = make_zero();
    sum = vec_sum4s((__vector uint8_t)a, (__vector uint32_t)sum);
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16_t i_reduce_add(const uint8x32& a)
{
    uint16x16 sum2 = _mm256_sad_epu8(a, _mm256_setzero_si256()); // results are in 0,2,4,6 elements
    uint16x8 sum = add(detail::extract128<0>(sum2), detail::extract128<1>(sum2));
    return extract<0>(sum) + extract<4>(sum);
}
#endif

template<unsigned N>
SIMDPP_INL uint16_t i_reduce_add(const uint8<N>& a)
{
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r += a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_AVX2
    uint16x16 r = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint16x16 sum = _mm256_sad_epu8(a.vec(j), _mm256_setzero_si256());
        r = add(r, sum);
    }
    uint16x8 rl = add(detail::extract128<0>(r), detail::extract128<1>(r));
    return extract<0>(rl) + extract<4>(rl);
#elif SIMDPP_USE_SSE2
    uint16x8 r = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
#if SIMDPP_USE_XOP
        uint16x8 sum = _mm_haddq_epu8(a.vec(j));
#else
        uint16x8 sum = _mm_sad_epu8(a.vec(j), _mm_setzero_si128());
#endif
        r = add(r, sum);
    }
    return extract<0>(r) + extract<4>(r);
#elif SIMDPP_USE_NEON
    uint16x8 r = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint16x8 sum = vpaddlq_u8(a.vec(j));
        r = add(r, sum);
    }
    uint32x4 r2 = vpaddlq_u16(r);
    uint64x2 r3 = vpaddlq_u32(r2);
    r2 = r3;
    uint32x2_t r4 = vadd_u32(vget_low_u32(r2), vget_high_u32(r2));
    return vget_lane_u32(r4, 0);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        sum = vec_sum4s((__vector uint8_t)a.vec(j), (__vector uint32_t)sum);
    }
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL int16_t i_reduce_add(const int8x16& a)
{
#if SIMDPP_USE_NULL
    int16_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r += a.el(i);
    }
    return r;
#elif SIMDPP_USE_XOP
    uint16x8 sum = _mm_haddq_epi8(a);
    return extract<0>(sum) + extract<4>(sum);
#elif SIMDPP_USE_SSE2
    return i_reduce_add(uint8x16(bit_xor(a, 0x80))) - a.length*0x80;
#elif SIMDPP_USE_NEON
    int16x8 a2 = vpaddlq_s8(a);
    int32x4 a3 = vpaddlq_s16(a2);
    int64x2 a4 = vpaddlq_s32(a3);
    a3 = a4;
    int32x2_t r = vadd_s32(vget_low_s32(a3), vget_high_s32(a3));
    return vget_lane_s32(r, 0);
#elif SIMDPP_USE_ALTIVEC
    int32x4 sum = make_zero();
    sum = vec_sum4s((__vector int8_t)a, (__vector int32_t)sum);
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int16_t i_reduce_add(const int8x32& a)
{
    return i_reduce_add(uint8x32(bit_xor(a, 0x80))) - a.length*0x80;
}
#endif

template<unsigned N>
SIMDPP_INL uint16_t i_reduce_add(const int8<N>& a)
{
#if SIMDPP_USE_NULL
    int16_t r = 0;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r += a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_XOP
    int16x8 r = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int16x8 sum = _mm_haddq_epi8(a.vec(j));
        r = add(r, sum);
    }
    return extract<0>(r) + extract<4>(r);
#elif SIMDPP_USE_SSE2
    return i_reduce_add(uint8<N>(bit_xor(a, 0x80))) - a.length*0x80;
#elif SIMDPP_USE_NEON
    int16x8 r = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int16x8 sum = vpaddlq_s8(a.vec(j));
        r = add(r, sum);
    }
    int32x4 r2 = vpaddlq_s16(r);
    int64x2 r3 = vpaddlq_s32(r2);
    r2 = r3;
    int32x2_t r4 = vadd_s32(vget_low_s32(r2), vget_high_s32(r2));
    return vget_lane_s32(r4, 0);
#elif SIMDPP_USE_ALTIVEC
    int32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        sum = vec_sum4s((__vector int8_t)a.vec(j), (__vector int32_t)sum);
    }
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32_t i_reduce_add(const uint16x8& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r += a.el(i);
    }
    return r;
#elif SIMDPP_USE_XOP
    uint32x4 sum = _mm_haddq_epu16(a); // sum in the 0 and 2 elements
    sum = add(sum, move4_l<2>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_SSE2
    uint16x8 ones = make_uint(1);
    uint16x8 ca = bit_xor(a, 0x8000);
    uint32x4 sum = _mm_madd_epi16(ca, ones);
    // phadd is slower option on intel processors
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum) + 0x8000 * a.length;
#elif SIMDPP_USE_NEON
    uint32x4 a2 = vpaddlq_u16(a);
    uint64x2 a3 = vpaddlq_u32(a2);
    a2 = a3;
    uint32x2_t r = vadd_u32(vget_low_u32(a2), vget_high_u32(a2));
    return vget_lane_u32(r, 0);
#elif SIMDPP_USE_ALTIVEC
    int32x4 sum = make_zero();
    int16x8 ca = bit_xor(a, 0x8000);
    sum = vec_sum4s((__vector int16_t)ca, (__vector int32_t)sum);
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum) + 0x8000 * a.length;
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32_t i_reduce_add(const uint16x16& a)
{
    uint16x16 ones = make_uint(1);
    uint16x16 ca = bit_xor(a, 0x8000);
    uint32x8 sum = _mm256_madd_epi16(ca, ones);
    // phadd is slower option on intel processors
    uint32x4 sum2 = add(detail::extract128<0>(sum), detail::extract128<1>(sum));
    sum2 = add(sum2, move4_l<2>(sum2));
    sum2 = add(sum2, move4_l<1>(sum2));
    return extract<0>(sum2) + 0x8000 * a.length;
}
#endif

template<unsigned N>
SIMDPP_INL uint32_t i_reduce_add(const uint16<N>& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = 0;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r += a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_AVX2
    uint32x8 sum = make_zero();
    uint16x16 ones = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint16x16 ca = bit_xor(a.vec(j), 0x8000);
        uint32x8 isum = _mm256_madd_epi16(ca, ones);
        sum = add(sum, isum);
    }
    uint32x4 sum2 = add(detail::extract128<0>(sum), detail::extract128<1>(sum));
    sum2 = add(sum2, move4_l<2>(sum2));
    sum2 = add(sum2, move4_l<1>(sum2));
    return extract<0>(sum2) + 0x8000 * a.length;
#elif SIMDPP_USE_XOP
    uint32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x4 isum = _mm_haddq_epu16(a.vec(j));
        sum = add(sum, isum);
    }
    sum = add(sum, move4_l<2>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_SSE2
    uint32x4 sum = make_zero();
    uint16x8 ones = make_uint(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint16x8 ca = bit_xor(a.vec(j), 0x8000);
        uint32x4 isum = _mm_madd_epi16(ca, ones);
        sum = add(sum, isum);
    }
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum) + 0x8000 * a.length;
#elif SIMDPP_USE_NEON
    uint32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        uint32x4 isum = vpaddlq_u16(a.vec(j));
        sum = add(sum, isum);
    }
    uint64x2 sum2 = vpaddlq_u32(sum);
    sum = sum2;
    uint32x2_t sum3 = vadd_u32(vget_low_u32(sum), vget_high_u32(sum));
    return vget_lane_u32(sum3, 0);
#elif SIMDPP_USE_ALTIVEC
    int32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int16x8 ca = bit_xor(a.vec(j), 0x8000);
        sum = vec_sum4s((__vector int16_t)ca, (__vector int32_t)sum);
    }
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum) + 0x8000 * a.length;
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL int32_t i_reduce_add(const int16x8& a)
{
#if SIMDPP_USE_NULL
    int32_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r += a.el(i);
    }
    return r;
#elif SIMDPP_USE_XOP
    int32x4 sum = _mm_haddq_epi16(a); // sum in the 0 and 2 elements
    sum = add(sum, move4_l<2>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_SSE2
    int16x8 ones = make_uint(1);
    int32x4 sum = _mm_madd_epi16(a, ones);
    // phadd is slower option on intel processors
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_NEON
    int32x4 a2 = vpaddlq_s16(a);
    int64x2 a3 = vpaddlq_s32(a2);
    a2 = a3;
    int32x2_t r = vadd_s32(vget_low_s32(a2), vget_high_s32(a2));
    return vget_lane_s32(r, 0);
#elif SIMDPP_USE_ALTIVEC
    int32x4 sum = make_zero();
    sum = vec_sum4s((__vector int16_t)a, (__vector int32_t)sum);
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int32_t i_reduce_add(const int16x16& a)
{
    int16x16 ones = make_uint(1);
    int32x8 sum = _mm256_madd_epi16(a, ones);
    // phadd is slower option on intel processors
    int32x4 sum2 = add(detail::extract128<0>(sum), detail::extract128<1>(sum));
    sum2 = add(sum2, move4_l<2>(sum2));
    sum2 = add(sum2, move4_l<1>(sum2));
    return extract<0>(sum2);
}
#endif

template<unsigned N>
SIMDPP_INL int32_t i_reduce_add(const int16<N>& a)
{
#if SIMDPP_USE_NULL
    int32_t r = 0;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r += a.vec(j).el(i);
        }
    }
    return r;
#elif SIMDPP_USE_AVX2
    int32x8 sum = make_zero();
    int16x16 ones = make_int(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int32x8 isum = _mm256_madd_epi16(a.vec(j), ones);
        sum = add(sum, isum);
    }
    int32x4 sum2 = add(detail::extract128<0>(sum), detail::extract128<1>(sum));
    sum2 = add(sum2, move4_l<2>(sum2));
    sum2 = add(sum2, move4_l<1>(sum2));
    return extract<0>(sum2);
#elif SIMDPP_USE_XOP
    int32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int32x4 isum = _mm_haddq_epi16(a.vec(j));
        sum = add(sum, isum);
    }
    sum = add(sum, move4_l<2>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_SSE2
    int32x4 sum = make_zero();
    int16x8 ones = make_int(1);
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int32x4 isum = _mm_madd_epi16(a.vec(j), ones);
        sum = add(sum, isum);
    }
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_NEON
    int32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        int32x4 isum = vpaddlq_s16(a.vec(j));
        sum = add(sum, isum);
    }
    int64x2 sum2 = vpaddlq_s32(sum);
    sum = sum2;
    int32x2_t sum3 = vadd_s32(vget_low_s32(sum), vget_high_s32(sum));
    return vget_lane_s32(sum3, 0);
#elif SIMDPP_USE_ALTIVEC
    int32x4 sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        sum = vec_sum4s((__vector int16_t)a.vec(j), (__vector int32_t)sum);
    }
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32_t i_reduce_add(const uint32x4& a)
{
#if SIMDPP_USE_NULL
    uint32_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r += a.el(i);
    }
    return r;
#else
    uint32x4 sum = a;
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32_t i_reduce_add(const uint32x8& a)
{
    uint32x4 sum = add(detail::extract128<0>(a), detail::extract128<1>(a));
    sum = add(sum, move4_l<2>(sum));
    sum = add(sum, move4_l<1>(sum));
    return extract<0>(sum);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32_t i_reduce_add(const uint32<16>& a)
{
#if SIMDPP_WORKAROUND_AVX512F_NO_REDUCE
    return i_reduce_add(add(extract256<0>(a), extract256<1>(a)));
#else
    return _mm512_reduce_add_epi32(a);
#endif
}
#endif

template<unsigned N>
SIMDPP_INL uint32_t i_reduce_add(const uint32<N>& a)
{
#if SIMDPP_USE_NULL
    uint64_t r = 0;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r += a.vec(j).el(i);
        }
    }
    return r;
#else
    uint32v sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        sum = add(sum, a.vec(j));
    }
    return i_reduce_add(sum);
#endif
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint64_t i_reduce_add(const uint64x2& a)
{
#if SIMDPP_USE_NULL
    uint64_t r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r += a.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    uint64x2 sum = a;
    sum = add(sum, move2_l<1>(sum));
    return extract<0>(sum);
#elif SIMDPP_USE_NEON
    uint64x1_t r = vadd_u64(vget_low_u64(a), vget_high_u64(a));
    return vget_lane_u64(r, 0);
#elif SIMDPP_USE_ALTIVEC
    return extract<0>(a) + extract<1>(a);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64_t i_reduce_add(const uint64x4& a)
{
    uint64x2 sum = add(detail::extract128<0>(a), detail::extract128<1>(a));
    sum = add(sum, move2_l<1>(sum));
    return extract<0>(sum);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64_t i_reduce_add(const uint64<8>& a)
{
#if SIMDPP_WORKAROUND_AVX512F_NO_REDUCE
    return i_reduce_add(add(extract256<0>(a), extract256<1>(a)));
#else
    return _mm512_reduce_add_epi64(a);
#endif
}
#endif

template<unsigned N>
SIMDPP_INL uint64_t i_reduce_add(const uint64<N>& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    uint64_t r = 0;
    for (unsigned j = 0; j < a.vec_length; ++j) {
        for (unsigned i = 0; i < a.base_length; i++) {
            r += a.vec(j).el(i);
        }
    }
    return r;
#else
    uint64v sum = make_zero();
    for (unsigned j = 0; j < a.vec_length; ++j) {
        sum = add(sum, a.vec(j));
    }
    return i_reduce_add(sum);
#endif
}

// -----------------------------------------------------------------------------


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

