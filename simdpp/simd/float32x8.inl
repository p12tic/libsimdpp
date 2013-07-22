/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT32X8_INL
#define LIBSIMDPP_SIMD_FLOAT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline float32x8 float32x8::zero()
{
    float32x8 r;
    r = bit_xor(r, r);
    return r;
}

inline float32x8 float32x8::load_broadcast(const float* v0)
{
#if SIMDPP_USE_AVX
    return _mm256_broadcast_ss(v0);
#else
    float32x4 a = float32x4::load_broadcast(v0);
    return {a, a};
#endif
}

inline float32x8 float32x8::set_broadcast(float v0)
{
#if SIMDPP_USE_AVX
    return _mm256_broadcast_ss(&v0);
#else
    float32x4 a = float32x4::set_broadcast(v0);
    return {a, a};
#endif
}

inline float32x8 float32x8::make_const(float v0)
{
#if SIMDPP_USE_AVX
    return _mm256_set_ps(v0, v0, v0, v0, v0, v0, v0, v0);
#else
    float32x4 a = float32x4::make_const(v0);
    return {a, a};
#endif
}

inline float32x8 float32x8::make_const(float v0, float v1)
{
#if SIMDPP_USE_AVX
    return _mm256_set_ps(v1, v0, v1, v0, v1, v0, v1, v0);
#else
    float32x4 a = float32x4::make_const(v0, v1);
    return {a, a};
#endif
}

inline float32x8 float32x8::make_const(float v0, float v1, float v2, float v3)
{
#if SIMDPP_USE_AVX
    return _mm256_set_ps(v3, v2, v1, v0, v3, v2, v1, v0);
#else
    float32x4 a = float32x4::make_const(v0, v1, v2, v3);
    return {a, a};
#endif
}

inline float32x8 float32x8::make_const(float v0, float v1, float v2, float v3,
                                       float v4, float v5, float v6, float v7)
{
#if SIMDPP_USE_AVX
    return _mm256_set_ps(v7, v6, v5, v4, v3, v2, v1, v0);
#else
    return {float32x4::make_const(v0, v1, v2, v3),
            float32x4::make_const(v4, v5, v6, v7)};
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
