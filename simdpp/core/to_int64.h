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

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_INT64_H
#define LIBSIMDPP_SIMDPP_CORE_TO_INT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_lo.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Extends the values of a signed int32x4 vector to 64-bits

    @code
    r0 = (int64_t) a0
    ...
    r3 = (int64_t) a3
    @endcode

    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX, 3}
    @icost{NEON, 2}
    @icost{ALTIVEC, 3-4}
*/
inline gint64x4 to_int64(int32x4 a)
{
#if SIMDPP_USE_NULL
    int64x4 r;
    r[0].el(0) = int64_t(a.el(0));
    r[0].el(1) = int64_t(a.el(1));
    r[1].el(0) = int64_t(a.el(2));
    r[1].el(1) = int64_t(a.el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepi32_epi64(a);
#elif SIMDPP_USE_SSE4_1
    gint64x2 r1, r2;
    r1 = _mm_cvtepi32_epi64(a);
    r2 = _mm_cvtepi32_epi64(move4_r<2>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    int32x4 u;
    u = shift_r(a, 31);
    return (gint64x4) combine(zip4_lo(a, u), zip4_hi(a, u));
#elif SIMDPP_USE_NEON
    int64x2 r1, r2;
    r1 = vmovl_s32(vget_low_s32(a));
    r2 = vmovl_s32(vget_high_s32(a));
    return combine(r1, r2);
#endif
}

// TODO support arbitrary length vectors

/// @{
/** Extends the values of an unsigned int32x4 vector to 64-bits

    @code
    r0 = (uint64_t) a0
    ...
    r3 = (uint64_t) a3
    @endcode

    @icost{SSE2-AVX, 3}
    @icost{NEON, ALTIVEC, 2}
*/
inline gint64x4 to_int64(uint32x4 a)
{
#if SIMDPP_USE_NULL
    uint64x4 r;
    r[0].el(0) = uint64_t(a.el(0));
    r[0].el(1) = uint64_t(a.el(1));
    r[1].el(0) = uint64_t(a.el(2));
    r[1].el(1) = uint64_t(a.el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepu32_epi64(a);
#elif SIMDPP_USE_SSE4_1
    gint64x2 r1, r2;
    r1 = _mm_cvtepu32_epi64(a);
    r2 = _mm_cvtepu32_epi64(move4_r<2>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return (gint64x4) combine(zip4_lo(a, uint32x4::zero()),
                              zip4_hi(a, uint32x4::zero()));
#elif SIMDPP_USE_NEON
    int64x2 r1, r2;
    r1 = vmovl_u32(vget_low_u32(a));
    r2 = vmovl_u32(vget_high_u32(a));
    return combine(r1, r2);
#endif
}
/// @}

// TODO support arbitrary length vectors

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

