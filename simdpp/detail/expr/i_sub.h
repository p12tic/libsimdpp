/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {


template<class E1, class E2>
uint8<16> expr_eval(expr_sub<uint8<16,E1>,
                             uint8<16,E2>> q)
{
    uint8<16> a = q.a.eval();
    uint8<16> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
uint8<32> expr_eval(expr_sub<uint8<32,E1>,
                             uint8<32,E2>> q)
{
    uint8<32> a = q.a.eval();
    uint8<32> b = q.b.eval();
    return _mm256_sub_epi8(a, b);
}
#endif

template<unsigned N, class E1, class E2>
uint8<N> expr_eval(expr_sub<uint8<N,E1>,
                            uint8<N,E2>> q)
{
    uint8<N> a = q.a.eval();
    uint8<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, sub, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
uint16<8> expr_eval(expr_sub<uint16<8,E1>,
                             uint16<8,E2>> q)
{
    uint16<8> a = q.a.eval();
    uint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
uint16<16> expr_eval(expr_sub<uint16<16,E1>,
                              uint16<16,E2>> q)
{
    uint16<16> a = q.a.eval();
    uint16<16> b = q.b.eval();
    return _mm256_sub_epi16(a, b);
}
#endif

template<unsigned N, class E1, class E2>
uint16<N> expr_eval(expr_sub<uint16<N,E1>,
                             uint16<N,E2>> q)
{
    uint16<N> a = q.a.eval();
    uint16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, sub, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
uint32<4> expr_eval(expr_sub<uint32<4,E1>,
                             uint32<4,E2>> q)
{
    uint32<4> a = q.a.eval();
    uint32<4> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
uint32<8> expr_eval(expr_sub<uint32<8,E1>,
                             uint32<8,E2>> q)
{
    uint32<8> a = q.a.eval();
    uint32<8> b = q.b.eval();
    return _mm256_sub_epi32(a, b);
}
#endif

#if SIMDPP_USE_AVX512
template<class E1, class E2>
uint32<16> expr_eval(expr_sub<uint32<16,E1>,
                              uint32<16,E2>> q)
{
    uint32<16> a = q.a.eval();
    uint32<16> b = q.b.eval();
    return _mm512_sub_epi32(a, b);
}
#endif

template<unsigned N, class E1, class E2>
uint32<N> expr_eval(expr_sub<uint32<N,E1>,
                             uint32<N,E2>> q)
{
    uint32<N> a = q.a.eval();
    uint32<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, sub, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
uint64<2> expr_eval(expr_sub<uint64<2,E1>,
                             uint64<2,E2>> q)
{
    uint64<2> a = q.a.eval();
    uint64<2> b = q.b.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi64(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u64(a, b);
#else
    uint64x2 c1 = make_uint(1);
    uint32x4 r, carry;
    carry = vec_subc((__vector uint32_t) a, (__vector uint32_t) b);
    carry = move_l<1>(carry);
    r = sub((uint32x4)a, (uint32x4)b);
    carry = bit_and(carry, c1);
    r = sub(r, carry);
    return r;
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
uint64<4> expr_eval(expr_sub<uint64<4,E1>,
                             uint64<4,E2>> q)
{
    uint64<4> a = q.a.eval();
    uint64<4> b = q.b.eval();
    return _mm256_sub_epi64(a, b);
}
#endif

#if SIMDPP_USE_AVX512
template<class E1, class E2>
uint64<8> expr_eval(expr_sub<uint64<8,E1>,
                             uint64<8,E2>> q)
{
    uint64<8> a = q.a.eval();
    uint64<8> b = q.b.eval();
    return _mm512_sub_epi64(a, b);
}
#endif

template<unsigned N, class E1, class E2>
uint64<N> expr_eval(expr_sub<uint64<N,E1>,
                             uint64<N,E2>> q)
{
    uint64<N> a = q.a.eval();
    uint64<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, sub, a, b);
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

