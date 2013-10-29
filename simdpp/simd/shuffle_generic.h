/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_SHUFFLE_GENERIC_H
#define LIBSIMDPP_SIMD_SHUFFLE_GENERIC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/fwd.h>
#include <simdpp/simd/make_shuffle_bytes_mask.h>
#include <simdpp/simd/detail/shuffle_emul.h>

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

/** @ingroup simd_shuffle
    @{
*/
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
int128 permute(basic_int16x8 a)
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
basic_int16x16 permute(basic_int16x16 a)
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
/** Permutes the 16-bit values within sets of two consecutive elements of the
    vector. The selector values must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s0+2]
    r3 = a[s1+2]
    r4 = a[s0+4]
    r5 = a[s1+4]
    ...
    @endcode

    @par: 128-bit version:
    @icost{SSE2-AVX2, 2}
    @icost{NEON, ALTIVEC, 1-2}

    @par: 256-bit version:
    @icost{SSE2-AVX, 4}
    @icost{AVX2, 2}
    @icost{NEON, 2-4}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1>
basic_int16x8 permute(basic_int16x8 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute<s0,s1,s0+2,s1+2>(a);
}

template<unsigned s0, unsigned s1>
basic_int16x16 permute(basic_int16x16 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute<s0,s1,s0+2,s1+2>(a);
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
basic_int32x4 permute(basic_int32x4 a)
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
basic_int32x8 permute(basic_int32x8 a)
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
/** Permutes the values of each set of four consecutive 32-bit values. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s0+2]
    r3 = a[s1+2]
    256-bit version:
    r4 = a[s0+4]
    r5 = a[s1+4]
    r6 = a[s0+6]
    r7 = a[s1+6]
    @endcode

    @par 128-bit version:
    @icost{NEON, 2-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 4-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1>
basic_int32x4 permute(basic_int32x4 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute<s0,s1,s0+2,s1+2>(a);
}

template<unsigned s0, unsigned s1>
basic_int32x8 permute(basic_int32x8 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute<s0,s1,s0+2,s1+2>(a);
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


/// @{
/** Permutes the values of each set of four consecutive 32-bit floating-point
    values. The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s0+2]
    r3 = a[s1+2]

    256-bit version:
    r4 = a[s0+4]
    r5 = a[s1+4]
    r6 = a[s0+6]
    r7 = a[s1+6]
    @endcode

    @par 128-bit version:
    @icost{NEON, 2-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 4-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1>
float32x4 permute(float32x4 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute<s0,s1,s0+2,s1+2>(a);
}

template<unsigned s0, unsigned s1>
float32x8 permute(float32x8 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute<s0,s1,s0+2,s1+2>(a);
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
basic_int64x4 permute(basic_int64x4 a)
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

/// @{
/** Permutes the values of each set of four consecutive 32-bit values. The
    selector values must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = a[s1]

    256-bit version:
    r2 = a[s0+2]
    r3 = a[s1+2]
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-4}
    @icost{ALTIVEC, 2-4}
*/
template<unsigned s0, unsigned s1>
basic_int64x2 permute(basic_int64x2 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1>(a);
#elif SIMDPP_USE_SSE2
    return permute<s0*2, s0*2+1, s1*2, s1*2+1>(int32x4(a));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int64x2::permute2<s0,s1>(a);
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint64x2 mask = make_shuffle_bytes16_mask<s0,s1>(mask);
    return permute_bytes16(a, mask);
#endif
}

template<unsigned s0, unsigned s1>
basic_int64x4 permute(basic_int64x4 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX2
    return _mm256_permute4x64_epi64(a, s0 | s1<<2 | (s0+2)<<4 | (s1+2)<<6);
#else
    return permute<s0,s1,s0+2,s1+2>(a);
#endif
}
/// @}

/// @{
/** Permutes the values of each set of four consecutive 32-bit values. The
    selector values must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = a[s1]

    256-bit version:
    r2 = a[s0+2]
    r3 = a[s1+2]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s0, unsigned s1>
float64x2 permute(float64x2 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_SSE2
    return _mm_shuffle_pd(a, a, _MM_SHUFFLE2(s1, s0));
#else
    return float64x2(permute<s0,s1>(int64x2(a)));
#endif
}
template<unsigned s0, unsigned s1>
float64x4 permute(float64x4 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX2
    return _mm256_permute4x64_pd(a, s0 | s1<<2 | (s0+2)<<4 | (s1+2)<<6);
#elif SIMDPP_USE_AVX
    return _mm256_permute_pd(a, s0 | s1<<1 | s0<<2 | s1<<3);
#else
    return permute<s0,s1,s0+2,s1+2>(a);
#endif
}
/// @}

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

/// @{
/** Selects 32-bit floating-point values from two vectors. The first two values
    in each four consecutive values must come from @a a, the last two - from @a
    b. The selector values must be in range [0; 3].

    @code
    r0 = a[a0]
    r1 = a[a1]
    r2 = b[b0]
    r3 = b[b1]

    256-bit version:
    r4 = a[a0+4]
    r5 = a[a1+4]
    r6 = b[b0+4]
    r7 = b[b1+4]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}
    @icost{NEON, 1-4}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
float32x4 shuffle2(float32x4 a, float32x4 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    return float32x4(shuffle2<a0,a1,b0,b1>(int32x4(a), int32x4(b)));
#elif SIMDPP_USE_SSE2
    if (a1 == a0 + 1 && b1 == b0 + 1 && a0 % 2 == 0 && b0 % 2 == 0) {
        float64x2 arga = bit_cast<float64x2>(a);
        float64x2 argb = bit_cast<float64x2>(b);
        float64x2 res = shuffle1<a0/2,b0/2>(arga, argb);
        return bit_cast<float32x4>(res);
    } else {
        return _mm_shuffle_ps(a, b, _MM_SHUFFLE(b1, b0, a1, a0));
    }
#elif SIMDPP_USE_ALTIVEC
    uint32x4 mask = make_shuffle_bytes16_mask<a0,a1,b0+4,b1+4>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
float32x8 shuffle2(float32x8 a, float32x8 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_shuffle_ps(a, b, _MM_SHUFFLE(b1, b0, a1, a0));
#else
    return {shuffle2<a0,a1,b0,b1>(a[0], b[0]), shuffle2<a0,a1,b0,b1>(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Selects 32-bit values from two vectors. The first two values in each four
    consecutive values must come from @a a, the last two - from @a b. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = b[s0]
    r3 = b[s1]

    256-bit version:
    r4 = a[s0+4]
    r5 = a[s1+4]
    r6 = b[s0+4]
    r7 = b[s1+4]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}
    @icost{NEON, 2-4}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 4-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1>
float32x4 shuffle2(float32x4 a, float32x4 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    return shuffle2<s0,s1,s0,s1>(a, b);
}

template<unsigned s0, unsigned s1>
float32x8 shuffle2(float32x8 a, float32x8 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    return shuffle2<s0,s1,s0,s1>(a, b);
}
/// @}

/// @{
/** Selects 32-bit values from two vectors. The first two values in each four
    consecutive values must come from @a a, the last two - from @a b. The
    selector values must be in range [0; 3].

    @code
    r0 = a[a0]
    r1 = a[a1]
    r2 = b[b0]
    r3 = b[b1]

    256-bit version:
    r4 = a[a0+4]
    r5 = a[a1+4]
    r6 = b[b0+4]
    r7 = b[b1+4]
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
basic_int32x4 shuffle2(basic_int32x4 a, basic_int32x4 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::shuffle2<a0,a1,b0,b1>(a, b);
#elif SIMDPP_USE_SSE2
    // We can't do this in the integer execution domain. Beware of additional latency
    return int32x4(shuffle2<a0,a1,b0,b1>(float32x4(a), float32x4(b)));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int32x4::shuffle2<a0,a1,b0,b1>(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 mask = make_shuffle_bytes16_mask<a0,a1,b0+4,b1+4>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
basic_int32x8 shuffle2(basic_int32x8 a, basic_int32x8 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
#if SIMDPP_USE_AVX2
    // We can't do this in the integer execution domain. Beware of additional latency
    return int32x8(shuffle2<a0,a1,b0,b1>(float32x8(a), float32x8(b)));
#else
    return {shuffle2<a0,a1,b0,b1>(a[0], b[0]), shuffle2<a0,a1,b0,b1>(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Selects 32-bit values from two vectors. The first two values in each four
    consecutive values must come from @a a, the last two - from @a b. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = b[s0]
    r3 = b[s1]

    256-bit version:
    r4 = a[s0+4]
    r5 = a[s1+4]
    r6 = b[s0+4]
    r7 = b[s1+4]
    @endcode

    @par 128-bit version:
    @icost{NEON, 2-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 4-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1>
basic_int32x4 shuffle2(basic_int32x4 a, basic_int32x4 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    return shuffle2<s0,s1,s0,s1>(a, b);
}

template<unsigned s0, unsigned s1>
basic_int32x8 shuffle2(basic_int32x8 a, basic_int32x8 b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    return shuffle2<s0,s1,s0,s1>(a, b);
}
/// @}

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
