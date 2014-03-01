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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_PACKED2_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_PACKED2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/core/load.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_load_packed2(V& a, V& b, const char* p);
template<class V>
void v_load_packed2(V& a, V& b, const char* p);

// -----------------------------------------------------------------------------

inline void i_load_packed2(gint8x16& a, gint8x16& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

#if SIMDPP_USE_AVX2
inline void i_load_packed2(gint8x32& a, gint8x32& b, const void* p)
{
    v256_load_packed2(a, b, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed2(gint8<N>& a, gint8<N>& b, const void* p)
{
    v_load_packed2(a, b, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed2(gint16x8& a, gint16x8& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

#if SIMDPP_USE_AVX2
inline void i_load_packed2(gint16x16& a, gint16x16& b, const void* p)
{
    v256_load_packed2(a, b, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed2(gint16<N>& a, gint16<N>& b, const void* p)
{
    v_load_packed2(a, b, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed2(gint32x4& a, gint32x4& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

#if SIMDPP_USE_AVX2
inline void i_load_packed2(gint32x8& a, gint32x8& b, const void* p)
{
    v256_load_packed2(a, b, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed2(gint32<N>& a, gint32<N>& b, const void* p)
{
    v_load_packed2(a, b, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed2(gint64x2& a, gint64x2& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
    const char* q = reinterpret_cast<const char*>(p);
    a = load(a, q);
    b = load(b, q+16);
    transpose2(a, b);
}

#if SIMDPP_USE_AVX2
inline void i_load_packed2(gint64x4& a, gint64x4& b, const void* p)
{
    v256_load_packed2(a, b, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed2(gint64<N>& a, gint64<N>& b, const void* p)
{
    v_load_packed2(a, b, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed2(float32x4& a, float32x4& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_f32(p);
    a = r.val[0];
    b = r.val[1];
#endif
}

#if SIMDPP_USE_AVX
inline void i_load_packed2(float32x8& a, float32x8& b, const void* p)
{
    v256_load_packed2(a, b, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed2(float32<N>& a, float32<N>& b, const void* p)
{
    v_load_packed2(a, b, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed2(float64x2& a, float64x2& b, const void* p)
{
    const double* q = reinterpret_cast<const double*>(p);
    q = detail::assume_aligned(q, 16);
    a = load(a, q);
    b = load(b, q+16);
    transpose2(a, b);
}

#if SIMDPP_USE_AVX
inline void i_load_packed2(float64x4& a, float64x4& b, const void* p)
{
    v256_load_packed2(a, b, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed2(float64<N>& a, float64<N>& b, const void* p)
{
    v_load_packed2(a, b, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

template<class V, class P>
void v256_load_packed2(V& a, V& b, const char* p)
{
    p = detail::assume_aligned(p, 32);
    load(a, p);
    load(b, p + 32);
    mem_unpack2(a, b);
}

template<class V>
void v_load_packed2(V& a, V& b, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load_packed2(a[i], b[i], p);
        p += veclen*2;
    }
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

