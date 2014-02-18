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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_SHUFFLE1_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_SHUFFLE1_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/fwd.h>
#include <simdpp/simd/make_shuffle_bytes_mask.h>

#if SIMDPP_USE_NULL
    #include <simdpp/null/shuffle.h>
#elif SIMDPP_USE_SSE2
    #include <simdpp/sse/shuffle.h>
#elif SIMDPP_USE_NEON
    #include <simdpp/neon/detail/shuffle_int16x8.h>
    #include <simdpp/neon/detail/shuffle_int32x4.h>
    #include <simdpp/neon/detail/shuffle_int64x2.h>
#endif


namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Selects 64-bit floating-point values from two vectors. The first value in
    each pair of values must come from @a a, the second - from @a b. The
    selector values must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = b[s1]

    256-bit version:
    r2 = a[s0+2]
    r3 = b[s1+2]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s0, unsigned s1>
float64x2 shuffle1(float64x2 a, float64x2 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return float64x2(shuffle1<s0,s1>(int64x2(a), int64x2(b)));
#elif SIMDPP_USE_SSE2
    if (s0 == 0 && s1 == 0) {
        return _mm_castps_pd(_mm_movelh_ps(_mm_castpd_ps(a),
                                           _mm_castpd_ps(b)));
    } else if (s0 == 1 && s1 == 1) {
        return _mm_castps_pd(_mm_movehl_ps(_mm_castpd_ps(b),
                                           _mm_castpd_ps(a)));
    } else if (s0 == 0 && s1 == 1) {
        return _mm_move_sd(b, a);
    } else if (s0 == 1 && s1 == 0) {
        return _mm_shuffle_pd(a, b, _MM_SHUFFLE2(s1, s0));
    }
#endif
}

template<unsigned s0, unsigned s1>
float64x4 shuffle1(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_shuffle_pd(a, b, s0 | s1<<1 | s0<<2 | s1<<3);
#else
    return {shuffle1<s0,s1>(a[0], b[0]), shuffle1<s0,s1>(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Selects 64-bit values from two vectors. The first value in each pair of
    values must come from @a a, the second - from @a b. The selector values
    must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = b[s1]

    256-bit version:
    r2 = a[s0+2]
    r3 = b[s1+2]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1>
basic_int64x2 shuffle1(basic_int64x2 a, basic_int64x2 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::shuffle1<s0,s1>(a, b);
#elif SIMDPP_USE_SSE2
    // We can't do this in the integer execution domain. Beware of additional latency
    return int64x2(shuffle1<s0,s1>(float64x2(a), float64x2(b)));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int64x2::shuffle1<s0,s1>(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<s0,s1+2>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

template<unsigned s0, unsigned s1>
basic_int64x4 shuffle1(basic_int64x4 a, basic_int64x4 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX2
    // We can't do this in the integer execution domain. Beware of additional latency
    return int64x4(shuffle1<s0,s1>(float64x4(a), float64x4(b)));
#else
    return {shuffle1<s0,s1>(a[0], b[0]), shuffle1<s0,s1>(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

