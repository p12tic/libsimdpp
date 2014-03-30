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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_NEQ_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_NEQ_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_not.h>
#include <simdpp/core/cmp_eq.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/null/compare.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline mask_int8x16 i_cmp_neq(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi8(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8x32 i_cmp_neq(uint8x32 a, uint8x32 b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

template<unsigned N>
mask_int8<N> i_cmp_neq(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, i_cmp_neq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int16x8 i_cmp_neq(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi16(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int16x16 i_cmp_neq(uint16x16 a, uint16x16 b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

template<unsigned N>
mask_int16<N> i_cmp_neq(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, i_cmp_neq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int32x4 i_cmp_neq(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi32(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int32x8 i_cmp_neq(uint32x8 a, uint32x8 b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

template<unsigned N>
mask_int32<N> i_cmp_neq(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, i_cmp_neq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_int64x2 i_cmp_neq(uint64x2 a, uint64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
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
#elif SIMDPP_USE_ALTIVEC
    uint16x8 mask = make_shuffle_bytes16_mask<0, 2, 1, 3>(mask);
    uint32x4 a0, b0, r, ones;
    ones = uint32x4::ones();

    a0 = a;  b0 = b;
    r = cmp_eq(a, b);
    r = permute_bytes16(uint16x8(a), mask);
    r = cmp_eq(r, ones);
    return r;
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int64x4 i_cmp_neq(uint64x4 a, uint64x4 b)
{
    return bit_not(cmp_eq(a, b));
}
#endif

template<unsigned N>
mask_int64<N> i_cmp_neq(uint64<N> a, uint64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int64<N>, i_cmp_neq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float32x4 i_cmp_neq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_ps(a, b);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return bit_not(cmp_eq(a, b));
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32x8 i_cmp_neq(float32x8 a, float32x8 b)
{
    return _mm256_cmp_ps(a, b, _CMP_NEQ_UQ);
}
#endif

template<unsigned N>
mask_float32<N> i_cmp_neq(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_cmp_neq, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float64x2 i_cmp_neq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64x4 i_cmp_neq(float64x4 a, float64x4 b)
{
    return _mm256_cmp_pd(a, b, _CMP_NEQ_UQ);
}
#endif

template<unsigned N>
mask_float64<N> i_cmp_neq(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_cmp_neq, a, b);
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

