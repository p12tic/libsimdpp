/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_XOR_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_XOR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/foreach.h>
#include <simdpp/detail/null/bitwise.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// -----------------------------------------------------------------------------
// uint8, uint8
SIMDPP_INL uint8x16 i_bit_xor(const uint8x16& a, const uint8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_xor(a, uint8x16(b));
#elif SIMDPP_USE_SSE2
    return _mm_xor_si128(a, b);
#elif SIMDPP_USE_NEON
    return veorq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_bit_xor(const uint8x32& a, const uint8x32& b)
{
    return _mm256_xor_si256(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_bit_xor(const uint8<N>& a, const uint8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8x32, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// mask_int8, mask_int8
SIMDPP_INL mask_int8x16 i_bit_xor(const mask_int8x16& a, const mask_int8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_xor_mm(a, b);
#else
    return (mask_int8x16) i_bit_xor(uint8x16(a), uint8x16(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8x32 i_bit_xor(const mask_int8x32& a, const mask_int8x32& b)
{
    return _mm256_xor_si256(a, b);
    }
#endif

template<unsigned N> SIMDPP_INL
mask_int8<N> i_bit_xor(const mask_int8<N>& a, const mask_int8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// uint16, uint16
SIMDPP_INL uint16<8> i_bit_xor(const uint16<8>& a, const uint16<8>& b)
{
    return (uint16<8>) i_bit_xor(uint8<16>(a), uint8<16>(b));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16<16> i_bit_xor(const uint16<16>& a, const uint16<16>& b)
{
    return _mm256_xor_si256(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint16<N> i_bit_xor(const uint16<N>& a, const uint16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// mask_int16, mask_int16
SIMDPP_INL mask_int16<8> i_bit_xor(const mask_int16<8>& a, const mask_int16<8>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_xor_mm(a, b);
#else
    return (mask_int16<8>) (uint16<8>) i_bit_xor(uint8<16>(a), uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int16<16> i_bit_xor(const mask_int16<16>& a, const mask_int16<16>& b)
{
    return (mask_int16<16>) (uint16<16>) i_bit_xor(uint16<16>(a), uint16<16>(b));
}
#endif

template<unsigned N> SIMDPP_INL
mask_int16<N> i_bit_xor(const mask_int16<N>& a, const mask_int16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, i_bit_xor, a, b)
}


// -----------------------------------------------------------------------------
// uint32, uint32
SIMDPP_INL uint32<4> i_bit_xor(const uint32<4>& a, const uint32<4>& b)
{
    return (uint32<4>) i_bit_xor(uint8<16>(a), uint8<16>(b));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32<8> i_bit_xor(const uint32<8>& a, const uint32<8>& b)
{
    return _mm256_xor_si256(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint32<16> i_bit_xor(const uint32<16>& a, const uint32<16>& b)
{
    return _mm512_xor_epi32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_bit_xor(const uint32<N>& a, const uint32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// mask_int32, mask_int32
SIMDPP_INL mask_int32<4> i_bit_xor(const mask_int32<4>& a, const mask_int32<4>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_xor_mm(a, b);
#else
    return (mask_int32<4>) (uint32<4>) i_bit_xor(uint8<16>(a), uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int32<8> i_bit_xor(const mask_int32<8>& a, const mask_int32<8>& b)
{
    return (mask_int32<8>) (uint32<8>) i_bit_xor(uint32<8>(a), uint32<8>(b));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_int32<16> i_bit_xor(const mask_int32<16>& a, const mask_int32<16>& b)
{
    return _mm512_kxor(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
mask_int32<N> i_bit_xor(const mask_int32<N>& a, const mask_int32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// uint64, uint64
SIMDPP_INL uint64<2> i_bit_xor(const uint64<2>& a, const uint64<2>& b)
{
    return (uint64<2>) i_bit_xor(uint8<16>(a), uint8<16>(b));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<4> i_bit_xor(const uint64<4>& a, const uint64<4>& b)
{
    return _mm256_xor_si256(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint64<8> i_bit_xor(const uint64<8>& a, const uint64<8>& b)
{
    return _mm512_xor_epi64(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint64<N> i_bit_xor(const uint64<N>& a, const uint64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// mask_int64, mask_int64
SIMDPP_INL mask_int64<2> i_bit_xor(const mask_int64<2>& a, const mask_int64<2>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_xor_mm(a, b);
#else
    return (mask_int64<2>) (uint64<2>) i_bit_xor(uint8<16>(a), uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int64<4> i_bit_xor(const mask_int64<4>& a, const mask_int64<4>& b)
{
    return (mask_int64<4>) (uint64<4>) i_bit_xor(uint64<4>(a), uint64<4>(b));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_int64<8> i_bit_xor(const mask_int64<8>& a, const mask_int64<8>& b)
{
    return _mm512_kxor(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
mask_int64<N> i_bit_xor(const mask_int64<N>& a, const mask_int64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int64<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------

SIMDPP_INL float32x4 i_bit_xor(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(a), vreinterpretq_s32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_or((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_bit_xor(const float32x8& a, const float32x8& b)
{
    return _mm256_xor_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL float32<16> i_bit_xor(const float32<16>& a, const float32<16>& b)
{
    return (float32<16>) i_bit_xor(uint32<16>(a), uint32<16>(b));
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_bit_xor(const float32<N>& a, const float32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// mask_float32, mask_float32

SIMDPP_INL mask_float32x4 i_bit_xor(const mask_float32x4& a, const mask_float32x4& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::bit_xor_mm(a, b);
#else
    return (mask_float32x4) i_bit_xor(float32x4(a), float32x4(b));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_bit_xor(const mask_float32x8& a, const mask_float32x8& b)
{
    return i_bit_xor(float32x8(a), float32x8(b));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_float32<16> i_bit_xor(const mask_float32<16>& a, const mask_float32<16>& b)
{
    return _mm512_kxor(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
mask_float32<N> i_bit_xor(const mask_float32<N>& a, const mask_float32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// float64, float64

SIMDPP_INL float64x2 i_bit_xor(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_pd(a, b);
#elif SIMDPP_USE_NEON64
    return vreinterpretq_f64_u64(veorq_u64(vreinterpretq_u64_f64(a),
                                           vreinterpretq_u64_f64(b)));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64x4 i_bit_xor(const float64x4& a, const float64x4& b)
{
    return _mm256_xor_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL float64<8> i_bit_xor(const float64<8>& a, const float64<8>& b)
{
    return (float64<8>) i_bit_xor(uint64<8>(a), uint64<8>(b));
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_bit_xor(const float64<N>& a, const float64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_bit_xor, a, b)
}

// -----------------------------------------------------------------------------
// mask_float64, mask_float64

SIMDPP_INL mask_float64x2 i_bit_xor(const mask_float64x2& a, mask_float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::bit_xor_mm(a, b);
#else
    return (mask_float64x2) i_bit_xor(float64x2(a), float64x2(b));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_bit_xor(const mask_float64x4& a, const mask_float64x4& b)
{
    return i_bit_xor(float64x4(a), float64x4(b));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_float64<8> i_bit_xor(const mask_float64<8>& a, const mask_float64<8>& b)
{
    return _mm512_kxor(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
mask_float64<N> i_bit_xor(const mask_float64<N>& a, const mask_float64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_bit_xor, a, b)
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


