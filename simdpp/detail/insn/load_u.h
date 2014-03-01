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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_U_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_U_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V>
struct is_expr_vec_load_u { static const bool value = false; };
template<>
struct is_expr_vec_load_u<expr_vec_load_u> { static const bool value = true; };

namespace insn {


// collect some boilerplate here
template<class V>
void v_load_u(V& a, const char* p);

// -----------------------------------------------------------------------------

// Each integer type is handled separately because higher aligment guarantees
// offer better performance on e.g. ARM. Note, we don't use LDDQU on SSE,
// because it has usage restrictions and offers improved performance only on
// Pentium 4 era processors.
inline gint8x16 i_load_u(gint8x16& a, const void* p)
{
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u8(reinterpret_cast<const uint8_t*>(p));
    return a;
#elif SIMDPP_USE_ALTIVEC
    const uint8_t* q = reinterpret_cast<const uint8_t*>(p);
    uint8x16 l1, l2, mask;
    l1 = vec_ldl(0, q);
    l2 = vec_ldl(16, q);
    mask = vec_lvsl(0, q);
    l1 = vec_perm((__vector uint8_t)l1, (__vector uint8_t)l2,
                 (__vector uint8_t)mask);
    return l1;
#endif
}

inline gint16x8 i_load_u(gint16x8& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b = i_load_u(b, p);
    a = b;
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u16(reinterpret_cast<const uint16_t*>(p));
    return a;
#endif
}

inline gint32x4 i_load_u(gint32x4& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b = i_load_u(b, p);
    a = b;
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u32(reinterpret_cast<const uint32_t*>(p));
    return a;
#endif
}

inline gint64x2 i_load_u(gint64x2& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b = i_load_u(b, p);
    a = b;
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u64(reinterpret_cast<const uint64_t*>(p));
    return a;
#endif
}

inline float32x4 i_load_u(float32x4& a, const void* p)
{
    const float* q = reinterpret_cast<const float*>(p);
#if SIMDPP_USE_NULL
    null::load(a, q);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_ps(q);
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_f32(q);
    return a;
#elif SIMDPP_USE_ALTIVEC
    uint32x4 b = i_load_u(b, reinterpret_cast<const uint32_t*>(q));
    a = b;
    return a;
#endif
}

inline float64x2 i_load_u(float64x2& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_pd(reinterpret_cast<const double*>(p));
    return a;
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, p);
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32  i_load_u(gint8x32& a,  const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline gint16x16 i_load_u(gint16x16& a, const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline gint32x8  i_load_u(gint32x8& a,  const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline gint64x4  i_load_u(gint64x4& a,  const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
inline float32x8 i_load_u(float32x8& a, const void* p)
{
    a = _mm256_loadu_ps(reinterpret_cast<const float*>(p)); return a;
}
inline float64x4 i_load_u(float64x4& a, const void* p)
{
    a = _mm256_loadu_pd(reinterpret_cast<const double*>(p)); return a;
}
#endif

template<unsigned N>
gint8<N>  i_load_u(gint8<N>& a,  const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
gint16<N> i_load_u(gint16<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
gint32<N> i_load_u(gint32<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
gint64<N> i_load_u(gint64<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
float32<N> i_load_u(float32<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N>
float64<N> i_load_u(float64<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}

// -----------------------------------------------------------------------------

template<class V>
void v_load_u(V& a, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load_u(a[i], p);
        p += veclen;
    }
}

template<class V>
struct i_load_u_dispatch {
    static V run(const char* p)
    {
        V r;
        i_load_u(r, p);
        return r;
    }
};

template<>
struct i_load_u_dispatch<expr_vec_load_u> {
    static expr_vec_load_u run(const char* p)
    {
        expr_vec_load_u r;
        r.a = p;
        return r;
    }
};

} // namespace insn

template<class V>
void construct_eval(V& v, const expr_vec_load_u& e)
{
    insn::i_load_u(v, e.a);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

