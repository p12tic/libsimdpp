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

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_INT16_H
#define LIBSIMDPP_SIMDPP_CORE_TO_INT16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Sign extends the first 8 values of a signed int8x16 vector to 16-bits

    @code
    r0 = (int16_t) a0
    ...
    r7 = (int16_t) a7
    @endcode
    @icost{SSE2-SSSE3, 2}
*/
inline gint16x8 to_int16x8(int8x16 a)
{
#if SIMDPP_USE_NULL
    int16x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r.el(i) = int16_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepi8_epi16(a);
#elif SIMDPP_USE_SSE2
    int16x8 r;
    r = zip_lo(int8x16::zero(), a);
    r = shift_r(r, 8);
    return r;
#elif SIMDPP_USE_NEON
    return vmovl_s8(vget_low_s8(a));
#elif SIMDPP_USE_ALTIVEC
    return vec_unpackh((__vector int8_t)a);
#endif
}

/** Sign extends the first 16 values of a signed int8x32 vector to 16-bits

    @code
    r0 = (int16_t) a0
    ...
    r15 = (int16_t) a15
    @endcode

    @icost{SSE4.1-AVX, 3}
    @icost{SSE2-SSSE3, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline gint16x16 to_int16x16(int8x32 a)
{
    /*
#if SIMDPP_USE_NULL
    int16x16 r;
    for (unsigned i = 0; i < 16; i++) {
        r[i/8].el(i%8) = int16_t(a[0].el(i));
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a));
#elif SIMDPP_USE_SSE4_1
    int16x16 r;
    r[0] = to_int16x8(a[0]);
    r[1] = to_int16x8(move_l<8>(a[0]));
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 b0, b1;
    b0 = zip_lo(int8x16::zero(), a[0]);
    b1 = zip_hi(int8x16::zero(), a[0]);
    b0 = shift_r<8>(b0);
    b1 = shift_r<8>(b1);
    return int16x16(b0, b1);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_s8(vget_low_s8(a[0]));
    r[1] = vmovl_s8(vget_high_s8(a[1]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int16x8 b0, b1;
    b0 = vec_unpackh((__vector int8_t)a[0]);
    b1 = vec_unpackl((__vector int8_t)a[0]);
    return {b0, b1};
#endif
    */
}


/** Extends the first 8 values of a unsigned int8x16 vector to 16-bits

    @code
    r0 = (uint16_t) a0
    ...
    r7 = (uint16_t) a7
    @endcode
*/
inline gint16x8 to_int16x8(uint8x16 a)
{
#if SIMDPP_USE_NULL
    uint16x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r.el(i) = int16_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepu8_epi16(a);
#elif SIMDPP_USE_SSE2
    return zip_lo(a, uint8x16::zero());
#elif SIMDPP_USE_NEON
    return vmovl_u8(vget_low_u8(a));
#elif SIMDPP_USE_ALTIVEC
    return zip_lo(uint8x16::zero(), a);
#endif
}

/** Extends the first 16 values of a unsigned int8x32 vector to 16-bits

    @code
    r0 = (uint16_t) a0
    ...
    r15 = (uint16_t) a15
    @endcode
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint16x16 to_int16x16(uint8x32 a)
{
    /*
#if SIMDPP_USE_NULL
    int16x16 r;
    for (unsigned i = 0; i < 16; i++) {
        r[i/8].el(i%8) = uint16_t(a[0].el(i));
    }
    return r;
#elif SIMDPP_USE_AVX2
    return  _mm256_cvtepu8_epi16(_mm256_castsi256_si128(a));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    int16x8 b0, b1;
    b0 = zip_lo(a[0], int8x16::zero());
    b1 = zip_hi(a[0], int8x16::zero());
    return int16x16(b0, b1);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_s8(vget_low_s8(a[0]));
    r[1] = vmovl_s8(vget_high_s8(a[1]));
    return r;
#endif
    */
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

