/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
    return null::sub(a, b);
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
    return null::sub(a, b);
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
    return null::sub(a, b);
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
    return null::sub(a, b);
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

template<unsigned N, class E1, class E2>
uint64<N> expr_eval(expr_sub<uint64<N,E1>,
                             uint64<N,E2>> q)
{
    uint64<N> a = q.a.eval();
    uint64<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, sub, a, b);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

