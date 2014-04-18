/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_L_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_L_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/permute4.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


template<unsigned shift>
uint8x16 i_move16_l(uint8x16 a)
{
    static_assert(shift <= 16, "Selector out of range");

#if SIMDPP_USE_NULL
    uint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int) (16-shift); i++) {
        r.el(i) = a.el(i + shift);
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r.el(i) = 0;
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_srli_si128(a, shift);
#elif SIMDPP_USE_NEON
    int8x16 z = int8x16::zero();
    return vextq_u8(a, z, shift);
#elif SIMDPP_USE_ALTIVEC
    // return align<shift>(a, uint8x16::zero());
    return vec_sld((__vector uint8_t)a, (__vector uint8_t)uint8x16::zero(), shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
uint8x32 i_move16_l(uint8x32 a)
{
    static_assert(shift <= 16, "Selector out of range");
    return _mm256_srli_si256(a, shift);
}
#endif

template<unsigned shift, unsigned N>
uint8<N> i_move16_l(uint8<N> a)
{
    static_assert(shift <= 16, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_move16_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift, unsigned N>
uint16<N> i_move8_l(uint16<N> a)
{
    return uint16<N>(i_move16_l<shift*2>(uint8<N*2>(a)));
}

// -----------------------------------------------------------------------------

template<unsigned shift>
uint32<4> i_move4_l(uint32<4> a)
{
    return (uint32<4>) i_move16_l<shift*4>(uint8<16>(a));
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
uint32<8> i_move4_l(uint32<8> a)
{
    static_assert(shift <= 4, "Selector out of range");
    return _mm256_srli_si256(a, shift*4);
}
#endif

#if SIMDPP_USE_AVX512
template<unsigned shift>
uint32<16> i_move4_l(uint32<16> a)
{
    static_assert(shift <= 4, "Selector out of range");
    switch (shift) {
    case 0: return a;
    case 1: return _mm512_maskz_shuffle_epi32(0x7777, a, _MM_SHUFFLE(3, 3, 2, 1));
    case 2: return _mm512_maskz_shuffle_epi32(0x3333, a, _MM_SHUFFLE(3, 3, 3, 2));
    case 3: return _mm512_maskz_shuffle_epi32(0x1111, a, _MM_SHUFFLE(3, 3, 3, 3));
    case 4: return uint32<16>::zero();
    }
}
#endif

template<unsigned shift, unsigned N>
uint32<N> i_move4_l(uint32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, i_move4_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift>
uint64<2> i_move2_l(uint64<2> a)
{
    return (uint64<2>) i_move16_l<shift*8>(uint8<16>(a));
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
uint64<4> i_move2_l(uint64<4> a)
{
    static_assert(shift <= 2, "Selector out of range");
    return _mm256_srli_si256(a, shift*8);
}
#endif

#if SIMDPP_USE_AVX512
template<unsigned shift>
uint64<8> i_move2_l(uint64<8> a)
{
    static_assert(shift <= 4, "Selector out of range");
    return (uint64<8>) i_move4_l<shift*2>(uint32<16>(a));
}
#endif

template<unsigned shift, unsigned N>
uint64<N> i_move2_l(uint64<N> a)
{
    return uint64<N>(i_move16_l<shift*8>(uint8<N*8>(a)));
}

// -----------------------------------------------------------------------------

template<unsigned shift>
float32<4> i_move4_l(float32<4> a)
{
    return (float32<4>) i_move16_l<shift*4>(uint8<16>(a));
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
float32<8> i_move4_l(float32<8> a)
{
    static_assert(shift <= 4, "Selector out of range");
    return (float32<8>) i_move16_l<shift*4>(uint8<32>(a));
}
#endif

#if SIMDPP_USE_AVX512
template<unsigned shift>
float32<16> i_move4_l(float32<16> a)
{
    static_assert(shift <= 4, "Selector out of range");
    switch (shift) {
    case 0: return a;
    case 1: return _mm512_maskz_shuffle_ps(0x7777, a, a, _MM_SHUFFLE(3, 3, 2, 1));
    case 2: return _mm512_maskz_shuffle_ps(0x3333, a, a, _MM_SHUFFLE(3, 3, 3, 2));
    case 3: return _mm512_maskz_shuffle_ps(0x1111, a, a, _MM_SHUFFLE(3, 3, 3, 3));
    case 4: return float32<16>::zero();
    }
}
#endif

template<unsigned shift, unsigned N>
float32<N> i_move4_l(float32<N> a)
{
    return float32<N>(i_move4_l<shift>(uint32<N>(a)));
}

// -----------------------------------------------------------------------------

template<unsigned shift>
float64<2> i_move2_l(float64<2> a)
{
    return (float64<2>) i_move16_l<shift*8>(uint8<16>(a));
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
float64<4> i_move2_l(float64<4> a)
{
    static_assert(shift <= 2, "Selector out of range");
    return (float64<4>) i_move16_l<shift*8>(uint8<32>(a));
}
#endif

#if SIMDPP_USE_AVX512
template<unsigned shift>
float64<8> i_move2_l(float64<8> a)
{
    static_assert(shift <= 2, "Selector out of range");
    switch (shift) {
    case 0: return a;
    case 1: return _mm512_maskz_shuffle_pd(0x55, a, a, _MM_SHUFFLE2(1, 1));
    case 2: return float64<8>::zero();
    }
}
#endif

template<unsigned shift, unsigned N>
float64<N> i_move2_l(float64<N> a)
{
    return float64<N>(i_move2_l<shift>(uint64<N>(a)));
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

