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

#ifndef LIBSIMDPP_SIMDPP_CORE_F_FLOOR_H
#define LIBSIMDPP_SIMDPP_CORE_F_FLOOR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cmath>
#include <simdpp/types.h>
#include <simdpp/core/f_abs.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/cmp_eq.h>
#include <simdpp/core/cmp_gt.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/core/to_float32.h>
#include <simdpp/core/to_int32.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Rounds the values of a vector towards negative infinity

    @code
    r0 = floor(a0)
    ...
    rN = floor(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 12-14}
    @icost{NEON, 10-11}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 24-26}
    @icost{NEON, 20-21}
    @icost{ALTIVEC, 2}
*/
inline float32x4 floor(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float x){ return std::floor(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_floor_ps(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large, or is zero
    float32x4 ba = abs(a);
    mask_float32x4 large_mask, zero_mask, mask;
    large_mask = cmp_gt(ba, float32x4::make_const(8388607.0f));
    zero_mask = cmp_eq(ba, float32x4::zero());
    mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the floor using trunc
    int32x4 s = shift_r((uint32x4)a, 31); //=1 if a<0
    float32x4 at = (float32x4) sub((int32x4)a, s); //=nextafter towards +inf, if a<0
    int32x4 ia = to_int32(at);
            ia = sub(ia, s);
    float32x4 fa = to_float32(ia);

    //combine the results
    a = blend(a, fa, mask);
    return a;
#elif SIMDPP_USE_ALTIVEC
    return vec_floor((__vector float)a);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 floor(float32x8 a)
{
    return _mm256_floor_ps(a);
}
#endif

template<unsigned N>
float32x8 floor(float32x8 a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float32x8, floor, a);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

