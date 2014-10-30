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
#include <simdpp/detail/null/foreach.h>
#include <simdpp/detail/null/bitwise.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


SIMDPP_INL uint8x16 i_bit_not(const uint8x16& a)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<uint8x16>(a, [](uint64_t a){ return ~a; });
#elif SIMDPP_USE_SSE2
    uint8x16 ones = uint8x16::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return vmvnq_u8(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector uint8_t)a, (__vector uint8_t)a);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_bit_not(const uint8x32& a)
{
    uint8x32 ones = uint8x32::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_bit_not(const uint8<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

template<unsigned N> SIMDPP_INL
uint16<N> i_bit_not(const uint16<N>& a) { return uint16<N>(i_bit_not(uint8<N*2>(a))); }

// -----------------------------------------------------------------------------

SIMDPP_INL uint32<4> i_bit_not(const uint32<4>& a)
{
    return uint32<4>(i_bit_not(uint8<16>(a)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32<8> i_bit_not(const uint32<8>& a)
{
    return uint32<8>(i_bit_not(uint8<32>(a)));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint32<16> i_bit_not(const uint32<16>& a)
{
    uint32<16> ones = uint32<16>::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_bit_not(const uint32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint64<2> i_bit_not(const uint64<2>& a)
{
    return uint64<2>(i_bit_not(uint8<16>(a)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<4> i_bit_not(const uint64<4>& a)
{
    return uint64<4>(i_bit_not(uint8<32>(a)));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint64<8> i_bit_not(const uint64<8>& a)
{
    uint64<8> ones = uint64<8>::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N> SIMDPP_INL
uint64<N> i_bit_not(const uint64<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int8x16 i_bit_not(const mask_int8x16& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int8x16)i_bit_not(uint8x16(a));
#endif
}

SIMDPP_INL mask_int16x8 i_bit_not(const mask_int16x8& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int16x8)i_bit_not(uint16x8(a));
#endif
}

SIMDPP_INL mask_int32x4 i_bit_not(const mask_int32x4& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int32x4)i_bit_not(uint32x4(a));
#endif
}

SIMDPP_INL mask_int64x2 i_bit_not(const mask_int64x2& a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int64x2)i_bit_not(uint64x2(a));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8x32  i_bit_not(const mask_int8x32& a)  { return i_bit_not(uint8x32(a)); }
SIMDPP_INL mask_int16x16 i_bit_not(const mask_int16x16& a) { return i_bit_not(uint16x16(a)); }
SIMDPP_INL mask_int32x8  i_bit_not(const mask_int32x8& a)  { return i_bit_not(uint32x8(a)); }
SIMDPP_INL mask_int64x4  i_bit_not(const mask_int64x4& a)  { return i_bit_not(uint64x4(a)); }
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_int32<16> i_bit_not(const mask_int32<16>& a)
{
    return _mm512_knot(a);
}

SIMDPP_INL mask_int64<8> i_bit_not(const mask_int64<8>& a)
{
    return _mm512_knot(a);
}
#endif

template<unsigned N> SIMDPP_INL
mask_int8<N> i_bit_not(const mask_int8<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int8<N>, i_bit_not, a)
}
template<unsigned N> SIMDPP_INL
mask_int16<N> i_bit_not(const mask_int16<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int16<N>, i_bit_not, a)
}
template<unsigned N> SIMDPP_INL
mask_int32<N> i_bit_not(const mask_int32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int32<N>, i_bit_not, a)
}
template<unsigned N> SIMDPP_INL
mask_int64<N> i_bit_not(const mask_int64<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int64<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

SIMDPP_INL float32x4 i_bit_not(const float32x4& a)
{
#if SIMDPP_USE_NULL
    return float32x4(i_bit_not(uint32x4(a)));
#elif SIMDPP_USE_SSE2
    uint32x4 ones = uint32x4::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return (float32<4>) (uint32<4>) vmvnq_u32((uint32x4)a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector float)a, (__vector float)a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_bit_not(const float32x8& a)
{
    uint32x8 ones = uint32x8::ones();
    return bit_xor(a, ones);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL float32<16> i_bit_not(const float32<16>& a)
{
    uint32<16> ones = uint32<16>::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_bit_not(const float32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

SIMDPP_INL float64x2 i_bit_not(const float64x2& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return float64x2(i_bit_not(uint64x2(a)));
#elif SIMDPP_USE_SSE2
    uint64x2 ones = uint64x2::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON64
    return (float64<2>) (uint32<4>) vmvnq_u32((uint32<4>)a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64x4 i_bit_not(const float64x4& a)
{
    uint64x4 ones = uint64x4::ones();
    return bit_xor(a, ones);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL float64<8> i_bit_not(const float64<8>& a)
{
    uint64<8> ones = uint64<8>::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_bit_not(const float64<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float32x4 i_bit_not(const mask_float32x4& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::bit_not_mm(a);
#else
    return (mask_float32<4>) (float32<4>) i_bit_not(float32<4>(a));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_bit_not(const mask_float32x8& a)
{
    return i_bit_not(float32x8(a));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_float32<16> i_bit_not(const mask_float32<16>& a)
{
    return _mm512_knot(a);
}
#endif

template<unsigned N> SIMDPP_INL
mask_float32<N> i_bit_not(const mask_float32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_float32<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float64x2 i_bit_not(const mask_float64x2& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::bit_not_mm(a);
#else
    return (mask_float64x2) i_bit_not(float64x2(a));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_bit_not(const mask_float64x4& a)
{
    return i_bit_not(float64x4(a));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_float64<8> i_bit_not(const mask_float64<8>& a)
{
    return _mm512_knot(a);
}
#endif

template<unsigned N> SIMDPP_INL
mask_float64<N> i_bit_not(const mask_float64<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_float64<N>, i_bit_not, a)
}


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

