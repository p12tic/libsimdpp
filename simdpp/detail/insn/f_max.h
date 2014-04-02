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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float32x4 i_max(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_ps(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_max(float32x8 a, float32x8 b)
{
    return _mm256_max_ps(a, b);
}
#endif

template<unsigned N>
float32<N> i_max(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_max, a, b);
}

// -----------------------------------------------------------------------------

inline float64x2 i_max(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_pd(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline float64x4 i_max(float64x4 a, float64x4 b)
{
    return _mm256_max_pd(a, b);
}
#endif

template<unsigned N>
float64<N> i_max(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_max, a, b);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

