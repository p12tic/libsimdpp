/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_GE_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_GE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/null/compare.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline mask_float32x4 i_cmp_ge(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_ge(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_GE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpge_ps(a, b);
#elif SIMDPP_USE_NEON
    return vcgeq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_cmpge((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32x8 i_cmp_ge(float32x8 a, float32x8 b)
{
    return _mm256_cmp_ps(a, b, _CMP_GE_OQ);
}
#endif

template<unsigned N>
mask_float32<N> i_cmp_ge(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_cmp_ge, a, b);
}

// -----------------------------------------------------------------------------

inline mask_float64x2 i_cmp_ge(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_ge(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_GE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpge_pd(a, b);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64x4 i_cmp_ge(float64x4 a, float64x4 b)
{
    return _mm256_cmp_pd(a, b, _CMP_GE_OQ);
}
#endif

template<unsigned N>
mask_float64<N> i_cmp_ge(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_cmp_ge, a, b);
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

