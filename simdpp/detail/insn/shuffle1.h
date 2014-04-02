/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE1_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE1_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/detail/null/shuffle.h>
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
    return detail::null::shuffle1<s0,s1>(a, b);
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
    return int64x4(i_shuffle1<s0,s1>(float64x4(a), float64x4(b)));
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

