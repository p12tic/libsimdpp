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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STREAM_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STREAM_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/store.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


template<class V>
void v_stream(char* p, V a);

inline void i_stream(void* p, gint8<16> a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    store(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(p));
#endif
}

#if SIMDPP_USE_AVX2
inline void i_stream(void* p, gint8<32> a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_si256(reinterpret_cast<__m256i*>(p), a);
}
#endif

template<unsigned N>
void i_stream(void* p, gint8<N> a)
{
    v_stream(reinterpret_cast<char*>(p), a);
}

template<unsigned N>
void i_stream(void* p, gint16<N> a) { i_stream(p, gint8<N*2>(a)); }
template<unsigned N>
void i_stream(void* p, gint32<N> a) { i_stream(p, gint8<N*4>(a)); }
template<unsigned N>
void i_stream(void* p, gint64<N> a) { i_stream(p, gint8<N*8>(a)); }

// -----------------------------------------------------------------------------

inline void i_stream(void* p, float32x4 a)
{
    float* q = reinterpret_cast<float*>(p);
    q = detail::assume_aligned(q, 16);
#if SIMDPP_USE_NULL
    null::store(q, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_ps(q, a);
#elif SIMDPP_USE_NEON
    store(q, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector float)a, 0, q);
#endif
}

#if SIMDPP_USE_AVX
inline void i_stream(void* p, float32x8 a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_ps(reinterpret_cast<double*>(p), a);
}
#endif

template<unsigned N>
void i_stream(void* p, float32<N> a)
{
    v_stream(reinterpret_cast<char*>(p), a);
}

// -----------------------------------------------------------------------------

inline void i_stream(void* p, float64x2 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_pd(reinterpret_cast<double*>(p), a);
#endif
}

#if SIMDPP_USE_AVX
inline void i_stream(void* p, float64x4 a)
{
    p = detail::assume_aligned(p, 32);
    _mm256_stream_pd(reinterpret_cast<double*>(p), a);
}
#endif

template<unsigned N>
void i_stream(void* p, float64<N> a)
{
    v_stream(reinterpret_cast<char*>(p), a);
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

