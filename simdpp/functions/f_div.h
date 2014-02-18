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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_F_DIV_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_F_DIV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/functions/f_rcp_e.h>
#include <simdpp/functions/f_rcp_rh.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Divides the values of two vectors.

    @code
    r0 = a0 / b0
    ...
    rN = aN / bN
    @endcode

    @icost{NEON, 6}
    @icost{ALTIVEC, 10}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 12}
    @icost{ALTIVEC, 19}
*/
inline float32x4 div(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, b, [](float a, float b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_ps(a, b);
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
#endif
}

inline float32x8 div(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_div_ps(a, b);
#else
    return {div(a[0], b[0]), div(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Divides the values of two vectors

    @code
    r0 = a0 / b0
    ...
    rN = aN / bN
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 div(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::foreach<float64x2>(a, b, [](double a, double b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_pd(a, b);
#endif
}

inline float64x4 div(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_div_pd(a, b);
#else
    return {div(a[0], b[0]), div(a[1], b[1])};
#endif
}
/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

