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
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


template<class V>
void v_stream(char* p, V a);

inline void i_stream(char* p, uint8<16> a)
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
inline void i_stream(char* p, uint8<32> a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_si256(reinterpret_cast<__m256i*>(p), a);
}
#endif

template<unsigned N>
void i_stream(char* p, uint8<N> a)
{
    v_stream(p, a);
}

template<unsigned N>
void i_stream(char* p, uint16<N> a) { i_stream(p, uint8<N*2>(a)); }
template<unsigned N>
void i_stream(char* p, uint32<N> a) { i_stream(p, uint8<N*4>(a)); }
template<unsigned N>
void i_stream(char* p, uint64<N> a) { i_stream(p, uint8<N*8>(a)); }

// -----------------------------------------------------------------------------

inline void i_stream(char* p, float32x4 a)
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
inline void i_stream(char* p, float32x8 a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_ps(reinterpret_cast<float*>(p), a);
}
#endif

template<unsigned N>
void i_stream(char* p, float32<N> a)
{
    v_stream(p, a);
}

// -----------------------------------------------------------------------------

inline void i_stream(char* p, float64x2 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_pd(reinterpret_cast<double*>(p), a);
#endif
}

#if SIMDPP_USE_AVX
inline void i_stream(char* p, float64x4 a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_pd(reinterpret_cast<double*>(p), a);
}
#endif

template<unsigned N>
void i_stream(char* p, float64<N> a)
{
    v_stream(p, a);
}

template<class V>
void v_stream(char* p, V a)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_stream(p, a[i]);
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

