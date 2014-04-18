/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE128_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

/// @{
/** Shuffles 128 bit parts within the vectors.

    For larger than 256-bits vectors the same operation is applied to each
    256-bit element.

@code
    switch(s0):
        case 0: r[0..127] = a[0..127]
        case 1: r[0..127] = a[128..255]

    switch(s1):
        case 0: r[128..255] = b[0..127]
        case 1: r[128..255] = b[128..255]
@endcode
*/
template<unsigned s0, unsigned s1>
uint8x32 shuffle1_128(uint8x32 a, uint8x32 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX2
    return _mm256_permute2x128_si256(a, b, s1*0x10 + s0);
#else
    uint8x32 r;
    r[0] = a[s0];
    r[1] = b[s1];
    return r;
#endif
}
template<unsigned s0, unsigned s1>
uint16x16 shuffle1_128(uint16x16 a, uint16x16 b) { return (uint16x16)shuffle1_128<s0,s1>(uint8x32(a), uint8x32(b)); }
template<unsigned s0, unsigned s1>
uint32x8 shuffle1_128(uint32x8 a, uint32x8 b) { return (uint32x8)shuffle1_128<s0,s1>(uint8x32(a), uint8x32(b)); }
template<unsigned s0, unsigned s1>
uint64x4 shuffle1_128(uint64x4 a, uint64x4 b) { return (uint64x4)shuffle1_128<s0,s1>(uint8x32(a), uint8x32(b)); }

template<unsigned s0, unsigned s1>
float32x8 shuffle1_128(float32x8 a, float32x8 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_permute2f128_ps(a, b, s1*0x10 + s0);
#else
    float32x8 r;
    r[0] = a[s0];
    r[1] = b[s1];
    return r;
#endif
}
template<unsigned s0, unsigned s1>
float64x4 shuffle1_128(float64x4 a, float64x4 b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
#if SIMDPP_USE_AVX
    return _mm256_permute2f128_pd(a, b, s1*0x10 + s0);
#else
    float64x4 r;
    r[0] = a[s0];
    r[1] = b[s1];
    return r;
#endif
}
/// @}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

