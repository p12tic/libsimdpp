/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_FLOAT32X4_INL
#define LIBSIMDPP_SIMD_FLOAT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

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
#elif SIMDPP_USE_AVX
    return _mm_broadcast_ss(v0);
#elif SIMDPP_USE_SSE2
    float32x4 r;
    r = _mm_load_ss(v0);
    r = permute<0,0,0,0>(r);
    return r;
#elif SIMDPP_USE_NEON
    return vld1q_dup_f32(v0);
#elif SIMDPP_USE_ALTIVEC
    float32x4 r = altivec::load1_u(r, v0);
    r = broadcast_w<0>(r);
    return r;
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
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
#endif
    // Yes, we know what we're doing here. The unused elements within the
    // vector are overwritten by broadcast
    float32x4 r0 = vsetq_lane_f32(v0, r0, 0);
    r0 = broadcast_w<0>(r0);
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    return r0;
#elif SIMDPP_USE_ALTIVEC
    union {
        float v[4];
        float32x4 align;
    };
    v[0] = v0;
    float32x4 r = altivec::load1(r, v);
    r = broadcast_w<0>(r);
    return r;
#endif
}

inline float32x4 float32x4::make_const(float v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return float32x4::make_const(v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_f32(&v0);
#endif
}

inline float32x4 float32x4::make_const(float v0, float v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return float32x4::make_const(v0, v1, v0, v1);
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
#elif SIMDPP_USE_ALTIVEC
    return (__vector float){v0, v1, v2, v3};
#endif
}

inline mask_float32x4::operator float32x4() const
{
#if SIMDPP_USE_NULL
    return null::convert_mask<float32x4>(*this);
#else
    return d_;
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
