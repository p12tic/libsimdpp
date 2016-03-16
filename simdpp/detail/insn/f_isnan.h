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
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL mask_float32x4 i_isnan(const float32x4& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::isnan(a);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, a, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return (mask_float32x4) _mm_cmpunord_ps(a, a);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return cmp_neq(a, a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_isnan(const float32x8& a)
{
    return _mm256_cmp_ps(a, a, _CMP_UNORD_Q);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float32<16> i_isnan(const float32<16>& a)
{
    return _mm512_cmp_ps_mask(a, a, _CMP_UNORD_Q);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float64x2 i_isnan(const float64x2& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::isnan(a);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, a, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return _mm_cmpunord_pd(a, a);
#elif SIMDPP_USE_NEON64
    return cmp_neq(a, a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_isnan(const float64x4& a)
{
    return _mm256_cmp_pd(a, a, _CMP_UNORD_Q);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float64<8> i_isnan(const float64<8>& a)
{
    return _mm512_cmp_pd_mask(a, a, _CMP_UNORD_Q);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
typename V::mask_vector_type i_isnan(const V& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(typename V::mask_vector_type, i_isnan, a);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

