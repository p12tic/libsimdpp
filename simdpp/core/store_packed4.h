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

#ifndef LIBSIMDPP_SIMDPP_CORE_STORE_PACKED4_H
#define LIBSIMDPP_SIMDPP_CORE_STORE_PACKED4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/detail/mem_pack.h>
#include <simdpp/core/store.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

namespace detail {
// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_store_i_pack4(void* p, V a, V b, V c, V d)
{
    p = detail::assume_aligned(p, 32);
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q + 32, b);
    store(q + 64, c);
    store(q + 96, d);
#else
    store_packed4(q, a[0], b[0], c[0], d[0]);
    store_packed4(q + 64, a[1], b[1], c[1], d[1]);
#endif
}

} // namespace detail


/// @{
/** Interleaves 8-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+124) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+125) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+126) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+127) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          gint8x16 a, gint8x16 b,
                          gint8x16 c, gint8x16 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    uint8x16x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_u8(reinterpret_cast<uint8_t*>(p), t);
#endif
}

inline void store_packed4(void* p,
                          gint8x32 a, gint8x32 b,
                          gint8x32 c, gint8x32 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 16-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          gint16x8 a, gint16x8 b,
                          gint16x8 c, gint16x8 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    uint16x8x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_u16(reinterpret_cast<uint16_t*>(p), t);
#endif
}

inline void store_packed4(void* p,
                          gint16x16 a, gint16x16 b,
                          gint16x16 c, gint16x16 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 32-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          gint32x4 a, gint32x4 b,
                          gint32x4 c, gint32x4 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    uint32x4x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_u32(reinterpret_cast<uint32_t*>(p), t);
#endif
}

inline void store_packed4(void* p,
                          gint32x8 a, gint32x8 b,
                          gint32x8 c, gint32x8 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 64-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4) ] = a
    [ *(p+1), *(p+5) ] = b
    [ *(p+2), *(p+6) ] = c
    [ *(p+3), *(p+7) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          gint64x2 a, gint64x2 b,
                          gint64x2 c, gint64x2 d)
{
    p = detail::assume_aligned(p, 16);
    char* q = reinterpret_cast<char*>(p);
    transpose2(a, b);
    transpose2(c, d);
    store(q, a);
    store(q+16, c);
    store(q+32, b);
    store(q+48, d);
}

inline void store_packed4(void* p,
                          gint64x4 a, gint64x4 b,
                          gint64x4 c, gint64x4 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 32-bit floating-point values from four vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(float* p,
                          float32x4 a, float32x4 b, float32x4 c, float32x4 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p+4, b);
    store(p+8, c);
    store(p+12, d);
#elif SIMDPP_USE_NEON
    float32x4x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_f32(p, t);
#endif
}

inline void store_packed4(float* p,
                          float32x8 a, float32x8 b, float32x8 c, float32x8 d)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p + 8, b);
    store(p + 16, c);
    store(p + 24, d);
#else
    store_packed4(p, a[0], b[0], c[0], d[0]);
    store_packed4(p + 16, a[1], b[1], c[1], d[1]);
#endif
}
/// @}

/// @{
/** Interleaves 64-bit floating-point values from four vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4) ] = a
    [ *(p+1), *(p+5) ] = b
    [ *(p+2), *(p+6) ] = c
    [ *(p+3), *(p+7) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(double* p,
                          float64x2 a, float64x2 b, float64x2 c, float64x2 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p+2, b);
    store(p+4, c);
    store(p+6, d);
#endif
}

inline void store_packed4(double* p,
                          float64x4 a, float64x4 b, float64x4 c, float64x4 d)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p + 4, b);
    store(p + 8, c);
    store(p + 12, d);
#else
    store_packed4(p, a[0], b[0], c[0], d[0]);
    store_packed4(p + 8, a[1], b[1], c[1], d[1]);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

