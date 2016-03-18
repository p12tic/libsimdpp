/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/types/traits.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/core/transpose.h>
#include <simdpp/detail/null/memory.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL void i_load(uint8x16& a, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::load(a, p);
#elif SIMDPP_USE_SSE2
    a = _mm_load_si128(reinterpret_cast<const __m128i*>(p));
#elif SIMDPP_USE_NEON
    a = vreinterpretq_u8_u64(vld1q_u64(reinterpret_cast<const uint64_t*>(p)));
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, reinterpret_cast<const uint8_t*>(p));
#endif
}

SIMDPP_INL void i_load(uint16x8& a, const char* p) { uint8x16 r; i_load(r, p); a = r;  }
SIMDPP_INL void i_load(uint32x4& a, const char* p) { uint8x16 r; i_load(r, p); a = r;  }

SIMDPP_INL void i_load(uint64x2& a, const char* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    const uint64_t* q = reinterpret_cast<const uint64_t*>(p);
    q = detail::assume_aligned(q, 16);
    detail::null::load(a, q);
#else
    uint8x16 r; i_load(r, p); a = r;
#endif
}

SIMDPP_INL void i_load(float32x4& a, const char* p)
{
    const float* q = reinterpret_cast<const float*>(p);
    q = detail::assume_aligned(q, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    detail::null::load(a, q);
#elif SIMDPP_USE_SSE2
    a = _mm_load_ps(q);
#elif SIMDPP_USE_NEON
    a = vld1q_f32(q);
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, q);
#endif
}

SIMDPP_INL void i_load(float64x2& a, const char* p)
{
    const double* q = reinterpret_cast<const double*>(p);
    q = detail::assume_aligned(q, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON32
    detail::null::load(a, q);
#elif SIMDPP_USE_SSE2
    a = _mm_load_pd(q);
#elif SIMDPP_USE_NEON64
    a = vld1q_f64(q);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load(uint8x32& a,  const char* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p));
}
SIMDPP_INL void i_load(uint16x16& a, const char* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p));
}
SIMDPP_INL void i_load(uint32x8& a,  const char* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p));
}
SIMDPP_INL void i_load(uint64x4& a,  const char* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p));
}
#endif
#if SIMDPP_USE_AVX
SIMDPP_INL void i_load(float32x8& a, const char* p)
{
    a = _mm256_load_ps(reinterpret_cast<const float*>(p));
}
SIMDPP_INL void i_load(float64x4& a, const char* p)
{
    a = _mm256_load_pd(reinterpret_cast<const double*>(p));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_load(uint32<16>& a,  const char* p)
{
    a = _mm512_load_epi32(p);
}
SIMDPP_INL void i_load(uint64<8>& a,  const char* p)
{
    a = _mm512_load_epi64(p);
}
SIMDPP_INL void i_load(float32<16>& a, const char* p)
{
    a = _mm512_load_ps(p);
}
SIMDPP_INL void i_load(float64<8>& a, const char* p)
{
    a = _mm512_load_pd(p);
}
#endif

template<class V> SIMDPP_INL
void i_load(V& a, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load(a.vec(i), p);
        p += veclen;
    }
}

template<class V> SIMDPP_INL
V i_load_any(const char* p)
{
    typename detail::remove_sign<V>::type r;
    i_load(r, p);
    return V(r);
}

} // namespace insn

template<class V> SIMDPP_INL
void construct_eval(V& v, const expr_vec_load& e)
{
    v = insn::i_load_any<V>(e.a);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

