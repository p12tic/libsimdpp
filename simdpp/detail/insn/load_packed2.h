/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_PACKED2_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_PACKED2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/core/load.h>
#include <simdpp/detail/null/memory.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


// collect some boilerplate
template<class V> SIMDPP_INL
void v128_load_packed2(V& a, V& b, const char* p);
template<class V> SIMDPP_INL
void v256_load_packed2(V& a, V& b, const char* p);
template<class V> SIMDPP_INL
void v512_load_packed2(V& a, V& b, const char* p);

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_packed2(uint8x16& a, uint8x16& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_load_packed2(a, b, p);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
#else
    detail::null::load_packed2(a, b, p);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_packed2(uint8x32& a, uint8x32& b, const char* p)
{
    v256_load_packed2(a, b, p);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_packed2(uint16x8& a, uint16x8& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_load_packed2(a, b, p);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
#else
    detail::null::load_packed2(a, b, p);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_packed2(uint16x16& a, uint16x16& b, const char* p)
{
    v256_load_packed2(a, b, p);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_packed2(uint32x4& a, uint32x4& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_load_packed2(a, b, p);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
#else
    detail::null::load_packed2(a, b, p);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_packed2(uint32x8& a, uint32x8& b, const char* p)
{
    v256_load_packed2(a, b, p);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_load_packed2(uint32<16>& a, uint32<16>& b, const char* p)
{
    v512_load_packed2(a, b, p);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_packed2(uint64x2& a, uint64x2& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    detail::null::load_packed2(a, b, p);
#elif SIMDPP_USE_NEON64
    auto r = vld2q_u64(reinterpret_cast<const uint64_t*>(p));
    a = r.val[0];
    b = r.val[1];
#else
    v128_load_packed2(a, b, p);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_packed2(uint64x4& a, uint64x4& b, const char* p)
{
    v256_load_packed2(a, b, p);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_load_packed2(uint64<8>& a, uint64<8>& b, const char* p)
{
    v512_load_packed2(a, b, p);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_packed2(float32x4& a, float32x4& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_load_packed2(a, b, p);
#elif SIMDPP_USE_NEON
    auto r = vld2q_f32(reinterpret_cast<const float*>(p));
    a = r.val[0];
    b = r.val[1];
#else
    detail::null::load_packed2(a, b, p);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_load_packed2(float32x8& a, float32x8& b, const char* p)
{
    v256_load_packed2(a, b, p);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_load_packed2(float32<16>& a, float32<16>& b, const char* p)
{
    v512_load_packed2(a, b, p);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_packed2(float64x2& a, float64x2& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    detail::null::load_packed2(a, b, p);
#elif SIMDPP_USE_NEON64
    auto r = vld2q_f64(reinterpret_cast<const double*>(p));
    a = r.val[0];
    b = r.val[1];
#else
    v128_load_packed2(a, b, p);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_load_packed2(float64x4& a, float64x4& b, const char* p)
{
    v256_load_packed2(a, b, p);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_load_packed2(float64<8>& a, float64<8>& b, const char* p)
{
    v512_load_packed2(a, b, p);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void v128_load_packed2(V& a, V& b, const char* p)
{
    p = detail::assume_aligned(p, 16);
    a = load(p);
    b = load(p + 16);
    mem_unpack2(a, b);
}

template<class V> SIMDPP_INL
void v256_load_packed2(V& a, V& b, const char* p)
{
    p = detail::assume_aligned(p, 32);
    a = load(p);
    b = load(p + 32);
    mem_unpack2(a, b);
}

template<class V> SIMDPP_INL
void v512_load_packed2(V& a, V& b, const char* p)
{
    p = detail::assume_aligned(p, 64);
    a = load(p);
    b = load(p + 64);
    mem_unpack2(a, b);
}

template<class V> SIMDPP_INL
void i_load_packed2(V& a, V& b, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load_packed2(a.vec(i), b.vec(i), p);
        p += veclen*2;
    }
}


} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

