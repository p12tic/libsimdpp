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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE2_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/null/shuffle.h>
#include <simdpp/sse/shuffle.h>
#include <simdpp/neon/detail/shuffle_int16x8.h>
#include <simdpp/neon/detail/shuffle_int32x4.h>
#include <simdpp/neon/detail/shuffle_int64x2.h>
#include <simdpp/detail/insn/shuffle_emul.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// fwd decl
template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
uint32x4 i_shuffle2(uint32x4 a, uint32x4 b);

template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
float32x4 i_shuffle2(float32x4 a, float32x4 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    return float32x4(i_shuffle2<a0,a1,b0,b1>(int32x4(a), int32x4(b)));
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

#if SIMDPP_USE_AVX
template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
float32x8 i_shuffle2(float32x8 a, float32x8 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
    return _mm256_shuffle_ps(a, b, _MM_SHUFFLE(b1, b0, a1, a0));
}
#endif

template<unsigned a0, unsigned a1, unsigned b0, unsigned b1, unsigned N>
float32<N> i_shuffle2(float32<N> a, float32<N> b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL2(float32x8, (i_shuffle2<a0,a1,b0,b1>), a, b);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned N>
float32<N> i_shuffle2(float32<N> a, float32<N> b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    return i_shuffle2<s0,s1,s0,s1>(a, b);
}

// -----------------------------------------------------------------------------

template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
uint32x4 i_shuffle2(uint32x4 a, uint32x4 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::shuffle2<a0,a1,b0,b1>(a, b);
#elif SIMDPP_USE_SSE2
    // We can't do this in the integer execution domain. Beware of additional latency
    return uint32x4(i_shuffle2<a0,a1,b0,b1>(float32x4(a), float32x4(b)));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int32x4::shuffle2<a0,a1,b0,b1>(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 mask = make_shuffle_bytes16_mask<a0,a1,b0+4,b1+4>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned a0, unsigned a1, unsigned b0, unsigned b1>
uint32x8 i_shuffle2(uint32x8 a, uint32x8 b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
    // We can't do this in the integer execution domain. Beware of additional latency
    return int32x8(i_shuffle2<a0,a1,b0,b1>(float32x8(a), float32x8(b)));
}
#endif

template<unsigned a0, unsigned a1, unsigned b0, unsigned b1, unsigned N>
uint32<N> i_shuffle2(uint32<N> a, uint32<N> b)
{
    static_assert(a0 < 4 && a1 < 4 && b0 < 4 && b1 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, (i_shuffle2<a0,a1,b0,b1>), a, b);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned N>
uint32<N> i_shuffle2(uint32<N> a, uint32<N> b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    return i_shuffle2<s0,s1,s0,s1>(a, b);
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

