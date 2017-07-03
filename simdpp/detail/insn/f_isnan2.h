/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_ISNAN2_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_ISNAN2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/f_isnan.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL mask_float32x4 i_isnan2(const float32x4& a, const float32x4& b)
{
#if SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return (mask_float32x4) _mm_cmpunord_ps(a, b);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return bit_or(isnan(a), isnan(b));
#else
    return detail::null::isnan2(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_isnan2(const float32x8& a, const float32x8& b)
{
    return _mm256_cmp_ps(a, b, _CMP_UNORD_Q);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float32<16> i_isnan2(const float32<16>& a, const float32<16>& b)
{
    return _mm512_cmp_ps_mask(a, b, _CMP_UNORD_Q);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float64x2 i_isnan2(const float64x2& a, const float64x2& b)
{
#if SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return _mm_cmpunord_pd(a, b);
#elif SIMDPP_USE_NEON64
    return bit_or(isnan(a), isnan(b));
#else
    return detail::null::isnan2(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_isnan2(const float64x4& a, const float64x4& b)
{
    return _mm256_cmp_pd(a, b, _CMP_UNORD_Q);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL mask_float64<8> i_isnan2(const float64<8>& a, const float64<8>& b)
{
    return _mm512_cmp_pd_mask(a, b, _CMP_UNORD_Q);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
typename V::mask_vector_type i_isnan2(const V& a, const V& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(typename V::mask_vector_type, i_isnan2, a, b);
}
/// @}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

