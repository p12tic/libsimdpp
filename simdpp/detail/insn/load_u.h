/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_U_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_U_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/transpose.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/detail/null/memory.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V>
struct is_expr_vec_load_u { static const bool value = false; };
template<>
struct is_expr_vec_load_u<expr_vec_load_u> { static const bool value = true; };

namespace insn {


// collect some boilerplate here
template<class V> SIMDPP_INL
void v_load_u(V& a, const char* p);

// -----------------------------------------------------------------------------

// Each integer type is handled separately because higher aligment guarantees
// offer better performance on e.g. ARM. Note, we don't use LDDQU on SSE,
// because it has usage restrictions and offers improved performance only on
// Pentium 4 era processors.
SIMDPP_INL uint8x16 i_load_u(uint8x16& a, const void* p)
{
#if SIMDPP_USE_NULL
    detail::null::load(a, p);
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
    a = vec_perm((__vector uint8_t)l1, (__vector uint8_t)l2,
                 (__vector uint8_t)mask);
    return a;
#endif
}

SIMDPP_INL uint16x8 i_load_u(uint16x8& a, const void* p)
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

SIMDPP_INL uint32x4 i_load_u(uint32x4& a, const void* p)
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

SIMDPP_INL uint64x2 i_load_u(uint64x2& a, const void* p)
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

SIMDPP_INL float32x4 i_load_u(float32x4& a, const void* p)
{
    const float* q = reinterpret_cast<const float*>(p);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    detail::null::load(a, q);
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

SIMDPP_INL float64x2 i_load_u(float64x2& a, const void* p)
{
    const double* q = reinterpret_cast<const double*>(p);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON32
    detail::null::load(a, q);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_pd(q);
    return a;
#elif SIMDPP_USE_NEON64
    a = vld1q_f64(q);
    return a;
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, p);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32  i_load_u(uint8x32& a,  const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
SIMDPP_INL uint16x16 i_load_u(uint16x16& a, const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
SIMDPP_INL uint32x8  i_load_u(uint32x8& a,  const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
SIMDPP_INL uint64x4  i_load_u(uint64x4& a,  const void* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return a;
}
#endif
#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_load_u(float32x8& a, const void* p)
{
    a = _mm256_loadu_ps(reinterpret_cast<const float*>(p)); return a;
}
SIMDPP_INL float64x4 i_load_u(float64x4& a, const void* p)
{
    a = _mm256_loadu_pd(reinterpret_cast<const double*>(p)); return a;
}
#endif
#if SIMDPP_USE_AVX512
SIMDPP_INL uint32<16> i_load_u(uint32<16>& a, const void* p)
{
    a = _mm512_loadu_si512(p); return a;
}
SIMDPP_INL uint64<8> i_load_u(uint64<8>& a,  const void* p)
{
    a = _mm512_loadu_si512(p); return a;
}
SIMDPP_INL float32<16> i_load_u(float32<16>& a, const void* p)
{
    a = _mm512_loadu_ps(p); return a;
}
SIMDPP_INL float64<8> i_load_u(float64<8>& a, const void* p)
{
    a = _mm512_loadu_pd(p); return a;
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N>  i_load_u(uint8<N>& a,  const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N> SIMDPP_INL
uint16<N> i_load_u(uint16<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N> SIMDPP_INL
uint32<N> i_load_u(uint32<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N> SIMDPP_INL
uint64<N> i_load_u(uint64<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N> SIMDPP_INL
float32<N> i_load_u(float32<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}
template<unsigned N> SIMDPP_INL
float64<N> i_load_u(float64<N>& a, const void* p)
{
    v_load_u(a, reinterpret_cast<const char*>(p)); return a;
}

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void v_load_u(V& a, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load_u(a.vec(i), p);
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

template<class V> SIMDPP_INL
void construct_eval(V& v, const expr_vec_load_u& e)
{
    typename detail::remove_sign<V>::type r;
    insn::i_load_u(r, e.a);
    v = r;
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

