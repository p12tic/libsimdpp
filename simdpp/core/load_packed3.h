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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED3_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED3_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
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
template<class V, class P>
void v256_load_packed3(V& a, V& b, V& c, const P* p)
{
    p = detail::assume_aligned(p, 32);
    load(a, p);
    load(b, p + 32 / sizeof(P));
    load(c, p + 64 / sizeof(P));
    detail::mem_unpack3(a, b, c);
}

template<class V, class P>
void v_load_packed3(V& a, V& b, V& c, const P* p)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        load_packed3(a[i], b[i], c[i], p);
        p += veclen*3 / sizeof(P);
    }
}
} // namespace detail

/// @{
/** Loads 8-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+45) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+93) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+94) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+95) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(gint8x16& a, gint8x16& b, gint8x16& c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

#if SIMDPP_USE_AVX2
inline void load_packed3(gint8x32& a, gint8x32& b, gint8x32& c,
                         const void* p)
{
    detail::v256_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void load_packed3(gint8<N>& a, gint8<N>& b, gint8<N>& c, const void* p)
{
    detail::v_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
/// @}

/// @{
/** Loads 16-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+45) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(gint16x8& a, gint16x8& b, gint16x8& c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

#if SIMDPP_USE_AVX2
inline void load_packed3(gint16x16& a, gint16x16& b, gint16x16& c,
                         const void* p)
{
    detail::v256_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void load_packed3(gint16<N>& a, gint16<N>& b, gint16<N>& c, const void* p)
{
    detail::v_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
/// @}

/// @{
/** Loads 32-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(gint32x4& a, gint32x4& b, gint32x4&c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

#if SIMDPP_USE_AVX2
inline void load_packed3(gint32x8& a, gint32x8& b, gint32x8& c,
                         const void* p)
{
    detail::v256_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void load_packed3(gint32<N>& a, gint32<N>& b, gint32<N>& c, const void* p)
{
    detail::v_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
/// @}

/// @{
/** Loads 64-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3) ]
    b = [ *(p+1), *(p+4) ]
    c = [ *(p+2), *(p+5) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(gint64x2& a, gint64x2& b, gint64x2& c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    const char* q = reinterpret_cast<const char*>(p);
    uint64x2 a0, b0, c0;
    a0 = load(a0, q);
    b0 = load(b0, q+16);
    c0 = load(c0, q+32);

    int64x1_t al, bl, cl, ah, bh, ch;
    al = vget_low_u64(a0);
    ah = vget_high_u64(a0);
    bl = vget_low_u64(b0);
    bh = vget_high_u64(b0);
    cl = vget_low_u64(c0);
    ch = vget_high_u64(c0);
    a = vcombine_u64(al, bh);
    b = vcombine_u64(ah, cl);
    c = vcombine_u64(bl, ch);
#endif
}

#if SIMDPP_USE_AVX2
inline void load_packed3(gint64x4& a, gint64x4& b, gint64x4& c,
                         const void* p)
{
    detail::v256_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
#endif

template<unsigned N>
void load_packed3(gint64<N>& a, gint64<N>& b, gint64<N>& c, const void* p)
{
    detail::v_load_packed3(a, b, c, reinterpret_cast<const char*>(p));
}
/// @}

/// @{
/** Loads 32-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(float32x4& a, float32x4& b, float32x4& c,
                         const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    load(a, p);
    load(b, p+4);
    load(c, p+8);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_f32(p);
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

#if SIMDPP_USE_AVX
inline void load_packed3(float32x8& a, float32x8& b, float32x8& c,
                         const float* p)
{
    detail::v256_load_packed3(a, b, c, p);
}
#endif

template<unsigned N>
void load_packed3(float32<N>& a, float32<N>& b, float32<N>& c, const float* p)
{
    detail::v_load_packed3(a, b, c, p);
}
/// @}

/// @{
/** Loads 64-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3) ]
    b = [ *(p+1), *(p+4) ]
    c = [ *(p+2), *(p+5) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(float64x2& a, float64x2& b, float64x2& c, const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2
    load(a, p);
    load(b, p+2);
    load(c, p+4);
    detail::mem_unpack3(a, b, c);
#endif
}

#if SIMDPP_USE_AVX
inline void load_packed3(float64x4& a, float64x4& b, float64x4& c,
                         const double* p)
{
    detail::v256_load_packed3(a, b, c, p);
}
#endif

template<unsigned N>
void load_packed3(float64<N>& a, float64<N>& b, float64<N>& c, const double* p)
{
    detail::v_load_packed3(a, b, c, p);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

