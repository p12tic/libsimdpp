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

#ifndef LIBSIMDPP_SIMDPP_CORE_PERMUTE4_H
#define LIBSIMDPP_SIMDPP_CORE_PERMUTE4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/detail/shuffle_emul.h>
#include <simdpp/null/shuffle.h>
#include <simdpp/sse/shuffle.h>
#include <simdpp/neon/detail/shuffle_int16x8.h>
#include <simdpp/neon/detail/shuffle_int32x4.h>
#include <simdpp/neon/detail/shuffle_int64x2.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Permutes the 16-bit values within each 4 consecutive values of the vector.
    The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]

    256-bit version:

    r8 = a[s0+8]
    ...
    r11 = a[s3+8]
    r12 = a[s0+12]
    ...
    r15 = a[s3+12]
    @endcode

    @par: 128-bit version:
    @icost{SSE2-AVX2, 2}
    @icost{NEON, 1-5}
    @icost{ALTIVEC, 1-2}

    @par: 256-bit version:
    @icost{SSE2-AVX, 4}
    @icost{AVX2, 2}
    @icost{NEON, 2-10}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
int128 permute(gint16x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_SSE2
    a = sse::permute_lo<s0,s1,s2,s3>(a);
    a = sse::permute_hi<s0,s1,s2,s3>(a);
    return a;
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int16x8::permute4<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint16x8 mask = make_shuffle_bytes16_mask<s0,s1,s2,s3>(mask);
    return permute_bytes16(a, mask);
#endif
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint16x16 permute(gint16x16 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_AVX2
    a = sse::permute_lo<s0,s1,s2,s3>(a);
    a = sse::permute_hi<s0,s1,s2,s3>(a);
    return a;
#else
    return {permute<s0,s1,s2,s3>(a[0]), permute<s0,s1,s2,s3>(a[1])};
#endif
}
/// @}

/// @{
/** Permutes the values of each set of four consecutive 32-bit values. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]

    256-bit version:
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint32x4 permute(gint32x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_SSE2
    return _mm_shuffle_epi32(a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int32x4::permute4<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint32x4 mask = make_shuffle_bytes16_mask<s0,s1,s2,s3>(mask);
    return permute_bytes16(a, mask);
#endif
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint32x8 permute(gint32x8 a)
{
#if SIMDPP_USE_AVX2
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shuffle_epi32(a, _MM_SHUFFLE(s3, s2, s1, s0));
#else
    return {permute<s0,s1,s2,s3>(a[0]), permute<s0,s1,s2,s3>(a[1])};
#endif
}
/// @}

/// @{
/** Permutes the values of each set of four consecutive 32-bit floating point
    values. The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]

    256-bit version:
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float32x4 permute(float32x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_SSE2
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_NEON
    return float32x4(neon::detail::shuffle_int32x4::permute4<s0,s1,s2,s3>(int32x4(a)));
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint32x4 mask = make_shuffle_bytes16_mask<s0,s1,s2,s3>(mask);
    return permute_bytes16(a, mask);
#endif
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float32x8 permute(float32x8 a)
{
#if SIMDPP_USE_AVX
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shuffle_ps(a, a, _MM_SHUFFLE(s3, s2, s1, s0));
#else
    return {permute<s0,s1,s2,s3>(a[0]), permute<s0,s1,s2,s3>(a[1])};
#endif
}
/// @}

/** Permutes the values of each set of four consecutive 64-bit values. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s2]
    r3 = a[s3]
    @endcode
    @icost{SSE2-AVX, 2}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint64x4 permute(gint64x4 a)
{
#if SIMDPP_USE_NULL
    uint64x4 r;
    r[0][0] = a[s0/2][s0%2];
    r[0][1] = a[s1/2][s1%2];
    r[1][0] = a[s2/2][s2%2];
    r[1][1] = a[s3/2][s3%2];
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_permute4x64_epi64(a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::permute_emul<s0,s1,s2,s3>(a);
#endif
}

/** Permutes the values of each set of four consecutive 64-bit floating-point
    values. The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s2]
    r3 = a[s3]
    @endcode

    @icost{SSE2-AVX, 1-2}
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-4}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float64x4 permute(float64x4 a)
{
#if SIMDPP_USE_NULL
    float64x4 r;
    r[0][0] = a[s0/2][s0%2];
    r[0][1] = a[s1/2][s1%2];
    r[1][0] = a[s2/2][s2%2];
    r[1][1] = a[s3/2][s3%2];
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_permute4x64_pd(a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::permute_emul<s0,s1,s2,s3>(a);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

