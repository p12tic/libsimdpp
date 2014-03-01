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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_PACKED4_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_PACKED4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/mem_unpack.h>
#include <simdpp/core/load.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_load_packed4(V& a, V& b, V& c, V& d, const char* p);
template<class V>
void v_load_packed4(V& a, V& b, V& c, V& d, const char* p);

// -----------------------------------------------------------------------------

inline void i_load_packed4(gint8x16& a, gint8x16& b,
                           gint8x16& c, gint8x16& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

#if SIMDPP_USE_AVX2
inline void i_load_packed4(gint8x32& a, gint8x32& b, gint8x32& c, gint8x32& d,
                           const void* p)
{
    v256_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed4(gint8<N>& a, gint8<N>& b, gint8<N>& c, gint8<N>& d,
                    const void* p)
{
    v_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed4(gint16x8& a, gint16x8& b,
                           gint16x8& c, gint16x8& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

#if SIMDPP_USE_AVX2
inline void i_load_packed4(gint16x16& a, gint16x16& b, gint16x16& c, gint16x16& d,
                           const void* p)
{
    v256_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed4(gint16<N>& a, gint16<N>& b, gint16<N>& c, gint16<N>& d,
                    const void* p)
{
    v_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed4(gint32x4& a, gint32x4& b,
                           gint32x4& c, gint32x4& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

#if SIMDPP_USE_AVX2
inline void i_load_packed4(gint32x8& a, gint32x8& b, gint32x8& c, gint32x8& d,
                           const void* p)
{
    v256_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed4(gint32<N>& a, gint32<N>& b, gint32<N>& c, gint32<N>& d,
                    const void* p)
{
    v_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed4(gint64x2& a, gint64x2& b,
                           gint64x2& c, gint64x2& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
    const char* q = reinterpret_cast<const char*>(p);
    a = load(a, q);
    c = load(c, q+16);
    b = load(b, q+32);
    d = load(d, q+48);
    transpose2(a, b);
    transpose2(c, d);
}

#if SIMDPP_USE_AVX2
inline void i_load_packed4(gint64x4& a, gint64x4& b, gint64x4& c, gint64x4& d,
                         const void* p)
{
    v256_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed4(gint64<N>& a, gint64<N>& b, gint64<N>& c, gint64<N>& d,
                  const void* p)
{
    v_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed4(float32x4& a, float32x4& b, float32x4& c, float32x4& d,
                           const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_f32(p);
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

#if SIMDPP_USE_AVX
inline void i_load_packed4(float32x8& a, float32x8& b, float32x8& c, float32x8& d,
                           const void* p)
{
    v256_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed4(float32<N>& a, float32<N>& b, float32<N>& c, float32<N>& d,
                  const void* p)
{
    v_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

inline void i_load_packed4(float64x2& a, float64x2& b, float64x2& c, float64x2& d,
                           const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    mem_unpack4(a, b, c, d);
#endif
}

#if SIMDPP_USE_AVX
inline void i_load_packed4(float64x4& a, float64x4& b, float64x4& c, float64x4& d,
                           const void* p)
{
    v256_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void i_load_packed4(float64<N>& a, float64<N>& b, float64<N>& c, float64<N>& d,
                    const void* p)
{
    v_load_packed4(a, b, c, d, reinterpret_cast<const char*>(p));
}

// -----------------------------------------------------------------------------

template<class V>
void v256_load_packed4(V& a, V& b, V& c, V& d, const char* p)
{
    p = detail::assume_aligned(p, 32);
    load(a, p);
    load(b, p + 32);
    load(c, p + 64);
    load(d, p + 96);
    mem_unpack4(a, b, c, d);
}

template<class V>
void v_load_packed4(V& a, V& b, V& c, V& d, const char* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_load_packed4(a[i], b[i], c[i], d[i], p);
        p += veclen*4;
    }
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

