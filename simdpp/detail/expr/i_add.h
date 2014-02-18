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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_H

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
gint8<16> expr_eval(expr_add<gint8<16,E1>,
                             gint8<16,E2>> q)
{
    gint8<16> a = q.a.eval();
    gint8<16> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
gint8<32> expr_eval(expr_add<gint8<32,E1>,
                             gint8<32,E2>> q)
{
    gint8<32> a = q.a.eval();
    gint8<32> b = q.b.eval();
    return _mm256_add_epi8(a, b);
}
#endif

template<unsigned N, class E1, class E2>
gint8<N> expr_eval(expr_add<gint8<N,E1>,
                            gint8<N,E2>> q)
{
    gint8<N> a = q.a.eval();
    gint8<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(gint8<N>, add, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
gint16<8> expr_eval(expr_add<gint16<8,E1>,
                             gint16<8,E2>> q)
{
    gint16<8> a = q.a.eval();
    gint16<8> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
gint16<16> expr_eval(expr_add<gint16<16,E1>,
                              gint16<16,E2>> q)
{
    gint16<16> a = q.a.eval();
    gint16<16> b = q.b.eval();
    return _mm256_add_epi16(a, b);
}
#endif

template<unsigned N, class E1, class E2>
gint16<N> expr_eval(expr_add<gint16<N,E1>,
                             gint16<N,E2>> q)
{
    gint16<N> a = q.a.eval();
    gint16<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(gint16<N>, add, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
gint32<4> expr_eval(expr_add<gint32<4,E1>,
                             gint32<4,E2>> q)
{
    gint32<4> a = q.a.eval();
    gint32<4> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
gint32<8> expr_eval(expr_add<gint32<8,E1>,
                             gint32<8,E2>> q)
{
    gint32<8> a = q.a.eval();
    gint32<8> b = q.b.eval();
    return _mm256_add_epi32(a, b);
}
#endif

template<unsigned N, class E1, class E2>
gint32<N> expr_eval(expr_add<gint32<N,E1>,
                             gint32<N,E2>> q)
{
    gint32<N> a = q.a.eval();
    gint32<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(gint32<N>, add, a, b);
}

// -----------------------------------------------------------------------------

template<class E1, class E2>
gint64<2> expr_eval(expr_add<gint64<2,E1>,
                             gint64<2,E2>> q)
{
    gint64<2> a = q.a.eval();
    gint64<2> b = q.b.eval();
#if SIMDPP_USE_NULL
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi64(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_u64(a, b);
#else
    uint64x2 c1 = uint64x2::make_const(1);
    uint32x4 r, carry;
    carry = vec_addc((__vector uint32_t) a, (__vector uint32_t) b);
    carry = move_l<1>(carry);
    r = add((uint32x4)a, (uint32x4)b);
    carry = bit_and(carry, c1);
    r = add(r, carry);
    return r;
#endif
}

#if SIMDPP_USE_AVX2
template<class E1, class E2>
gint64<4> expr_eval(expr_add<gint64<4,E1>,
                             gint64<4,E2>> q)
{
    gint64<4> a = q.a.eval();
    gint64<4> b = q.b.eval();
    return _mm256_add_epi64(a, b);
}
#endif

template<unsigned N, class E1, class E2>
gint64<N> expr_eval(expr_add<gint64<N,E1>,
                             gint64<N,E2>> q)
{
    gint64<N> a = q.a.eval();
    gint64<N> b = q.b.eval();
    SIMDPP_VEC_ARRAY_IMPL2(gint64<N>, add, a, b);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

