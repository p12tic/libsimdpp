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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_MUL_H
#define LIBSIMDPP_SIMDPP_CORE_I_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_mull.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/unzip_hi.h>
#include <simdpp/null/math.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// no 8 bit multiplications in SSE
/// @{
/** Multiplies 16-bit values and returns the lower part of the multiplication

    @code
    r0 = low(a0 * b0)
    ...
    rN = low(aN * bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint16x8 mul_lo(gint16x8 a, gint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mullo_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vmulq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_mladd((__vector uint16_t)a, (__vector uint16_t)b,
                     (__vector uint16_t)uint16x8::zero());
#endif
}

inline gint16x16 mul_lo(gint16x16 a, gint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mullo_epi16(a, b);
#else
    return {mul_lo(a[0], b[0]), mul_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 16-bit values and returns the higher half of the result.

    @code
    r0 = high(a0 * b0)
    ...
    rN = high(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, ALTIVEC, 6}
*/
inline int16x8 mul_hi(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){ return (int32_t(a) * b) >> 16; });
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epi16(a, b);
#elif SIMDPP_USE_NEON
    return unzip_hi((int16x8)mull_lo(a, b), (int16x8)mull_hi(a, b));
#elif SIMDPP_USE_ALTIVEC
    return unzip_lo(mull_lo(a, b), mull_hi(a, b));
#endif
}

inline int16x16 mul_hi(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mulhi_epi16(a, b);
#else
    return {mul_hi(a[0], b[0]), mul_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 16-bit values and returns the higher half of the result.

    @code
    r0 = high(a0 * b0)
    ...
    rN = high(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, ALTIVEC, 6}
*/
inline uint16x8 mul_hi(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){ return (int64_t(a) * b) >> 16; });
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epu16(a, b);
#elif SIMDPP_USE_NEON
    return unzip_hi((uint16x8)mull_lo(a, b), (uint16x8)mull_hi(a, b));
#elif SIMDPP_USE_ALTIVEC
    return unzip_lo(mull_lo(a, b), mull_hi(a, b));
#endif
}

inline uint16x16 mul_hi(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mulhi_epu16(a, b);
#else
    return {mul_hi(a[0], b[0]), mul_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies 32-bit values and returns the lower half of the result.

    @code
    r0 = low(a0 * b0)
    ...
    rN = low(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6}
    @icost{ALTIVEC, 8}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12}
    @icost{SSE4.1, AVX, NEON, 2}
    @icost{ALTIVEC, 16}
*/
inline gint32x4 mul_lo(gint32x4 a, gint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::mul(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_mullo_epi32(a, b);
#elif SIMDPP_USE_SSE2
    gint32x4 a1, b1;
    a1 = move_l<1>(a);
    b1 = move_l<1>(b);
    a = _mm_mul_epu32(a, b);
    a1 = _mm_mul_epu32(a1, b1);
    a = shuffle2<0,2,0,2>(a, a1); // additional latency unavoidable
    a = permute<0,2,1,3>(a);
    return a;
#elif SIMDPP_USE_NEON
    return vmulq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    // implement in terms of 16-bit multiplies
    uint16x8 la, lb, ha, hb;
    uint32x4 rl, rh1, rh2;
    la = a;  lb = b;
    ha = move_r<1>(la);
    hb = move_r<1>(lb);

    rl = mull_lo(la, lb);
    rh1 = mull_lo(la, hb);
    rh2 = mull_lo(ha, lb);

    rh1 = shift_l<16>(add(rh1, rh2));
    rl = add(rl, rh1);
    return rl;
#endif
}

inline gint32x8 mul_lo(gint32x8 a, gint32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_mullo_epi32(a, b);
#else
    return {mul_lo(a[0], b[0]), mul_lo(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

