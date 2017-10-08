/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_NOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_NOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/detail/null/bitwise.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


static SIMDPP_INL
uint8x16 i_bit_not(const uint8x16& a)
{
#if SIMDPP_USE_NULL
    uint8x16 r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = ~a.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    return bit_xor(a, 0xff);
#elif SIMDPP_USE_NEON
    return vmvnq_u8(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector uint8_t)a, (__vector uint8_t)a);
#elif SIMDPP_USE_MSA
    return __msa_nor_v(a, a);
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
uint8x32 i_bit_not(const uint8x32& a)
{
    return bit_xor(a, 0xff);
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL uint8<64> i_bit_not(const uint8<64>& a)
{
    return _mm512_ternarylogic_epi32(a, a, a, 0x1);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint16<8> i_bit_not(const uint16<8>& a)
{
    return uint16<8>(i_bit_not(uint8<16>(a)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16<16> i_bit_not(const uint16<16>& a)
{
    return uint16<16>(i_bit_not(uint8<32>(a)));
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL uint16<32> i_bit_not(const uint16<32>& a)
{
    return _mm512_ternarylogic_epi32(a, a, a, 0x1);
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
uint32<4> i_bit_not(const uint32<4>& a)
{
    return uint32<4>(i_bit_not(uint8<16>(a)));
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
uint32<8> i_bit_not(const uint32<8>& a)
{
    return uint32<8>(i_bit_not(uint8<32>(a)));
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
uint32<16> i_bit_not(const uint32<16>& a)
{
    return _mm512_ternarylogic_epi32(a, a, a, 0x1);
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
uint64<2> i_bit_not(const uint64<2>& a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_ALTIVEC && !SIMDPP_USE_VSX_207)
    uint64x2 r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = ~a.el(i);
    }
    return r;
#else
    return uint64<2>(i_bit_not(uint8<16>(a)));
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL
uint64<4> i_bit_not(const uint64<4>& a)
{
    return uint64<4>(i_bit_not(uint8<32>(a)));
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
uint64<8> i_bit_not(const uint64<8>& a)
{
    return _mm512_ternarylogic_epi64(a, a, a, 0x1);
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
mask_int8x16 i_bit_not(const mask_int8x16& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int8x16)i_bit_not(uint8x16(a));
#endif
}

static SIMDPP_INL
mask_int16x8 i_bit_not(const mask_int16x8& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int16x8)i_bit_not(uint16x8(a));
#endif
}

static SIMDPP_INL
mask_int32x4 i_bit_not(const mask_int32x4& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int32x4)i_bit_not(uint32x4(a));
#endif
}

static SIMDPP_INL
mask_int64x2 i_bit_not(const mask_int64x2& a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_ALTIVEC && !SIMDPP_USE_VSX_207)
    return detail::null::bit_not_mm(a);
#else
    return (mask_int64x2)i_bit_not(uint64x2(a));
#endif
}

#if SIMDPP_USE_AVX2
static SIMDPP_INL mask_int8x32  i_bit_not(const mask_int8x32& a)  { return i_bit_not(uint8x32(a)); }
static SIMDPP_INL mask_int16x16 i_bit_not(const mask_int16x16& a) { return i_bit_not(uint16x16(a)); }
static SIMDPP_INL mask_int32x8  i_bit_not(const mask_int32x8& a)  { return i_bit_not(uint32x8(a)); }
static SIMDPP_INL mask_int64x4  i_bit_not(const mask_int64x4& a)  { return i_bit_not(uint64x4(a)); }
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
mask_int32<16> i_bit_not(const mask_int32<16>& a)
{
    return _mm512_knot(a);
}

static SIMDPP_INL
mask_int64<8> i_bit_not(const mask_int64<8>& a)
{
    return _mm512_knot(a);
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL mask_int8<64> i_bit_not(const mask_int8<64>& a)
{
    return ~(__mmask64)a;
}

SIMDPP_INL mask_int16<32> i_bit_not(const mask_int16<32>& a)
{
    return ~(__mmask32)a;
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
float32x4 i_bit_not(const float32x4& a)
{
#if SIMDPP_USE_SSE2
    return bit_xor(a, 0xffffffff);
#elif SIMDPP_USE_NEON
    return (float32<4>) (uint32<4>) vmvnq_u32((uint32x4)a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector float)a, (__vector float)a);
#elif SIMDPP_USE_NULL || SIMDPP_USE_MSA
    return float32x4(i_bit_not(uint32x4(a)));
#endif
}

#if SIMDPP_USE_AVX
static SIMDPP_INL
float32x8 i_bit_not(const float32x8& a)
{
    return bit_xor(a, 0xffffffff);
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
float32<16> i_bit_not(const float32<16>& a)
{
    uint32<16> b; b = a;
    b = _mm512_ternarylogic_epi32(b, b, b, 0x1);
    return float32<16>(b);
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
float64x2 i_bit_not(const float64x2& a)
{
#if SIMDPP_USE_SSE2
    return bit_xor(a, 0xffffffffffffffff);
#elif SIMDPP_USE_NEON64
    return (float64<2>) (uint32<4>) vmvnq_u32((uint32<4>)a);
#elif SIMDPP_USE_VSX_206
    return vec_nor((__vector double) a, (__vector double) a);
#elif SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
    return float64x2(i_bit_not(uint64x2(a)));
#endif
}

#if SIMDPP_USE_AVX
static SIMDPP_INL
float64x4 i_bit_not(const float64x4& a)
{
    return bit_xor(a, 0xffffffffffffffff);
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
float64<8> i_bit_not(const float64<8>& a)
{
    uint64<8> b; b = a;
    b = _mm512_ternarylogic_epi64(b, b, b, 0x1);
    return float64<8>(b);
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
mask_float32x4 i_bit_not(const mask_float32x4& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::bit_not_mm(a);
#else
    return (mask_float32<4>) (float32<4>) i_bit_not(float32<4>(a));
#endif
}

#if SIMDPP_USE_AVX
static SIMDPP_INL
mask_float32x8 i_bit_not(const mask_float32x8& a)
{
    return i_bit_not(float32x8(a));
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
mask_float32<16> i_bit_not(const mask_float32<16>& a)
{
    return _mm512_knot(a);
}
#endif

// -----------------------------------------------------------------------------

static SIMDPP_INL
mask_float64x2 i_bit_not(const mask_float64x2& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || (SIMDPP_USE_ALTIVEC && !SIMDPP_USE_VSX_206)
    return detail::null::bit_not_mm(a);
#else
    return (mask_float64x2) i_bit_not(float64x2(a));
#endif
}

#if SIMDPP_USE_AVX
static SIMDPP_INL
mask_float64x4 i_bit_not(const mask_float64x4& a)
{
    return i_bit_not(float64x4(a));
}
#endif

#if SIMDPP_USE_AVX512F
static SIMDPP_INL
mask_float64<8> i_bit_not(const mask_float64<8>& a)
{
    return _mm512_knot(a);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
V i_bit_not(const V& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(V, i_bit_not, a)
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

