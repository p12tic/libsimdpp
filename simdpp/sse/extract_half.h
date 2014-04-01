/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_EXTRACT_HALF_H
#define LIBSIMDPP_SSE_EXTRACT_HALF_H
#if SIMDPP_USE_SSE2 || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace sse {

/// @{
/** Extracts the lower half of a 256-bit vector
    @icost{0}
*/
inline uint8x16 extract_lo(uint8x32 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_castsi256_si128(a);
#else
    return a[0];
#endif
}

inline uint16x8 extract_lo(uint16x16 a) { return (uint16x8) extract_lo(uint8x32(a)); }
inline uint32x4 extract_lo(uint32x8 a) { return (uint32x4) extract_lo(uint8x32(a)); }
inline uint64x2 extract_lo(uint64x4 a) { return (uint64x2) extract_lo(uint8x32(a)); }

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
inline uint8x16 extract_hi(uint8x32 a)
{
#if SIMDPP_USE_AVX2
    return _mm256_extracti128_si256(a, 1);
#else
    return a[1];
#endif
}

inline uint16x8 extract_hi(uint16x16 a) { return (uint16x8) extract_hi(uint8x32(a)); }
inline uint32x4 extract_hi(uint32x8 a) { return (uint32x4) extract_hi(uint8x32(a)); }
inline uint64x2 extract_hi(uint64x4 a) { return (uint64x2) extract_hi(uint8x32(a)); }

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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
