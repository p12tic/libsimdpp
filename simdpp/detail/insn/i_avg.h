/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_AVG_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_AVG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/i_add.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/detail/null/foreach.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

template<class V> SIMDPP_INL V v_emul_avg_u32(const V& a, const V& b);
template<class V> SIMDPP_INL V v_emul_avg_i32(const V& a, const V& b);


SIMDPP_INL uint8x16 i_avg(const uint8x16& a, const uint8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<uint8x16>(a, b, [](uint8_t a, uint8_t b){
        return (uint16_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return _mm_avg_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_avg(const uint8x32& a, const uint8x32& b)
{
    return _mm256_avg_epu8(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> i_avg(const uint8<N>& a, const uint8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_avg, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL int8x16 i_avg(const int8x16& a, const int8x16& b)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<int8x16>(a, b, [](int8_t a, int8_t b){
        return (int16_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint8x16 a2, b2, bias, r;
    bias = make_uint(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = i_avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int8x32 i_avg(const int8x32& a, const int8x32& b)
{
    uint8x32 a2, b2, bias, r;
    bias = make_uint(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = i_avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
}
#endif

template<unsigned N> SIMDPP_INL
int8<N> i_avg(const int8<N>& a, const int8<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, i_avg, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_avg(const uint16x8& a, const uint16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){
        return (uint32_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return _mm_avg_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16x16 i_avg(const uint16x16& a, const uint16x16& b)
{
    return _mm256_avg_epu16(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint16<N> i_avg(const uint16<N>& a, const uint16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_avg, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL int16x8 i_avg(const int16x8& a, const int16x8& b)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){
        return (int32_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint16x8 a2, b2, r;
    a2 = bit_xor(a, 0x8000); // add
    b2 = bit_xor(b, 0x8000); // add
    r = i_avg(a2, b2); // unsigned
    r = bit_xor(r, 0x8000); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int16x16 i_avg(const int16x16& a, const int16x16& b)
{
    uint16x16 a2, b2, r;
    a2 = bit_xor(a, 0x8000); // add
    b2 = bit_xor(b, 0x8000); // add
    r = i_avg(a2, b2); // unsigned
    r = bit_xor(r, 0x8000); // sub
    return r;
}
#endif

template<unsigned N> SIMDPP_INL
int16<N> i_avg(const int16<N>& a, const int16<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, i_avg, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_avg(const uint32x4& a, const uint32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<uint32x4>(a, b, [](uint32_t a, uint32_t b){
        return (uint64_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return v_emul_avg_u32(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32x8 i_avg(const uint32x8& a, const uint32x8& b)
{
    return v_emul_avg_u32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL uint32<16> i_avg(const uint32<16>& a, const uint32<16>& b)
{
    return v_emul_avg_u32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
uint32<N> i_avg(const uint32<N>& a, const uint32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_avg, a, b);
}

SIMDPP_INL int32x4 i_avg(const int32x4& a, const int32x4& b)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<int32x4>(a, b, [](int32_t a, int32_t b){
        return (int64_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return v_emul_avg_i32(a, b);

#elif SIMDPP_USE_NEON
    return vrhaddq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL int32x8 i_avg(const int32x8& a, const int32x8& b)
{
    return v_emul_avg_i32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL int32<16> i_avg(const int32<16>& a, const int32<16>& b)
{
    return v_emul_avg_i32(a, b);
}
#endif

template<unsigned N> SIMDPP_INL
int32<N> i_avg(const int32<N>& a, const int32<N>& b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int32<N>, i_avg, a, b);
}

// generic implementations

template<class V> SIMDPP_INL
V v_emul_avg_u32(const V& a, const V& b)
{
    // (x & y) + ((x ^ y) >> 1) + (x ^ y) & 1
    V x1, x2, round;
    x1 = bit_and(a, b);
    x2 = bit_xor(a, b);
    round = bit_and(x2, 1);
    x1 = add(x1, shift_r<1>(x2));
    x1 = add(x1, round);
    return x1;
}

template<class V> SIMDPP_INL
V v_emul_avg_i32(const V& a, const V& b)
{
    using VI = typename V::uint_vector_type;
    VI a2, b2, r;
    a2 = bit_xor(a, 0x80000000); // add
    b2 = bit_xor(b, 0x80000000); // add
    r = v_emul_avg_u32(a2, b2); // unsigned
    r = bit_xor(r, 0x80000000); // sub
    return r;
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

