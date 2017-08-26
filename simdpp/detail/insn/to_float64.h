/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_FLOAT64_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/combine.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/detail/subvec_insert.h>
#include <simdpp/detail/extract128.h>
#include <simdpp/detail/mem_block.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL float64x4 i_to_float64(const int32x4& a)
{
#if SIMDPP_USE_AVX
    return _mm256_cvtepi32_pd(a);
#elif SIMDPP_USE_SSE2
    float64x2 r1, r2;
    r1 = _mm_cvtepi32_pd(a);
    r2 = _mm_cvtepi32_pd(move4_l<2>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_NEON64
    float64<2> r1, r2;
    r1 = vcvtq_f64_s64(vmovl_s32(vget_low_s32(a)));
    r2 = vcvtq_f64_s64(vmovl_s32(vget_high_s32(a)));
    return combine(r1, r2);
#elif SIMDPP_USE_VSX_206
    int32x4 sign, lo, hi;
    sign = shift_r(a, 31);
#if UNITY_BIG_ENDIAN
    lo = zip4_lo(sign, a);
    hi = zip4_hi(sign, a);
#else
    lo = zip4_lo(a, sign);
    hi = zip4_hi(a, sign);
#endif

    float64x2 f_lo, f_hi;
    f_lo = vec_ctf((__vector int64_t)(__vector int32_t) lo, 0);
    f_hi = vec_ctf((__vector int64_t)(__vector int32_t) hi, 0);
    return combine(f_lo, f_hi);
#elif SIMDPP_USE_MSA
    int64x4 a64 = to_int64(a);
    float64x4 r;
    r.vec(0) = __msa_ffint_s_d(a64.vec(0));
    r.vec(1) = __msa_ffint_s_d(a64.vec(1));
    return r;
#elif SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> ax(a);
    float64x4 r;
    r.vec(0).el(0) = double(ax[0]);
    r.vec(0).el(1) = double(ax[1]);
    r.vec(1).el(0) = double(ax[2]);
    r.vec(1).el(1) = double(ax[3]);
    return r;
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL float64<8> i_to_float64(const int32x8& a)
{
#if SIMDPP_USE_AVX512F
    return _mm512_cvtepi32_pd(a);
#else
    float64x4 r1, r2;
    int32x4 a1, a2;
    split(a, a1, a2);
    r1 = _mm256_cvtepi32_pd(a1);
    r2 = _mm256_cvtepi32_pd(a2);
    return combine(r1, r2);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<16> i_to_float64(const int32<16>& a)
{
    float64<8> r1, r2;
    r1 = _mm512_cvtepi32_pd(_mm512_castsi512_si256(a));
    r2 = _mm512_cvtepi32_pd(_mm512_extracti64x4_epi64(a, 1));
    return combine(r1, r2);
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_to_float64(const int32<N>& a)
{
    float64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
    }
    return r;
}

// -----------------------------------------------------------------------------

SIMDPP_INL float64x4 i_to_float64(const float32x4& a)
{
#if SIMDPP_USE_AVX
    return _mm256_cvtps_pd(a);
#elif SIMDPP_USE_SSE2
    float64x2 r1, r2;
    r1 = _mm_cvtps_pd(a);
    r2 = _mm_cvtps_pd(move4_l<2>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_NEON64
    float64<2> r1, r2;
    r1 = vcvt_f64_f32(vget_low_f32(a));
    r2 = vcvt_high_f64_f32(a);
    return combine(r1, r2);
#elif SIMDPP_USE_VSX_206
    float32<4> lo, hi;
    lo = zip4_lo(a, (float32<4>) make_zero());
    hi = zip4_hi(a, (float32<4>) make_zero());
    float64<2> lo_f, hi_f;
    lo_f = __builtin_vsx_xvcvspdp((__vector float) lo);
    hi_f = __builtin_vsx_xvcvspdp((__vector float) hi);
    return combine(lo_f, hi_f);
#elif SIMDPP_USE_MSA
    float64<2> lo, hi;
    lo = __msa_fexupl_d(a);
    hi = __msa_fexupr_d(a);
    return combine(lo, hi);
#elif SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> ax(a);
    float64x4 r;
    r.vec(0).el(0) = double(ax[0]);
    r.vec(0).el(1) = double(ax[1]);
    r.vec(1).el(0) = double(ax[2]);
    r.vec(1).el(1) = double(ax[3]);
    return r;
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64<8> i_to_float64(const float32x8& a)
{
#if SIMDPP_USE_AVX512F
    return _mm512_cvtps_pd(a);
#else
    float64x4 r1, r2;
    float32x4 a1, a2;
    split(a, a1, a2);
    r1 = _mm256_cvtps_pd(a1);
    r2 = _mm256_cvtps_pd(a2);
    return combine(r1, r2);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<16> i_to_float64(const float32<16>& a)
{
    float64<8> r1, r2;
    float32<8> a1, a2;
    split(a, a1, a2);
    r1 = _mm512_cvtps_pd(a1);
    r2 = _mm512_cvtps_pd(a2);
    return combine(r1, r2);
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_to_float64(const float32<N>& a)
{
    float64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::subvec_insert(r, i_to_float64(a.vec(i)), i);
    }
    return r;
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif


