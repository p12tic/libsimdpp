/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_MIN_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_MIN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float32x4 i_min(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_ps(a, b);
#elif SIMDPP_USE_NEON
    return vminq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_min(float32x8 a, float32x8 b)
{
    return _mm256_min_ps(a, b);
}
#endif

template<unsigned N>
float32<N> i_min(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_min, a, b);
}

// -----------------------------------------------------------------------------

inline float64x2 i_min(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_pd(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline float64x4 i_min(float64x4 a, float64x4 b)
{
    return _mm256_min_pd(a, b);
}
#endif

template<unsigned N>
float64<N> i_min(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_min, a, b);
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

