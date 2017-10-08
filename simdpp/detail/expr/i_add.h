/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_I_ADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/math.h>
#include <simdpp/core/bit_and.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E1, class E2> SIMDPP_INL
uint8<16> expr_eval_add(const uint8<16,E1>& qa,
                        const uint8<16,E2>& qb)
{
    uint8<16> a = qa.eval();
    uint8<16> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi8(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vaddq_u8(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_add(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return (v16u8) __msa_addv_b((v16i8) a.native(), (v16i8) b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint8<32> expr_eval_add(const uint8<32,E1>& qa,
                        const uint8<32,E2>& qb)
{
    uint8<32> a = qa.eval();
    uint8<32> b = qb.eval();
    return _mm256_add_epi8(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
uint8<64> expr_eval_add(const uint8<64,E1>& qa,
                        const uint8<64,E2>& qb)
{
    uint8<64> a = qa.eval();
    uint8<64> b = qb.eval();
    return _mm512_add_epi8(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint8<N> expr_eval_add(const uint8<N,E1>& qa,
                       const uint8<N,E2>& qb)
{
    uint8<N> a = qa.eval();
    uint8<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, add, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint16<8> expr_eval_add(const uint16<8,E1>& qa,
                        const uint16<8,E2>& qb)
{
    uint16<8> a = qa.eval();
    uint16<8> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi16(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vaddq_u16(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_add(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return (v8u16) __msa_addv_h((v8i16) a.native(), (v8i16) b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint16<16> expr_eval_add(const uint16<16,E1>& qa,
                         const uint16<16,E2>& qb)
{
    uint16<16> a = qa.eval();
    uint16<16> b = qb.eval();
    return _mm256_add_epi16(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512BW
template<class R, class E1, class E2> SIMDPP_INL
uint16<32> expr_eval_add(const uint16<32,E1>& qa,
                         const uint16<32,E2>& qb)
{
    uint16<32> a = qa.eval();
    uint16<32> b = qb.eval();
    return _mm512_add_epi16(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint16<N> expr_eval_add(const uint16<N,E1>& qa,
                        const uint16<N,E2>& qb)
{
    uint16<N> a = qa.eval();
    uint16<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, add, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint32<4> expr_eval_add(const uint32<4,E1>& qa,
                        const uint32<4,E2>& qb)
{
    uint32<4> a = qa.eval();
    uint32<4> b = qb.eval();
#if SIMDPP_USE_NULL
    return detail::null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_epi32(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vaddq_u32(a.native(), b.native());
#elif SIMDPP_USE_ALTIVEC
    return vec_add(a.native(), b.native());
#elif SIMDPP_USE_MSA
    return (v4u32) __msa_addv_w((v4i32) a.native(), (v4i32) b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint32<8> expr_eval_add(const uint32<8,E1>& qa,
                        const uint32<8,E2>& qb)
{
    uint32<8> a = qa.eval();
    uint32<8> b = qb.eval();
    return _mm256_add_epi32(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
uint32<16> expr_eval_add(const uint32<16,E1>& qa,
                         const uint32<16,E2>& qb)
{
    uint32<16> a = qa.eval();
    uint32<16> b = qb.eval();
    return _mm512_add_epi32(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint32<N> expr_eval_add(const uint32<N,E1>& qa,
                        const uint32<N,E2>& qb)
{
    uint32<N> a = qa.eval();
    uint32<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, add, a, b);
}

// -----------------------------------------------------------------------------

template<class R, class E1, class E2> SIMDPP_INL
uint64<2> expr_eval_add(const uint64<2,E1>& qa,
                        const uint64<2,E2>& qb)
{
    uint64<2> a = qa.eval();
    uint64<2> b = qb.eval();
#if SIMDPP_USE_SSE2
    return _mm_add_epi64(a.native(), b.native());
#elif SIMDPP_USE_NEON
    return vaddq_u64(a.native(), b.native());
#elif SIMDPP_USE_VSX_207
    return vec_add(a.native(), b.native());
#elif SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::add(a, b);
#elif SIMDPP_USE_MSA
    return (v2u64) __msa_addv_d((v2i64) a.native(), (v2i64) b.native());
#endif
}

#if SIMDPP_USE_AVX2
template<class R, class E1, class E2> SIMDPP_INL
uint64<4> expr_eval_add(const uint64<4,E1>& qa,
                        const uint64<4,E2>& qb)
{
    uint64<4> a = qa.eval();
    uint64<4> b = qb.eval();
    return _mm256_add_epi64(a.native(), b.native());
}
#endif

#if SIMDPP_USE_AVX512F
template<class R, class E1, class E2> SIMDPP_INL
uint64<8> expr_eval_add(const uint64<8,E1>& qa,
                        const uint64<8,E2>& qb)
{
    uint64<8> a = qa.eval();
    uint64<8> b = qb.eval();
    return _mm512_add_epi64(a.native(), b.native());
}
#endif

template<class R, unsigned N, class E1, class E2> SIMDPP_INL
uint64<N> expr_eval_add(const uint64<N,E1>& qa,
                        const uint64<N,E2>& qb)
{
    uint64<N> a = qa.eval();
    uint64<N> b = qb.eval();
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, add, a, b);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

