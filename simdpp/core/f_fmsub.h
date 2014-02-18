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

#ifndef LIBSIMDPP_SIMDPP_CORE_F_FMSUB_H
#define LIBSIMDPP_SIMDPP_CORE_F_FMSUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Performs a fused multiply-sutract operation

    @code
    r0 = a0 * b0 - c0
    ...
    rN = aN * bN - cN
    @endcode

    Implemented only on architectures with either @c X86_FMA3 or @c X86_FMA4
    support.
*/
inline float32x4 fmsub(float32x4 a, float32x4 b, float32x4 c)
{
#if SIMDPP_USE_NULL
    return null::fmsub(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmsub_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_msub_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

inline float32x8 fmsub(float32x8 a, float32x8 b, float32x8 c)
{
#if SIMDPP_USE_AVX
#if SIMDPP_USE_FMA3
    return _mm256_fmsub_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_msub_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
#else
    SIMDPP_VEC_ARRAY_IMPL3(float32x8, fmsub, a, b, c);
#endif
}

inline float64x2 fmsub(float64x2 a, float64x2 b, float64x2 c)
{
#if SIMDPP_USE_NULL
    return null::fmsub(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmsub_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_msub_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

inline float64x4 fmsub(float64x4 a, float64x4 b, float64x4 c)
{
#if SIMDPP_USE_AVX
#if SIMDPP_USE_FMA3
    return _mm256_fmsub_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_msub_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
#else
    SIMDPP_VEC_ARRAY_IMPL3(float64x4, fmsub, a, b, c);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

