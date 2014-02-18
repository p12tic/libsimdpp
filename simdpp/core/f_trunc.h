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

#ifndef LIBSIMDPP_SIMDPP_CORE_F_TRUNC_H
#define LIBSIMDPP_SIMDPP_CORE_F_TRUNC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cmath>
#include <simdpp/types.h>
#include <simdpp/core/f_ceil.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Rounds the values of a vector towards zero
    @code
    r0 = trunc(a0)
    ...
    rN = trunc(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, 7-9}
    @icost{NEON, 5-6}

    @par 256-bit version:
    @icost{SSE2, SSE3, SSSE3, 14-16}
    @icost{NEON, 10-11}
    @icost{SSE4.1, ALTIVEC, 2}
*/
inline float32x4 trunc(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float x){ return std::trunc(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_round_ps(a, 3); // 3 = truncate
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large
    float32x4 af = abs(a);
    mask_float32x4 mask = cmp_gt(af, float32x4::make_const(8388607.0f));

    //truncate
    int32x4 ia = to_int32x4(a);
    float32x4 fa = to_float32x4(ia);

    //combine the results
    a = blend(a, fa, mask);     // takes care of NaNs
    return a;
#elif SIMDPP_USE_ALTIVEC
    return vec_trunc((__vector float)a);
#endif
}

inline float32x8 trunc(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_round_ps(a, 3); // 3 = truncate
#else
    SIMDPP_VEC_ARRAY_IMPL1(float32x8, trunc, a);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

