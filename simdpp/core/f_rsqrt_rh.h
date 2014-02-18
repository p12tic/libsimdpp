/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_CORE_F_RSQRT_RH_H
#define LIBSIMDPP_SIMDPP_CORE_F_RSQRT_RH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cmath>
#include <simdpp/types.h>
#include <simdpp/core/f_mul.h>
#include <simdpp/core/f_sub.h>
#include <simdpp/null/foreach.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes one Newton-Rhapson iteration for inverse of square root. @a x is
    the current estimate, @a a are the values to estimate the inverse square
    root for.

    @code
    r0 = x0 * (3 - a0*x0*x0) * 0.5
    ...
    rN = xN * (3 - aN*xN*xN) * 0.5
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, SSE4.1, 5-7}
    @icost{NEON, 3}
    @icost{ALTIVEC, 4-6}

    @par 256-bit version:
    @icost{AVX-AVX2, 7}
    @icost{SSE2, SSE3, SSSE3, SSE4.1, 10-12}
    @icost{NEON, 6}
    @icost{ALTIVEC, 8-10}
*/
inline float32x4 rsqrt_rh(float32x4 x, float32x4 a)
{
    // x_n = x*(3-d*x*x)/2
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(x, a, [](float x, float a){ return x * (3.0f - a*x*x) * 0.5f; });
#elif SIMDPP_USE_SSE2
    float32x4 x2, c3, c0p5, r;

    c3 = float32x4::make_const(3.0f);
    c0p5 = float32x4::make_const(0.5f);

    x2 = mul(x, x);
    r = mul(a, x2);
    r = sub(c3, r);
    x = mul(x, c0p5);
    r = mul(x, r);

    return r;
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 x2, r;

    x2 = mul(x, x);
    r = vrsqrtsq_f32(a, x2);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_ALTIVEC
    float32x4 c3, c0p5, x2, r, xp5;

    c3 = float32x4::make_const(3.0f);
    c0p5 = float32x4::make_const(0.5f);

    x2 = mul(x, x);
    // r = (c3 - a*x2)
    r = vec_nmsub((__vector float)a, (__vector float)x2, (__vector float)c3);
    xp5 = mul(x, c0p5);
    r = mul(xp5, r);

    return r;
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 rsqrt_rh(float32x8 x, float32x8 a)
{
    float32x8 x2, c3, c0p5, r;

    c3 = float32x8::make_const(3.0f);
    c0p5 = float32x8::make_const(0.5f);

    x2 = mul(x, x);
    r = mul(a, x2);
    r = sub(c3, r);
    x = mul(x, c0p5);
    r = mul(x, r);

    return r;
}
#endif

template<unsigned N>
float32<N> rsqrt_rh(float32<N> x, float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, rsqrt_rh, x, a);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

