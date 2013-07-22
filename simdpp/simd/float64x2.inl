/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT64X2_INL
#define LIBSIMDPP_SIMD_FLOAT64X2_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>

#if SIMDPP_USE_NEON_VFP_DP
    #include <simdpp/null/set.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline float64x2 float64x2::zero()
{
    float64x2 r;
    r = bit_xor(r, r);
    return r;
}

inline float64x2 float64x2::load_broadcast(const double* v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::make_vec<float64x2>(*v0);
#elif SIMDPP_USE_SSE3
    return _mm_loaddup_pd(v0);
#elif SIMDPP_USE_SSE2
    float64x2 r;
    r = _mm_load_sd(v0);
    r = permute<0,0>(r);
    return r;
#else
    return SIMDPP_NOT_IMPLEMENTED1(v0);
#endif
}

inline float64x2 float64x2::set_broadcast(double v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::make_vec<float64x2>(v0);
#elif SIMDPP_USE_SSE2
    int64x2 r0;
    r0 = _mm_cvtsi64_si128(bit_cast<int64_t>(v0));
    return permute<0,0>(float64x2(r0));
#else
    return SIMDPP_NOT_IMPLEMENTED1(v0);
#endif
}

inline float64x2 float64x2::make_const(double v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::make_vec<float64x2>(v0);
#elif SIMDPP_USE_SSE2
    return _mm_set_pd(v0, v0);
#else
    return SIMDPP_NOT_IMPLEMENTED1(v0);
#endif
}

inline float64x2 float64x2::make_const(double v0, double v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::make_vec<float64x2>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_pd(v1, v0);
#else
    return SIMDPP_NOT_IMPLEMENTED2(v0, v1);
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
