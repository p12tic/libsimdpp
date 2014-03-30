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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE1_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE1_H

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

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// fwd declarations
template<unsigned s0, unsigned s1>
uint64x2 i_shuffle1(uint64x2 a, uint64x2 b);

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1>
float64x2 i_shuffle1(float64x2 a, float64x2 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return float64x2(i_shuffle1<s0,s1>(int64x2(a), int64x2(b)));
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

#if SIMDPP_USE_AVX
template<unsigned s0, unsigned s1>
float64x4 i_shuffle1(float64x4 a, float64x4 b)
{
    return _mm256_shuffle_pd(a, b, s0 | s1<<1 | s0<<2 | s1<<3);
}
#endif

template<unsigned s0, unsigned s1, unsigned N>
float64<N> i_shuffle1(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, (i_shuffle1<s0,s1>), a, b);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1>
uint64x2 i_shuffle1(uint64x2 a, uint64x2 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::shuffle1<s0,s1>(a, b);
#elif SIMDPP_USE_SSE2
    // We can't do this in the integer execution domain. Beware of additional latency
    return int64x2(i_shuffle1<s0,s1>(float64x2(a), float64x2(b)));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int64x2::shuffle1<s0,s1>(a, b);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 mask = make_shuffle_bytes16_mask<s0,s1+2>(mask);
    return shuffle_bytes16(a, b, mask);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s0, unsigned s1>
uint64x4 i_shuffle1(uint64x4 a, uint64x4 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    // We can't do this in the integer execution domain. Beware of additional latency
    return int64x4(shuffle1<s0,s1>(float64x4(a), float64x4(b)));
}
#endif

template<unsigned s0, unsigned s1, unsigned N>
uint64<N> i_shuffle1(uint64<N> a, uint64<N> b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return int64<N>(i_shuffle1<s0,s1>(float64<N>(a), float64<N>(b)));
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

