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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED2_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/detail/mem_unpack.h>
#include <simdpp/core/load.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


namespace detail {

// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_load_i_packed2(V& a, V& b, const void* p)
{
    p = detail::assume_aligned(p, 32);
    const char* q = reinterpret_cast<const char*>(p);
#if SIMDPP_USE_AVX2
    load(a, q);
    load(b, q + 32);
    detail::mem_unpack2(a, b);
#else
    load_packed2(a[0], b[0], q);
    load_packed2(a[1], b[1], q + 32);
#endif
}
} // namespace detail

/// @{
/** Loads 8-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+30) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+62) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+63) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(gint8x16& a, gint8x16& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(gint8x32& a, gint8x32& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @{
/** Loads 16-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+30) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(gint16x8& a, gint16x8& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(gint16x16& a, gint16x16& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @{
/** Loads 32-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), *(p+6) ]
    b = [ *(p+1), *(p+3), *(p+5), *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(gint32x4& a, gint32x4& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(gint32x8& a, gint32x8& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @{
/** Loads 64-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2) ]
    b = [ *(p+1), *(p+3) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(gint64x2& a, gint64x2& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
    const char* q = reinterpret_cast<const char*>(p);
    a = load(a, q);
    b = load(b, q+16);
    transpose2(a, b);
}

inline void load_packed2(gint64x4& a, gint64x4& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @}
/** Loads 32-bit float values packed in pairs, de-interleaves them and stores
    the result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+6) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.

*/
inline void load_packed2(float32x4& a, float32x4& b, const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    load(a, p);
    load(b, p+4);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_f32(p);
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(float32x8& a, float32x8& b, const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 8);
    detail::mem_unpack2(a, b);
#else
    load_packed2(a[0], b[0], p);
    load_packed2(a[1], b[1], p + 8);
#endif
}
/// @}

/// @{
/** Loads 64-bit float values packed in pairs, de-interleaves them and stores
    the result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2) ]
    b = [ *(p+1), *(p+3) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(float64x2& a, float64x2& b, const double* p)
{
    p = detail::assume_aligned(p, 16);
    a = load(a, p);
    b = load(b, p+2);
    transpose2(a, b);
}

inline void load_packed2(float64x4& a, float64x4& b, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 4);
    detail::mem_unpack2(a, b);
#else
    load_packed2(a[0], b[0], p);
    load_packed2(a[1], b[1], p + 4);
#endif
}
/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

