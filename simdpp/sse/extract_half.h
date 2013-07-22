/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_EXTRACT_HALF_H
#define LIBSIMDPP_SSE_EXTRACT_HALF_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/types.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace sse {

/// @{
/** Extracts the lower half of a 256-bit vector
    @icost{0}
*/
inline int128 extract_lo(int256 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_castsi256_si128(a);
#else
    return a[0];
#endif
}

inline basic_int8x16 extract_lo(basic_int8x32 a) { return extract_lo(int256(a)); }
inline basic_int16x8 extract_lo(basic_int16x16 a) { return extract_lo(int256(a)); }
inline basic_int32x4 extract_lo(basic_int32x8 a) { return extract_lo(int256(a)); }
inline basic_int64x2 extract_lo(basic_int64x4 a) { return extract_lo(int256(a)); }

inline float32x4 extract_lo(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_castps256_ps128(a);
#else
    return a[0];
#endif
}

inline float64x2 extract_lo(float64x4 a)
{
#if SIMDPP_USE_AVX
    return _mm256_castpd256_pd128(a);
#else
    return a[0];
#endif
}
/// @}

/// @{
/** Extracts the higher half of a 256-bit vector
    @icost{0}
*/
inline int128 extract_hi(int256 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_extracti128_si256(a, 1);
#else
    return a[1];
#endif
}

inline basic_int8x16 extract_hi(basic_int8x32 a) { return extract_hi(int256(a)); }
inline basic_int16x8 extract_hi(basic_int16x16 a) { return extract_hi(int256(a)); }
inline basic_int32x4 extract_hi(basic_int32x8 a) { return extract_hi(int256(a)); }
inline basic_int64x2 extract_hi(basic_int64x4 a) { return extract_hi(int256(a)); }

inline float32x4 extract_hi(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_extractf128_ps(a, 1);
#else
    return a[1];
#endif
}

inline float64x2 extract_hi(float64x4 a)
{
#if SIMDPP_USE_AVX
    return _mm256_extractf128_pd(a, 1);
#else
    return a[1];
#endif
}
/// @}

} // namespace sse
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
