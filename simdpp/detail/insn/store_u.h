/*  Copyright (C) 2015

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_U_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_U_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/memory.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/cast.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

SIMDPP_INL void i_store_u(char* p, const uint8<16>& a)
{
#if SIMDPP_USE_NULL
    detail::null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u8(reinterpret_cast<uint8_t*>(p), a);
#elif SIMDPP_USE_ALTIVEC
    // From https://web.archive.org/web/20110305043420/http://developer.apple.com/hardwaredrivers/ve/alignment.html
    uint8_t* q = reinterpret_cast<uint8_t*>(p);
    __vector uint8_t MSQ, LSQ, edges;
    __vector uint8_t edgeAlign, align;
    MSQ = vec_ld(0, q);                                 // most significant quadword
    LSQ = vec_ld(15, q);                                // least significant quadword
    edgeAlign = vec_lvsl(0, q);                         // permute map to extract edges
    edges = vec_perm(LSQ, MSQ, edgeAlign);              // extract the edges
    align = vec_lvsr(0, q);                             // permute map to misalign data
    MSQ = vec_perm(edges, (__vector uint8_t)a, align);  // misalign the data (MSQ)
    LSQ = vec_perm((__vector uint8_t)a, edges, align);  // misalign the data (LSQ)
    vec_st(LSQ, 15, q);                                 // Store the LSQ part first
    vec_st(MSQ, 0, q);                                  // Store the MSQ part
#endif
}

SIMDPP_INL void i_store_u(char* p, const uint16<8>& a)
{
#if SIMDPP_USE_NEON
    vst1q_u16(reinterpret_cast<uint16_t*>(p), a);
#else
    i_store_u(p, uint8<16>(a));
#endif
}

SIMDPP_INL void i_store_u(char* p, const uint32<4>& a)
{
#if SIMDPP_USE_NEON
    vst1q_u32(reinterpret_cast<uint32_t*>(p), a);
#else
    i_store_u(p, uint8<16>(a));
#endif
}

SIMDPP_INL void i_store_u(char* p, const uint64<2>& a)
{
#if SIMDPP_USE_NEON
    vst1q_u64(reinterpret_cast<uint64_t*>(p), a);
#else
    i_store_u(p, uint8<16>(a));
#endif
}

SIMDPP_INL void i_store_u(char* p, const float32x4& a)
{
    float* q = reinterpret_cast<float*>(p);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    detail::null::store(q, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_ps(q, a);
#elif SIMDPP_USE_NEON
    vst1q_f32(q, a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 b = bit_cast<uint32x4>(a.eval());
    i_store_u(reinterpret_cast<char*>(q), b);
#endif
}

SIMDPP_INL void i_store_u(char* p, const float64x2& a)
{
    double* q = reinterpret_cast<double*>(p);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    detail::null::store(q, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_pd(q, a);
#elif SIMDPP_USE_NEON64
    vst1q_f64(q, a);
#endif
}


#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_u(char* p, const uint8<32>& a)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
}

SIMDPP_INL void i_store_u(char* p, const uint16<16>& a)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
}

SIMDPP_INL void i_store_u(char* p, const uint32<8>& a)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
}

SIMDPP_INL void i_store_u(char* p, const uint64<4>& a)
{
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
}
#endif

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_u(char* p, const float32x8& a)
{
    _mm256_storeu_ps(reinterpret_cast<float*>(p), a);
}

SIMDPP_INL void i_store_u(char* p, const float64x4& a)
{
    _mm256_storeu_pd(reinterpret_cast<double*>(p), a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_u(char* p, const uint32<16>& a)
{
    _mm512_storeu_si512(reinterpret_cast<__m512i*>(p), a);
}

SIMDPP_INL void i_store_u(char* p, const uint64<8>& a)
{
    _mm512_storeu_si512(reinterpret_cast<__m512i*>(p), a);
}

SIMDPP_INL void i_store_u(char* p, const float32<16>& a)
{
    _mm512_storeu_ps(p, a);
}

SIMDPP_INL void i_store_u(char* p, const float64<8>& a)
{
    _mm512_storeu_pd(p, a);
}
#endif

template<class V> SIMDPP_INL
void v_store_u(char* p, const V& a)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_store_u(p, a.vec(i));
        p += veclen;
    }
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

