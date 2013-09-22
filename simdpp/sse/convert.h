/*  libsimdpp
    Copyright (C) 2011-2012 Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SSE_CONVERT_H
#define LIBSIMDPP_SSE_CONVERT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
inline basic_int32x4 to_int32x4(int8x16 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepi8_epi32(a);
#else
    int16x8 a1;
    int32x4 r;
    a1 = zip_lo(int128::zero(), a);
    r = zip_lo(int128::zero(), a1);
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
inline basic_int32x4 to_int32x4(uint8x16 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepu8_epi32(a);
#else
    int16x8 a1 = zip_lo(a, int128::zero());
    int32x4 r = zip_lo(a1, int128::zero());
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
inline basic_int64x2 to_int64x2(int8x16 a)
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
inline basic_int64x2 to_int64x2(int16x8 a)
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
inline basic_int64x2 to_int64x2(uint8x16 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_cvtepu8_epi64(a);
#else
    int16x8 a1 = zip_lo(a, int128::zero());
    int32x4 a2 = zip_lo(a1, int128::zero());
    int64x2 r = zip_lo(a2, int128::zero());
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
inline basic_int32x4 to_int32x4_r(float32x4 a)
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
inline basic_int32x4 to_int32x4(float64x2 a)
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
inline basic_int32x4 to_int32x4_r(float64x2 a)
{
    return _mm_cvtpd_epi32(a);
}

} // namespace sse
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
