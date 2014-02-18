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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_F_SIGN_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_F_SIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/functions/bit_and.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Extracts sign bits from the values in float32x4 vector

    @code
    r0 = a0 & 0x80000000
    ...
    rN = aN & 0x80000000
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, NEON, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, NEON, 2-3}
    @icost{AVX-AVX2, 1-2}
*/
inline float32x4 sign(float32x4 a)
{
    return bit_and(a, int32x4::make_const(0x80000000));
}

inline float32x8 sign(float32x8 a)
{
    return bit_and(a, int32x8::make_const(0x80000000));
}
/// @}

/// @{
/** Extracts sigh bit from the values in float64x2 vector.

    @code
    r0 = a0 & 0x8000000000000000
    ...
    r0 = aN & 0x8000000000000000
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 1-2}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX-AVX2, 1-2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 sign(float64x2 a)
{
    return bit_and(a, uint64x2::make_const(0x8000000000000000));
}

inline float64x4 sign(float64x4 a)
{
#if SIMDPP_USE_AVX
    return bit_and(a, uint64x4::make_const(0x8000000000000000));
#else
    return {sign(a[0]), sign(a[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

