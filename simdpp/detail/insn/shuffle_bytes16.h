/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE_BYTES16_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE_BYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/i_add.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL uint8x16 i_shuffle_bytes16(const uint8x16& a, const uint8x16& b, const uint8x16& mask)
{
#if SIMDPP_USE_NULL
    uint8x16 ai = a;
    uint8x16 bi = b;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi.el(i) & 0x0f;
        unsigned which = mi.el(i) < 0x10;
        r.el(i) = which ? ai.el(j) : bi.el(j);
    }
    return r;
#elif SIMDPP_USE_XOP
    return _mm_perm_epi8(a, b, mask);
#elif SIMDPP_USE_SSE4_1
    int16x8 sel, ai, bi, r;
    sel = mask;
    sel = _mm_slli_epi16(sel, 3);

    ai = _mm_shuffle_epi8(a, mask);
    bi = _mm_shuffle_epi8(b, mask);
    r = _mm_blendv_epi8(ai, bi, sel);
    return (uint8<16>) r;
#elif SIMDPP_USE_SSSE3
    uint8x16 m, m1, m2, ai, bi;
    m = mask;
    // sets the 7-th bit if we want an element from the other vector
    m1 = add(m, 0x70);
    m2 = add(m, 0xf0);

    ai = _mm_shuffle_epi8(a, m1);
    bi = _mm_shuffle_epi8(b, m2);
    return bit_or(ai, bi);
#elif SIMDPP_USE_NEON32
    uint8x8x4_t table = {{vget_low_u8(a), vget_high_u8(a),
                          vget_low_u8(b), vget_high_u8(b)}};
    uint8x8_t lo = vtbl4_u8(table, vget_low_u8(mask));
    uint8x8_t hi = vtbl4_u8(table, vget_high_u8(mask));
    return vcombine_u8(lo, hi);
#elif SIMDPP_USE_NEON64
    uint8x16x2_t table;
    table.val[0] = a;
    table.val[1] = b;
    return vqtbl2q_u8(table, mask);
#elif SIMDPP_USE_ALTIVEC
    return vec_perm((__vector uint8_t)a, (__vector uint8_t)b,
                    (__vector uint8_t)mask);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, mask);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_shuffle_bytes16(const uint8x32& a, const uint8x32& b, const uint8x32& mask)
{
    int16x16 sel, ai, bi, r;
    sel = mask;
    sel = _mm256_slli_epi16(sel, 3); // the top 3 bits are already clear

    ai = _mm256_shuffle_epi8(a, mask);
    bi = _mm256_shuffle_epi8(b, mask);
    r = _mm256_blendv_epi8(ai, bi, sel);
    return (uint8<32>) r;
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_shuffle_bytes16(const uint8<N>& a, const uint8<N>& b, const uint8<N>& mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint8<N>, i_shuffle_bytes16, a, b, mask);
}

template<unsigned N> SIMDPP_INL
uint16<N> i_shuffle_bytes16(const uint16<N>& a, const uint16<N>& b, const uint16<N>& mask)
{
    return (uint16<N>) i_shuffle_bytes16(uint8<N*2>(a), uint8<N*2>(b), uint8<N*2>(mask));
}
template<unsigned N> SIMDPP_INL
uint32<N> i_shuffle_bytes16(const uint32<N>& a, const uint32<N>& b, const uint32<N>& mask)
{
    return (uint32<N>) i_shuffle_bytes16(uint8<N*4>(a), uint8<N*4>(b), uint8<N*4>(mask));
}
template<unsigned N> SIMDPP_INL
uint64<N> i_shuffle_bytes16(const uint64<N>& a, const uint64<N>& b, const uint64<N>& mask)
{
    return (uint64<N>) i_shuffle_bytes16(uint8<N*8>(a), uint8<N*8>(b), uint8<N*8>(mask));
}
template<unsigned N> SIMDPP_INL
float32<N> i_shuffle_bytes16(const float32<N>& a, const float32<N>& b, const uint32<N>& mask)
{
    return float32<N>(i_shuffle_bytes16(uint32<N>(a), uint32<N>(b), mask));
}
template<unsigned N> SIMDPP_INL
float64<N> i_shuffle_bytes16(const float64<N>& a, const float64<N>& b, const uint64<N>& mask)
{
    return float64<N>(i_shuffle_bytes16(uint64<N>(a), uint64<N>(b), mask));
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

