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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_MAX_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_MAX_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/cmp_gt.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline int8x16 i_max(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epi8(a, b);
#elif SIMDPP_USE_SSE2
    mask_int8x16 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int8x32 i_max(int8x32 a, int8x32 b)
{
    return _mm256_max_epi8(a, b);
}
#endif

template<unsigned N>
int8<N> i_max(int8<N> a, int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

inline uint8x16 i_max(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 i_max(uint8x32 a, uint8x32 b)
{
    return _mm256_max_epu8(a, b);
}
#endif

template<unsigned N>
uint8<N> i_max(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

inline int16x8 i_max(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int16x16 i_max(int16x16 a, int16x16 b)
{
    return _mm256_max_epi16(a, b);
}
#endif

template<unsigned N>
int16<N> i_max(int16<N> a, int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

inline uint16x8 i_max(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epu16(a, b);
#elif SIMDPP_USE_SSE2
    mask_int16x8 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint16x16 i_max(uint16x16 a, uint16x16 b)
{
    return _mm256_max_epu16(a, b);
}
#endif

template<unsigned N>
uint16<N> i_max(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

inline int32x4 i_max(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epi32(a, b);
#elif SIMDPP_USE_SSE2
    mask_int32x4 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int32x8 i_max(int32x8 a, int32x8 b)
{
    return _mm256_max_epi32(a, b);
}
#endif

template<unsigned N>
int32<N> i_max(int32<N> a, int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int32<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

inline uint32x4 i_max(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_max_epu32(a, b);
#elif SIMDPP_USE_SSE2
    mask_int32x4 mask = cmp_gt(a, b);
    return blend(a, b, mask);
#elif SIMDPP_USE_NEON
    return vmaxq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint32x8 i_max(uint32x8 a, uint32x8 b)
{
    return _mm256_max_epu32(a, b);
}
#endif

template<unsigned N>
uint32<N> i_max(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_max, a, b);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

