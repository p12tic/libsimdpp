/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_LT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_LT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/detail/null/compare.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL mask_int8x16 i_cmp_lt(const int8x16& a, const int8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8x32 i_cmp_lt(const int8x32& a, const int8x32& b)
{
    return _mm256_cmpgt_epi8(b, a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int8x16 i_cmp_lt(const uint8x16& ca, const uint8x16& cb)
{
    uint8<16> a = ca, b = cb;
#if SIMDPP_USE_NULL
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comlt_epu8(a, b);
#elif SIMDPP_USE_SSE2
    a = bit_xor(a, 0x80); // sub
    b = bit_xor(b, 0x80); // sub
    return _mm_cmplt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int8x32 i_cmp_lt(const uint8x32& ca, const uint8x32& cb)
{
    uint8<32> a = ca, b = cb;
    a = bit_xor(a, 0x80); // sub
    b = bit_xor(b, 0x80); // sub
    return _mm256_cmpgt_epi8(b, a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int16x8 i_cmp_lt(const int16x8& a, const int16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int16x16 i_cmp_lt(const int16x16& a, const int16x16& b)
{
    return _mm256_cmpgt_epi16(b, a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int16x8 i_cmp_lt(const uint16x8& ca, const uint16x8& cb)
{
    uint16<8> a = ca, b = cb;
#if SIMDPP_USE_NULL
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comlt_epu16(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 bias = make_uint(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmplt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int16x16 i_cmp_lt(const uint16x16& ca, const uint16x16& cb)
{
    uint16<16> a = ca, b = cb;
    a = bit_xor(a, 0x8000); // sub
    b = bit_xor(b, 0x8000); // sub
    return _mm256_cmpgt_epi16(b, a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int32x4 i_cmp_lt(const int32x4& a, const int32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int32x8 i_cmp_lt(const int32x8& a, const int32x8& b)
{
    return _mm256_cmpgt_epi32(b, a);

}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int32<16> i_cmp_lt(const int32<16>& a, const int32<16>& b)
{
    return _mm512_cmpgt_epi32_mask(b, a);

}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int32x4 i_cmp_lt(const uint32x4& ca, const uint32x4& cb)
{
    uint32<4> a = ca, b = cb;
#if SIMDPP_USE_NULL
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comlt_epu32(a, b);
#elif SIMDPP_USE_SSE2
    a = bit_xor(a, 0x80000000); // sub
    b = bit_xor(b, 0x80000000); // sub
    return _mm_cmplt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcltq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int32x8 i_cmp_lt(const uint32x8& ca, const uint32x8& cb)
{
    uint32<8> a = ca, b = cb;
    a = bit_xor(a, 0x80000000); // sub
    b = bit_xor(b, 0x80000000); // sub
    return _mm256_cmpgt_epi32(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int32<16> i_cmp_lt(const uint32<16>& a, const uint32<16>& b)
{
    return _mm512_cmplt_epu32_mask(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int64x2 i_cmp_lt(const int64x2& a, const int64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comlt_epi64(a, b);
#elif SIMDPP_USE_AVX2
    return _mm_cmpgt_epi64(b, a);
#elif SIMDPP_USE_NEON64
    return vcltq_s64(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int64x4 i_cmp_lt(const int64x4& a, const int64x4& b)
{
    return _mm256_cmpgt_epi64(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int64<8> i_cmp_lt(const int64<8>& a, const int64<8>& b)
{
    return _mm512_cmplt_epi64_mask(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_int64x2 i_cmp_lt(const uint64x2& a, const uint64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_XOP && !SIMDPP_WORKAROUND_XOP_COM
    return _mm_comlt_epu64(a, b);
#elif SIMDPP_USE_AVX2
    uint64<2> ca = bit_xor(a, 0x8000000000000000); // sub
    uint64<2> cb = bit_xor(b, 0x8000000000000000); // sub
    return _mm_cmpgt_epi64(cb, ca);
#elif SIMDPP_USE_NEON64
    return vcltq_u64(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL mask_int64x4 i_cmp_lt(const uint64x4& ca, const uint64x4& cb)
{
    uint64<4> a = ca, b = cb;
    a = bit_xor(a, 0x8000000000000000); // sub
    b = bit_xor(b, 0x8000000000000000); // sub
    return _mm256_cmpgt_epi64(b, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_int64<8> i_cmp_lt(const uint64<8>& a, const uint64<8>& b)
{
    return _mm512_cmplt_epu64_mask(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float32x4 i_cmp_lt(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_LT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vcltq_f32(a, b));
#elif SIMDPP_USE_ALTIVEC
    return vec_cmplt((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_cmp_lt(const float32x8& a, const float32x8& b)
{
    return _mm256_cmp_ps(a, b, _CMP_LT_OQ);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float32<16> i_cmp_lt(const float32<16>& a, const float32<16>& b)
{
    return _mm512_cmp_ps_mask(a, b, _CMP_LT_OQ);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float64x2 i_cmp_lt(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_lt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_LT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmplt_pd(a, b);
#elif SIMDPP_USE_NEON64
    return vreinterpretq_f64_u64(vcltq_f64(a, b));
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_cmp_lt(const float64x4& a, const float64x4& b)
{
    return _mm256_cmp_pd(a, b, _CMP_LT_OQ);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float64<8> i_cmp_lt(const float64<8>& a, const float64<8>& b)
{
    return _mm512_cmp_pd_mask(a, b, _CMP_LT_OQ);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
typename V::mask_vector_type i_cmp_lt(const V& a, const V& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(typename V::mask_vector_type, i_cmp_lt, a, b);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

