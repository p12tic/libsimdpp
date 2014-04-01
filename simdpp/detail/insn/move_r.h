/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_R_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


template<unsigned shift>
uint8x16 i_move16_r(uint8x16 a)
{
    static_assert(shift <= 16, "Selector out of range");

#if SIMDPP_USE_NULL
    uint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)shift; i++) {
        r.el(i) = 0;
    }
    for (unsigned i = shift; i < 16; i++) {
        r.el(i) = a.el(i - shift);
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_slli_si128(a, shift);
#elif SIMDPP_USE_NEON
    uint8x16 z = uint8x16::zero();
    return vextq_u8(z, a, 16-shift);
#elif SIMDPP_USE_ALTIVEC
    // return align<16-shift>(uint8x16::zero(), a);
    return vec_sld((__vector uint8_t)uint8x16::zero(), (__vector uint8_t)a, 16-shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
uint8x32 i_move16_r(uint8x32 a)
{
    static_assert(shift <= 16, "Selector out of range");
    return _mm256_slli_si256(a, shift);
}
#endif

template<unsigned shift, unsigned N>
uint8<N> i_move16_r(uint8<N> a)
{
    static_assert(shift <= 16, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_move16_r<shift>, a);
}

template<unsigned shift, unsigned N>
uint16<N> i_move8_r(uint16<N> a)
{
    return uint16<N>(i_move16_r<shift*2>(uint8<N*2>(a)));
}

template<unsigned shift, unsigned N>
uint32<N> i_move4_r(uint32<N> a)
{
    return uint32<N>(i_move16_r<shift*4>(uint8<N*4>(a)));
}

template<unsigned shift, unsigned N>
uint64<N> i_move2_r(uint64<N> a)
{
    return uint64<N>(i_move16_r<shift*8>(uint8<N*8>(a)));
}

template<unsigned shift, unsigned N>
float32<N> i_move4_r(float32<N> a)
{
    return float32<N>(i_move4_r<shift>(uint32<N>(a)));
}

template<unsigned shift, unsigned N>
float64<N> i_move2_r(float64<N> a)
{
    return float64<N>(i_move2_r<shift>(uint64<N>(a)));
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

