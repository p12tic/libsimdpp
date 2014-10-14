/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_MATH_FP_H
#define LIBSIMDPP_SSE_MATH_FP_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/sse/convert.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
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
SIMDPP_INL float32x4 hadd2(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_SSE3
    return _mm_hadd_ps(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Adds the values in adjacent pairs of two float32x8 vectors

    @code
    r0 = a0 + a1
    r1 = a2 + a3
    r2 = b0 + b1
    r3 = b2 + b3
    r4 = a4 + a5
    r5 = a6 + a7
    r6 = b4 + b5
    r7 = b6 + b7    
    @endcode
    @unimp{SSE2,SSE3}
*/
SIMDPP_INL float32x8 hadd2(const float32x8& a, const float32x8& b)
{
#if SIMDPP_USE_AVX
    return _mm256_hadd_ps(a, b);
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
SIMDPP_INL float64x2 hadd2(const float64x2& a, const float64x2& b)
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
SIMDPP_INL float32x4 hadd4(const float32x4& ca)
{
    float32<4> a = ca;
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
SIMDPP_INL float32x4 hadd4(const float32x4& a, const float32x4& b, const float32x4& c, const float32x4& d)
{
#if SIMDPP_USE_SSE3
    float32<4> ab, cd;
    ab = hadd2(a, b);
    cd = hadd2(c, d);
    return hadd2(ab, cd);
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
SIMDPP_INL float32x4 hsub2(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_SSE3
    return _mm_hsub_ps(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

/** Subtracts the values in adjacent pairs of two float32x8 vectors

    @code
    r0 = a0 - a1
    r1 = a2 - a3
    r2 = b0 - b1
    r3 = b2 - b3
    r4 = a4 - a5
    r5 = a6 - a7
    r6 = b4 - b5
    r7 = b6 - b7
    @endcode
    @unimp{SSE2,SSE3}
*/
SIMDPP_INL float32x8 hsub2(const float32x8& a, const float32x8& b)
{
#if SIMDPP_USE_AVX
    return _mm256_hsub_ps(a, b);
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
SIMDPP_INL float64x2 hsub2(const float64x2& a, const float64x2& b)
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
SIMDPP_INL float32x4 sub_add(const float32x4& a, const float32x4& b)
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
SIMDPP_INL float64x2 sub_add(const float64x2& a, const float64x2& b)
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
SIMDPP_INL float64x2 floor(const float64x2& a)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<float64x2>(a, [](double x){ return std::floor(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_floor_pd(a);
#elif SIMDPP_USE_SSE2
    //check if the value is not too large, or is zero
    float64x2 ba = abs(a);
    mask_float64x2 large_mask = cmp_gt(ba, 4503599627370495.0);
    mask_float64x2 zero_mask = cmp_eq(ba, 0);
    mask_float64x2 mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the floor using trunc
    int64x2 s = shift_r((uint64x2)a, 63); //=1 if a<0
    float64x2 at = (float64x2) sub((int64x2)a, s); //=nextafter towards +inf if a<0
    int64x2 ia = to_int64x2(at);
            ia = sub(ia, s);
    float64x2 fa = to_float64x2(ia);

    //combine the results
    return blend(a, fa, mask);
#endif
}

/** Rounds the values of a float64x2 vector towards positive infinity

    @code
    r0 = ceil(a0)
    r1 = ceil(a1)
    @endcode
    @icost{SSE2, SSE3, SSSE3, 21}
*/
SIMDPP_INL float64x2 ceil(const float64x2& a)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<float64x2>(a, [](float x){ return std::ceil(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_ceil_pd(a);
#elif SIMDPP_USE_SSE2
    //check if the value is not too large, or is zero
    float64x2 ba = abs(a);
    mask_float64x2 large_mask = cmp_gt(ba, 4503599627370495.0);
    mask_float64x2 zero_mask = cmp_eq(ba, float64x2::zero());
    mask_float64x2 mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the ceil using trunc
    int64x2 s = shift_r((uint64x2)a, 63);
            s = bit_xor(s, 0x0000000000000001); //=1 if a>0
    float64x2 at = (float64x2) sub((int64x2)a, s); //=nextafter towards -inf if a>0
    int64x2 ia = to_int64x2(at);
            ia = add(ia, s);
    float64x2 fa = to_float64x2(ia);

    //combine the results
    return blend(a, fa, mask);
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
SIMDPP_INL float64x2 trunc(const float64x2& a)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<float64x2>(a, [](double x){ return std::trunc(x); });
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
    mask_float64x2 mask = cmp_gt(af, 4503599627370495.0);

    //truncate
    int64x2 ia = sse::to_int64x2(a);
    float64x2 fa = sse::to_float64x2(ia);

    //combine the results
    return blend(a, fa, mask); // takes care of nans
#endif
}

#endif
} // namespace sse
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
