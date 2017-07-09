/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_R_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/splat.h>
#include <simdpp/core/set_splat.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/detail/insn/i_shift.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL int8x16 i_shift_r(const int8x16& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r(int16x8(lo), count);
    lo = shift_r<8>(lo);

    hi = shift_r(int16x8(hi), 8+count);
    hi = shift_l<8>(hi);
    return (int8<16>) bit_or(lo, hi);    //higher part of lo is already clear
#elif SIMDPP_USE_NEON
    int8x16 shift = splat(-int(count));
    return vshlq_s8(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = splat(count);
    return vec_sra((__vector int8_t)a, (__vector uint8_t)shift);
#elif SIMDPP_USE_MSA
    int8x16 shift = splat(count);
    return __msa_sra_b(a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int8x32 i_shift_r(const int8x32& a, unsigned count)
{
    uint16x16 hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r(int16x16(lo), count);
    lo = shift_r<8>(lo);

    hi = shift_r(int16x16(hi), 8+count);
    hi = shift_l<8>(hi);
    return (int8<32>) bit_or(lo, hi);    //higher part of lo is already clear
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL int8<64> i_shift_r(const int8<64>& a, unsigned count)
{
    uint16<32> hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r(int16<32>(lo), count);
    lo = shift_r<8>(lo);

    hi = shift_r(int16<32>(hi), 8+count);
    hi = shift_l<8>(hi);
    return (int8<64>) bit_or(lo, hi);    //higher part of lo is already clear
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint8x16 i_shift_r(const uint8x16& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, a16;
    mask = make_ones();
    mask = shift_l(mask, 16-count);
    mask = shift_r<8>(mask);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return uint8x16(a16);
#elif SIMDPP_USE_NEON
    int8x16 shift = splat(-int(count));
    return vshlq_u8(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = splat(count);
    return vec_sr((__vector uint8_t)a, (__vector uint8_t)shift);
#elif SIMDPP_USE_MSA
    int8x16 shift = splat(count);
    return (v16u8) __msa_srl_b((v16i8)(v16u8) a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_shift_r(const uint8x32& a, unsigned count)
{
    unsigned shift = 8 - count;
    uint16_t mask1 = (0xff >> shift) << shift;
    uint16x16 mask, a16;
    mask = splat(mask1);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return uint8x32(a16);
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL uint8<64> i_shift_r(const uint8<64>& a, unsigned count)
{
    unsigned shift = 8 - count;
    uint16_t mask1 = (0xff >> shift) << shift;
    uint16<32> mask, a16;
    mask = splat(mask1);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return uint8<64>(a16);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL int16x8 i_shift_r(const int16x8& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_sra_epi16(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int16x8 shift = splat(-int(count));
    return vshlq_s16(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = splat(count);
    return vec_sra((__vector int16_t)a, (__vector uint16_t)shift);
#elif SIMDPP_USE_MSA
    int16x8 shift = splat(count);
    return __msa_sra_h(a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int16x16 i_shift_r(const int16x16& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsraw	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_sra_epi16(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL int16<32> i_shift_r(const int16<32>& a, unsigned count)
{
    return _mm512_sra_epi16(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_shift_r(const uint16x8& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srli_epi16(a, count);
#elif SIMDPP_USE_NEON
    int16x8 shift = splat(-int(count));
    return vshlq_u16(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = splat(count);
    return vec_sr((__vector uint16_t)a, (__vector uint16_t)shift);
#elif SIMDPP_USE_MSA
    int16x8 shift = splat(count);
    return (v8u16) __msa_srl_h((v8i16)(v8u16) a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16x16 i_shift_r(const uint16x16& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsrlw	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_srl_epi16(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL uint16<32> i_shift_r(const uint16<32>& a, unsigned count)
{
    return _mm512_srl_epi16(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL int32x4 i_shift_r(const int32x4& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_sra_epi32(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int32x4 shift = splat(-int(count));
    return vshlq_s32(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = splat(count);
    return vec_sra((__vector int32_t)a, (__vector uint32_t)shift);
#elif SIMDPP_USE_MSA
    int32x4 shift = splat(count);
    return __msa_sra_w(a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int32x8 i_shift_r(const int32x8& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsrad	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_sra_epi32(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL int32<16> i_shift_r(const int32<16>& a, unsigned count)
{
    return _mm512_sra_epi32(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_shift_r(const uint32x4& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srl_epi32(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int32x4 shift = splat(-int(count));
    return vshlq_u32(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = splat(count);
    return vec_sr((__vector uint32_t)a, (__vector uint32_t)shift);
#elif SIMDPP_USE_MSA
    int32x4 shift = splat(count);
    return (v4u32) __msa_srl_w((v4i32)(v4u32) a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32x8 i_shift_r(const uint32x8& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsrld	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_srl_epi32(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_shift_r(const uint32<16>& a, unsigned count)
{
    return _mm512_srl_epi32(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL int64x2 i_shift_r(const int64x2& a, unsigned count)
{
#if SIMDPP_USE_SSE2
    if (count > 31) {
        int32x4 s, v;
        v = a;
        s = shift_r<31>(v);
        v = shift_r(v, count - 32);
        v = shuffle2<1,3,1,3>(v, s);
        v = permute4<0,2,1,3>(v);
        return int64x2(v);
    } else {
        // shift the sign bit using 32-bit shift, then combine the result with
        // the unsigned shift using a mask
        uint64x2 v, mask, sgn;
        v = sgn = a;
        v = shift_r(v, count);
        sgn = shift_r(int32x4(sgn), count);
        mask = make_ones();
        mask = shift_l(mask, 64 - count);
        sgn = bit_and(sgn, mask);
        v = bit_or(v, sgn);
        return int64x2(v);
    }
#elif SIMDPP_USE_NEON
    int64x2 shift = splat(-int(count));
    return vshlq_s64(a, shift);
#elif SIMDPP_USE_VSX_207
    uint64x2 shift = splat(count);
    return vec_sra((__vector int64_t)a, (__vector uint64_t)shift);
#elif SIMDPP_USE_MSA
    int32x4 shift = splat(count);
    return __msa_sra_d(a, (int64<2>) shift);
#elif SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::shift_r(a, count);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int64x4 i_shift_r(const int64x4& a, unsigned count)
{
    // a copy of the 128-bit implementation
    if (count > 31) {
        int32x8 s, v;
        v = a;
        s = shift_r<31>(v);
        v = shift_r(v, count - 32);
        v = shuffle2<1,3,1,3>(v, s);
        v = permute4<0,2,1,3>(v);
        return int64x4(v);
    } else {
        uint64x4 v, mask;
        int32x8 sgn;
        v = sgn = a;
        v = shift_r(v, count);
        sgn = shift_r(sgn, count);
        mask = make_ones();
        mask = shift_l(mask, 64 - count);
        sgn = bit_and(sgn, mask);
        v = bit_or(v, sgn);
        return int64x4(v);
    }
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL int64<8> i_shift_r(const int64<8>& a, unsigned count)
{
    return _mm512_sra_epi64(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint64x2 i_shift_r(const uint64x2& a, unsigned count)
{
#if SIMDPP_USE_SSE2
    return _mm_srl_epi64(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int64x2 shift = splat(-int(count));
    return vshlq_u64(a, shift);
#elif SIMDPP_USE_VSX_207
    uint64x2 shift = splat(count);
    return vec_sr((__vector uint64_t)a, (__vector uint64_t)shift);
#elif SIMDPP_USE_MSA
    int32x4 shift = splat(count);
    return (v2u64) __msa_srl_d((v2i64)(v2u64) a, (int64<2>) shift);
#elif SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::shift_r(a, count);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64x4 i_shift_r(const uint64x4& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsrlq	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_srl_epi64(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_shift_r(const uint64<8>& a, unsigned count)
{
    return _mm512_srl_epi64(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
V i_shift_r(const V& a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(V, i_shift_r, a, count);
}


// -----------------------------------------------------------------------------

template<unsigned count, unsigned N> SIMDPP_INL
uint8<N> shift_r_u8(const uint8<N>& a);


template<unsigned count> SIMDPP_INL
int8x16 i_shift_r(const int8x16& a)
{
    static_assert(count < 8, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint16<8> hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r<count>(int16<8>(lo));
    lo = shift_r<8>(lo);

    hi = shift_r<8+count>(int16<8>(hi));
    hi = shift_l<8>(hi);
    return (int8<16>) bit_or(lo, hi);    //higher part of lo is already clear
#elif SIMDPP_USE_NEON
    return vshrq_n_s8(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = make_uint(count);
    return vec_sra((__vector int8_t)a, (__vector uint8_t)shift);
#elif SIMDPP_USE_MSA
    return __msa_srai_b(a, count);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
int8x32 i_shift_r(const int8x32& a)
{
    static_assert(count < 8, "Shift out of bounds");
    uint16<16> hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r<count>(int16<16>(lo));
    lo = shift_r<8>(lo);

    hi = shift_r<8+count>(int16<16>(hi));
    hi = shift_l<8>(hi);
    return (int8<32>) bit_or(lo, hi);    //higher part of lo is already clear
}
#endif

#if SIMDPP_USE_AVX512BW
template<unsigned count> SIMDPP_INL
int8<64> i_shift_r(const int8<64>& a)
{
    static_assert(count < 8, "Shift out of bounds");
    uint16<32> hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r<count>(int16<32>(lo));
    lo = shift_r<8>(lo);

    hi = shift_r<8+count>(int16<32>(hi));
    hi = shift_l<8>(hi);
    return (int8<64>) bit_or(lo, hi);    //higher part of lo is already clear
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count, unsigned N> SIMDPP_INL
uint8<N> sse_shift_r_u8(const uint8<N>& a)
{
    uint8_t mask1 = (0xff << count) & 0xff;
    uint8<N> mask = make_uint(mask1);

    uint16<N/2> a16 = (uint16<N/2>) bit_and(a, mask);
    a16 = shift_r<count>(a16);

    return uint8<N>(a16);
}

template<unsigned count> SIMDPP_INL
uint8x16 i_shift_r(const uint8x16& a)
{
    static_assert(count < 8, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return sse_shift_r_u8<count>(a);
#elif SIMDPP_USE_NEON
    return vshrq_n_u8(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = make_uint(count);
    return vec_sr((__vector uint8_t)a, (__vector uint8_t)shift);
#elif SIMDPP_USE_MSA
    return (v16u8) __msa_srli_b((v16i8)(v16u8) a, count);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint8x32 i_shift_r(const uint8x32& a)
{
    static_assert(count < 8, "Shift out of bounds");
    return sse_shift_r_u8<count>(a);
}
#endif

#if SIMDPP_USE_AVX512BW
template<unsigned count> SIMDPP_INL
uint8<64> i_shift_r(const uint8<64>& a)
{
    static_assert(count < 8, "Shift out of bounds");
    return sse_shift_r_u8<count>(a);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
int16x8 i_shift_r(const int16x8& a)
{
    static_assert(count < 16, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return detail::null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srai_epi16(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_s16(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = make_uint(count);
    return vec_sra((__vector int16_t)a, (__vector uint16_t)shift);
#elif SIMDPP_USE_MSA
    return __msa_srai_h(a, count);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
int16x16 i_shift_r(const int16x16& a)
{
    static_assert(count < 16, "Shift out of bounds");
    return _mm256_srai_epi16(a, count);
}
#endif

#if SIMDPP_USE_AVX512BW
template<unsigned count> SIMDPP_INL
int16<32> i_shift_r(const int16<32>& a)
{
    static_assert(count < 16, "Shift out of bounds");
    return _mm512_srai_epi16(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
uint16x8 i_shift_r(const uint16x8& a)
{
    static_assert(count < 16, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srli_epi16(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u16(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = make_uint(count);
    return vec_sr((__vector uint16_t)a, (__vector uint16_t)shift);
#elif SIMDPP_USE_MSA
    return (v8u16) __msa_srli_h((v8i16)(v8u16) a, count);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint16x16 i_shift_r(const uint16x16& a)
{
    static_assert(count < 16, "Shift out of bounds");
    return _mm256_srli_epi16(a, count);
}
#endif

#if SIMDPP_USE_AVX512BW
template<unsigned count> SIMDPP_INL
uint16<32> i_shift_r(const uint16<32>& a)
{
    static_assert(count < 16, "Shift out of bounds");
    return _mm512_srli_epi16(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
int32x4 i_shift_r(const int32x4& a)
{
    static_assert(count < 32, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srai_epi32(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_s32(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = make_uint(count);
    return vec_sra((__vector int32_t)a, (__vector uint32_t)shift);
#elif SIMDPP_USE_MSA
    return __msa_srai_w(a, count);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
int32x8 i_shift_r(const int32x8& a)
{
    static_assert(count < 32, "Shift out of bounds");
    return _mm256_srai_epi32(a, count);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned count> SIMDPP_INL
int32<16> i_shift_r(const int32<16>& a)
{
    static_assert(count < 32, "Shift out of bounds");
    return _mm512_srai_epi32(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
uint32x4 i_shift_r(const uint32x4& a)
{
    static_assert(count < 32, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srli_epi32(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u32(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = make_uint(count);
    return vec_sr((__vector uint32_t)a, (__vector uint32_t)shift);
#elif SIMDPP_USE_MSA
    return (v4u32) __msa_srli_w((v4i32)(v4u32) a, count);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint32x8 i_shift_r(const uint32x8& a)
{
    static_assert(count < 32, "Shift out of bounds");
    return _mm256_srli_epi32(a, count);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned count> SIMDPP_INL
uint32<16> i_shift_r(const uint32<16>& a)
{
    static_assert(count < 32, "Shift out of bounds");
    return _mm512_srli_epi32(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
int64x2 i_shift_r(const int64x2& a)
{
    static_assert(count < 64, "Shift out of bounds");
#if SIMDPP_USE_NEON
    return vshrq_n_s64(a, count);
#elif SIMDPP_USE_VSX_207
    uint64x2 shift = splat(count);
    return vec_sra((__vector int64_t)a, (__vector uint64_t)shift);
#elif SIMDPP_USE_MSA
    return __msa_srai_d(a, count);
#elif SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return i_shift_r(a, count);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE1(int64<count>, a);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
int64x4 i_shift_r(const int64x4& a)
{
    return i_shift_r(a, count);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned count> SIMDPP_INL
int64<8> i_shift_r(const int64<8>& a)
{
    static_assert(count < 64, "Shift out of bounds");
    return _mm512_srai_epi64(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
uint64x2 i_shift_r(const uint64x2& a)
{
    static_assert(count < 64, "Shift out of bounds");
#if SIMDPP_USE_SSE2
    return _mm_srli_epi64(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u64(a, count);
#elif SIMDPP_USE_VSX_207
    uint64x2 shift = splat(count);
    return vec_sr((__vector uint64_t)a, (__vector uint64_t)shift);
#elif SIMDPP_USE_MSA
    return (v2u64) __msa_srli_d((v2i64)(v2u64) a, count);
#elif SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return i_shift_r(a, count);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE1(int64<count>, a);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint64x4 i_shift_r(const uint64x4& a)
{
    static_assert(count < 64, "Shift out of bounds");
    return _mm256_srli_epi64(a, count);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned count> SIMDPP_INL
uint64<8> i_shift_r(const uint64<8>& a)
{
    static_assert(count < 64, "Shift out of bounds");
    return _mm512_srli_epi64(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count, class V> SIMDPP_INL
V i_shift_r(const V& a)
{
    static_assert(count < 64, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(V, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<bool no_shift>
struct i_shift_r_wrapper {
    template<unsigned count, class V>
    static SIMDPP_INL V run(const V& arg) { return i_shift_r<count>(arg); }
};
template<>
struct i_shift_r_wrapper<true> {
    template<unsigned count, class V>
    static SIMDPP_INL V run(const V& arg) { return arg; }
};

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

