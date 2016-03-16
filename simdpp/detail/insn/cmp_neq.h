/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_NEQ_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_NEQ_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_not.h>
#include <simdpp/core/cmp_eq.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/detail/null/compare.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL mask_int8x16 i_cmp_neq(const uint8x16& a, const uint8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comneq_epi8(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8x32 i_cmp_neq(const uint8x32& a, const uint8x32& b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int16x8 i_cmp_neq(const uint16x8& a, const uint16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comneq_epi16(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int16x16 i_cmp_neq(const uint16x16& a, const uint16x16& b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int32x4 i_cmp_neq(const uint32x4& a, const uint32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comneq_epi32(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int32x8 i_cmp_neq(const uint32x8& a, const uint32x8& b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int32<16> i_cmp_neq(const uint32<16>& a, const uint32<16>& b)
{
    return _mm512_cmpneq_epu32_mask(a, b);
}

SIMDPP_INL mask_int32<16> i_cmp_neq(const mask_int32<16>& a, const mask_int32<16>& b)
{
    return _mm512_kxor(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int64x2 i_cmp_neq(const uint64x2& a, const uint64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comneq_epi64(a, b);
#elif SIMDPP_USE_SSE4_1 || SIMDPP_USE_NEON
    return bit_not(cmp_eq(a, b));
#elif SIMDPP_USE_SSE2
    uint64x2 r32, r32s;
    r32 = (uint32x4)cmp_eq(uint32x4(a), uint32x4(b));
    // swap the 32-bit halves
    r32s = bit_or(shift_l<32>(r32), shift_r<32>(r32));
    // combine the results. Each 32-bit half is ORed with the neighbouring pair
    r32 = bit_or(r32, r32s);
    return r32;
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int64x4 i_cmp_neq(const uint64x4& a, const uint64x4& b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int64<8> i_cmp_neq(const uint64<8>& a, const uint64<8>& b)
{
    return _mm512_cmpneq_epi64_mask(a, b);
}

SIMDPP_INL mask_int64<8> i_cmp_neq(const mask_int64<8>& a, const mask_int64<8>& b)
{
    return _mm512_kxor(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float32x4 i_cmp_neq(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_ps(a, b);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_cmp_neq(const float32x8& a, const float32x8& b)
{
    return _mm256_cmp_ps(a, b, _CMP_NEQ_UQ);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float32<16> i_cmp_neq(const float32<16>& a, const float32<16>& b)
{
    return _mm512_cmp_ps_mask(a, b, _CMP_NEQ_UQ);
}

SIMDPP_INL mask_float32<16> i_cmp_neq(const mask_float32<16>& a, const mask_float32<16>& b)
{
    return _mm512_kxor(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float64x2 i_cmp_neq(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_pd(a, b);
#elif SIMDPP_USE_NEON64
    return bit_not(cmp_eq(a, b));
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_cmp_neq(const float64x4& a, const float64x4& b)
{
    return _mm256_cmp_pd(a, b, _CMP_NEQ_UQ);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float64<8> i_cmp_neq(const float64<8>& a, const float64<8>& b)
{
    return _mm512_cmp_pd_mask(a, b, _CMP_NEQ_UQ);
}

SIMDPP_INL mask_float64<8> i_cmp_neq(const mask_float64<8>& a, const mask_float64<8>& b)
{
    return _mm512_kxor(a, b);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
typename V::mask_vector_type i_cmp_neq(const V& a, const V& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(typename V::mask_vector_type, i_cmp_neq, a, b);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

