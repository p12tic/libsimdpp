/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_INT32_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_INT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/insert.h>
#include <simdpp/detail/null/foreach.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

inline int32x8 i_to_int32(int16x8 a)
{
#if SIMDPP_USE_NULL
    int32x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i/4].el(i%4) = int32_t(a[0].el(i));
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepi16_epi32(a);
#elif SIMDPP_USE_SSE4_1
    int32x8 r;
    r[0] = _mm_cvtepi16_epi32(a);
    r[1] = _mm_cvtepi16_epi32(move8_l<4>(a).eval());
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 b0, b1, sign;
    sign = shift_r<16>(a);
    b0 = zip8_lo(a, sign);
    b1 = zip8_hi(a, sign);
    return uint32x8(combine(b0, b1));
#elif SIMDPP_USE_NEON
    int32x8 r;
    r[0] = vmovl_s16(vget_low_s16(a[0]));
    r[1] = vmovl_s16(vget_high_s16(a[1]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int32x4 b0, b1;
    b0 = vec_unpackh((__vector int16_t)a[0]);
    b1 = vec_unpackl((__vector int16_t)a[0]);
    return combine(b0, b1);
#endif
}

// TODO support arbitrary length vectors

// -----------------------------------------------------------------------------

inline int32x4 i_to_int32(float32x4 a)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<int32x4>(a, [](float x) { return int32_t(x); });
#elif SIMDPP_USE_SSE2
    return _mm_cvttps_epi32(a);
#elif SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP
    detail::mem_block<float32x4> mf(a);
    detail::mem_block<int32x4> mi;
    mi[0] = int(mf[0]);
    mi[1] = int(mf[1]);
    mi[2] = int(mf[2]);
    mi[3] = int(mf[3]);
    return mi;
#elif SIMDPP_USE_NEON_FLT_SP
    return vcvtq_s32_f32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_cts((__vector float)a, 0);
#endif
}

#if SIMDPP_USE_AVX2
inline uint32x8 i_to_int32(float32x8 a)
{
    return _mm256_cvttps_epi32(a);
}
#endif

template<unsigned N>
uint32<N> i_to_int32(float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, i_to_int32, a);
}

// -----------------------------------------------------------------------------

inline int32x4 i_to_int32(float64x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> r;
    r[0] = int32_t(a[0].el(0));
    r[1] = int32_t(a[0].el(1));
    r[2] = int32_t(a[1].el(0));
    r[3] = int32_t(a[1].el(1));
    return r;
#elif SIMDPP_USE_SSE2
    int32x4 r1, r2;
    float64x2 a1, a2;
    split(a, a1, a2);
    r1 = _mm_cvttpd_epi32(a1);
    r2 = _mm_cvttpd_epi32(a2);
    r2 = move4_l<2>(r2);
    return bit_or(r1, r2);
#else
    SIMDPP_NOT_IMPLEMENTED1(a); return int32x4();
#endif
}

// TODO support arbitrary length vectors


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


