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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SUBS_H
#define LIBSIMDPP_SIMDPP_CORE_I_SUBS_H

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
/** Subtracts and saturaters signed 8-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int8x16 subs(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int8x32 subs(int8x32 a, int8x32 b)
{
    return _mm256_subs_epi8(a, b);
}
#endif

template<unsigned N>
int8<N> subs(int8<N> a, int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, subs, a, b);
}
/// @}

/// @{
/** Subtracts and saturaters signed 16-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int16x8 subs(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int16x16 subs(int16x16 a, int16x16 b)
{
    return _mm256_subs_epi16(a, b);
}
#endif

template<unsigned N>
int16<N> subs(int16<N> a, int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, subs, a, b);
}
/// @}

/// @{
/** Subtracts and saturaters unsigned 8-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint8x16 subs(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 subs(uint8x32 a, uint8x32 b)
{
    return _mm256_subs_epu8(a, b);
}
#endif

template<unsigned N>
uint8<N> subs(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, subs, a, b);
}
/// @}

/// @{
/** Subtracts and saturaters unsigned 16-bit integer values.

    @code
    r0 = saturated(a0 - b0)
    ...
    rN = saturated(aN - bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint16x8 subs(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::subs(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint16x16 subs(uint16x16 a, uint16x16 b)
{
    return _mm256_subs_epu16(a, b);
}
#endif

template<unsigned N>
uint16<N> subs(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, subs, a, b);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

