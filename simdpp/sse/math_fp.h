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

#ifndef LIBSIMDPP_SSE_MATH_FP_H
#define LIBSIMDPP_SSE_MATH_FP_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/sse/convert.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace sse {


/** Adds the values in adjacent pairs of two float32x4 vectors

    @code
    r0 = a0 + a1
    r1 = a2 + a3
    r2 = b0 + b1
    r3 = b2 + b3
    @endcode
    @unimp{SSE2}
*/
inline float32x4 hadd2(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_SSE3
    return _mm_hadd_ps(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Adds the values in adjacent pairs of two float64x2 vectors

    @code
    r0 = a0 + a1
    r1 = b0 + b1
    @endcode
    @unimp{SSE2}
*/
inline float64x2 hadd2(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_SSE3
    return _mm_hadd_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Sums the values of a float32x4 vector

    @code
    r0 = a0 + a1 + a2 + a3
    r1 = 0.0f
    r2 = 0.0f
    r3 = 0.0f
    @endcode
    @unimp{SSE2}
*/
inline float32x4 hadd4(float32x4 a)
{
#if SIMDPP_USE_SSE3
    a = hadd2(a, float32x4::zero());
    a = hadd2(a, float32x4::zero());
    return a;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

/** Sums the values within each of four float32x4 vector

    @code
    r0 = a0 + a1 + a2 + a3
    r1 = b0 + b1 + b2 + b3
    r2 = c0 + c1 + c2 + c3
    r3 = d0 + d1 + d2 + d3
    @endcode
    @icost{SSE3, SSSE3, SSE4.1, 3}
    @unimp{SSE2}
*/
inline float32x4 hadd4(float32x4 a, float32x4 b, float32x4 c, float32x4 d)
{
#if SIMDPP_USE_SSE3
    a = hadd2(a, b);
    c = hadd2(c, d);
    a = hadd2(a, c);
    return a;
#else
    return SIMDPP_NOT_IMPLEMENTED4(a, b, c, d);
#endif
}

/** Subtracts the values in adjacent pairs of two float32x4 vectors

    @code
    r0 = a0 - a1
    r1 = a2 - a3
    r2 = b0 - b1
    r3 = b2 - b3
    @endcode
    @unimp{SSE2}
*/
inline float32x4 hsub2(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_SSE3
    return _mm_hsub_ps(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Subtracts the values in adjacent pairs of two float64x2 vectors

    @code
    r0 = a0 - a1
    r1 = b0 - b1
    @endcode
    @unimp{SSE2}
*/
inline float64x2 hsub2(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_SSE3
    return _mm_hsub_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Adds or substracts the values of two float32x4 vectors

    @code
    r0 = a0 - b0
    r1 = a1 + b1
    r2 = a2 - b2
    r3 = a3 + b3
    @endcode
    @unimp{SSE2}
*/
inline float32x4 sub_add(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_SSE3
    return _mm_addsub_ps(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Adds or subtracts the values of two float64x2 vectors

    @code
    r0 = a0 - b0
    r1 = a1 + b1
    @endcode
    @unimp{SSE2}
*/
inline float64x2 sub_add(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_SSE3
    return _mm_addsub_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

#if 0
/** Rounds the values of a float64x2 vector towards negative infinity

    @code
    r0 = floor(a0)
    r1 = floor(a1)
    @endcode
    @icost{SSE2, SSE3, SSSE3, 20}
*/
inline float64x2 floor(float64x2 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<float64x2>(a, [](double x){ return std::floor(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_floor_pd(a);
#elif SIMDPP_USE_SSE2
    //check if the value is not too large, or is zero
    float64x2 ba = abs(a);
    int128 large_mask = cmp_gt(ba, float64x2::make_const(4503599627370495.0));
    int128 zero_mask = cmp_eq(ba, float64x2::zero());
    int128 mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the floor using trunc
    int64x2 s = shift_r((uint64x2)a, 63); //=1 if a<0
    float64x2 at = (float64x2) sub((int64x2)a, s); //=nextafter towards +inf if a<0
    int64x2 ia = to_int64x2(at);
            ia = sub(ia, s);
    float64x2 fa = to_float64x2(ia);

    //combine the results
    a = blend(a, fa, mask);
    return a;
#endif
}

/** Rounds the values of a float64x2 vector towards positive infinity

    @code
    r0 = ceil(a0)
    r1 = ceil(a1)
    @endcode
    @icost{SSE2, SSE3, SSSE3, 21}
*/
inline float64x2 ceil(float64x2 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<float64x2>(a, [](float x){ return std::ceil(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_ceil_pd(a);
#elif SIMDPP_USE_SSE2
    //check if the value is not too large, or is zero
    float64x2 ba = abs(a);
    int128 large_mask = cmp_gt(ba, float64x2::make_const(4503599627370495.0));
    int128 zero_mask = cmp_eq(ba, float64x2::zero());
    int128 mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the ceil using trunc
    int64x2 s = shift_r((uint64x2)a, 63);
            s = bit_xor(s, int64x2::make_const(0x0000000000000001)); //=1 if a>0
    float64x2 at = (float64x2) sub((int64x2)a, s); //=nextafter towards -inf if a>0
    int64x2 ia = to_int64x2(at);
            ia = add(ia, s);
    float64x2 fa = to_float64x2(ia);

    //combine the results
    a = blend(a, fa, mask);
    return a;
#endif
}

/** Rounds the values of a float64x2 vector towards zero

    @code
    r0 = floor(a0)
    r1 = floor(a1)
    @endcode
    @icost{SSE2, SSE3, SSSE3, 10}
    @icost{SSE4_1, 5}
*/
inline float64x2 trunc(float64x2 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<float64x2>(a, [](double x){ return std::trunc(x); });
#elif SIMDPP_USE_SSE4_1
    //use floor to implement trunc
    float64x2 s = sign(a);
    float64x2 af = abs(a);
    af = floor(af);
    af = bit_or(af, s);
    return af;
#elif SIMDPP_USE_SSE2
    //check if the value is not too large
    float64x2 af = abs(a);
    int128 mask = cmp_gt(af, float64x2::make_const(4503599627370495.0));

    //truncate
    int64x2 ia = sse::to_int64x2(a);
    float64x2 fa = sse::to_float64x2(ia);

    //combine the results
    a = blend(a, fa, mask); // takes care of nans
    return a;
#endif
}

#endif
} // namespace sse
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
