/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_EXTRACT128_H
#define LIBSIMDPP_DETAIL_EXTRACT128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

#if SIMDPP_USE_AVX2
template<unsigned s>
SIMDPP_INL uint8x16 extract128(const uint8x32& a)
{
    return s == 0 ? _mm256_castsi256_si128(a) : _mm256_extracti128_si256(a, 1);
}

template<unsigned s>
SIMDPP_INL uint16x8 extract128(const uint16x16& a) { return (uint16x8) extract128<s>(uint8x32(a)); }
template<unsigned s>
SIMDPP_INL uint32x4 extract128(const uint32x8& a) { return (uint32x4) extract128<s>(uint8x32(a)); }
template<unsigned s>
SIMDPP_INL uint64x2 extract128(const uint64x4& a) { return (uint64x2) extract128<s>(uint8x32(a)); }

template<unsigned s>
SIMDPP_INL int8x16 extract128(const int8x32& a) { return (int8x16) extract128<s>(uint8x32(a)); }
template<unsigned s>
SIMDPP_INL int16x8 extract128(const int16x16& a) { return (int16x8) extract128<s>(uint8x32(a)); }
template<unsigned s>
SIMDPP_INL int32x4 extract128(const int32x8& a) { return (int32x4) extract128<s>(uint8x32(a)); }
template<unsigned s>
SIMDPP_INL int64x2 extract128(const int64x4& a) { return (int64x2) extract128<s>(uint8x32(a)); }
#endif

#if SIMDPP_USE_AVX
template<unsigned s>
SIMDPP_INL float32x4 extract128(const float32x8& a)
{
    return s == 0 ? _mm256_castps256_ps128(a) : _mm256_extractf128_ps(a, 1);
}

template<unsigned s>
SIMDPP_INL float64x2 extract128(const float64x4& a)
{
    return s == 0 ? _mm256_castpd256_pd128(a) : _mm256_extractf128_pd(a, 1);
}
#endif

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
