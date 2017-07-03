/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_REDUCE_MUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_REDUCE_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/extract.h>
#include <simdpp/core/f_mul.h>
#include <simdpp/core/permute2.h>
#include <simdpp/detail/extract128.h>
#include <simdpp/detail/workarounds.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL float i_reduce_mul(const float32x4& a)
{
#if SIMDPP_USE_SSE2
    float32x4 b = _mm_movehl_ps(a, a);
    b = mul(a, b);
    b = mul(b, permute2<1,0>(b));
    return _mm_cvtss_f32(b);
#elif SIMDPP_USE_NEON_FLT_SP
    float32x2_t a2 = vmul_f32(vget_low_f32(a), vget_high_f32(a));
    a2 = vmul_f32(a2, vext_f32(a2, a2, 1));
    return vget_lane_f32(a2, 0);
#elif SIMDPP_USE_ALTIVEC
    float32x4 b = a;
    b = mul(b, move4_l<1>(b));
    b = mul(b, move4_l<2>(b));
    return extract<0>(b);
#else
    float r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r *= a.el(i);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float i_reduce_mul(const float32x8& a)
{
    float32x4 ah = detail::extract128<1>(a);
    float32x4 al = detail::extract128<0>(a);
    al = mul(al, ah);
    return i_reduce_mul(al);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float i_reduce_mul(const float32<16>& a)
{
#if SIMDPP_WORKAROUND_AVX512F_NO_REDUCE
    return i_reduce_mul(mul(extract256<0>(a), extract256<1>(a)));
#else
    return _mm512_reduce_mul_ps(a);
#endif
}
#endif

template<unsigned N>
SIMDPP_INL float i_reduce_mul(const float32<N>& a)
{
    float32v r = a.vec(0);
    for (unsigned i = 1; i < a.vec_length; ++i)
        r = mul(r, a.vec(i));
    return i_reduce_mul(r);
}

// -----------------------------------------------------------------------------

SIMDPP_INL double i_reduce_mul(const float64x2& a)
{
#if SIMDPP_USE_SSE2
    float64x2 b = mul(a, permute2<1,0>(a));
    return _mm_cvtsd_f64(b);
#elif SIMDPP_USE_NEON64
    float64x1_t a2 = vmul_f64(vget_low_f64(a), vget_high_f64(a));
    return vget_lane_f64(a2, 0);
#else
    double r = a.el(0);
    for (unsigned i = 1; i < a.length; i++) {
        r *= a.el(i);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL double i_reduce_mul(const float64x4& a)
{
    float64x2 ah = detail::extract128<1>(a);
    float64x2 al = detail::extract128<0>(a);
    al = mul(al, ah);
    return i_reduce_mul(al);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL double i_reduce_mul(const float64<8>& a)
{
#if SIMDPP_WORKAROUND_AVX512F_NO_REDUCE
    return i_reduce_mul(mul(extract256<0>(a), extract256<1>(a)));
#else
    return _mm512_reduce_mul_pd(a);
#endif
}
#endif

template<unsigned N>
SIMDPP_INL double i_reduce_mul(const float64<N>& a)
{
    float64v r = a.vec(0);
    for (unsigned i = 1; i < a.vec_length; ++i)
        r = mul(r, a.vec(i));
    return i_reduce_mul(r);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

