/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STREAM_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STREAM_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/store.h>
#include <simdpp/detail/null/memory.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL void i_stream(char* p, const uint8<16>& a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    store(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(p));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_stream(char* p, const uint8<32>& a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_si256(reinterpret_cast<__m256i*>(p), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_stream(char* p, const uint16<8>& a)
{
    i_stream(p, uint8<16>(a));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_stream(char* p, const uint16<16>& a)
{
    i_stream(p, uint8<32>(a));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_stream(char* p, const uint32<4>& a)
{
    i_stream(p, uint8<16>(a));
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_stream(char* p, const uint32<8>& a)
{
    i_stream(p, uint8<32>(a));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_stream(char* p, const uint32<16>& a)
{
    p = detail::assume_aligned(p, 64);
    _mm512_stream_si512(reinterpret_cast<__m512i*>(p), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_stream(char* p, const uint64<2>& a)
{
#if SIMDPP_USE_ALTIVEC
    p = detail::assume_aligned(p, 16);
    detail::null::store(p, a);
#else
    i_stream(p, uint8<16>(a));
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_stream(char* p, const uint64<4>& a)
{
    i_stream(p, uint8<32>(a));
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_stream(char* p, const uint64<8>& a)
{
    p = detail::assume_aligned(p, 64);
    _mm512_stream_si512(reinterpret_cast<__m512i*>(p), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_stream(char* p, const float32x4& a)
{
    float* q = reinterpret_cast<float*>(p);
    q = detail::assume_aligned(q, 16);
#if SIMDPP_USE_NULL
    detail::null::store(q, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_ps(q, a);
#elif SIMDPP_USE_NEON
    store(q, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector float)a, 0, q);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_stream(char* p, const float32x8& a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_ps(reinterpret_cast<float*>(p), a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_stream(char* p, const float32<16>& a)
{
    p = detail::assume_aligned(p, 64);
    _mm512_stream_ps(reinterpret_cast<float*>(p), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_stream(char* p, const float64x2& a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    detail::null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_pd(reinterpret_cast<double*>(p), a);
#elif SIMDPP_USE_NEON64
    store(p, a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_stream(char* p, const float64x4& a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_pd(reinterpret_cast<double*>(p), a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_stream(char* p, const float64<8>& a)
{
    p = detail::assume_aligned(p, 64);
    _mm512_stream_pd(reinterpret_cast<double*>(p), a);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void i_stream(char* p, const V& a)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_stream(p, a.vec(i));
        p += veclen;
    }
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

