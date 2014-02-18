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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_ADD_H
#define LIBSIMDPP_SIMDPP_CORE_I_ADD_H

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
/** Adds 8-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 add(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

inline basic_int8x32 add(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi8(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds 16-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int16x8 add(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

inline basic_int16x16 add(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi16(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds 32-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline basic_int32x4 add(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

inline basic_int32x8 add(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi32(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds 64-bit integer values.

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 5-6}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 10-11}
*/
inline basic_int64x2 add(basic_int64x2 a, basic_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi64(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u64(a, b);
#else
    uint64x2 c1 = uint64x2::make_const(1);
    uint32x4 r, carry;
    carry = vec_addc((__vector uint32_t) a, (__vector uint32_t) b);
    carry = move_l<1>(carry);
    r = add((uint32x4)a, (uint32x4)b);
    carry = bit_and(carry, c1);
    r = add(r, carry);
    return r;
#endif
}

inline basic_int64x4 add(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_add_epi64(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

