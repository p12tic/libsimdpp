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
#include <simdpp/core/insert.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Sign extends the 16 values of a signed int8x16 vector to 16-bits

    @code
    r0 = (int16_t) a0
    ...
    r15 = (int16_t) a15
    @endcode

    @icost{SSE4.1-AVX, 3}
    @icost{SSE2-SSSE3, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline gint16x16 to_int16(int8x16 a)
{
#if SIMDPP_USE_NULL
    int16x16 r;
    for (unsigned i = 0; i < 16; i++) {
        r[i/8].el(i%8) = int16_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    int16x8 r1, r2;
    r1 = _mm_cvtepi8_epi16(a);
    r2 = _mm_cvtepi8_epi16(move_r<8>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2
    int16x8 r1, r2;
    r1 = zip_lo(int8x16::zero(), a);
    r1 = shift_r(r1, 8);
    r2 = zip_hi(int8x16::zero(), a);
    r2 = shift_r(r2, 8);
    return combine(r1, r2);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_s8(vget_low_s8(a));
    r[1] = vmovl_s8(vget_high_s8(a));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int16x16 r;
    r[0] = vec_unpackh((__vector int8_t)a[0]);
    r[1] = vec_unpackl((__vector int8_t)a[0]);
    return r;
#endif
}

// TODO support arbitrary length vectors

/** Extends the 16 values of a unsigned int8x16 vector to 16-bits

    @code
    r0 = (uint16_t) a0
    ...
    r15 = (uint16_t) a15
    @endcode
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint16x16 to_int16(uint8x16 a)
{
#if SIMDPP_USE_NULL
    uint16x16 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i/8].el(i%8) = uint16_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    int16x8 r1, r2;
    r1 = _mm_cvtepu8_epi16(a);
    r2 = _mm_cvtepu8_epi16(move_r<8>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2
    int16x8 r1, r2;
    r1 = zip_lo(a, uint8x16::zero());
    r2 = zip_hi(a, uint8x16::zero());
    return combine(r1, r2);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_u8(vget_low_u8(a));
    r[1] = vmovl_u8(vget_high_u8(a));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int16x16 r;
    r[0] = vmovl_u8(vget_low_u8(a[0]));
    r[1] = vmovl_u8(vget_high_u8(a[1]));
    return r;
#endif
}

// TODO support arbitrary length vectors

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

