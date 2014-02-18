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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_NEG_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {


template<class E>
int8<16> expr_eval(expr_neg<int8<16,E>> q)
{
    int8<16> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(int8x16::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s8(a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
int8<32> expr_eval(expr_neg<int8<32,E>> q)
{
    int8<32> a = q.a.eval();
    return sub(int8x32::zero(), a);
}
#endif

template<unsigned N, class E>
int8<N> expr_eval(expr_neg<int8<N,E>> q)
{
    int8<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int8<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class E>
int16<8> expr_eval(expr_neg<int16<8,E>> q)
{
    int16<8> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(int16x8::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s16(a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
int16<16> expr_eval(expr_neg<int16<16,E>> q)
{
    int16<16> a = q.a.eval();
    return sub(int16x16::zero(), a);
}
#endif

template<unsigned N, class E>
int16<N> expr_eval(expr_neg<int16<N,E>> q)
{
    int16<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int16<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class E>
int32<4> expr_eval(expr_neg<int32<4,E>> q)
{
    int32<4> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return sub(int32x4::zero(), a);
#elif SIMDPP_USE_NEON
    return vnegq_s32(a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
int32<8> expr_eval(expr_neg<int32<8,E>> q)
{
    int32<8> a = q.a.eval();
    return sub(int32x8::zero(), a);
}
#endif

template<unsigned N, class E>
int32<N> expr_eval(expr_neg<int32<N,E>> q)
{
    int32<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int32<N>, neg, a);
}

// -----------------------------------------------------------------------------

template<class E>
int64<2> expr_eval(expr_neg<int64<2,E>> q)
{
    int64<2> a = q.a.eval();
#if SIMDPP_USE_NULL
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return sub(int64x2::zero(), a);
#endif
}

#if SIMDPP_USE_AVX2
template<class E>
uint64<4> expr_eval(expr_neg<int64<4,E>> q)
{
    int64<4> a = q.a.eval();
    return sub(int64x4::zero(), a);
}
#endif

template<unsigned N, class E>
uint64<N> expr_eval(expr_neg<int64<N,E>> q)
{
    int64<N> a = q.a.eval();
    SIMDPP_VEC_ARRAY_IMPL1(int64<N>, neg, a);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

