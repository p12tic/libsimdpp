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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_ADDS_H
#define LIBSIMDPP_SIMDPP_CORE_I_ADDS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Adds and saturates signed 8-bit integer values.

    @code
    r0 = signed_saturate(a0 + b0)
    ...
    rN = signed_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int8x16 adds(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector int8_t)a, (__vector int8_t)b);
#endif
}

inline int8x32 adds(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epi8(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates signed 16-bit integer values.

    @code
    r0 = signed_saturate(a0 + b0)
    ...
    rN = signed_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int16x8 adds(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector int16_t)a, (__vector int16_t)b);
#endif
}

inline int16x16 adds(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epi16(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates unsigned 8-bit integer values.

    @code
    r0 = unsigned_saturate(a0 + b0)
    ...
    rN = unsigned_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint8x16 adds(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline uint8x32 adds(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epu8(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds and saturates unsigned 16-bit integer values.

    @code
    r0 = unsigned_saturate(a0 + b0)
    ...
    rN = unsigned_saturate(aN + bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint16x8 adds(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::adds(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_adds_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vqaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_adds((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline uint16x16 adds(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_adds_epu16(a, b);
#else
    return {adds(a[0], b[0]), adds(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

