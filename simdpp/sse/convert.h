/*  Copyright (C) 2011  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_CONVERT_H
#define LIBSIMDPP_SSE_CONVERT_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace sse {

/** Sign extends the values of a signed int8x16 vector to 32-bits

    @code
    r0 = (int32_t) a0
    ...
    r3 = (int32_t) a3
    @endcode
    @icost{SSE2, SSE3, SSSE3, 4}
*/
SIMDPP_INL uint32x4 to_int32x4(const int8x16& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepi8_epi32(a);
#else
    int16x8 a1;
    int32x4 r;
    a1 = zip16_lo(int8x16::zero(), a);
    r = zip8_lo(int16x8::zero(), a1);
    r = shift_r(r, 24);
    return r;
#endif
}

/** Extends the values of a unsigned int8x16 vector to 32-bits

    @code
    r0 = (uint32_t) a0
    ...
    r3 = (uint32_t) a3
    @endcode
    @icost{SSE2, SSE3, SSSE3, 3}
*/
SIMDPP_INL uint32x4 to_int32x4(const uint8x16& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepu8_epi32(a);
#else
    int16x8 a1 = (int16x8) zip16_lo(a, int8x16::zero());
    int32x4 r = (int32x4) zip8_lo(a1, int16x8::zero());
    return r;
#endif
}

/** Sign extends the values of a signed int8x16 vector to 64-bits

    @code
    r0 = (int64_t) a0
    r1 = (int64_t) a1
    @endcode
    @unimp{SSE2, SSE3, SSSE3}
*/
SIMDPP_INL uint64x2 to_int64x2(const int8x16& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepi8_epi64(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

/** Sign extends the values of a signed int16x8 vector to 64-bits

    @code
    r0 = (int64_t) a0
    r1 = (int64_t) a1
    @endcode
    @unimp{SSE2, SSE3, SSSE3}
*/
SIMDPP_INL uint64x2 to_int64x2(const int16x8& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepi16_epi64(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

/** Extends the values of a unsigned int8x16 vector to 64-bits

    @code
    r0 = (uint64_t) a0
    r1 = (uint64_t) a1
    @endcode
    @icost{SSE2, SSE3, SSSE3, 4}
*/
SIMDPP_INL uint64x2 to_int64x2(const uint8x16& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepu8_epi64(a);
#else
    int16x8 a1 = (int16x8) zip16_lo(a, uint8x16::zero());
    int32x4 a2 = (int32x4) zip8_lo(a1, int16x8::zero());
    int64x2 r = (int64x2) zip4_lo(a2, int32x4::zero());
    return r;
#endif
}

/** Converts the values of a float32x4 vector into signed int32_t representation.
    If the value can not be represented by int32_t, @c 0x80000000 is returned
    If only inexact conversion can be performed, the current rounding mode is
    used.

    @code
    r0 = (int32_t) a0
    r1 = (int32_t) a1
    r2 = (int32_t) a2
    r3 = (int32_t) a3
    @endcode
*/
SIMDPP_INL uint32x4 to_int32x4_r(const float32x4& a)
{
    return _mm_cvtps_epi32(a);
}

/** Converts the values of a float64x2 vector into int32_t representation using
    truncation

    If the value can not be represented by int32_t, @c 0x80000000 is returned

    @code
    r0 = (int32_t) a0
    r1 = (int32_t) a1
    r2 = 0
    r3 = 0
    @endcode
*/
SIMDPP_INL uint32x4 to_int32x4(const float64x2& a)
{
    return _mm_cvttpd_epi32(a);
}

/** Converts the values of a float64x2 vector into int32_t representation.

    If the value can not be represented by int32_t, @c 0x80000000 is returned
    If only inexact conversion can be performed, it is rounded according to the
    current rounding mode.

    @code
    r0 = (int32_t) a0
    r1 = (int32_t) a1
    r2 = 0
    r3 = 0
    @endcode
*/
SIMDPP_INL uint32x4 to_int32x4_r(const float64x2& a)
{
    return _mm_cvtpd_epi32(a);
}

} // namespace sse
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
