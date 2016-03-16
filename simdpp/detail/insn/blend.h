/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BLEND_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BLEND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/detail/null/shuffle.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// see doc/src/expressions.md for the list of types we must cover

// -----------------------------------------------------------------------------
// uint8, uint8, uint8

SIMDPP_INL uint8<16> i_blend(const uint8<16>& con, const uint8<16>& coff, const uint8<16>& mask)
{
    uint8<16> on = con, off = coff;
#if SIMDPP_USE_NULL
    return detail::null::blend(on, off, mask);
#elif SIMDPP_USE_AVX2
    return _mm_blendv_epi8(off, on, mask);
#elif SIMDPP_USE_XOP
    return _mm_cmov_si128(on, off, mask);
#elif SIMDPP_USE_SSE2
    // _mm_blendv_epi8 needs xmm0 and occupies the shuffle ports, yet saves
    // only one uop
    uint8<16> r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON
    return vbslq_u8(mask, on, off);
#elif SIMDPP_USE_ALTIVEC
    return vec_sel((__vector uint8_t)off, (__vector uint8_t)on,
                   (__vector uint8_t)mask);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8<32> i_blend(const uint8<32>& on, const uint8<32>& off, const uint8<32>& mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

// -----------------------------------------------------------------------------
// uint8, uint8, mask_int8

SIMDPP_INL uint8<16> i_blend(const uint8<16>& on, const uint8<16>& off, const mask_int8<16>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, uint8<16>(mask));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8<32> i_blend(const uint8<32>& on, const uint8<32>& off, const mask_int8<32>& mask)
{
    return i_blend(on, off, uint8<32>(mask));
}
#endif

// -----------------------------------------------------------------------------
// mask_int8, mask_int8, mask_int8

SIMDPP_INL mask_int8<16> i_blend(const mask_int8<16>& on, const mask_int8<16>& off, const mask_int8<16>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int8<16>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8<32> i_blend(const mask_int8<32>& on, const mask_int8<32>& off, const mask_int8<32>& mask)
{
    return mask_int8<32>(i_blend(uint8<32>(on), uint8<32>(off), uint8<32>(mask)));
}
#endif

// -----------------------------------------------------------------------------
// uint16, uint16, uint16

SIMDPP_INL uint16<8> i_blend(const uint16<8>& on, const uint16<8>& off, const uint16<8>& mask)
{
    return uint16<8>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16<16> i_blend(const uint16<16>& on, const uint16<16>& off, const uint16<16>& mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

// -----------------------------------------------------------------------------
// uint16, uint16, mask_int16

SIMDPP_INL uint16<8> i_blend(const uint16<8>& on, const uint16<8>& off, const mask_int16<8>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return uint16<8>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16<16> i_blend(const uint16<16>& on, const uint16<16>& off, const mask_int16<16>& mask)
{
    return i_blend(on, off, uint16<16>(mask));
}
#endif

// -----------------------------------------------------------------------------
// mask_int16, mask_int16, mask_int16

SIMDPP_INL mask_int16<8> i_blend(const mask_int16<8>& on, const mask_int16<8>& off, const mask_int16<8>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int16<8>(i_blend(uint16<8>(on), uint16<8>(off), uint16<8>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int16<16> i_blend(const mask_int16<16>& on, const mask_int16<16>& off, const mask_int16<16>& mask)
{
    return mask_int16<16>(i_blend(uint16<16>(on), uint16<16>(off), uint16<16>(mask)));
}
#endif

// -----------------------------------------------------------------------------
// uint32, uint32, uint32

SIMDPP_INL uint32<4> i_blend(const uint32<4>& on, const uint32<4>& off, const uint32<4>& mask)
{
    return uint32<4>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32<8> i_blend(const uint32<8>& on, const uint32<8>& off, const uint32<8>& mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_blend(const uint32<16>& on, const uint32<16>& off, const uint32<16>& mask)
{
    return _mm512_ternarylogic_epi32(on, off, mask, 0xe4);
}
#endif

// -----------------------------------------------------------------------------
// uint32, uint32, mask_int32

SIMDPP_INL uint32<4> i_blend(const uint32<4>& on, const uint32<4>& off, const mask_int32<4>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return uint32<4>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32<8> i_blend(const uint32<8>& on, const uint32<8>& off, const mask_int32<8>& mask)
{
    return i_blend(on, off, uint32<8>(mask));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_blend(const uint32<16>& on, const uint32<16>& off, const mask_int32<16>& mask)
{
    return _mm512_mask_blend_epi32(mask, off, on);
}
#endif

// -----------------------------------------------------------------------------
// mask_int32, mask_int32, mask_int32

SIMDPP_INL mask_int32<4> i_blend(const mask_int32<4>& on, const mask_int32<4>& off, const mask_int32<4>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int32<4>(i_blend(uint32<4>(on), uint32<4>(off), uint32<4>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int32<8> i_blend(const mask_int32<8>& on, const mask_int32<8>& off, const mask_int32<8>& mask)
{
    return mask_int32<8>(i_blend(uint32<8>(on), uint32<8>(off), uint32<8>(mask)));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int32<16> i_blend(const mask_int32<16>& on, const mask_int32<16>& off, const mask_int32<16>& mask)
{
    return _mm512_kor(_mm512_kand(on, mask), _mm512_kandn(mask, off));
}
#endif

// -----------------------------------------------------------------------------
// float32, float32, float32

SIMDPP_INL float32<4> i_blend(const float32<4>& con, const float32<4>& coff, const float32<4>& mask)
{
    float32<4> on = con, off = coff;
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::blend(on, off, mask);
#elif SIMDPP_USE_AVX
    return _mm_blendv_ps(off, on, mask);
#elif SIMDPP_USE_SSE2
    float32x4 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON
    return vbslq_f32(uint32x4(mask), on, off);
#elif SIMDPP_USE_ALTIVEC
    return vec_sel((__vector float)off, (__vector float)on,
                   (__vector float)mask);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32<8> i_blend(const float32<8>& on, const float32<8>& off, const float32<8>& mask)
{
    return _mm256_blendv_ps(off, on, mask);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_blend(const float32<16>& on, const float32<16>& off, const float32<16>& mask)
{
    // maybe cmp_eq + blend has lower latency?
    return (float32<16>) i_blend(uint32<16>(on), uint32<16>(off), uint32<16>(mask));
}
#endif

// -----------------------------------------------------------------------------
// float32, float32, mask_float32

SIMDPP_INL float32<4> i_blend(const float32<4>& on, const float32<4>& off, const mask_float32<4>& mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, float32<4>(mask));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32<8> i_blend(const float32<8>& on, const float32<8>& off, const mask_float32<8>& mask)
{
    return i_blend(on, off, float32<8>(mask));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_blend(const float32<16>& on, const float32<16>& off, const mask_float32<16>& mask)
{
    return _mm512_mask_blend_ps(mask, off, on);
}
#endif

// -----------------------------------------------------------------------------
// mask_float32, mask_float32, mask_float32

SIMDPP_INL mask_float32<4> i_blend(const mask_float32<4>& on, const mask_float32<4>& off, const mask_float32<4>& mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_float32<4>(i_blend(float32<4>(on), float32<4>(off), float32<4>(mask)));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32<8> i_blend(const mask_float32<8>& on, const mask_float32<8>& off,const mask_float32<8>& mask)
{
    return mask_float32<8>(i_blend(float32<8>(on), float32<8>(off), float32<8>(mask)));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float32<16> i_blend(const mask_float32<16>& on, const mask_float32<16>& off, const mask_float32<16>& mask)
{
    return _mm512_kor(_mm512_kand(on, mask), _mm512_kandn(mask, off));
}
#endif

// -----------------------------------------------------------------------------
// uint64, uint64, uint64

SIMDPP_INL uint64<2> i_blend(const uint64<2>& on, const uint64<2>& off, const uint64<2>& mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::blend(on, off, mask);
#else
    return uint64<2>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<4> i_blend(const uint64<4>& on, const uint64<4>& off, const uint64<4>& mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_blend(const uint64<8>& on, const uint64<8>& off, const uint64<8>& mask)
{
    return _mm512_ternarylogic_epi64(on, off, mask, 0xe4);
}
#endif

// -----------------------------------------------------------------------------
// uint64, uint64, mask_int64

SIMDPP_INL uint64<2> i_blend(const uint64<2>& on, const uint64<2>& off, const mask_int64<2>& mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::blend_mask(on, off, mask);
#else
    return uint64<2>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<4> i_blend(const uint64<4>& on, const uint64<4>& off, const mask_int64<4>& mask)
{
    return i_blend(on, off, uint64<4>(mask));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_blend(const uint64<8>& on, const uint64<8>& off, const mask_int64<8>& mask)
{
    return _mm512_mask_blend_epi64(mask, off, on);
}
#endif

// -----------------------------------------------------------------------------
// mask_int64, mask_int64, mask_int64

SIMDPP_INL mask_int64<2> i_blend(const mask_int64<2>& on, const mask_int64<2>& off, const mask_int64<2>& mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int64<2>(i_blend(uint64<2>(on), uint64<2>(off), uint64<2>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int64<4> i_blend(const mask_int64<4>& on, const mask_int64<4>& off, const mask_int64<4>& mask)
{
    return mask_int64<4>(i_blend(uint64<4>(on), uint64<4>(off), uint64<4>(mask)));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int64<8> i_blend(const mask_int64<8>& on, const mask_int64<8>& off, const mask_int64<8>& mask)
{
    return _mm512_kor(_mm512_kand(on, mask), _mm512_kandn(mask, off));
}
#endif

// -----------------------------------------------------------------------------
// float64, float64, float64

SIMDPP_INL float64<2> i_blend(const float64<2>& con, const float64<2>& coff, const float64<2>& mask)
{
    float64<2> on = con, off = coff;
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::blend(on, off, mask);
#elif SIMDPP_USE_AVX
    return _mm_blendv_pd(off, on, mask);
#elif SIMDPP_USE_SSE2
    float64x2 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON64
    return vbslq_f64(uint64<2>(mask), on, off);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64<4> i_blend(const float64<4>& on, const float64<4>& off, const float64<4>& mask)
{
    return _mm256_blendv_pd(off, on, mask);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_blend(const float64<8>& on, const float64<8>& off, const float64<8>& mask)
{
    return (float64<8>) i_blend(uint64<8>(on), uint64<8>(off), uint64<8>(mask));
}
#endif

// -----------------------------------------------------------------------------
// float64, float64, mask_float64

SIMDPP_INL float64<2> i_blend(const float64<2>& on, const float64<2>& off, const mask_float64<2>& mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, float64<2>(mask));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64<4> i_blend(const float64<4>& on, const float64<4>& off, const mask_float64<4>& mask)
{
    return i_blend(on, off, float64<4>(mask));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_blend(const float64<8>& on, const float64<8>& off, const mask_float64<8>& mask)
{
    return _mm512_mask_blend_pd(mask, off, on);
}
#endif

// -----------------------------------------------------------------------------
// mask_float64, mask_float64, mask_float64

SIMDPP_INL mask_float64<2> i_blend(const mask_float64<2>& on, const mask_float64<2>& off, const mask_float64<2>& mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_float64<2>(i_blend(float64<2>(on), float64<2>(off), float64<2>(mask)));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64<4> i_blend(const mask_float64<4>& on, const mask_float64<4>& off, const mask_float64<4>& mask)
{
    return mask_float64<4>(i_blend(float64<4>(on), float64<4>(off), float64<4>(mask)));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float64<8> i_blend(const mask_float64<8>& on, const mask_float64<8>& off, const mask_float64<8>& mask)
{
    return _mm512_kor(_mm512_kand(on, mask), _mm512_kandn(mask, off));
}
#endif

// -----------------------------------------------------------------------------

template<class V1, class V2, class V3> SIMDPP_INL
V1 i_blend(const V1& on, const V2& off, const V3& mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(V1, i_blend, on, off, mask)
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

