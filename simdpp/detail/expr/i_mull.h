/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_MULL_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_MULL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/mem_block.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/detail/vec_insert.h>
#include <simdpp/core/to_int64.h>
#include <simdpp/core/combine.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {


/*  Note: widening integer multiplication instructions are very different among
    instruction sets. The main difference is in which half of the elements are
    selected for multiplication. Trying to abstract this incurs definite
    overhead.

     - SSE2-SSE4.1 and AVX2 provide only instructions with interfaces similar
        to mul_lo and mul_hi. The result vectors must be interleaved to obtain
        contiguous result values. Multiplying 2 vectors always incurs
        overhead of at least two interleaving instructions.

     - AVX512 only provides 32-bit integer support. Widening multiplication
        can be done only by using PMULDQ, which takes odd elements and produces
        widened multiplication results. Multiplication of two whole vectors
        always incurs overhead of at least two shifts or interleaving
        instructions.

     - NEON, NEONv2 provide instructions that take elements of either the lower
        or higher halves of two 128-bit vectors and multiply them. No
        additional overhead is incurred to obtain contiguous result values.

     - ALTIVEC hav multiply odd and multiply even instructions. No additional
        overhead is incurred to obtain contiguous result values.

    The abstraction below uses the NEON model. No additional overhead is
    incurred on SSE/AVX and NEON. On ALTIVEC, a single additional permute
    instruction is needed for each vector multiplication on average.
*/

template<class R, class E1, class E2> SIMDPP_INL
int32<8> expr_eval(const expr_mull<int16<8,E1>,
                                   int16<8,E2>>& q)
{
    int16<8> a = q.a.eval();
    int16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    int32x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r.vec(i/4).el(i%4) = int32_t(a.el(i)) * b.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epi16(a, b);
    return (int32x8)combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
#elif SIMDPP_USE_NEON
    int32x4 lo = vmull_s16(vget_low_s16(a), vget_low_s16(b));
    int32x4 hi = vmull_s16(vget_high_s16(a), vget_high_s16(b));
    return combine(lo, hi);
#elif SIMDPP_USE_ALTIVEC
    int32x4 lo = vec_mule((__vector int16_t)a, (__vector int16_t)b);
    int32x4 hi = vec_mulo((__vector int16_t)a, (__vector int16_t)b);
    return combine(zip4_lo(lo, hi), zip4_hi(lo, hi));
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int32<16> expr_eval(const expr_mull<int16<16,E1>,
                                    int16<16,E2>>& q)
{
    int16<16> a = q.a.eval();
    int16<16> b = q.b.eval();
    a = _mm256_permute4x64_epi64(a, _MM_SHUFFLE(3,1,2,0));
    b = _mm256_permute4x64_epi64(b, _MM_SHUFFLE(3,1,2,0));
    int16x16 lo = _mm256_mullo_epi16(a, b);
    int16x16 hi = _mm256_mulhi_epi16(a, b);
    return (int32<16>) combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int32<N> expr_eval(const expr_mull<int16<N,E1>,
                                   int16<N,E2>>& q)
{
    int16<N> a = q.a.eval();
    int16<N> b = q.b.eval();
    int32<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
    }
    return r;
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint32<8> expr_eval(const expr_mull<uint16<8,E1>,
                                    uint16<8,E2>>& q)
{
    uint16<8> a = q.a.eval();
    uint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    int32x8 r;
    for (unsigned i = 0; i < 8; i++) {
        r.vec(i/4).el(i%4) = uint32_t(a.el(i)) * b.el(i);
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epu16(a, b);
    return (uint32x8) combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
#elif SIMDPP_USE_NEON
    uint32x4 lo = vmull_u16(vget_low_u16(a), vget_low_u16(b));
    uint32x4 hi = vmull_u16(vget_high_u16(a), vget_high_u16(b));
    return combine(lo, hi);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 lo = vec_mule((__vector uint16_t)a, (__vector uint16_t)b);
    uint32x4 hi = vec_mulo((__vector uint16_t)a, (__vector uint16_t)b);
    return combine(zip4_lo(lo, hi), zip4_hi(lo, hi));
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint32<16> expr_eval(const expr_mull<uint16<16,E1>,
                                     uint16<16,E2>>& q)
{
    uint16<16> a = q.a.eval();
    uint16<16> b = q.b.eval();
    a = _mm256_permute4x64_epi64(a, _MM_SHUFFLE(3,1,2,0));
    b = _mm256_permute4x64_epi64(b, _MM_SHUFFLE(3,1,2,0));
    int16x16 lo = _mm256_mullo_epi16(a, b);
    int16x16 hi = _mm256_mulhi_epu16(a, b);
    return (uint32<16>) combine(zip8_lo(lo, hi), zip8_hi(lo, hi));
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint32<N> expr_eval(const expr_mull<uint16<N,E1>,
                                    uint16<N,E2>>& q)
{
    uint16<N> a = q.a.eval();
    uint16<N> b = q.b.eval();
    uint32<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
    }
    return r;
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
int64<4> expr_eval(const expr_mull<int32<4,E1>,
                                   int32<4,E2>>& q)
{
    int32<4> a = q.a.eval();
    int32<4> b = q.b.eval();
#if SIMDPP_USE_NULL
    int64x4 r;
    r.vec(0).el(0) = int64_t(a.el(0)) * b.el(0);
    r.vec(0).el(1) = int64_t(a.el(1)) * b.el(1);
    r.vec(1).el(0) = int64_t(a.el(2)) * b.el(2);
    r.vec(1).el(1) = int64_t(a.el(3)) * b.el(3);
    return r;
#elif SIMDPP_USE_SSE4_1
    int32x4 al, ah, bl, bh;
    int64x2 rl, rh;
    al = zip4_lo(a, a);
    bl = zip4_lo(b, b);
    ah = zip4_hi(a, a);
    bh = zip4_hi(b, b);
    rl = _mm_mul_epi32(al, bl);
    rh = _mm_mul_epi32(ah, bh);
    return combine(rl, rh);
#elif SIMDPP_USE_NEON
    int64x2 lo = vmull_s32(vget_low_s32(a), vget_low_s32(b));
    int64x2 hi = vmull_s32(vget_high_s32(a), vget_high_s32(b));
    return combine(lo, hi);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE2(R, a, b);
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int64<8> expr_eval(const expr_mull<int32<8,E1>,
                                   int32<8,E2>>& q)
{
    int32<8> a = q.a.eval();
    int32<8> b = q.b.eval();
    int32x4 al, ah, bl, bh;
    int64x4 rl, rh;
    split(a, al, ah);
    split(b, bl, bh);

    rl = _mm256_mul_epi32(to_int64(al).eval(), to_int64(bl).eval());
    rh = _mm256_mul_epi32(to_int64(ah).eval(), to_int64(bh).eval());
    return combine(rl, rh);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int64<N> expr_eval(const expr_mull<int32<N,E1>,
                                   int32<N,E2>>& q)
{
    int32<N> a = q.a.eval();
    int32<N> b = q.b.eval();
    int64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
    }
    return r;
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint64<4> expr_eval(const expr_mull<uint32<4,E1>,
                                    uint32<4,E2>>& q)
{
    uint32<4> a = q.a.eval();
    uint32<4> b = q.b.eval();
#if SIMDPP_USE_NULL
    uint64x4 r;
    r.vec(0).el(0) = uint64_t(a.el(0)) * b.el(0);
    r.vec(0).el(1) = uint64_t(a.el(1)) * b.el(1);
    r.vec(1).el(0) = uint64_t(a.el(2)) * b.el(2);
    r.vec(1).el(1) = uint64_t(a.el(3)) * b.el(3);
    return r;
#elif SIMDPP_USE_SSE2
    uint32x4 al, ah, bl, bh;
    uint64x2 rl, rh;
    al = zip4_lo(a, a);
    bl = zip4_lo(b, b);
    ah = zip4_hi(a, a);
    bh = zip4_hi(b, b);
    rl = _mm_mul_epu32(al, bl);
    rh = _mm_mul_epu32(ah, bh);
    return combine(rl, rh);
#elif SIMDPP_USE_NEON
    uint64x2 lo = vmull_u32(vget_low_u32(a), vget_low_u32(b));
    uint64x2 hi = vmull_u32(vget_high_u32(a), vget_high_u32(b));
    return combine(lo, hi);
#elif SIMDPP_USE_ALTIVEC
    mem_block<uint32<4>> ba = a;
    mem_block<uint32<4>> bb = b;
    uint64x4 r;
    r.vec(0).el(0) = (uint64_t) ba[0] * bb[0];
    r.vec(0).el(1) = (uint64_t) ba[1] * bb[1];
    r.vec(1).el(0) = (uint64_t) ba[2] * bb[2];
    r.vec(1).el(1) = (uint64_t) ba[3] * bb[3];
    return r;
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint64<8> expr_eval(const expr_mull<uint32<8,E1>,
                                    uint32<8,E2>>& q)
{
    uint32<8> a = q.a.eval();
    uint32<8> b = q.b.eval();
    uint32x4 al, ah, bl, bh;
    uint64x4 rl, rh;

    split(a, al, ah);
    split(b, bl, bh);

    rl = _mm256_mul_epu32(to_uint64(al).eval(), to_uint64(bl).eval());
    rh = _mm256_mul_epu32(to_uint64(ah).eval(), to_uint64(bh).eval());

    return combine(rl, rh);
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
uint64<16> expr_eval(const expr_mull<uint32<16,E1>,
                                     uint32<16,E2>>& q)
{
    uint32<16> a = q.a.eval();
    uint32<16> b = q.b.eval();
    uint32<8> al, ah, bl, bh;
    uint64<8> rl, rh;

    split(a, al, ah);
    split(b, bl, bh);

    rl = _mm512_mul_epu32(to_int64(al).eval(), to_int64(bl).eval());
    rh = _mm512_mul_epu32(to_int64(ah).eval(), to_int64(bh).eval());

    return combine(rl, rh);
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint64<N> expr_eval(const expr_mull<uint32<N,E1>,
                                    uint32<N,E2>>& q)
{
    uint32<N> a = q.a.eval();
    uint32<N> b = q.b.eval();
    uint64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, mull(a.vec(i), b.vec(i)).eval(), i);
    }
    return r;
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

