/*  Copyright (C) 2013-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CONV_EXTEND_TO_INT64_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CONV_EXTEND_TO_INT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/combine.h>
#include <simdpp/detail/mem_block.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// -----------------------------------------------------------------------------

static SIMDPP_INL
uint64<4> i_to_uint64(const uint32<4>& a)
{
#if SIMDPP_USE_NULL
    uint64x4 r;
    r.vec<0>().el(0) = uint64_t(a.el(0));
    r.vec<0>().el(1) = uint64_t(a.el(1));
    r.vec<1>().el(0) = uint64_t(a.el(2));
    r.vec<1>().el(1) = uint64_t(a.el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepu32_epi64(a.native());
#elif SIMDPP_USE_SSE4_1
    uint64x2 r1, r2;
    r1 = _mm_cvtepu32_epi64(a.native());
    r2 = _mm_cvtepu32_epi64(move4_l<2>(a).native());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_MSA || SIMDPP_USE_VSX_207
    return (uint64x4) combine(zip4_lo(a, (uint32x4) make_zero()),
                              zip4_hi(a, (uint32x4) make_zero()));
#elif SIMDPP_USE_NEON
    uint64x2 r1, r2;
    r1 = vmovl_u32(vget_low_u32(a.native()));
    r2 = vmovl_u32(vget_high_u32(a.native()));
    return combine(r1, r2);
#elif SIMDPP_USE_ALTIVEC
    uint64x4 r;
    mem_block<uint32x4> b = a;
    r.vec<0>().el(0) = b[0];
    r.vec<0>().el(1) = b[1];
    r.vec<1>().el(0) = b[2];
    r.vec<1>().el(1) = b[3];
    return r;
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
uint64<8> i_to_uint64(const uint32<8>& a)
{
    uint32<4> a1, a2;
    uint64<4> r1, r2;
    split(a, a1, a2);
    r1 = _mm256_cvtepu32_epi64(a1.native());
    r2 = _mm256_cvtepu32_epi64(a2.native());
    return combine(r1, r2);
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
uint64<16> i_to_uint64(const uint32<16>& a)
{
    uint32<8> a1, a2;
    uint64<8> r1, r2;
    split(a, a1, a2);
    r1 = _mm512_cvtepu32_epi64(a1.native());
    r2 = _mm512_cvtepu32_epi64(a2.native());
    return combine(r1, r2);
}
#endif


template<unsigned I, unsigned End, unsigned M, unsigned N>
struct uint_32_to_uint64_converter {
    static SIMDPP_INL void convert(uint64<N>& dst, const uint32<N>& src)
    {
        uint64<M> sr;
        sr = i_to_uint64(src.template vec<I>());
        dst.template vec<I*2>() = sr.template vec<0>();
        dst.template vec<I*2+1>() = sr.template vec<1>();
        uint_32_to_uint64_converter<I + 1, End, M, N>::convert(dst, src);
    }
};

template<unsigned End, unsigned M, unsigned N>
struct uint_32_to_uint64_converter<End, End, M, N> {
    static SIMDPP_INL void convert(uint64<N>& dst, const uint32<N>& src)
    {
        (void) dst;
        (void) src;
    }
};

template<unsigned N> SIMDPP_INL
uint64<N> i_to_uint64(const uint32<N>& a)
{
    uint64<N> r;
    uint_32_to_uint64_converter<0, uint32<N>::vec_length, uint32<N>::base_length, N>::convert(r, a);
    return r;
}

// -----------------------------------------------------------------------------

static SIMDPP_INL
uint64<8> i_to_uint64(const uint16<8>& a)
{
#if SIMDPP_USE_NULL
    uint64<8> r;
    for (unsigned i = 0; i < 8; i++) {
        r.vec(i/2).el(i%2) = uint64_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_AVX512F
    return _mm512_cvtepu16_epi64(a.native());
#elif SIMDPP_USE_AVX2
    uint64<8> r;
    r.vec<0>() = _mm256_cvtepu16_epi64(a.native());
    r.vec<1>() = _mm256_cvtepu16_epi64(move8_l<4>(a).native());
    return r;
#elif SIMDPP_USE_SSE4_1
    uint64<8> r;
    r.vec<0>() = _mm_cvtepu16_epi64(a.native());
    r.vec<1>() = _mm_cvtepu16_epi64(move8_l<2>(a).native());
    r.vec<2>() = _mm_cvtepu16_epi64(move8_l<4>(a).native());
    r.vec<3>() = _mm_cvtepu16_epi64(move8_l<6>(a).native());
    return r;
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_MSA || SIMDPP_USE_VSX_207
    return i_to_uint64(i_to_uint32(a));
#elif SIMDPP_USE_ALTIVEC
    uint64<8> r;
    mem_block<uint16<8>> b = a;
    for (unsigned i = 0; i < 8; i++) {
        r.vec(i/2).el(i%2) = uint64_t(b[i]);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
uint64<16> i_to_uint64(const uint16<16>& a)
{
#if SIMDPP_USE_AVX512F
    uint64<16> r;
    uint16<8> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm512_cvtepu16_epi64(a0.native());
    r.vec<1>() = _mm512_cvtepu16_epi64(a1.native());
    return r;
#else
    uint64<16> r;
    uint16<8> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm256_cvtepu16_epi64(a0.native());
    r.vec<1>() = _mm256_cvtepu16_epi64(move8_l<4>(a0).native());
    r.vec<2>() = _mm256_cvtepu16_epi64(a1.native());
    r.vec<3>() = _mm256_cvtepu16_epi64(move8_l<4>(a1).native());
    return r;
#endif
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
uint64<32> i_to_uint64(const uint16<32>& a)
{
    uint64<32> r;
    uint16<16> a01, a23;
    uint16<8> a0, a1, a2, a3;
#if SIMDPP_USE_AVX512BW
    split(a, a01, a23);
#else
    a01 = a.vec<0>();
    a23 = a.vec<1>();
#endif
    split(a01, a0, a1);
    split(a23, a2, a3);

    r.vec<0>() =  _mm512_cvtepu16_epi64(a0.native());
    r.vec<1>() =  _mm512_cvtepu16_epi64(a1.native());
    r.vec<2>() =  _mm512_cvtepu16_epi64(a2.native());
    r.vec<3>() =  _mm512_cvtepu16_epi64(a3.native());
    return r;
}
#endif


template<unsigned I, unsigned End, unsigned M, unsigned N>
struct uint_16_to_uint64_converter {
    static SIMDPP_INL void convert(uint64<N>& dst, const uint16<N>& src)
    {
        uint64<M> sr;
        sr = i_to_uint64(src.template vec<I>());
        dst.template vec<I*4>() = sr.template vec<0>();
        dst.template vec<I*4+1>() = sr.template vec<1>();
        dst.template vec<I*4+2>() = sr.template vec<2>();
        dst.template vec<I*4+3>() = sr.template vec<3>();
        uint_16_to_uint64_converter<I + 1, End, M, N>::convert(dst, src);
    }
};

template<unsigned End, unsigned M, unsigned N>
struct uint_16_to_uint64_converter<End, End, M, N> {
    static SIMDPP_INL void convert(uint64<N>& dst, const uint16<N>& src)
    {
        (void) dst;
        (void) src;
    }
};

template<unsigned N> SIMDPP_INL
uint64<N> i_to_uint64(const uint16<N>& a)
{
    uint64<N> r;
    uint_16_to_uint64_converter<0, uint16<N>::vec_length, uint16<N>::base_length, N>::convert(r, a);
    return r;
}

// -----------------------------------------------------------------------------

static SIMDPP_INL
uint64<16> i_to_uint64(const uint8<16>& a)
{
#if SIMDPP_USE_NULL
    uint64<16> r;
    for (unsigned i = 0; i < 16; i++) {
        r.vec(i/2).el(i%2) = uint64_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_AVX512F
    uint64<16> r;
    r.vec<0>() = _mm512_cvtepu8_epi64(a.native());
    r.vec<1>() = _mm512_cvtepu8_epi64(move16_l<8>(a).native());
    return r;
#elif SIMDPP_USE_AVX2
    uint64<16> r;
    r.vec<0>() = _mm256_cvtepu8_epi64(a.native());
    r.vec<1>() = _mm256_cvtepu8_epi64(move16_l<4>(a).native());
    r.vec<2>() = _mm256_cvtepu8_epi64(move16_l<8>(a).native());
    r.vec<3>() = _mm256_cvtepu8_epi64(move16_l<12>(a).native());
    return r;
#elif SIMDPP_USE_SSE4_1
    uint64<16> r;
    r.vec<0>() = _mm_cvtepu8_epi64(a.native());
    r.vec<1>() = _mm_cvtepu8_epi64(move16_l<2>(a).native());
    r.vec<2>() = _mm_cvtepu8_epi64(move16_l<4>(a).native());
    r.vec<3>() = _mm_cvtepu8_epi64(move16_l<6>(a).native());
    r.vec<4>() = _mm_cvtepu8_epi64(move16_l<8>(a).native());
    r.vec<5>() = _mm_cvtepu8_epi64(move16_l<10>(a).native());
    r.vec<6>() = _mm_cvtepu8_epi64(move16_l<12>(a).native());
    r.vec<7>() = _mm_cvtepu8_epi64(move16_l<14>(a).native());
    return r;
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_MSA || SIMDPP_USE_VSX_207
    return i_to_uint64(i_to_uint32(a));
#elif SIMDPP_USE_ALTIVEC
    uint64<16> r;
    mem_block<uint8<16>> b = a;
    for (unsigned i = 0; i < 16; i++) {
        r.vec(i/2).el(i%2) = uint64_t(b[i]);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
uint64<32> i_to_uint64(const uint8<32>& a)
{
#if SIMDPP_USE_AVX512F
    uint64<32> r;
    uint8<16> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm512_cvtepu8_epi64(a0.native());
    r.vec<1>() = _mm512_cvtepu8_epi64(move16_l<8>(a0).native());
    r.vec<2>() = _mm512_cvtepu8_epi64(a1.native());
    r.vec<3>() = _mm512_cvtepu8_epi64(move16_l<8>(a1).native());
    return r;
#else
    uint64<32> r;
    uint8<16> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm256_cvtepu8_epi64(a0.native());
    r.vec<1>() = _mm256_cvtepu8_epi64(move16_l<4>(a0).native());
    r.vec<2>() = _mm256_cvtepu8_epi64(move16_l<8>(a0).native());
    r.vec<3>() = _mm256_cvtepu8_epi64(move16_l<12>(a0).native());
    r.vec<4>() = _mm256_cvtepu8_epi64(a1.native());
    r.vec<5>() = _mm256_cvtepu8_epi64(move16_l<4>(a1).native());
    r.vec<6>() = _mm256_cvtepu8_epi64(move16_l<8>(a1).native());
    r.vec<7>() = _mm256_cvtepu8_epi64(move16_l<12>(a1).native());
    return r;
#endif
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
uint64<64> i_to_uint64(const uint8<64>& a)
{
    uint64<64> r;
    uint8<32> a01, a23;
    uint8<16> a0, a1, a2, a3;
#if SIMDPP_USE_AVX512BW
    split(a, a01, a23);
#else
    a01 = a.vec<0>();
    a23 = a.vec<1>();
#endif
    split(a01, a0, a1);
    split(a23, a2, a3);

    r.vec<0>() =  _mm512_cvtepu8_epi64(a0.native());
    r.vec<1>() =  _mm512_cvtepu8_epi64(move16_l<8>(a0).native());
    r.vec<2>() =  _mm512_cvtepu8_epi64(a1.native());
    r.vec<3>() =  _mm512_cvtepu8_epi64(move16_l<8>(a1).native());
    r.vec<4>() =  _mm512_cvtepu8_epi64(a2.native());
    r.vec<5>() =  _mm512_cvtepu8_epi64(move16_l<8>(a2).native());
    r.vec<6>() =  _mm512_cvtepu8_epi64(a3.native());
    r.vec<7>() =  _mm512_cvtepu8_epi64(move16_l<8>(a3).native());
    return r;
}
#endif

template<unsigned I, unsigned End, unsigned M, unsigned N>
struct uint_8_to_uint64_converter {
    static SIMDPP_INL void convert(uint64<N>& dst, const uint8<N>& src)
    {
        uint64<M> sr;
        sr = i_to_uint64(src.template vec<I>());
        dst.template vec<I*8>() = sr.template vec<0>();
        dst.template vec<I*8+1>() = sr.template vec<1>();
        dst.template vec<I*8+2>() = sr.template vec<2>();
        dst.template vec<I*8+3>() = sr.template vec<3>();
        dst.template vec<I*8+4>() = sr.template vec<4>();
        dst.template vec<I*8+5>() = sr.template vec<5>();
        dst.template vec<I*8+6>() = sr.template vec<6>();
        dst.template vec<I*8+7>() = sr.template vec<7>();
        uint_8_to_uint64_converter<I + 1, End, M, N>::convert(dst, src);
    }
};

template<unsigned End, unsigned M, unsigned N>
struct uint_8_to_uint64_converter<End, End, M, N> {
    static SIMDPP_INL void convert(uint64<N>& dst, const uint8<N>& src)
    {
        (void) dst;
        (void) src;
    }
};

template<unsigned N> SIMDPP_INL
    uint64<N> i_to_uint64(const uint8<N>& a)
{
    uint64<N> r;
    uint_8_to_uint64_converter<0, uint8<N>::vec_length, uint8<N>::base_length, N>::convert(r, a);
    return r;
}

// -----------------------------------------------------------------------------

static SIMDPP_INL
int64<4> i_to_int64(const int32<4>& a)
{
#if SIMDPP_USE_NULL
    int64<4> r;
    r.vec<0>().el(0) = int64_t(a.el(0));
    r.vec<0>().el(1) = int64_t(a.el(1));
    r.vec<1>().el(0) = int64_t(a.el(2));
    r.vec<1>().el(1) = int64_t(a.el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepi32_epi64(a.native());
#elif SIMDPP_USE_SSE4_1
    uint64x2 r1, r2;
    r1 = _mm_cvtepi32_epi64(a.native());
    r2 = _mm_cvtepi32_epi64(move4_l<2>(a).native());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_MSA || SIMDPP_USE_VSX_207
    int32x4 sign = shift_r<31>(a);
    int64x2 lo, hi;
    lo = zip4_lo(a, sign);
    hi = zip4_hi(a, sign);
    return combine(lo, hi);
#elif SIMDPP_USE_NEON
    int64x2 r1, r2;
    r1 = vmovl_s32(vget_low_s32(a.native()));
    r2 = vmovl_s32(vget_high_s32(a.native()));
    return combine(r1, r2);
#elif SIMDPP_USE_ALTIVEC
    int64x4 r;
    mem_block<int32x4> b = a;
    r.vec<0>().el(0) = b[0];
    r.vec<0>().el(1) = b[1];
    r.vec<1>().el(0) = b[2];
    r.vec<1>().el(1) = b[3];
    return r;
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
int64<8> i_to_int64(const int32<8>& a)
{
    int32<4> a1, a2;
    int64<4> r1, r2;
    split(a, a1, a2);
    r1 = _mm256_cvtepi32_epi64(a1.native());
    r2 = _mm256_cvtepi32_epi64(a2.native());
    return combine(r1, r2);
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
int64<16> i_to_int64(const int32<16>& a)
{
    int64<8> r1, r2;
    r1 = _mm512_cvtepi32_epi64(_mm512_castsi512_si256(a.native()));
    r2 = _mm512_cvtepi32_epi64(_mm512_extracti64x4_epi64(a.native(), 1));
    return combine(r1, r2);
}
#endif


template<unsigned I, unsigned End, unsigned M, unsigned N>
struct int32_to_int64_converter {
    static SIMDPP_INL void convert(int64<N>& dst, const int32<N>& src)
    {
        int64<M> sr;
        sr = i_to_int64(src.template vec<I>());
        dst.template vec<I*2>() = sr.template vec<0>();
        dst.template vec<I*2+1>() = sr.template vec<1>();
        int32_to_int64_converter<I + 1, End, M, N>::convert(dst, src);
    }
};

template<unsigned End, unsigned M, unsigned N>
struct int32_to_int64_converter<End, End, M, N> {
    static SIMDPP_INL void convert(int64<N>& dst, const int32<N>& src)
    {
        (void) dst;
        (void) src;
    }
};

template<unsigned N> SIMDPP_INL
int64<N> i_to_int64(const int32<N>& a)
{
    int64<N> r;
    int32_to_int64_converter<0, int32<N>::vec_length, int32<N>::base_length, N>::convert(r, a);
    return r;
}


// -----------------------------------------------------------------------------

static SIMDPP_INL
int64<8> i_to_int64(const int16<8>& a)
{
#if SIMDPP_USE_NULL
    int64<8> r;
    for (unsigned i = 0; i < 8; i++) {
        r.vec(i/2).el(i%2) = int64_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_AVX512F
    return _mm512_cvtepi16_epi64(a.native());
#elif SIMDPP_USE_AVX2
    int64<8> r;
    r.vec<0>() = _mm256_cvtepi16_epi64(a.native());
    r.vec<1>() = _mm256_cvtepi16_epi64(move8_l<4>(a).native());
    return r;
#elif SIMDPP_USE_SSE4_1
    int64<8> r;
    r.vec<0>() = _mm_cvtepi16_epi64(a.native());
    r.vec<1>() = _mm_cvtepi16_epi64(move8_l<2>(a).native());
    r.vec<2>() = _mm_cvtepi16_epi64(move8_l<4>(a).native());
    r.vec<3>() = _mm_cvtepi16_epi64(move8_l<6>(a).native());
    return r;
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_MSA || SIMDPP_USE_VSX_207
    return i_to_int64(i_to_int32(a));
#elif SIMDPP_USE_ALTIVEC
    int64<8> r;
    mem_block<int16<8>> b = a;
    for (unsigned i = 0; i < 8; i++) {
        r.vec(i/2).el(i%2) = int64_t(b[i]);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
int64<16> i_to_int64(const int16<16>& a)
{
#if SIMDPP_USE_AVX512F
    int64<16> r;
    int16<8> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm512_cvtepi16_epi64(a0.native());
    r.vec<1>() = _mm512_cvtepi16_epi64(a1.native());
    return r;
#else
    int64<16> r;
    int16<8> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm256_cvtepi16_epi64(a0.native());
    r.vec<1>() = _mm256_cvtepi16_epi64(move8_l<4>(a0).native());
    r.vec<2>() = _mm256_cvtepi16_epi64(a1.native());
    r.vec<3>() = _mm256_cvtepi16_epi64(move8_l<4>(a1).native());
    return r;
#endif
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
int64<32> i_to_int64(const int16<32>& a)
{
    int64<32> r;
    int16<16> a01, a23;
    int16<8> a0, a1, a2, a3;
#if SIMDPP_USE_AVX512BW
    split(a, a01, a23);
#else
    a01 = a.vec<0>();
    a23 = a.vec<1>();
#endif
    split(a01, a0, a1);
    split(a23, a2, a3);

    r.vec<0>() =  _mm512_cvtepi16_epi64(a0.native());
    r.vec<1>() =  _mm512_cvtepi16_epi64(a1.native());
    r.vec<2>() =  _mm512_cvtepi16_epi64(a2.native());
    r.vec<3>() =  _mm512_cvtepi16_epi64(a3.native());
    return r;
}
#endif

template<unsigned I, unsigned End, unsigned M, unsigned N>
struct int16_to_int64_converter {
    static SIMDPP_INL void convert(int64<N>& dst, const int16<N>& src)
    {
        int64<M> sr;
        sr = i_to_int64(src.template vec<I>());
        dst.template vec<I*4>() = sr.template vec<0>();
        dst.template vec<I*4+1>() = sr.template vec<1>();
        dst.template vec<I*4+2>() = sr.template vec<2>();
        dst.template vec<I*4+3>() = sr.template vec<3>();
        int16_to_int64_converter<I + 1, End, M, N>::convert(dst, src);
    }
};

template<unsigned End, unsigned M, unsigned N>
struct int16_to_int64_converter<End, End, M, N> {
    static SIMDPP_INL void convert(int64<N>& dst, const int16<N>& src)
    {
        (void) dst;
        (void) src;
    }
};

template<unsigned N> SIMDPP_INL
int64<N> i_to_int64(const int16<N>& a)
{
    int64<N> r;
    int16_to_int64_converter<0, int16<N>::vec_length, int16<N>::base_length, N>::convert(r, a);
    return r;
}

// -----------------------------------------------------------------------------

static SIMDPP_INL
int64<16> i_to_int64(const int8<16>& a)
{
#if SIMDPP_USE_NULL
    int64<16> r;
    for (unsigned i = 0; i < 16; i++) {
        r.vec(i/2).el(i%2) = int64_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_AVX512F
    int64<16> r;
    r.vec<0>() = _mm512_cvtepi8_epi64(a.native());
    r.vec<1>() = _mm512_cvtepi8_epi64(move16_l<8>(a).native());
    return r;
#elif SIMDPP_USE_AVX2
    int64<16> r;
    r.vec<0>() = _mm256_cvtepi8_epi64(a.native());
    r.vec<1>() = _mm256_cvtepi8_epi64(move16_l<4>(a).native());
    r.vec<2>() = _mm256_cvtepi8_epi64(move16_l<8>(a).native());
    r.vec<3>() = _mm256_cvtepi8_epi64(move16_l<12>(a).native());
    return r;
#elif SIMDPP_USE_SSE4_1
    int64<16> r;
    r.vec<0>() = _mm_cvtepi8_epi64(a.native());
    r.vec<1>() = _mm_cvtepi8_epi64(move16_l<2>(a).native());
    r.vec<2>() = _mm_cvtepi8_epi64(move16_l<4>(a).native());
    r.vec<3>() = _mm_cvtepi8_epi64(move16_l<6>(a).native());
    r.vec<4>() = _mm_cvtepi8_epi64(move16_l<8>(a).native());
    r.vec<5>() = _mm_cvtepi8_epi64(move16_l<10>(a).native());
    r.vec<6>() = _mm_cvtepi8_epi64(move16_l<12>(a).native());
    r.vec<7>() = _mm_cvtepi8_epi64(move16_l<14>(a).native());
    return r;
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_MSA || SIMDPP_USE_VSX_207
    return i_to_int64(i_to_int32(a));
#elif SIMDPP_USE_ALTIVEC
    int64<16> r;
    mem_block<int8<16>> b = a;
    for (unsigned i = 0; i < 16; i++) {
        r.vec(i/2).el(i%2) = int64_t(b[i]);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
int64<32> i_to_int64(const int8<32>& a)
{
#if SIMDPP_USE_AVX512F
    int64<32> r;
    int8<16> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm512_cvtepi8_epi64(a0.native());
    r.vec<1>() = _mm512_cvtepi8_epi64(move16_l<8>(a0).native());
    r.vec<2>() = _mm512_cvtepi8_epi64(a1.native());
    r.vec<3>() = _mm512_cvtepi8_epi64(move16_l<8>(a1).native());
    return r;
#else
    int64<32> r;
    int8<16> a0, a1;
    split(a, a0, a1);
    r.vec<0>() = _mm256_cvtepi8_epi64(a0.native());
    r.vec<1>() = _mm256_cvtepi8_epi64(move16_l<4>(a0).native());
    r.vec<2>() = _mm256_cvtepi8_epi64(move16_l<8>(a0).native());
    r.vec<3>() = _mm256_cvtepi8_epi64(move16_l<12>(a0).native());
    r.vec<4>() = _mm256_cvtepi8_epi64(a1.native());
    r.vec<5>() = _mm256_cvtepi8_epi64(move16_l<4>(a1).native());
    r.vec<6>() = _mm256_cvtepi8_epi64(move16_l<8>(a1).native());
    r.vec<7>() = _mm256_cvtepi8_epi64(move16_l<12>(a1).native());
    return r;
#endif
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
int64<64> i_to_int64(const int8<64>& a)
{
    int64<64> r;
    int8<32> a01, a23;
    int8<16> a0, a1, a2, a3;
#if SIMDPP_USE_AVX512BW
    split(a, a01, a23);
#else
    a01 = a.vec<0>();
    a23 = a.vec<1>();
#endif
    split(a01, a0, a1);
    split(a23, a2, a3);

    r.vec<0>() =  _mm512_cvtepi8_epi64(a0.native());
    r.vec<1>() =  _mm512_cvtepi8_epi64(move16_l<8>(a0).native());
    r.vec<2>() =  _mm512_cvtepi8_epi64(a1.native());
    r.vec<3>() =  _mm512_cvtepi8_epi64(move16_l<8>(a1).native());
    r.vec<4>() =  _mm512_cvtepi8_epi64(a2.native());
    r.vec<5>() =  _mm512_cvtepi8_epi64(move16_l<8>(a2).native());
    r.vec<6>() =  _mm512_cvtepi8_epi64(a3.native());
    r.vec<7>() =  _mm512_cvtepi8_epi64(move16_l<8>(a3).native());
    return r;
}
#endif

template<unsigned I, unsigned End, unsigned M, unsigned N>
struct int8_to_int64_converter {
    static SIMDPP_INL void convert(int64<N>& dst, const int8<N>& src)
    {
        int64<M> sr;
        sr = i_to_int64(src.template vec<I>());
        dst.template vec<I*8>() = sr.template vec<0>();
        dst.template vec<I*8+1>() = sr.template vec<1>();
        dst.template vec<I*8+2>() = sr.template vec<2>();
        dst.template vec<I*8+3>() = sr.template vec<3>();
        dst.template vec<I*8+4>() = sr.template vec<4>();
        dst.template vec<I*8+5>() = sr.template vec<5>();
        dst.template vec<I*8+6>() = sr.template vec<6>();
        dst.template vec<I*8+7>() = sr.template vec<7>();
        int8_to_int64_converter<I + 1, End, M, N>::convert(dst, src);
    }
};

template<unsigned End, unsigned M, unsigned N>
struct int8_to_int64_converter<End, End, M, N> {
    static SIMDPP_INL void convert(int64<N>& dst, const int8<N>& src)
    {
        (void) dst;
        (void) src;
    }
};

template<unsigned N> SIMDPP_INL
int64<N> i_to_int64(const int8<N>& a)
{
    int64<N> r;
    int8_to_int64_converter<0, int8<N>::vec_length, int8<N>::base_length, N>::convert(r, a);
    return r;
}

// -----------------------------------------------------------------------------

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif


