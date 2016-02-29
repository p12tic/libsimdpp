/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_SHUFFLE_H
#define LIBSIMDPP_SSE_SHUFFLE_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {

/// @{
/** Permutes the first 4 16-bit values in of each set of 8 consecutive valuees.
    The selector values @a s0, @a s1, @a s2 and @a s3 must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]
    r4 = a4
    ...
    r7 = a7

    256-bit version:
    r8 = a[s0+8]
    ...
    r11 = a[s3+8]
    r12 = a12
    ...
    r15 = a15
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
uint16x8 permute_lo(const uint16x8& a)
{
    SIMDPP_STATIC_ASSERT(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm_shufflelo_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
uint16x16 permute_lo(const uint16x16& a)
{
#if SIMDPP_USE_AVX2
    SIMDPP_STATIC_ASSERT(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shufflelo_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
#else
    uint16x16 r;
    r.vec(0) = permute_lo<s0,s1,s2,s3>(a.vec(0));
    r.vec(1) = permute_lo<s0,s1,s2,s3>(a.vec(1));
    return r;
#endif
}
/// @}


/// @{
/** Permutes the last 4 16-bit values in of each set of 8 consecutive valuees.
    The selector values @a s0, @a s1, @a s2 and @a s3 must be in range [0; 3].

    @code
    r0 = a0
    ...
    r3 = a3
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]

    256-bit version:
    r8 = a8
    ...
    r11 = a11
    r12 = a[s0+12]
    ...
    r15 = a[s3+12]
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
uint16x8 permute_hi(const uint16x8& a)
{
    SIMDPP_STATIC_ASSERT(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm_shufflehi_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
uint16x16 permute_hi(const uint16x16& a)
{
#if SIMDPP_USE_AVX2
    SIMDPP_STATIC_ASSERT(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shufflehi_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
#else
    uint16x16 r;
    r.vec(0) = permute_hi<s0,s1,s2,s3>(a.vec(0));
    r.vec(1) = permute_hi<s0,s1,s2,s3>(a.vec(1));
    return r;
#endif
}
/// @}

} // namespace sse
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif

