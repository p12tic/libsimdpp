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
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V>
struct is_expr_vec_load { static const bool value = false; };
template<>
struct is_expr_vec_load<expr_vec_load> { static const bool value = true; };

namespace insn {

// collect some boilerplate here
template<class V> SIMDPP_INL
void v_load(V& a, const char* p);

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
SIMDPP_INL void i_load(uint64x2& a, const char* p) { uint8x16 r; i_load(r, p); a = r;  }

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

#if SIMDPP_USE_AVX512
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

template<unsigned N> SIMDPP_INL
void i_load(uint8<N>& a,  const char* p) { v_load(a, p); }
template<unsigned N> SIMDPP_INL
void i_load(uint16<N>& a, const char* p) { v_load(a, p); }
template<unsigned N> SIMDPP_INL
void i_load(uint32<N>& a, const char* p) { v_load(a, p); }
template<unsigned N> SIMDPP_INL
void i_load(uint64<N>& a, const char* p) { v_load(a, p); }
template<unsigned N> SIMDPP_INL
void i_load(float32<N>& a, const char* p){ v_load(a, p); }
template<unsigned N> SIMDPP_INL
void i_load(float64<N>& a, const char* p){ v_load(a, p); }

template<class V> SIMDPP_INL
void v_load(V& a, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load(a.vec(i), p);
        p += veclen;
    }
}

template<class V>
struct i_load_dispatch {
    static V run(const char* p)
    {
        V r;
        i_load(r, p);
        return r;
    }
};

template<>
struct i_load_dispatch<expr_vec_load> {
    static expr_vec_load run(const char* p)
    {
        expr_vec_load r;
        r.a = p;
        return r;
    }
};

} // namespace insn

template<class V> SIMDPP_INL
void construct_eval(V& v, const expr_vec_load& e)
{
    typename detail::remove_sign<V>::type r;
    insn::i_load(r, e.a);
    v = r;
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

