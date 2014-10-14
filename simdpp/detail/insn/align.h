/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ALIGN_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ALIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/move_r.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


// base 8x16 implementation
template<unsigned shift> SIMDPP_INL
uint8x16 i_align16(const uint8x16& clower, const uint8x16& cupper)
{
    uint8x16 lower = clower, upper = cupper;
#if SIMDPP_USE_NULL
    uint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)(16-shift); i++) {
        r.el(i) = lower.el(i + shift);
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r.el(i) = upper.el(i - 16 + shift);
    }
    return r;
#elif SIMDPP_USE_SSSE3
    return _mm_alignr_epi8(upper, lower, shift);
#elif SIMDPP_USE_SSE2
    uint8x16 a;
    lower = move16_l<shift>(lower);
    upper = move16_r<16-shift>(upper);
    a = bit_or(upper, lower);
    return a;
#elif SIMDPP_USE_NEON
    return vextq_u8(lower, upper, shift);
#elif SIMDPP_USE_ALTIVEC
    return vec_sld((__vector uint8_t)lower, (__vector uint8_t)upper, (unsigned)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift> SIMDPP_INL
uint8x32 i_align16(const uint8x32& lower, const uint8x32& upper)
{
    return _mm256_alignr_epi8(upper, lower, shift);
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
uint8<N> i_align16(const uint8<N>& lower, const uint8<N>& upper)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_align16<shift>, lower, upper);
}

// generic implementations

template<unsigned shift, unsigned N> SIMDPP_INL
uint16<N> i_align8(const uint16<N>& lower, const uint16<N>& upper)
{
    return uint16<N>(i_align16<shift*2>(uint8<N*2>(lower),
                                        uint8<N*2>(upper)));
}

template<unsigned shift, unsigned N> SIMDPP_INL
uint32<N> i_align4(const uint32<N>& lower, const uint32<N>& upper)
{
    return uint32<N>(i_align16<shift*4>(uint8<N*4>(lower),
                                        uint8<N*4>(upper)));
}

template<unsigned shift, unsigned N> SIMDPP_INL
uint64<N> i_align2(const uint64<N>& lower, const uint64<N>& upper)
{
    return uint64<N>(i_align16<shift*8>(uint8<N*8>(lower),
                                        uint8<N*8>(upper)));
}

template<unsigned shift, unsigned N> SIMDPP_INL
float32<N> i_align4(const float32<N>& lower, const float32<N>& upper)
{
    return float32<N>(i_align4<shift>(uint32<N>(lower),
                                      uint32<N>(upper)));
}

template<unsigned shift, unsigned N> SIMDPP_INL
float64<N> i_align2(const float64<N>& lower, const float64<N>& upper)
{
    return float64<N>(i_align2<shift>(uint64<N>(lower),
                                      uint64<N>(upper)));
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

