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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_ABS_H
#define LIBSIMDPP_SIMDPP_CORE_I_ABS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/cmp_neq.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Computes absolute value of 8-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-4}
*/
inline uint8x16 abs(int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi8(a);
#elif SIMDPP_USE_SSE2
    int8x16 t;
    t = cmp_lt(a, int8x16::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int8x16(vabsq_s8(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint8_t) vec_abs((__vector int8_t)a);
#endif
}

inline uint8x32 abs(int8x32 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_abs_epi8(a);
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 16-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-5}
*/
inline uint16x8 abs(int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi16(a);
#elif SIMDPP_USE_SSE2
    int16x8 t;
    t = cmp_lt(a, int16x8::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int16x8(vabsq_s16(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint16_t) vec_abs((__vector int16_t)a);
#endif
}

inline uint16x16 abs(int16x16 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_abs_epi16(a);
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 32-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-4}
*/
inline uint32x4 abs(int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi32(a);
#elif SIMDPP_USE_SSE2
    int32x4 t;
    t = cmp_lt(a, int32x4::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int32x4(vabsq_s32(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint32_t) vec_abs((__vector int32_t)a);
#endif
}

inline uint32x8 abs(int32x8 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_abs_epi32(a);
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Computes absolute value of 64-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{NEON, 6}
    @novec{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 10}
    @icost{NEON, 12}
    @icost{AVX2, 4}
    @novec{ALTIVEC}
*/
inline uint64x2 abs(int64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return null::abs(a);
#elif SIMDPP_USE_SSE2
    float64x2 ta;
    int64x2 t;
    ta = float64x2(shift_r<63>(uint64x2(a)));
    t = cmp_neq(ta, float64x2::zero());
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    int32x4 z = shift_r<63>(uint64x2(a));
    z = cmp_eq(z, int32x4::zero());
    z = permute<0,0,2,2>(z);
    z = bit_not(z);
    int64x2 t = z;
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#endif
}

inline uint64x4 abs(int64x4 a)
{
#if SIMDPP_USE_AVX2
    int64x4 t;
    t = _mm256_cmpgt_epi64(int64x4::zero(), a);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

