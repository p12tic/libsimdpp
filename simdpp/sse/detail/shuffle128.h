/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_DETAIL_SHUFFLE128_H
#define LIBSIMDPP_SSE_DETAIL_SHUFFLE128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace sse {
namespace detail {

/// @{
/** Shuffles 128 bit parts within the vectors.

@code
    switch(s0):
        case 0: r[0..127] = a[0..127]
        case 1: r[0..127] = a[128..255]
        case 2: r[0..127] = b[0..127]
        case 3: r[0..127] = b[128..255]

    switch(s1):
        case 0: r[128..255] = a[0..127]
        case 1: r[128..255] = a[128..255]
        case 2: r[128..255] = b[0..127]
        case 3: r[128..255] = b[128..255]
@endcode
*/
template<unsigned s0, unsigned s1>
int256 shuffle128(int256 a, int256 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX2
    return _mm256_permute2x128_si256(a, b, s1*0x10 + s0);
#else
    return {a[s0], b[s1]};
#endif
}
template<unsigned s0, unsigned s1>
float32x8 shuffle128(float32x8 a, float32x8 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_permute2f128_ps(a, b, s1*0x10 + s0);
#else
    return {a[s0], b[s1]};
#endif
}
template<unsigned s0, unsigned s1>
float64x4 shuffle128(float64x4 a, float64x4 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_permute2f128_pd(a, b, s1*0x10 + s0);
#else
    return {a[s0], b[s1]};
#endif
}
/// @}

} // namespace detail
} // namespace sse
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif

