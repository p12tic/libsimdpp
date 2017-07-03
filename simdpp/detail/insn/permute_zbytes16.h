/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE_ZBYTES16_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE_ZBYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/permute_bytes16.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL uint8x16 i_permute_zbytes16(const uint8x16& a, const uint8x16& mask)
{
#if SIMDPP_USE_SSSE3 || SIMDPP_USE_NEON
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_ALTIVEC
    int8x16 a0 = a;
    int8x16 zero_mask = mask;
    zero_mask = shift_r<7>(zero_mask); // shift in the sign bit
    a0 = i_permute_bytes16(a0, mask);
    a0 = bit_andnot(a0, zero_mask);
    return a0;
#else
    uint8x16 ai = a;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi.el(i) & 0x0f;
        bool zero = mi.el(i) & 0x80;
        r.el(i) = zero ? 0 : ai.el(j);
    }
    return r;
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_permute_zbytes16(const uint8x32& a, const uint8x32& mask)
{
    return _mm256_shuffle_epi8(a, mask);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_permute_zbytes16(const uint8<N>& a, const uint8<N>& mask)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_permute_zbytes16, a, mask);
}
template<unsigned N> SIMDPP_INL
uint16<N> i_permute_zbytes16(const uint16<N>& a, const uint16<N>& mask)
{
    return (uint16<N>) i_permute_zbytes16(uint8<N*2>(a), uint8<N*2>(mask));
}
template<unsigned N> SIMDPP_INL
uint32<N> i_permute_zbytes16(const uint32<N>& a, const uint32<N>& mask)
{
    return (uint32<N>) i_permute_zbytes16(uint8<N*4>(a), uint8<N*4>(mask));
}
template<unsigned N> SIMDPP_INL
uint64<N> i_permute_zbytes16(const uint64<N>& a, const uint64<N>& mask)
{
    return (uint64<N>) i_permute_zbytes16(uint8<N*8>(a), uint8<N*8>(mask));
}
template<unsigned N> SIMDPP_INL
float32<N> i_permute_zbytes16(const float32<N>& a, const uint32<N>& mask)
{
    return float32<N>(i_permute_zbytes16(uint32<N>(a), mask));
}
template<unsigned N> SIMDPP_INL
float64<N> i_permute_zbytes16(const float64<N>& a, const uint64<N>& mask)
{
    return float64<N>(i_permute_zbytes16(uint64<N>(a), mask));
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

