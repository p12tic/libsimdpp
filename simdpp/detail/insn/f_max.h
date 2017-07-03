/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_MAX_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_MAX_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL float32x4 i_max(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_SSE2
    return _mm_max_ps(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector float)a, (__vector float)b);
#else
    return detail::null::max(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_max(const float32x8& a, const float32x8& b)
{
    return _mm256_max_ps(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_max(const float32<16>& a, const float32<16>& b)
{
    return _mm512_max_ps(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_max(const float32<N>& a, const float32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL float64x2 i_max(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_SSE2
    return _mm_max_pd(a, b);
#elif SIMDPP_USE_NEON64
    return vmaxq_f64(a, b);
#else
    return detail::null::max(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float64x4 i_max(const float64x4& a, const float64x4& b)
{
    return _mm256_max_pd(a, b);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float64<8> i_max(const float64<8>& a, const float64<8>& b)
{
    return _mm512_max_pd(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
float64<N> i_max(const float64<N>& a, const float64<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_max, a, b);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

