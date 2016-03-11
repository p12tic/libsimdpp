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
#include <simdpp/detail/null/shuffle.h>
#include <simdpp/detail/shuffle/shuffle_mask.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


template<unsigned shift> SIMDPP_INL
uint8x16 i_move16_l(const uint8x16& a)
{
    static_assert(shift <= 16, "Selector out of range");
#if SIMDPP_USE_NULL
    return detail::null::move_n_l<shift>(a);
#elif SIMDPP_USE_SSE2
    return _mm_srli_si128(a, shift);
#elif SIMDPP_USE_NEON
    uint8x16 z = make_zero();
    return vextq_u8(a, z, shift);
#elif SIMDPP_USE_ALTIVEC
    // return align<shift>(a, (uint8x16) make_zero());
    return vec_sld((__vector uint8_t)a, (__vector uint8_t)(uint8x16) make_zero(), shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift> SIMDPP_INL
uint8x32 i_move16_l(const uint8x32& a)
{
    static_assert(shift <= 16, "Selector out of range");
    return _mm256_srli_si256(a, shift);
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
uint8<N> i_move16_l(const uint8<N>& a)
{
    static_assert(shift <= 16, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_move16_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift> SIMDPP_INL
uint16<8> i_move8_l(const uint16<8>& a)
{
#if SIMDPP_USE_NULL
    return detail::null::move_n_l<shift>(a);
#else
    return (uint16<8>) i_move16_l<shift*2>(uint8<16>(a));
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift> SIMDPP_INL
uint16<16> i_move8_l(const uint16<16>& a)
{
    static_assert(shift <= 8, "Selector out of range");
    return _mm256_srli_si256(a, shift*2);
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
uint16<N> i_move8_l(const uint16<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint16<N>, i_move8_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift> SIMDPP_INL
uint32<4> i_move4_l(const uint32<4>& a)
{
#if SIMDPP_USE_NULL
    return detail::null::move_n_l<shift>(a);
#else
    return (uint32<4>) i_move16_l<shift*4>(uint8<16>(a));
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift> SIMDPP_INL
uint32<8> i_move4_l(const uint32<8>& a)
{
    static_assert(shift <= 4, "Selector out of range");
    return _mm256_srli_si256(a, shift*4);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned shift> SIMDPP_INL
uint32<16> i_move4_l(const uint32<16>& a)
{
    static_assert(shift <= 4, "Selector out of range");
    switch (shift) {
    case 0: return a;
    case 1: return _mm512_maskz_shuffle_epi32(0x7777, a, _MM_PERM_ENUM(_MM_SHUFFLE(3, 3, 2, 1)));
    case 2: return _mm512_maskz_shuffle_epi32(0x3333, a, _MM_PERM_ENUM(_MM_SHUFFLE(3, 3, 3, 2)));
    case 3: return _mm512_maskz_shuffle_epi32(0x1111, a, _MM_PERM_ENUM(_MM_SHUFFLE(3, 3, 3, 3)));
    case 4: return make_zero();
    }
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
uint32<N> i_move4_l(const uint32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, i_move4_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift> SIMDPP_INL
uint64<2> i_move2_l(const uint64<2>& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::move_n_l<shift>(a);
#else
    return (uint64<2>) i_move16_l<shift*8>(uint8<16>(a));
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift> SIMDPP_INL
uint64<4> i_move2_l(const uint64<4>& a)
{
    static_assert(shift <= 2, "Selector out of range");
    return _mm256_srli_si256(a, shift*8);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned shift> SIMDPP_INL
uint64<8> i_move2_l(const uint64<8>& a)
{
    static_assert(shift <= 4, "Selector out of range");
    return (uint64<8>) i_move4_l<shift*2>(uint32<16>(a));
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
uint64<N> i_move2_l(const uint64<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, i_move2_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift> SIMDPP_INL
float32<4> i_move4_l(const float32<4>& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::move_n_l<shift>(a);
#else
    return (float32<4>) i_move16_l<shift*4>(uint8<16>(a));
#endif
}

#if SIMDPP_USE_AVX
template<unsigned shift> SIMDPP_INL
float32<8> i_move4_l(const float32<8>& a)
{
    static_assert(shift <= 4, "Selector out of range");
    return (float32<8>) i_move16_l<shift*4>(uint8<32>(a));
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned shift> SIMDPP_INL
float32<16> i_move4_l(const float32<16>& a)
{
    static_assert(shift <= 4, "Selector out of range");
    switch (shift) {
    case 0: return a;
    case 1: return _mm512_maskz_shuffle_ps(0x7777, a, a, _MM_SHUFFLE(3, 3, 2, 1));
    case 2: return _mm512_maskz_shuffle_ps(0x3333, a, a, _MM_SHUFFLE(3, 3, 3, 2));
    case 3: return _mm512_maskz_shuffle_ps(0x1111, a, a, _MM_SHUFFLE(3, 3, 3, 3));
    case 4: return make_zero();
    }
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
float32<N> i_move4_l(const float32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_move4_l<shift>, a);
}

// -----------------------------------------------------------------------------

template<unsigned shift> SIMDPP_INL
float64<2> i_move2_l(const float64<2>& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    return detail::null::move_n_l<shift>(a);
#else
    return (float64<2>) i_move16_l<shift*8>(uint8<16>(a));
#endif
}

#if SIMDPP_USE_AVX
template<unsigned shift> SIMDPP_INL
float64<4> i_move2_l(const float64<4>& a)
{
    static_assert(shift <= 2, "Selector out of range");
    return (float64<4>) i_move16_l<shift*8>(uint8<32>(a));
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned shift> SIMDPP_INL
float64<8> i_move2_l(const float64<8>& a)
{
    static_assert(shift <= 2, "Selector out of range");
    switch (shift) {
    case 0: return a;
    case 1: return _mm512_maskz_shuffle_pd(0x55, a, a, SIMDPP_SHUFFLE_MASK_2x2_4(1, 1));
    case 2: return make_zero();
    }
}
#endif

template<unsigned shift, unsigned N> SIMDPP_INL
float64<N> i_move2_l(const float64<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, i_move2_l<shift>, a);
}

// -----------------------------------------------------------------------------
// Certain compilers don't like zero or full vector width moves. The templates
// below offer a warkaround

template<unsigned count>
struct i_move2_l_wrapper {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return i_move2_l<count>(arg); }
};
template<>
struct i_move2_l_wrapper<0> {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return arg; }
};
template<>
struct i_move2_l_wrapper<2> {
    template<class V>
    static SIMDPP_INL V run(const V&) { return (V) make_zero(); }
};

template<unsigned count>
struct i_move4_l_wrapper {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return i_move4_l<count>(arg); }
};
template<>
struct i_move4_l_wrapper<0> {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return arg; }
};
template<>
struct i_move4_l_wrapper<4> {
    template<class V>
    static SIMDPP_INL V run(const V&) { return (V) make_zero(); }
};

template<unsigned count>
struct i_move8_l_wrapper {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return i_move8_l<count>(arg); }
};
template<>
struct i_move8_l_wrapper<0> {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return arg; }
};
template<>
struct i_move8_l_wrapper<8> {
    template<class V>
    static SIMDPP_INL V run(const V&) { return (V) make_zero(); }
};

template<unsigned count>
struct i_move16_l_wrapper {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return i_move16_l<count>(arg); }
};
template<>
struct i_move16_l_wrapper<0> {
    template<class V>
    static SIMDPP_INL V run(const V& arg) { return arg; }
};
template<>
struct i_move16_l_wrapper<16> {
    template<class V>
    static SIMDPP_INL V run(const V&) { return (V) make_zero(); }
};

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

