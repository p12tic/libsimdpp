/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ISNAN_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ISNAN_H

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


inline mask_float32x4 i_isnan(float32x4 a)
{
#if SIMDPP_USE_NULL
    return null::isnan(a);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, a, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return (mask_float32x4) _mm_cmpunord_ps(a, a);
#elif SIMDPP_USE_NEON
    return vceqq_f32(a, a);
#elif SIMDPP_USE_ALTIVEC
    return (mask_float32x4) vec_cmpeq((__vector float)a, (__vector float)a);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32x8 i_isnan(float32x8 a)
{
    return _mm256_cmp_ps(a, a, _CMP_UNORD_Q);
}
#endif

template<unsigned N>
mask_float32<N> i_isnan(float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_float32<N>, i_isnan, a);
}

// -----------------------------------------------------------------------------

inline mask_float64x2 i_isnan(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::isnan(a);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, a, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return _mm_cmpunord_pd(a, a);
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64x4 i_isnan(float64x4 a)
{
    return _mm256_cmp_pd(a, a, _CMP_UNORD_Q);
}
#endif

template<unsigned N>
mask_float64<N> i_isnan(float64<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_float64<N>, i_isnan, a);
}
/// @}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

