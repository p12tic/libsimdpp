/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_PACKED3_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_PACKED3_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_pack.h>
#include <simdpp/core/store.h>
#include <simdpp/detail/null/memory.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// collect some boilerplate
template<class V> SIMDPP_INL
void v128_store_pack3(char* p, const V& ca, const V& cb, const V& cc);
template<class V> SIMDPP_INL
void v256_store_pack3(char* p, const V& ca, const V& cb, const V& cc);
template<class V> SIMDPP_INL
void v512_store_pack3(char* p, const V& ca, const V& cb, const V& cc);

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_packed3(char* p,
                                const uint8x16& a, const uint8x16& b, const uint8x16& c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint8x16x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u8(reinterpret_cast<uint8_t*>(p), t);
#else
    detail::null::store_packed3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_packed3(char* p,
                                const uint8x32& a, const uint8x32& b, const uint8x32& c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_packed3(char* p,
                                const uint16x8& a, const uint16x8& b, const uint16x8& c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint16x8x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u16(reinterpret_cast<uint16_t*>(p), t);
#else
    detail::null::store_packed3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_packed3(char* p,
                                const uint16x16& a, const uint16x16& b, const uint16x16& c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_packed3(char* p,
                                const uint32x4& a, const uint32x4& b, const uint32x4& c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint32x4x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u32(reinterpret_cast<uint32_t*>(p), t);
#else
    detail::null::store_packed3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_packed3(char* p,
                                const uint32x8& a, const uint32x8& b, const uint32x8& c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_packed3(char* p,
                                const uint32<16>& a, const uint32<16>& b, const uint32<16>& c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_packed3(char* p,
                                const uint64x2& a, const uint64x2& b, const uint64x2& c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON32
    uint64_t* q = reinterpret_cast<uint64_t*>(p);
    uint64x1x2_t t1, t2, t3;
    t1.val[0] = vget_low_u64(a);  t1.val[1] = vget_low_u64(b);
    t2.val[0] = vget_low_u64(c);  t2.val[1] = vget_high_u64(a);
    t3.val[0] = vget_high_u64(b);  t3.val[1] = vget_high_u64(c);

    vst2_u64(q, t1);
    vst2_u64(q+2, t2);
    vst2_u64(q+4, t3);
#elif SIMDPP_USE_NEON64
    uint64x2x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u64(reinterpret_cast<uint64_t*>(p), t);
#else
    detail::null::store_packed3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_packed3(char* p,
                                const uint64x4& a, const uint64x4& b, const uint64x4& c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_packed3(char* p,
                                const uint64<8>& a, const uint64<8>& b, const uint64<8>& c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_packed3(char* p, const float32x4& a, const float32x4& b, const float32x4& c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    float32x4x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_f32(reinterpret_cast<float*>(p), t);
#else
    detail::null::store_packed3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_packed3(char* p,
                                const float32x8& a, const float32x8& b, const float32x8& c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_packed3(char* p,
                                const float32<16>& a, const float32<16>& b, const float32<16>& c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_packed3(char* p, const float64x2& a, const float64x2& b, const float64x2& c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON64
    float64x2x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_f64(reinterpret_cast<double*>(p), t);
#else
    detail::null::store_packed3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_packed3(char* p,
                                const float64x4& a, const float64x4& b, const float64x4& c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_packed3(char* p,
                                const float64<8>& a, const float64<8>& b, const float64<8>& c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void v128_store_pack3(char* p, const V& ca, const V& cb, const V& cc)
{
    p = detail::assume_aligned(p, 16);
    V a = ca, b = cb, c = cc;
    mem_pack3(a, b, c);
    i_store(p, a);
    i_store(p + 16, b);
    i_store(p + 32, c);
}

template<class V> SIMDPP_INL
void v256_store_pack3(char* p, const V& ca, const V& cb, const V& cc)
{
    p = detail::assume_aligned(p, 32);
    V a = ca, b = cb, c = cc;
    mem_pack3(a, b, c);
    i_store(p, a);
    i_store(p + 32, b);
    i_store(p + 64, c);
}

template<class V> SIMDPP_INL
void v512_store_pack3(char* p, const V& ca, const V& cb, const V& cc)
{
    p = detail::assume_aligned(p, 64);
    V a = ca, b = cb, c = cc;
    mem_pack3(a, b, c);
    i_store(p, a);
    i_store(p + 64, b);
    i_store(p + 128, c);
}

template<class V> SIMDPP_INL
void i_store_packed3(char* p, const V& ca, const V& cb, const V& cc)
{
    typename detail::remove_sign<V>::type a = ca, b = cb, c = cc;
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_store_packed3(p, a.vec(i), b.vec(i), c.vec(i));
        p += veclen*3;
    }
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
