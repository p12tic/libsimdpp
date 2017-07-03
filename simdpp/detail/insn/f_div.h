/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_DIV_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_DIV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/f_rcp_e.h>
#include <simdpp/core/f_rcp_rh.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL float32x4 i_div(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_SSE2
    return _mm_div_ps(a, b);
#elif SIMDPP_USE_NEON64
    return vdivq_f32(a, b);
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b);
    return mul(a, x);
#elif SIMDPP_USE_ALTIVEC
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b); // TODO: check how many approximation steps are needed
    return mul(a, x);
#else
    float32x4 r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = a.el(i) / b.el(i);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_div(const float32x8& a, const float32x8& b)
{
    return _mm256_div_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_div(const float32<16>& a, const float32<16>& b)
{
    return _mm512_div_ps(a, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL float64x2 i_div(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_SSE2
    return _mm_div_pd(a, b);
#elif SIMDPP_USE_NEON64
    return vdivq_f64(a, b);
#else
    float64x2 r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = a.el(i) / b.el(i);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64x4 i_div(const float64x4& a, const float64x4& b)
{
    return _mm256_div_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_div(const float64<8>& a, const float64<8>& b)
{
    return _mm512_div_pd(a, b);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
V i_div(const V& a, const V& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(V, i_div, a, b);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

