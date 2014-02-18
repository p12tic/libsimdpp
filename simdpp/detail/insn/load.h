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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// collect some boilerplate here
template<class P, class V>
void v_load(V& a, const P* p);

inline gint8x16 i_load(gint8x16& a, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_si128(reinterpret_cast<const __m128i*>(p));
    return a;
#elif SIMDPP_USE_NEON
    a = vreinterpretq_u32_u64(vld1q_u64(reinterpret_cast<const uint64_t*>(p)));
    return a;
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, reinterpret_cast<const uint8_t*>(p));
    return a;
#endif
}

inline gint16x8 i_load(gint16x8& a, const void* p) { gint8x16 r; i_load(r, p); a = r; return a; }
inline gint32x4 i_load(gint32x4& a, const void* p) { gint8x16 r; i_load(r, p); a = r; return a; }
inline gint64x2 i_load(gint64x2& a, const void* p) { gint8x16 r; i_load(r, p); a = r; return a; }

inline float32x4 i_load(float32x4& a, const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_ps(p);
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_f32(p);
    return a;
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, p);
    return a;
#endif
}

inline float64x2 i_load(float64x2& a, const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_pd(p);
    return a;
#endif
}


#if SIMDPP_USE_AVX2
inline gint8x32  i_load(gint8x32& a,  const void* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline gint16x16 i_load(gint16x16& a, const void* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline gint32x8  i_load(gint32x8& a,  const void* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline gint64x4  i_load(gint64x4& a,  const void* p)
{
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline float32x8 i_load(float32x8& a, const float* p)
{
    a = _mm256_load_ps(p); return a;
}
inline float64x4 i_load(float64x4& a, const double* p)
{
    a = _mm256_load_pd(p); return a;
}
#endif

template<unsigned N>
gint8<N>  i_load(gint8<N>& a,  const void* p)
{
    v_load(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
gint16<N> i_load(gint16<N>& a, const void* p)
{
    v_load(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
gint32<N> i_load(gint32<N>& a, const void* p)
{
    v_load(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
gint64<N> i_load(gint64<N>& a, const void* p)
{
    v_load(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
float32<N> i_load(float32<N>& a, const float* p)
{
    v_load(a, p); return a;
}
template<unsigned N>
float64<N> i_load(float64<N>& a, const double* p)
{
    v_load(a, p); return a;
}

template<class P, class V>
void v_load(V& a, const P* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load(a[i], p);
        p += veclen / sizeof(P);
    }
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

