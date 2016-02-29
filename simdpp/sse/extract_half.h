/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_EXTRACT_HALF_H
#define LIBSIMDPP_SSE_EXTRACT_HALF_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {

/// @{
/** Extracts the lower half of a 256-bit vector
    @icost{0}
*/
SIMDPP_INL uint8x16 extract_lo(const uint8x32& a)
{
#if SIMDPP_USE_AVX2
    return _mm256_castsi256_si128(a);
#else
    return a.vec(0);
#endif
}

SIMDPP_INL uint16x8 extract_lo(const uint16x16& a) { return (uint16x8) extract_lo(uint8x32(a)); }
SIMDPP_INL uint32x4 extract_lo(const uint32x8& a) { return (uint32x4) extract_lo(uint8x32(a)); }
SIMDPP_INL uint64x2 extract_lo(const uint64x4& a) { return (uint64x2) extract_lo(uint8x32(a)); }

SIMDPP_INL int8x16 extract_lo(const int8x32& a) { return (int8x16) extract_lo(uint8x32(a)); }
SIMDPP_INL int16x8 extract_lo(const int16x16& a) { return (int16x8) extract_lo(uint8x32(a)); }
SIMDPP_INL int32x4 extract_lo(const int32x8& a) { return (int32x4) extract_lo(uint8x32(a)); }
SIMDPP_INL int64x2 extract_lo(const int64x4& a) { return (int64x2) extract_lo(uint8x32(a)); }

SIMDPP_INL float32x4 extract_lo(const float32x8& a)
{
#if SIMDPP_USE_AVX
    return _mm256_castps256_ps128(a);
#else
    return a.vec(0);
#endif
}

SIMDPP_INL float64x2 extract_lo(const float64x4& a)
{
#if SIMDPP_USE_AVX
    return _mm256_castpd256_pd128(a);
#else
    return a.vec(0);
#endif
}
/// @}

/// @{
/** Extracts the higher half of a 256-bit vector
    @icost{0}
*/
SIMDPP_INL uint8x16 extract_hi(const uint8x32& a)
{
#if SIMDPP_USE_AVX2
    return _mm256_extracti128_si256(a, 1);
#else
    return a.vec(1);
#endif
}

SIMDPP_INL uint16x8 extract_hi(const uint16x16& a) { return (uint16x8) extract_hi(uint8x32(a)); }
SIMDPP_INL uint32x4 extract_hi(const uint32x8& a) { return (uint32x4) extract_hi(uint8x32(a)); }
SIMDPP_INL uint64x2 extract_hi(const uint64x4& a) { return (uint64x2) extract_hi(uint8x32(a)); }

SIMDPP_INL int8x16 extract_hi(const int8x32& a) { return (int8x16) extract_hi(uint8x32(a)); }
SIMDPP_INL int16x8 extract_hi(const int16x16& a) { return (int16x8) extract_hi(uint8x32(a)); }
SIMDPP_INL int32x4 extract_hi(const int32x8& a) { return (int32x4) extract_hi(uint8x32(a)); }
SIMDPP_INL int64x2 extract_hi(const int64x4& a) { return (int64x2) extract_hi(uint8x32(a)); }

SIMDPP_INL float32x4 extract_hi(const float32x8& a)
{
#if SIMDPP_USE_AVX
    return _mm256_extractf128_ps(a, 1);
#else
    return a.vec(1);
#endif
}

SIMDPP_INL float64x2 extract_hi(const float64x4& a)
{
#if SIMDPP_USE_AVX
    return _mm256_extractf128_pd(a, 1);
#else
    return a.vec(1);
#endif
}
/// @}

} // namespace sse
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
