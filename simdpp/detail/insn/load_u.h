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
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// -----------------------------------------------------------------------------

// Each integer type is handled separately because higher aligment guarantees
// offer better performance on e.g. ARM. Note, we don't use LDDQU on SSE,
// because it has usage restrictions and offers improved performance only on
// Pentium 4 era processors.
SIMDPP_INL void i_load_u(uint8x16& a, const char* p)
{
#if SIMDPP_USE_NULL
    detail::null::load(a, p);
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
#elif SIMDPP_USE_NEON
    a = vld1q_u8(reinterpret_cast<const uint8_t*>(p));
#elif SIMDPP_USE_ALTIVEC
    const uint8_t* q = reinterpret_cast<const uint8_t*>(p);
    uint8x16 l1, l2, mask;
    l1 = vec_ld(0, q);
    l2 = vec_ld(16, q);
    mask = vec_lvsl(0, q);
    a = vec_perm((__vector uint8_t)l1, (__vector uint8_t)l2,
                 (__vector uint8_t)mask);
#elif SIMDPP_USE_MSA
    a = (v16u8) __msa_ld_b(p, 0);
#endif
}

SIMDPP_INL void i_load_u(uint16x8& a, const char* p)
{
#if SIMDPP_USE_NULL
    detail::null::load(a, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b;
    i_load_u(b, p);
    a = b;
#elif SIMDPP_USE_NEON
    a = vld1q_u16(reinterpret_cast<const uint16_t*>(p));
#elif SIMDPP_USE_MSA
    a = (v8u16) __msa_ld_h(p, 0);
#endif
}

SIMDPP_INL void i_load_u(uint32x4& a, const char* p)
{
#if SIMDPP_USE_NULL
    detail::null::load(a, p);
#elif SIMDPP_USE_VSX_206
    a = vec_vsx_ld(0, reinterpret_cast<const uint32_t*>(p));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b;
    i_load_u(b, p);
    a = b;
#elif SIMDPP_USE_NEON
    a = vld1q_u32(reinterpret_cast<const uint32_t*>(p));
#elif SIMDPP_USE_MSA
    a = (v4u32) __msa_ld_w(p, 0);
#endif
}

SIMDPP_INL void i_load_u(uint64x2& a, const char* p)
{
#if SIMDPP_USE_NULL
    detail::null::load(a, p);
#elif SIMDPP_USE_SSE2
    uint8x16 b;
    i_load_u(b, p);
    a = b;
#elif SIMDPP_USE_VSX_207
#if SIMDPP_64_BITS
    a = (__vector uint64_t) vec_vsx_ld(0, reinterpret_cast<const uint64_t*>(p));
#else
    // BUG: GCC does not support vec_vsx_ld in 32-bit mode even when
    // VSX 2.07 is enabled
    uint8x16 r;
    i_load_u(r, p);
    a = r;
#endif
#elif SIMDPP_USE_ALTIVEC
    detail::null::load(a, p);
#elif SIMDPP_USE_NEON
    a = vld1q_u64(reinterpret_cast<const uint64_t*>(p));
#elif SIMDPP_USE_MSA
    a = (v2u64) __msa_ld_d(p, 0);
#endif
}

SIMDPP_INL void i_load_u(float32x4& a, const char* p)
{
    const float* q = reinterpret_cast<const float*>(p);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    detail::null::load(a, q);
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_ps(q);
#elif SIMDPP_USE_NEON
    a = vld1q_f32(q);
#elif SIMDPP_USE_VSX_206
    a = vec_vsx_ld(0, q);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 b; (void) q;
    i_load_u(b, p);
    a = b;
#elif SIMDPP_USE_MSA
    a = (v4f32) __msa_ld_w(q, 0);
#endif
}

SIMDPP_INL void i_load_u(float64x2& a, const char* p)
{
    const double* q = reinterpret_cast<const double*>(p);
#if SIMDPP_USE_SSE2
    a = _mm_loadu_pd(q);
#elif SIMDPP_USE_NEON64
    a = vld1q_f64(q);
#elif SIMDPP_USE_VSX_206
    a = vec_vsx_ld(0, q);
#elif SIMDPP_USE_MSA
    a = (v2f64) __msa_ld_d(q, 0);
#elif SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    detail::null::load(a, q);
#else
    SIMDPP_NOT_IMPLEMENTED2(a, p);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void  i_load_u(uint8x32& a,  const char* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
}
SIMDPP_INL void i_load_u(uint16x16& a, const char* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
}
SIMDPP_INL void i_load_u(uint32x8& a,  const char* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
}
SIMDPP_INL void i_load_u(uint64x4& a,  const char* p)
{
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
}
#endif
#if SIMDPP_USE_AVX
SIMDPP_INL void i_load_u(float32x8& a, const char* p)
{
    a = _mm256_loadu_ps(reinterpret_cast<const float*>(p));
}
SIMDPP_INL void i_load_u(float64x4& a, const char* p)
{
    a = _mm256_loadu_pd(reinterpret_cast<const double*>(p));
}
#endif

#if SIMDPP_USE_AVX512BW
SIMDPP_INL void i_load_u(uint8<64>& a, const char* p)
{
    a = _mm512_loadu_si512(p);
}
SIMDPP_INL void i_load_u(uint16<32>& a,  const char* p)
{
    a = _mm512_loadu_si512(p);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_load_u(uint32<16>& a, const char* p)
{
    a = _mm512_loadu_si512(p);
}
SIMDPP_INL void i_load_u(uint64<8>& a,  const char* p)
{
    a = _mm512_loadu_si512(p);
}
SIMDPP_INL void i_load_u(float32<16>& a, const char* p)
{
    a = _mm512_loadu_ps(reinterpret_cast<const float*>(p));
}
SIMDPP_INL void i_load_u(float64<8>& a, const char* p)
{
    a = _mm512_loadu_pd(reinterpret_cast<const double*>(p));
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void i_load_u(V& a, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load_u(a.vec(i), p);
        p += veclen;
    }

}

template<class V>
V i_load_u_any(const char* p)
{
    typename detail::remove_sign<V>::type r;
    i_load_u(r, p);
    return V(r);
}

} // namespace insn

template<class V> SIMDPP_INL
void construct_eval(V& v, const expr_vec_load_u& e)
{
    v = insn::i_load_u_any<V>(e.a);
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

