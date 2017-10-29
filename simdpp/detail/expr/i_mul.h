/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_MUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_mull.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/unzip_hi.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {


template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval_mul_lo(const uint16<8,E1>& qa,
                           const uint16<8,E2>& qb)
{
    uint16<8> a = qa.eval();
    uint16<8> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mullo_epi16(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vmulq_u16(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_mladd(a.native(), b.native(),
                     ((uint16x8) make_zero()).native());
#elif SIMDPP_USE_MSA
    return (v8u16) __msa_mulv_h((v8i16) a.native(), (v8i16) b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval_mul_lo(const uint16<16,E1>& qa,
                            const uint16<16,E2>& qb)
{
    uint16<16> a = qa.eval();
    uint16<16> b = qb.eval();
    return _mm256_mullo_epi16(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
uint16<32> expr_eval_mul_lo(const uint16<32,E1>& qa,
                            const uint16<32,E2>& qb)
{
    uint16<32> a = qa.eval();
    uint16<32> b = qb.eval();
    return _mm512_mullo_epi16(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval_mul_lo(const uint16<N,E1>& qa,
                           const uint16<N,E2>& qb)
{
    uint16<N> a = qa.eval();
    uint16<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, mul_lo, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
int16<8> expr_eval_mul_hi(const int16<8,E1>& qa,
                          const int16<8,E2>& qb)
{
    int16<8> a = qa.eval();
    int16<8> b = qb.eval();
#if SIMDPP_USE_NULL
    uint16<8> r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = (int32_t(a.el(i)) * b.el(i)) >> 16;
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epi16(a.native(), b.native());
#elif SIMDPP_USE_NEON
    int32x4 lo = vmull_s16(vget_low_s16(a.native()), vget_low_s16(b.native()));
    int32x4 hi = vmull_s16(vget_high_s16(a.native()), vget_high_s16(b.native()));
    return unzip8_hi(int16x8(lo), int16x8(hi));
#elif SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
#if SIMDPP_BIG_ENDIAN
    int16<16> ab;
    ab = mull(a, b);
    return unzip8_lo(ab.vec(0), ab.vec(1));
#else
    int16<16> ab;
    ab = mull(a, b);
    return unzip8_hi(ab.vec(0), ab.vec(1));
#endif
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int16<16> expr_eval_mul_hi(const int16<16,E1>& qa,
                           const int16<16,E2>& qb)
{
    int16<16> a = qa.eval();
    int16<16> b = qb.eval();
    return _mm256_mulhi_epi16(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
int16<32> expr_eval_mul_hi(const int16<32,E1>& qa,
                           const int16<32,E2>& qb)
{
    int16<32> a = qa.eval();
    int16<32> b = qb.eval();
    return _mm512_mulhi_epi16(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int16<N> expr_eval_mul_hi(const int16<N,E1>& qa,
                          const int16<N,E2>& qb)
{
    int16<N> a = qa.eval();
    int16<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, mul_hi, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval_mul_hi(const uint16<8,E1>& qa,
                           const uint16<8,E2>& qb)
{
    uint16<8> a = qa.eval();
    uint16<8> b = qb.eval();
#if SIMDPP_USE_NULL
    uint16<8> r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = (uint32_t(a.el(i)) * b.el(i)) >> 16;
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_mulhi_epu16(a.native(), b.native());
#elif SIMDPP_USE_NEON
    uint32x4 lo = vmull_u16(vget_low_u16(a.native()), vget_low_u16(b.native()));
    uint32x4 hi = vmull_u16(vget_high_u16(a.native()), vget_high_u16(b.native()));
    return unzip8_hi(uint16x8(lo), uint16x8(hi));
#elif SIMDPP_USE_ALTIVEC && SIMDPP_BIG_ENDIAN
    uint16<16> ab;
    ab = mull(a, b);
    return unzip8_lo(ab.vec(0), ab.vec(1));
#elif (SIMDPP_USE_ALTIVEC && SIMDPP_LITTLE_ENDIAN) || SIMDPP_USE_MSA
    uint16<16> ab;
    ab = mull(a, b);
    return unzip8_hi(ab.vec(0), ab.vec(1));
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval_mul_hi(const uint16<16,E1>& qa,
                            const uint16<16,E2>& qb)
{
    uint16<16> a = qa.eval();
    uint16<16> b = qb.eval();
    return _mm256_mulhi_epu16(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
uint16<32> expr_eval_mul_hi(const uint16<32,E1>& qa,
                            const uint16<32,E2>& qb)
{
    uint16<32> a = qa.eval();
    uint16<32> b = qb.eval();
    return _mm512_mulhi_epu16(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval_mul_hi(const uint16<N,E1>& qa,
                           const uint16<N,E2>& qb)
{
    uint16<N> a = qa.eval();
    uint16<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, mul_hi, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint32<4> expr_eval_mul_lo(const uint32<4,E1>& qa,
                           const uint32<4,E2>& qb)
{
    uint32<4> a = qa.eval();
    uint32<4> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::mul(a, b);
#elif SIMDPP_USE_SSE4_1
    return _mm_mullo_epi32(a.native(), b.native());
#elif SIMDPP_USE_SSE2
    uint32x4 a1, b1;
    a1 = move4_l<1>(a);
    b1 = move4_l<1>(b);
    a = _mm_mul_epu32(a.native(), b.native());
    a1 = _mm_mul_epu32(a1.native(), b1.native());
    a = shuffle2<0,2,0,2>(a, a1); // moves to FP domain, additional latency unavoidable
    a = permute4<0,2,1,3>(a);
    return a;
#elif SIMDPP_USE_NEON
    return vmulq_u32(a.native(), b.native());
#elif SIMDPP_USE_VSX_207
    __vector uint32_t va = a, vb = b;
    __vector uint32_t vr;
    // BUG: GCC does not have support for vmuluwm yet
    // return vec_vmuluwm(a, b);
    asm("vmuluwm	%0, %1, %2" : "=wa"(vr) : "wa"(va), "wa"(vb));
    return vr;
#elif SIMDPP_USE_ALTIVEC
    // implement in terms of 16-bit multiplies
    //   *  ah  al
    //      bh  bl
    //      ======
    //   + (al*bl) <-  l_ab
    //+ (ah*bl)    <-  h_ab
    //+ (al*bh)    <-  h_ba

    uint16<8> ra, rb; ra = a, rb = b;
#if SIMDPP_BIG_ENDIAN
    uint16<8> sa = move8_r<1>(ra);
    uint16<8> sb = move8_r<1>(rb);

    uint32<4> l_ab = vec_mulo(ra.native(), rb.native());
    uint32<4> h_ab = vec_mulo(ra.native(), sb.native());
    uint32<4> h_ba = vec_mulo(sa.native(), rb.native());
#else
    uint16<8> sa = move8_l<1>(ra);
    uint16<8> sb = move8_l<1>(rb);

    uint32<4> l_ab = vec_mule(ra.native(), rb.native());
    uint32<4> h_ab = vec_mule(ra.native(), sb.native());
    uint32<4> h_ba = vec_mule(sa.native(), rb.native());
#endif

    h_ab = shift_l<16>(add(h_ab, h_ba));
    h_ab = add(h_ab, l_ab);
    return h_ab;
#elif SIMDPP_USE_MSA
    return (v4u32) __msa_mulv_w((v4i32) a.native(), (v4i32) b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint32<8> expr_eval_mul_lo(const uint32<8,E1>& qa,
                           const uint32<8,E2>& qb)
{
    uint32<8> a = qa.eval();
    uint32<8> b = qb.eval();
    return _mm256_mullo_epi32(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
uint32<16> expr_eval_mul_lo(const uint32<16,E1>& qa,
                            const uint32<16,E2>& qb)
{
    uint32<16> a = qa.eval();
    uint32<16> b = qb.eval();
    return _mm512_mullo_epi32(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint32<N> expr_eval_mul_lo(const uint32<N,E1>& qa,
                           const uint32<N,E2>& qb)
{
    uint32<N> a = qa.eval();
    uint32<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, mul_lo, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

