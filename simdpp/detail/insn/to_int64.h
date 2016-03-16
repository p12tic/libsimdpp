/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_INT64_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_INT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/combine.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL int64x4 i_to_int64(const int32x4& a)
{
#if SIMDPP_USE_NULL
    int64x4 r;
    r.vec(0).el(0) = int64_t(a.el(0));
    r.vec(0).el(1) = int64_t(a.el(1));
    r.vec(1).el(0) = int64_t(a.el(2));
    r.vec(1).el(1) = int64_t(a.el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepi32_epi64(a);
#elif SIMDPP_USE_SSE4_1
    uint64x2 r1, r2;
    r1 = _mm_cvtepi32_epi64(a);
    r2 = _mm_cvtepi32_epi64(move4_l<2>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2
    int32x4 u;
    u = shift_r(a, 31);
    return (uint64x4) combine(zip4_lo(a, u), zip4_hi(a, u));
#elif SIMDPP_USE_NEON
    int64x2 r1, r2;
    r1 = vmovl_s32(vget_low_s32(a));
    r2 = vmovl_s32(vget_high_s32(a));
    return combine(r1, r2);
#elif SIMDPP_USE_ALTIVEC
    int64x4 r;
    mem_block<int32x4> b = a;
    r.vec(0).el(0) = b[0];
    r.vec(0).el(1) = b[1];
    r.vec(1).el(0) = b[2];
    r.vec(1).el(1) = b[3];
    return r;
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int64<8> i_to_int64(const int32<8>& a)
{
    int32<4> a1, a2;
    int64<4> r1, r2;
    split(a, a1, a2);
    r1 = _mm256_cvtepi32_epi64(a1);
    r2 = _mm256_cvtepi32_epi64(a2);
    return combine(r1, r2);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL int64<16> i_to_int64(const int32<16>& a)
{
    int32<8> a1, a2;
    int64<8> r1, r2;
    split(a, a1, a2);
    r1 = _mm512_cvtepi32_epi64(a1);
    r2 = _mm512_cvtepi32_epi64(a2);
    return combine(r1, r2);
}
#endif

template<unsigned N> SIMDPP_INL
int64<N> i_to_int64(const int32<N>& a)
{
    int64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, i_to_int64(a.vec(i)), i);
    }
    return r;
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint64x4 i_to_uint64(const uint32x4& a)
{
#if SIMDPP_USE_NULL
    uint64x4 r;
    r.vec(0).el(0) = uint64_t(a.el(0));
    r.vec(0).el(1) = uint64_t(a.el(1));
    r.vec(1).el(0) = uint64_t(a.el(2));
    r.vec(1).el(1) = uint64_t(a.el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepu32_epi64(a);
#elif SIMDPP_USE_SSE4_1
    uint64x2 r1, r2;
    r1 = _mm_cvtepu32_epi64(a);
    r2 = _mm_cvtepu32_epi64(move4_l<2>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2
    return (uint64x4) combine(zip4_lo(a, (uint32x4) make_zero()),
                              zip4_hi(a, (uint32x4) make_zero()));
#elif SIMDPP_USE_NEON
    uint64x2 r1, r2;
    r1 = vmovl_u32(vget_low_u32(a));
    r2 = vmovl_u32(vget_high_u32(a));
    return combine(r1, r2);
#elif SIMDPP_USE_ALTIVEC
    uint64x4 r;
    mem_block<uint32x4> b = a;
    r.vec(0).el(0) = b[0];
    r.vec(0).el(1) = b[1];
    r.vec(1).el(0) = b[2];
    r.vec(1).el(1) = b[3];
    return r;
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64<8> i_to_uint64(const uint32<8>& a)
{
    uint32<4> a1, a2;
    uint64<4> r1, r2;
    split(a, a1, a2);
    r1 = _mm256_cvtepu32_epi64(a1);
    r2 = _mm256_cvtepu32_epi64(a2);
    return combine(r1, r2);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<16> i_to_uint64(const uint32<16>& a)
{
    uint32<8> a1, a2;
    uint64<8> r1, r2;
    split(a, a1, a2);
    r1 = _mm512_cvtepu32_epi64(a1);
    r2 = _mm512_cvtepu32_epi64(a2);
    return combine(r1, r2);
}
#endif

template<unsigned N> SIMDPP_INL
uint64<N> i_to_uint64(const uint32<N>& a)
{
    uint64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, i_to_uint64(a.vec(i)), i);
    }
    return r;
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif


