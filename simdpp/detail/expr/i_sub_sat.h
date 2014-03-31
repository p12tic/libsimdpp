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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_SAT_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_SAT_H

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
int8<16> expr_eval(expr_sub_sat<int8<16,E1>,
                                int8<16,E2>> q)
{
    int8<16> a = q.a.eval();
    int8<16> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
int8<32> expr_eval(expr_sub_sat<int8<32,E1>,
                                int8<32,E2>> q)
{
    int8<32> a = q.a.eval();
    int8<32> b = q.b.eval();
    return _mm256_subs_epi8(a, b);
}
#endif

template<unsigned N, class E1, class E2>
int8<N> expr_eval(expr_sub_sat<int8<N,E1>,
                               int8<N,E2>> q)
{
    int8<N> a = q.a.eval();
    int8<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, sub_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
int16<8> expr_eval(expr_sub_sat<int16<8,E1>,
                                int16<8,E2>> q)
{
    int16<8> a = q.a.eval();
    int16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
int16<16> expr_eval(expr_sub_sat<int16<16,E1>,
                                 int16<16,E2>> q)
{
    int16<16> a = q.a.eval();
    int16<16> b = q.b.eval();
    return _mm256_subs_epi16(a, b);
}
#endif

template<unsigned N, class E1, class E2>
int16<N> expr_eval(expr_sub_sat<int16<N,E1>,
                                int16<N,E2>> q)
{
    int16<N> a = q.a.eval();
    int16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, sub_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
uint8<16> expr_eval(expr_sub_sat<uint8<16,E1>,
                                 uint8<16,E2>> q)
{
    uint8<16> a = q.a.eval();
    uint8<16> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
uint8<32> expr_eval(expr_sub_sat<uint8<32,E1>,
                                 uint8<32,E2>> q)
{
    uint8<32> a = q.a.eval();
    uint8<32> b = q.b.eval();
    return _mm256_subs_epu8(a, b);
}
#endif

template<unsigned N, class E1, class E2>
uint8<N> expr_eval(expr_sub_sat<uint8<N,E1>,
                                uint8<N,E2>> q)
{
    uint8<N> a = q.a.eval();
    uint8<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, sub_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
uint16<8> expr_eval(expr_sub_sat<uint16<8,E1>,
                                 uint16<8,E2>> q)
{
    uint16<8> a = q.a.eval();
    uint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vqsubq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_subs((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
uint16<16> expr_eval(expr_sub_sat<uint16<16,E1>,
                                  uint16<16,E2>> q)
{
    uint16<16> a = q.a.eval();
    uint16<16> b = q.b.eval();
    return _mm256_subs_epu16(a, b);
}
#endif

template<unsigned N, class E1, class E2>
uint16<N> expr_eval(expr_sub_sat<uint16<N,E1>,
                                 uint16<N,E2>> q)
{
    uint16<N> a = q.a.eval();
    uint16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, sub_sat, a, b);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

