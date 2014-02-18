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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_RCP_RH_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_RCP_RH_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/f_sub.h>
#include <simdpp/core/f_mul.h>
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    #include <cmath>
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float32x4 i_rcp_rh(float32x4 x, float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(x, a, [](float x, float a){ return x*(2.0f - x*a); });
#elif SIMDPP_USE_SSE2
    float32x4 c2, r;
    c2 = float32x4::make_const(2.0f);

    r = mul(a, x);
    r = sub(c2, r);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 r;
    r = vrecpsq_f32(a, x);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_ALTIVEC
    float32x4 r, c2;
    c2 = float32x4::make_const(2.0f);
    // -(x*a-c2)
    r = vec_nmsub((__vector float)x, (__vector float)a, (__vector float)c2);
    x = mul(x, r);
    return x;
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_rcp_rh(float32x8 x, float32x8 a)
{
    float32x8 c2, r;
    c2 = float32x8::make_const(2.0f);

    r = mul(a, x);
    r = sub(c2, r);
    x = mul(x, r);

    return x;
}
#endif

template<unsigned N>
float32<N> i_rcp_rh(float32<N> x, float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_rcp_rh, x, a);
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

