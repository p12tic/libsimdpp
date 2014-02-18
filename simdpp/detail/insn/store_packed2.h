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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_PACKED2_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_PACKED2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_pack.h>
#include <simdpp/core/store.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class P, class V>
void v256_store_pack2(P* p, V a, V b);
template<class P, class V>
void v_store_pack2(P* p, V a, V b);

// -----------------------------------------------------------------------------

inline void i_store_packed2(void* p, gint8x16 a, gint8x16 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    mem_pack2(a, b);
    i_store(q, a);
    i_store(q+16, b);
#elif SIMDPP_USE_NEON
    uint8x16x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_u8(reinterpret_cast<uint8_t*>(p), t);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed2(void* p, gint8x32 a, gint8x32 b)
{
    v256_store_pack2(reinterpret_cast<char*>(p), a, b);
}
#endif

template<unsigned N>
void i_store_packed2(void* p, gint8<N> a, gint8<N> b)
{
    v_store_pack2(reinterpret_cast<char*>(p), a, b);
}

// -----------------------------------------------------------------------------

inline void i_store_packed2(void* p, gint16x8 a, gint16x8 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    mem_pack2(a, b);
    i_store(q, a);
    i_store(q+16, b);
#elif SIMDPP_USE_NEON
    uint16x8x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_u16(reinterpret_cast<uint16_t*>(p), t);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed2(void* p, gint16x16 a, gint16x16 b)
{
    v256_store_pack2(reinterpret_cast<char*>(p), a, b);
}
#endif

template<unsigned N>
void i_store_packed2(void* p, gint16<N> a, gint16<N> b)
{
    v_store_pack2(reinterpret_cast<char*>(p), a, b);
}

// -----------------------------------------------------------------------------

inline void i_store_packed2(void* p, gint32x4 a, gint32x4 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    mem_pack2(a, b);
    i_store(q, a);
    i_store(q+16, b);
#elif SIMDPP_USE_NEON
    uint32x4x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_u32(reinterpret_cast<uint32_t*>(p), t);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed2(void* p, gint32x8 a, gint32x8 b)
{
    v256_store_pack2(reinterpret_cast<char*>(p), a, b);
}
#endif

template<unsigned N>
void i_store_packed2(void* p, gint32<N> a, gint32<N> b)
{
    v_store_pack2(reinterpret_cast<char*>(p), a, b);
}

// -----------------------------------------------------------------------------

inline void i_store_packed2(void* p, gint64x2 a, gint64x2 b)
{
    p = detail::assume_aligned(p, 16);
    char* q = reinterpret_cast<char*>(p);
    transpose2(a, b);
    i_store(q, a);
    i_store(q+16, b);
}

#if SIMDPP_USE_AVX2
inline void i_store_packed2(void* p, gint64x4 a, gint64x4 b)
{
    v256_store_pack2(reinterpret_cast<char*>(p), a, b);
}
#endif

template<unsigned N>
void i_store_packed2(void* p, gint64<N> a, gint64<N> b)
{
    v_store_pack2(reinterpret_cast<char*>(p), a, b);
}

// -----------------------------------------------------------------------------

inline void i_store_packed2(float* p, float32x4 a, float32x4 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    mem_pack2(a, b);
    i_store(p, a);
    i_store(p+4, b);
#elif SIMDPP_USE_NEON
    float32x4x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_f32(p, t);
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_packed2(float* p, float32x8 a, float32x8 b)
{
    v256_store_pack2(p, a, b);
}
#endif

template<unsigned N>
void i_store_packed2(float* p, float32<N> a, float32<N> b)
{
    v_store_pack2(p, a, b);
}

// -----------------------------------------------------------------------------

inline void i_store_packed2(double* p, float64x2 a, float64x2 b)
{
    p = detail::assume_aligned(p, 16);
    transpose2(a, b);
    i_store(p, a);
    i_store(p+2, b);
}

#if SIMDPP_USE_AVX
inline void i_store_packed2(double* p, float64x4 a, float64x4 b)
{
    v256_store_pack2(p, a, b);
}
#endif

template<unsigned N>
void i_store_packed2(double* p, float64<N> a, float64<N> b)
{
    v_store_pack2(p, a, b);
}

// -----------------------------------------------------------------------------

template<class P, class V>
void v256_store_pack2(P* p, V a, V b)
{
    p = detail::assume_aligned(p, 32);
    mem_pack2(a, b);
    i_store(p, a);
    i_store(p + 32 / sizeof(P), b);
}

template<class P, class V>
void v_store_pack2(P* p, V a, V b)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_store_packed2(p, a[i], b[i]);
        p += veclen*2 / sizeof(P);
    }
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

