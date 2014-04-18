/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_COMBINE_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_COMBINE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

#if SIMDPP_USE_AVX2
template<class V = void>
uint8<32> i_combine(uint8<16> a, uint8<16> b)
{
    uint8<32> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX2
template<class V = void>
uint16<16> i_combine(uint16<8> a, uint16<8> b)
{
    uint16<16> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX2
template<class V = void>
uint32<8> i_combine(uint32<4> a, uint32<4> b)
{
    uint32<8> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX2
template<class V = void>
uint64<4> i_combine(uint64<2> a, uint64<2> b)
{
    uint64<4> r;
    r = _mm256_castsi128_si256(a);
    r = _mm256_inserti128_si256(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX
template<class V = void>
float32<8> i_combine(float32<4> a, float32<4> b)
{
    float32<8> r;
    r = _mm256_castps128_ps256(a);
    r = _mm256_insertf128_ps(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_AVX
template<class V = void>
float64<4> i_combine(float64<2> a, float64<2> b)
{
    float64<4> r;
    r = _mm256_castpd128_pd256(a);
    r = _mm256_insertf128_pd(r, b, 1);
    return r;
}
#endif

// -----------------------------------------------------------------------------
// generic implementation
template<class V, class H>
V i_combine(H a1, H a2)
{
    V r;
    unsigned h = H::vec_length;
    for (unsigned i = 0; i < h; ++i) { r[i] = a1[i]; }
    for (unsigned i = 0; i < h; ++i) { r[i+h] = a2[i]; }
    return r;
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif