/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_FLOAT32X8_INL
#define LIBSIMDPP_SIMD_FLOAT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

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
    return float32x8::make_const(v0, v0, v0, v0, v0, v0, v0, v0);
}

inline float32x8 float32x8::make_const(float v0, float v1)
{
    return float32x8::make_const(v0, v1, v0, v1, v0, v1, v0, v1);
}

inline float32x8 float32x8::make_const(float v0, float v1, float v2, float v3)
{
    return float32x8::make_const(v0, v1, v2, v3, v0, v1, v2, v3);
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

inline mask_float32x8::operator float32x8() const
{
#if SIMDPP_USE_AVX
    return d_;
#else
    return float32x8(m_[0], m_[1]);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
