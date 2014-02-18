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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED4_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/detail/mem_unpack.h>
#include <simdpp/core/load.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

namespace detail {

// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_load_i_packed4(V& a, V& b, V& c, V& d, const void* p)
{
    p = detail::assume_aligned(p, 32);
    const char* q = reinterpret_cast<const char*>(p);
#if SIMDPP_USE_AVX2
    load(a, q);
    load(b, q + 32);
    load(c, q + 64);
    load(d, q + 96);
    detail::mem_unpack4(a, b, c, d);
#else
    load_packed4(a[0], b[0], c[0], d[0], q);
    load_packed4(a[1], b[1], c[1], d[1], q + 64);
#endif
}

} // namespace detail


/// @{
/** Loads 8-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+124) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+125) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+126) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+127) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(gint8x16& a, gint8x16& b,
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
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(gint8x32& a, gint8x32& b,
                         gint8x32& c, gint8x32& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 16-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(gint16x8& a, gint16x8& b,
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
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(gint16x16& a, gint16x16& b,
                         gint16x16& c, gint16x16& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 32-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(gint32x4& a, gint32x4& b,
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
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(gint32x8& a, gint32x8& b,
                         gint32x8& c, gint32x8& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 64-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4) ]
    b = [ *(p+1), *(p+5) ]
    c = [ *(p+2), *(p+6) ]
    d = [ *(p+3), *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(gint64x2& a, gint64x2& b,
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

inline void load_packed4(gint64x4& a, gint64x4& b,
                         gint64x4& c, gint64x4& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 32-bit floating-point values packed in quartets, de-interleaves them
    and stores the result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(float32x4& a, float32x4& b, float32x4& c, float32x4& d,
                         const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    load(a, p);
    load(b, p+4);
    load(c, p+8);
    load(d, p+12);
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_f32(p);
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(float32x8& a, float32x8& b,
                         float32x8& c, float32x8& d, const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 8);
    load(c, p + 16);
    load(d, p + 24);
    detail::mem_unpack4(a, b, c, d);
#else
    load_packed4(a[0], b[0], c[0], d[0], p);
    load_packed4(a[1], b[1], c[1], d[1], p + 16);
#endif
}
/// @}

/// @{
/** Loads 64-bit floating-point values packed in quartets, de-interleaves them
    and stores the result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4) ]
    b = [ *(p+1), *(p+5) ]
    c = [ *(p+2), *(p+6) ]
    d = [ *(p+3), *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(float64x2& a, float64x2& b, float64x2& c, float64x2& d,
                         const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2
    load(a, p);
    load(b, p+2);
    load(c, p+4);
    load(d, p+6);
    detail::mem_unpack4(a, b, c, d);
#endif
}

inline void load_packed4(float64x4& a, float64x4& b,
                         float64x4& c, float64x4& d, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 4);
    load(c, p + 8);
    load(d, p + 12);
    detail::mem_unpack4(a, b, c, d);
#else
    load_packed4(a[0], b[0], c[0], d[0], p);
    load_packed4(a[1], b[1], c[1], d[1], p + 8);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

