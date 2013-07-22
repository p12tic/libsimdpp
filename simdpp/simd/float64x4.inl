/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT64X4_INL
#define LIBSIMDPP_SIMD_FLOAT64X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline float64x4 float64x4::zero()
{
    float64x4 r;
    r = bit_xor(r, r);
    return r;
}

#if SIMDPP_USE_AVX2
#elif SIMDPP_USE_AVX
inline float64x4::float64x4(basic_int64x4 d)
{
    d_ = float64x4(sse::combine(d[0], d[1]));
}
#endif

inline float64x4 float64x4::load_broadcast(const double* v0)
{
#if SIMDPP_USE_AVX
    return _mm256_broadcast_sd(v0);
#else
    float64x2 a = float64x2::load_broadcast(v0);
    return {a, a};
#endif
}

inline float64x4 float64x4::set_broadcast(double v0)
{
#if SIMDPP_USE_AVX
    return float64x4::load_broadcast(&v0);
#else
    float64x2 a = float64x2::set_broadcast(v0);
    return {a, a};
#endif
}

inline float64x4 float64x4::make_const(double v0)
{
#if SIMDPP_USE_AVX
    return _mm256_set_pd(v0, v0, v0, v0);
#else
    float64x2 a = float64x2::make_const(v0, v0);
    return {a, a};
#endif
}

inline float64x4 float64x4::make_const(double v0, double v1)
{
#if SIMDPP_USE_AVX
    return _mm256_set_pd(v1, v0, v1, v0);
#else
    float64x2 a = float64x2::make_const(v0, v1);
    return {a, a};
#endif
}

inline float64x4 float64x4::make_const(double v0, double v1, double v2, double v3)
{
#if SIMDPP_USE_AVX
    return _mm256_set_pd(v3, v2, v1, v0);
#else
    return {float64x2::make_const(v0, v1),
            float64x2::make_const(v2, v3)};
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
