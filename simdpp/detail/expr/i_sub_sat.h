/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_SAT_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_SUB_SAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>
#include <simdpp/detail/vector_array_macros.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E1, class E2> SIMDPP_INL
int8<16> expr_eval_sub_sat(const int8<16,E1>& qa,
                           const int8<16,E2>& qb)
{
    int8<16> a = qa.eval();
    int8<16> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi8(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vqsubq_s8(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_subs(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return __msa_subs_s_b(a.native(), b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int8<32> expr_eval_sub_sat(const int8<32,E1>& qa,
                           const int8<32,E2>& qb)
{
    int8<32> a = qa.eval();
    int8<32> b = qb.eval();
    return _mm256_subs_epi8(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
int8<64> expr_eval_sub_sat(const int8<64,E1>& qa,
                           const int8<64,E2>& qb)
{
    int8<64> a = qa.eval();
    int8<64> b = qb.eval();
    return _mm512_subs_epi8(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int8<N> expr_eval_sub_sat(const int8<N,E1>& qa,
                          const int8<N,E2>& qb)
{
    int8<N> a = qa.eval();
    int8<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, sub_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
int16<8> expr_eval_sub_sat(const int16<8,E1>& qa,
                           const int16<8,E2>& qb)
{
    int16<8> a = qa.eval();
    int16<8> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epi16(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vqsubq_s16(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_subs(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return __msa_subs_s_h(a.native(), b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
int16<16> expr_eval_sub_sat(const int16<16,E1>& qa,
                            const int16<16,E2>& qb)
{
    int16<16> a = qa.eval();
    int16<16> b = qb.eval();
    return _mm256_subs_epi16(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
int16<32> expr_eval_sub_sat(const int16<32,E1>& qa,
                            const int16<32,E2>& qb)
{
    int16<32> a = qa.eval();
    int16<32> b = qb.eval();
    return _mm512_subs_epi16(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
int16<N> expr_eval_sub_sat(const int16<N,E1>& qa,
                           const int16<N,E2>& qb)
{
    int16<N> a = qa.eval();
    int16<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, sub_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint8<16> expr_eval_sub_sat(const uint8<16,E1>& qa,
                            const uint8<16,E2>& qb)
{
    uint8<16> a = qa.eval();
    uint8<16> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu8(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vqsubq_u8(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_subs(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return __msa_subs_u_b(a.native(), b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint8<32> expr_eval_sub_sat(const uint8<32,E1>& qa,
                            const uint8<32,E2>& qb)
{
    uint8<32> a = qa.eval();
    uint8<32> b = qb.eval();
    return _mm256_subs_epu8(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
uint8<64> expr_eval_sub_sat(const uint8<64,E1>& qa,
                            const uint8<64,E2>& qb)
{
    uint8<64> a = qa.eval();
    uint8<64> b = qb.eval();
    return _mm512_subs_epu8(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint8<N> expr_eval_sub_sat(const uint8<N,E1>& qa,
                           const uint8<N,E2>& qb)
{
    uint8<N> a = qa.eval();
    uint8<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, sub_sat, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval_sub_sat(const uint16<8,E1>& qa,
                            const uint16<8,E2>& qb)
{
    uint16<8> a = qa.eval();
    uint16<8> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::sub_sat(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_subs_epu16(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vqsubq_u16(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_subs(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return __msa_subs_u_h(a.native(), b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval_sub_sat(const uint16<16,E1>& qa,
                             const uint16<16,E2>& qb)
{
    uint16<16> a = qa.eval();
    uint16<16> b = qb.eval();
    return _mm256_subs_epu16(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
uint16<32> expr_eval_sub_sat(const uint16<32,E1>& qa,
                             const uint16<32,E2>& qb)
{
    uint16<32> a = qa.eval();
    uint16<32> b = qb.eval();
    return _mm512_subs_epu16(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval_sub_sat(const uint16<N,E1>& qa,
                            const uint16<N,E2>& qb)
{
    uint16<N> a = qa.eval();
    uint16<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, sub_sat, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

