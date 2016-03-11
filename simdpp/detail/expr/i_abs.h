/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ABS_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ABS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/cmp_neq.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/core/move_r.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E> SIMDPP_INL
uint8<16> expr_eval(const expr_abs<int8<16,E>>& q)
{
    int8<16> a = q.a.eval();
#if SIMDPP_USE_NULL
    return detail::null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi8(a);
#elif SIMDPP_USE_SSE2
    int8x16 t;
    t = cmp_lt(a, 0);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int8x16(vabsq_s8(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint8_t) vec_abs((__vector int8_t)a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
uint8<32> expr_eval(const expr_abs<int8<32,E>>& q)
{
    int8<32> a = q.a.eval();
    return _mm256_abs_epi8(a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
uint8<N> expr_eval(const expr_abs<int8<N,E>>& q)
{
    int8<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
uint16<8> expr_eval(const expr_abs<int16<8,E>>& q)
{
    int16<8> a = q.a.eval();
#if SIMDPP_USE_NULL
    return detail::null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi16(a);
#elif SIMDPP_USE_SSE2
    int16x8 t;
    t = cmp_lt(a, 0);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int16x8(vabsq_s16(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint16_t) vec_abs((__vector int16_t)a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
uint16<16> expr_eval(const expr_abs<int16<16,E>>& q)
{
    int16<16> a = q.a.eval();
    return _mm256_abs_epi16(a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
uint16<N> expr_eval(const expr_abs<int16<N,E>>& q)
{
    int16<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint16<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
uint32<4> expr_eval(const expr_abs<int32<4,E>>& q)
{
    int32<4> a = q.a.eval();
#if SIMDPP_USE_NULL
    return detail::null::abs(a);
#elif SIMDPP_USE_SSSE3
    return _mm_abs_epi32(a);
#elif SIMDPP_USE_SSE2
    int32x4 t;
    t = cmp_lt(a, 0);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    return int32x4(vabsq_s32(a));
#elif SIMDPP_USE_ALTIVEC
    // expands to 3 instructions
    return (__vector uint32_t) vec_abs((__vector int32_t)a);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
uint32<8> expr_eval(const expr_abs<int32<8,E>>& q)
{
    int32<8> a = q.a.eval();
    return _mm256_abs_epi32(a);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E> SIMDPP_INL
uint32<16> expr_eval(const expr_abs<int32<16,E>>& q)
{
    int32<16> a = q.a.eval();
    return _mm512_abs_epi32(a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
uint32<N> expr_eval(const expr_abs<int32<N,E>>& q)
{
    int32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, abs, a);
}

// -----------------------------------------------------------------------------

template<class R, class E> SIMDPP_INL
uint64<2> expr_eval(const expr_abs<int64<2,E>>& q)
{
    int64<2> a = q.a.eval();
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::abs(a);
#elif SIMDPP_USE_SSE2
    uint32x4 ta;
    int64x2 t;
    ta = (uint32x4) bit_and(a, 0x8000000000000000);
    ta = shift_r<1>(ta);
    t = cmp_neq(float64x2(ta), 0);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#elif SIMDPP_USE_NEON
    int32x4 z;
    z = shift_r<63>(uint64x2(a));
    z = cmp_eq(z, 0);
    z = permute4<0,0,2,2>(z);
    z = bit_not(z);
    int64x2 t;
    t = z;
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E> SIMDPP_INL
uint64<4> expr_eval(const expr_abs<int64<4,E>>& q)
{
    int64<4> a = q.a.eval();
    int64x4 t;
    t = _mm256_cmpgt_epi64((int64x4) make_zero(), a);
    a = bit_xor(a, t);
    a = sub(a, t);
    return a;
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E> SIMDPP_INL
uint64<8> expr_eval(const expr_abs<int64<8,E>>& q)
{
    int64<8> a = q.a.eval();
    return _mm512_abs_epi64(a);
}
#endif

template<class R, unsigned N, class E> SIMDPP_INL
uint64<N> expr_eval(const expr_abs<int64<N,E>>& q)
{
    int64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, abs, a);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

