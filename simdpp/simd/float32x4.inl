/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT32X4_INL
#define LIBSIMDPP_SIMD_FLOAT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline float32x4 float32x4::zero()
{
    float32x4 r;
    r = bit_xor(r, r);
    return r;
}

inline float32x4 float32x4::load_broadcast(const float* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<float32x4>(*v0);
#elif SIMDPP_USE_SSE2
    float32x4 r;
    r = _mm_load_ss(v0);
    r = permute<0,0,0,0>(r);
    return r;
#elif SIMDPP_USE_NEON
    return vld1q_dup_f32(v0);
#endif
}

inline float32x4 float32x4::set_broadcast(float v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<float32x4>(v0);
#elif SIMDPP_USE_SSE2
    int32x4 r0;
    r0 = _mm_cvtsi32_si128(bit_cast<int>(v0));
    r0 = permute<0,0,0,0>(r0);
    return float32x4(r0);
#elif SIMDPP_USE_NEON
    float32x4 r0 = vsetq_lane_f32(v0, r0, 0);
    r0 = broadcast<0>(r0);
    return r0;
#endif
}

inline float32x4 float32x4::make_const(float v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<float32x4>(v0);
#elif SIMDPP_USE_SSE2
    return _mm_set_ps(v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_f32(&v0);
#endif
}

inline float32x4 float32x4::make_const(float v0, float v1)
{
#if SIMDPP_USE_NULL
    return null::make_vec<float32x4>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_ps(v1, v0, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        float v[2];
    };
    v[0] = v0;
    v[1] = v1;
    float32x2_t r0 = vld1_f32(v);
    return vcombine_f32(r0, r0);
#endif
}

inline float32x4 float32x4::make_const(float v0, float v1, float v2, float v3)
{
#if SIMDPP_USE_NULL
    return null::make_vec<float32x4>(v0, v1, v2, v3);
#elif SIMDPP_USE_SSE2
    return _mm_set_ps(v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        float v[4];
    };
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
    return vld1q_f32(v);
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
