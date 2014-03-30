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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE2_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/permute4.h>
#include <simdpp/null/shuffle.h>
#include <simdpp/sse/shuffle.h>
#include <simdpp/neon/detail/shuffle_int16x8.h>
#include <simdpp/neon/detail/shuffle_int32x4.h>
#include <simdpp/neon/detail/shuffle_int64x2.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


template<unsigned s0, unsigned s1, unsigned N>
uint16<N> i_permute2(uint16<N> a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return i_permute4<s0,s1,s0+2,s1+2>(a);
}


template<unsigned s0, unsigned s1, unsigned N>
uint32<N> i_permute2(uint32<N> a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return i_permute4<s0,s1,s0+2,s1+2>(a);
}


template<unsigned s0, unsigned s1, unsigned N>
float32<N> i_permute2(float32<N> a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return i_permute4<s0,s1,s0+2,s1+2>(a);
}


template<unsigned s0, unsigned s1>
uint64x2 i_permute2(uint64x2 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1>(a);
#elif SIMDPP_USE_SSE2
    return (uint64x2) i_permute4<s0*2, s0*2+1, s1*2, s1*2+1>(int32x4(a));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int64x2::permute2<s0,s1>(a);
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint64x2 mask = make_shuffle_bytes16_mask<s0,s1>(mask);
    return permute_bytes16(a, mask);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s0, unsigned s1>
uint64x4 i_permute2(uint64x4 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return _mm256_permute4x64_epi64(a, s0 | s1<<2 | (s0+2)<<4 | (s1+2)<<6);
}
#endif

template<unsigned s0, unsigned s1, unsigned N>
uint64<N> i_permute2(uint64<N> a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return i_permute4<s0,s1,s0+2,s1+2>(a);
}


template<unsigned s0, unsigned s1>
float64x2 i_permute2(float64x2 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_SSE2
    return _mm_shuffle_pd(a, a, _MM_SHUFFLE2(s1, s0));
#else
    return float64x2(i_permute2<s0,s1>(int64x2(a)));
#endif
}

#if SIMDPP_USE_AVX
template<unsigned s0, unsigned s1>
float64x4 i_permute2(float64x4 a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX2
    return _mm256_permute4x64_pd(a, s0 | s1<<2 | (s0+2)<<4 | (s1+2)<<6);
#else // SIMDPP_USE_AVX
    return _mm256_permute_pd(a, s0 | s1<<1 | s0<<2 | s1<<3);
#endif
}
#endif

template<unsigned s0, unsigned s1, unsigned N>
float64<N> i_permute2(float64<N> a)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return permute4<s0,s1,s0+2,s1+2>(a);
}
/// @}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

