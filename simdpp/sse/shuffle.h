/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SSE_SHUFFLE_H
#define LIBSIMDPP_SSE_SHUFFLE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
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
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
basic_int16x8 permute_lo(basic_int16x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    a = _mm_shufflelo_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
    return a;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
basic_int16x16 permute_lo(basic_int16x16 a)
{
#if SIMDPP_USE_AVX2
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    a = _mm256_shufflelo_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
    return a;
#else
    return {permute_lo<s0,s1,s2,s3>(a[0]), permute_lo<s0,s1,s2,s3>(a[1])};
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
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
basic_int16x8 permute_hi(basic_int16x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    a = _mm_shufflehi_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
    return a;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
basic_int16x16 permute_hi(basic_int16x16 a)
{
#if SIMDPP_USE_AVX2
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    a = _mm256_shufflehi_epi16(a, _MM_SHUFFLE(s3, s2, s1, s0));
    return a;
#else
    return {permute_hi<s0,s1,s2,s3>(a[0]), permute_hi<s0,s1,s2,s3>(a[1])};
#endif
}
/// @}

} // namespace sse
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

