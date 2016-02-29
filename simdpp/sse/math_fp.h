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
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {

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
    float64x2 r;
    for (unsigned i = 0; i < r.length; ++i) {
        r.el(i) = std::floor(a.el(i));
    }
    return r;
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
    float64x2 r;
    for (unsigned i = 0; i < r.length; ++i) {
        r.el(i) = std::ceil(a.el(i));
    }
    return r;
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
    float64x2 r;
    for (unsigned i = 0; i < r.length; ++i) {
        r.el(i) = std::trunc(a.el(i));
    }
    return r;
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
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
