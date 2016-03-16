/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_ANDNOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_ANDNOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/bitwise.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// see doc/src/expressions.md for the list of types we must cover

// -----------------------------------------------------------------------------
// uint8, uint8
SIMDPP_INL uint8<16> i_bit_andnot(const uint8<16>& a, const uint8<16>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_si128(b, a);
#elif SIMDPP_USE_NEON
    return vbicq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_andc((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8<32> i_bit_andnot(const uint8<32>& a, const uint8<32>& b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

// -----------------------------------------------------------------------------
// uint8, mask_int8
SIMDPP_INL uint8<16> i_bit_andnot(const uint8<16>& a, const mask_int8<16>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8<32> i_bit_andnot(const uint8<32>& a, const mask_int8<32>& b)
{
    return i_bit_andnot(a, uint8<32>(b));
}
#endif

// -----------------------------------------------------------------------------
// mask_int8, mask_int8
SIMDPP_INL mask_int8<16> i_bit_andnot(const mask_int8<16>& a, const mask_int8<16>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_int8<16>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8<32> i_bit_andnot(const mask_int8<32>& a, const mask_int8<32>& b)
{
    return mask_int8<32>(i_bit_andnot(uint8<32>(a), uint8<32>(b)));
}
#endif

// -----------------------------------------------------------------------------
// uint16, uint16
SIMDPP_INL uint16<8> i_bit_andnot(const uint16<8>& a, const uint16<8>& b)
{
    return uint16<8>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16<16> i_bit_andnot(const uint16<16>& a, const uint16<16>& b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

// -----------------------------------------------------------------------------
// uint16, mask_int16
SIMDPP_INL uint16<8> i_bit_andnot(const uint16<8>& a, const mask_int16<8>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint16<8>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16<16> i_bit_andnot(const uint16<16>& a, const mask_int16<16>& b)
{
    return i_bit_andnot(a, uint16<16>(b));
}
#endif

// -----------------------------------------------------------------------------
// mask_int16, mask_int16
SIMDPP_INL mask_int16<8> i_bit_andnot(const mask_int16<8>& a, const mask_int16<8>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return (mask_int16<8>) (uint16<8>) i_bit_andnot(uint8<16>(a), uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int16<16> i_bit_andnot(const mask_int16<16>& a, const mask_int16<16>& b)
{
    return (mask_int16<16>) (uint16<16>) i_bit_andnot(uint16<16>(a), uint16<16>(b));
}
#endif

// -----------------------------------------------------------------------------
// uint32, uint32
SIMDPP_INL uint32<4> i_bit_andnot(const uint32<4>& a, const uint32<4>& b)
{
    return uint32<4>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32<8> i_bit_andnot(const uint32<8>& a, const uint32<8>& b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_bit_andnot(const uint32<16>& a, const uint32<16>& b)
{
    return _mm512_andnot_epi32(b, a);
}
#endif

// -----------------------------------------------------------------------------
// uint32, mask_int32
SIMDPP_INL uint32<4> i_bit_andnot(const uint32<4>& a, const mask_int32<4>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint32<4>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32<8> i_bit_andnot(const uint32<8>& a, const mask_int32<8>& b)
{
    return i_bit_andnot(a, uint32<8>(b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_bit_andnot(const uint32<16>& a, const mask_int32<16>& b)
{
    return _mm512_maskz_mov_epi32(_mm512_knot(b), a);
}
#endif

// -----------------------------------------------------------------------------
// mask_int32, mask_int32
SIMDPP_INL mask_int32<4> i_bit_andnot(const mask_int32<4>& a, const mask_int32<4>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return (mask_int32<4>) (uint32<4>) i_bit_andnot(uint8<16>(a), uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int32<8> i_bit_andnot(const mask_int32<8>& a, const mask_int32<8>& b)
{
    return (mask_int32<8>) (uint32<8>) i_bit_andnot(uint32<8>(a), uint32<8>(b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int32<16> i_bit_andnot(const mask_int32<16>& a, const mask_int32<16>& b)
{
    return _mm512_kandn(b, a);
}
#endif

// -----------------------------------------------------------------------------
// uint64, uint64
SIMDPP_INL uint64<2> i_bit_andnot(const uint64<2>& a, const uint64<2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::bit_andnot(a, b);
#else
    return uint64<2>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<4> i_bit_andnot(const uint64<4>& a, const uint64<4>& b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_bit_andnot(const uint64<8>& a, const uint64<8>& b)
{
    return _mm512_andnot_epi64(b, a);
}
#endif

// -----------------------------------------------------------------------------
// uint64, mask_int64
SIMDPP_INL uint64<2> i_bit_andnot(const uint64<2>& a, const mask_int64<2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint64<2>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<4> i_bit_andnot(const uint64<4>& a, const mask_int64<4>& b)
{
    return i_bit_andnot(a, uint64<4>(b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_bit_andnot(const uint64<8>& a, const mask_int64<8>& b)
{
    return _mm512_maskz_mov_epi64(_mm512_knot(b), a);
}
#endif

// -----------------------------------------------------------------------------
// mask_int64, mask_int64
SIMDPP_INL mask_int64<2> i_bit_andnot(const mask_int64<2>& a, const mask_int64<2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::bit_andnot_mm(a, b);
#else
    return (mask_int64<2>) (uint64<2>) i_bit_andnot(uint8<16>(a), uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int64<4> i_bit_andnot(const mask_int64<4>& a, const mask_int64<4>& b)
{
    return (mask_int64<4>) (uint64<4>) i_bit_andnot(uint64<4>(a), uint64<4>(b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int64<8> i_bit_andnot(const mask_int64<8>& a, const mask_int64<8>& b)
{
    return _mm512_kandn(b, a);
}
#endif

// -----------------------------------------------------------------------------
// float32, float32
SIMDPP_INL float32<4> i_bit_andnot(const float32<4>& a, const float32<4>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_ps(b, a);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(a),
                                           vreinterpretq_u32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_andc((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32<8> i_bit_andnot(const float32<8>& a, const float32<8>& b)
{
    return _mm256_andnot_ps(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_bit_andnot(const float32<16>& a, const float32<16>& b)
{
    return float32<16>(i_bit_andnot(uint32<16>(a), uint32<16>(b)));
}
#endif

// -----------------------------------------------------------------------------
// float32, mask_float32
SIMDPP_INL float32<4> i_bit_andnot(const float32<4>& a, const mask_float32<4>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, float32<4>(b));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32<8> i_bit_andnot(const float32<8>& a, const mask_float32<8>& b)
{
    return i_bit_andnot(a, float32<8>(b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_bit_andnot(const float32<16>& a, const mask_float32<16>& b)
{
    return _mm512_maskz_mov_ps(_mm512_knot(b), a);
}
#endif

// -----------------------------------------------------------------------------
// mask_float32, mask_float32
SIMDPP_INL mask_float32<4> i_bit_andnot(const mask_float32<4>& a, const mask_float32<4>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_float32<4>(i_bit_andnot(float32<4>(a), float32<4>(b)));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32<8> i_bit_andnot(const mask_float32<8>& a, const mask_float32<8>& b)
{
    return mask_float32<8>(i_bit_andnot(float32<8>(a), float32<8>(b)));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float32<16> i_bit_andnot(const mask_float32<16>& a, const mask_float32<16>& b)
{
    return _mm512_kandn(b, a);
}
#endif

// -----------------------------------------------------------------------------
// float64, float64
SIMDPP_INL float64<2> i_bit_andnot(const float64<2>& a, const float64<2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_pd(b, a);
#elif SIMDPP_USE_NEON64
    return vreinterpretq_f64_u64(vbicq_u64(vreinterpretq_u64_f64(a),
                                           vreinterpretq_u64_f64(b)));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64<4> i_bit_andnot(const float64<4>& a, const float64<4>& b)
{
    return _mm256_andnot_pd(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_bit_andnot(const float64<8>& a, const float64<8>& b)
{
    return float64<8>(i_bit_andnot(uint64<8>(a), uint64<8>(b)));
}
#endif

// -----------------------------------------------------------------------------
// float64, mask_float64
SIMDPP_INL float64<2> i_bit_andnot(const float64<2>& a, const mask_float64<2>& b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, float64<2>(b));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64<4> i_bit_andnot(const float64<4>& a, const mask_float64<4>& b)
{
    return i_bit_andnot(a, float64<4>(b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_bit_andnot(const float64<8>& a, const mask_float64<8>& b)
{
    return _mm512_maskz_mov_pd(_mm512_knot(b), a);
}
#endif

// -----------------------------------------------------------------------------
// mask_float64, mask_float64
SIMDPP_INL mask_float64<2> i_bit_andnot(const mask_float64<2>& a, const mask_float64<2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_float64<2>(i_bit_andnot(float64<2>(a), float64<2>(b)));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64<4> i_bit_andnot(const mask_float64<4>& a, const mask_float64<4>& b)
{
    return mask_float64<4>(i_bit_andnot(float64<4>(a), float64<4>(b)));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float64<8> i_bit_andnot(const mask_float64<8>& a, const mask_float64<8>& b)
{
    return _mm512_kandn(b, a);
}
#endif

// -----------------------------------------------------------------------------

template<class V, class VM> SIMDPP_INL
V i_bit_andnot(const V& a, const VM& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(V, i_bit_andnot, a, b)
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

