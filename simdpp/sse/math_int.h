/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_MATH_INT_H
#define LIBSIMDPP_SSE_MATH_INT_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {


/** Copies sign from the values of one int8x16 vector to another

    @code
    r0 = (b0 > 0) ? a0 : ((b0 == 0) ? 0 : -a0)
    ...
    r15 = (b15 > 0) ? a15 : ((b15 == 0) ? 0 : -a15)
    @endcode
    @unimp{SSE2, SSE3}
*/
SIMDPP_INL int8x16 copysign(const int8x16& a, const int8x16& b)
{
#if SIMDPP_USE_SSSE3
    return _mm_sign_epi8(a,b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a,b);
#endif
}

/** Copies sign from the values of one int16x8 vector to another

    @code
    r0 = (b0 > 0) ? a0 : ((b0 == 0) ? 0 : -a0)
    ...
    r7 = (b7 > 0) ? a7 : ((b7 == 0) ? 0 : -a7)
    @endcode
    @unimp{SSE2, SSE3}
*/
SIMDPP_INL int16x8 copysign(const int16x8& a, const int16x8& b)
{
#if SIMDPP_USE_SSSE3
    return _mm_sign_epi16(a,b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a,b);
#endif
}

/** Copies sign from the values of one int32x4 vector to another

    @code
    r0 = (b0 > 0) ? a0 : ((b0 == 0) ? 0 : -a0)
    r1 = (b1 > 0) ? a1 : ((b1 == 0) ? 0 : -a1)
    r2 = (b2 > 0) ? a2 : ((b2 == 0) ? 0 : -a2)
    r3 = (b3 > 0) ? a3 : ((b3 == 0) ? 0 : -a3)
    @endcode
    @unimp{SSE2, SSE3}
*/
SIMDPP_INL int32x4 copysign(const int32x4& a, const int32x4& b)
{
#if SIMDPP_USE_SSSE3
    return _mm_sign_epi32(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a,b);
#endif
}

} // namespace sse
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
