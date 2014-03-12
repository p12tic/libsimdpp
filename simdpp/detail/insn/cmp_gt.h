/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_GT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_GT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/make_uint.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/null/compare.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline mask_int8x16 i_cmp_gt(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8x32 i_cmp_gt(int8x32 a, int8x32 b)
{
    return _mm256_cmpgt_epi8(a, b);
}
#endif

template<unsigned N>
mask_int8<N> i_cmp_gt(int8<N> a, int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int8x16 i_cmp_gt(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comgt_epu8(a, b);
#elif SIMDPP_USE_SSE2
    uint8x16 bias = make_uint(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8x32 i_cmp_gt(uint8x32 a, uint8x32 b)
{
    uint8x32 bias = make_uint(0x80);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi8(a, b);
}
#endif

template<unsigned N>
mask_int8<N> i_cmp_gt(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int16x8 i_cmp_gt(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int16x16 i_cmp_gt(int16x16 a, int16x16 b)
{
    return _mm256_cmpgt_epi16(a, b);
}
#endif

template<unsigned N>
mask_int16<N> i_cmp_gt(int16<N> a, int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int16x8 i_cmp_gt(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comgt_epu16(a, b);
#elif SIMDPP_USE_SSE2
    uint16x8 bias = make_uint(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int16x16 i_cmp_gt(uint16x16 a, uint16x16 b)
{
    uint16x16 bias = make_uint(0x8000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi16(a, b);
}
#endif

template<unsigned N>
mask_int16<N> i_cmp_gt(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int32x4 i_cmp_gt(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int32x8 i_cmp_gt(int32x8 a, int32x8 b)
{
    return _mm256_cmpgt_epi32(a, b);
}
#endif

template<unsigned N>
mask_int32<N> i_cmp_gt(int32<N> a, int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int32x4 i_cmp_gt(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comgt_epu32(a, b);
#elif SIMDPP_USE_SSE2
    uint32x4 bias = make_uint(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm_cmpgt_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int32x8 i_cmp_gt(uint32x8 a, uint32x8 b)
{
    uint32x8 bias = make_uint(0x80000000);
    a = bit_xor(a, bias); // sub
    b = bit_xor(b, bias); // sub
    return _mm256_cmpgt_epi32(a, b);
}
#endif

template<unsigned N>
mask_int32<N> i_cmp_gt(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float32x4 i_cmp_gt(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_GT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_ps(a, b);
#elif SIMDPP_USE_NEON
    return vcgtq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpgt((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32x8 i_cmp_gt(float32x8 a, float32x8 b)
{
    return _mm256_cmp_ps(a, b, _CMP_GT_OQ);
}
#endif

template<unsigned N>
mask_float32<N> i_cmp_gt(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_cmp_gt, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float64x2 i_cmp_gt(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_gt(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_GT_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpgt_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64x4 i_cmp_gt(float64x4 a, float64x4 b)
{
    return _mm256_cmp_pd(a, b, _CMP_GT_OQ);
}
#endif

template<unsigned N>
mask_float64<N> i_cmp_gt(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_cmp_gt, a, b);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

