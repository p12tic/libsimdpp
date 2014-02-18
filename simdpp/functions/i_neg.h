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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_I_NEG_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_I_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Negates signed 8-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int8x16 neg(int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(int8x16::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s8(a);
#endif
}

inline int8x32 neg(int8x32 a)
{
#if SIMDPP_USE_AVX2
    return sub(int8x32::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates signed 16-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int16x8 neg(int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(int16x8::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s16(a);
#endif
}

inline int16x16 neg(int16x16 a)
{
#if SIMDPP_USE_AVX2
    return sub(int16x16::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates signed 32-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline int32x4 neg(int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(int32x4::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s32(a);
#endif
}

inline int32x8 neg(int32x8 a)
{
#if SIMDPP_USE_AVX2
    return sub(int32x8::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates signed 64-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 8-9}
*/
inline int64x2 neg(int64x2 a)
{
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return sub(int64x2::zero(), a);
#endif
}

inline int64x4 neg(int64x4 a)
{
#if SIMDPP_USE_AVX2
    return sub(int64x4::zero(), a);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

