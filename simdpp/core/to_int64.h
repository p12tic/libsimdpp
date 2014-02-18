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

    @par 128-bit version:
    @code
    r0 = (int64_t) a0
    r1 = (int64_t) a1
    @endcode

    @icost{SSE2-SSSE3, 2}
    @icost{ALTIVEC, 2-3}

    @par 256-bit version:
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
inline gint64x2 to_int64x2(int32x4 a)
{
    /* FIXME
#if SIMDPP_USE_NULL
    int64x2 r;
    r.el(0) = int64_t(a.el(0));
    r.el(1) = int64_t(a.el(1));
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepi32_epi64(a);
#elif SIMDPP_USE_SSE2
    int32x4 u;
    u = shift_r(a, 31);
    a = zip_lo(a, u);
    return a;
#elif SIMDPP_USE_NEON
    return vmovl_s32(vget_low_s32(a));
#elif SIMDPP_USE_ALTIVEC
    int32x4 u;
    u = shift_r(a, 31);
    a = zip_lo(u, a);
    return a;
#endif
    */
}

inline gint64x4 to_int64x4(int32x8 a)
{
    /* FIXME
#if SIMDPP_USE_NULL
    int64x4 r;
    r[0].el(0) = int64_t(a[0].el(0));
    r[0].el(1) = int64_t(a[0].el(1));
    r[1].el(0) = int64_t(a[0].el(2));
    r[1].el(1) = int64_t(a[0].el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepi32_epi64(sse::extract_lo(a));
#elif SIMDPP_USE_SSE2
    return int64x4(to_int64x2(a[0]), to_int64x2(move_l<2>(a[0])));
#elif SIMDPP_USE_NEON
    int64x4 r;
    r[0] = vmovl_s32(vget_low_s32(a[0]));
    r[1] = vmovl_s32(vget_high_s32(a[0]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int32x4 a0 = a[0];
    int32x4 u = shift_r(a0, 31);
    int64x2 b0, b1;
    b0 = zip_lo(u, a0);
    b1 = zip_hi(u, a0);
    return { b0, b1 };
#endif
    */
}

/// @{
/** Extends the values of an unsigned int32x4 vector to 64-bits

    @par 128-bit version:
    @code
    r0 = (uint64_t) a0
    r1 = (uint64_t) a1
    @endcode

    @par 256-bit version:
    @code
    r0 = (uint64_t) a0
    ...
    r3 = (uint64_t) a3
    @endcode

    @icost{SSE2-AVX, 3}
    @icost{NEON, ALTIVEC, 2}
*/
inline gint64x2 to_int64x2(uint32x4 a)
{
    /* FIXME
#if SIMDPP_USE_NULL
    int64x2 r;
    r.el(0) = int64_t(a.el(0));
    r.el(1) = int64_t(a.el(1));
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_cvtepu32_epi64(a);
#elif SIMDPP_USE_SSE2
    return zip_lo(a, uint32x4::zero());
#elif SIMDPP_USE_NEON
    return vmovl_u32(vget_low_u32(a));
#elif SIMDPP_USE_ALTIVEC
    return zip_lo(uint32x4::zero(), a);
#endif
    */
}

inline gint64x4 to_int64x4(uint32x8 a)
{
    /* FIXME
#if SIMDPP_USE_NULL
    int64x4 r;
    r[0].el(0) = int64_t(a[0].el(0));
    r[0].el(1) = int64_t(a[0].el(1));
    r[1].el(0) = int64_t(a[0].el(2));
    r[1].el(1) = int64_t(a[0].el(3));
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_cvtepu32_epi64(sse::extract_lo(a));
#elif SIMDPP_USE_SSE2
    uint32x4 u1 = move_l<2>(a[0]);
    return int64x4(to_int64x2(a[0]), u1);
#elif SIMDPP_USE_NEON
    uint64x4 r;
    r[0] = vmovl_u32(vget_low_u32(a[0]));
    r[1] = vmovl_u32(vget_high_u32(a[0]));
    return r;
#elif SIMDPP_USE_ALTIVEC
    return { zip_lo(uint32x4::zero(), a[0]), zip_hi(uint32x4::zero(), a[1]) };
#endif
    */
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

