/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X8_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int32x8.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline gint32<8>::gint32(const gint8x32& d) { *this = bit_cast<gint32x8>(d); }
inline gint32<8>::gint32(const gint16x16& d){ *this = bit_cast<gint32x8>(d); }
inline gint32<8>::gint32(const gint64x4& d) { *this = bit_cast<gint32x8>(d); }
inline gint32<8>& gint32<8>::operator=(const gint8x32& d) { *this = bit_cast<gint32x8>(d); return *this; }
inline gint32<8>& gint32<8>::operator=(const gint16x16& d){ *this = bit_cast<gint32x8>(d); return *this; }
inline gint32<8>& gint32<8>::operator=(const gint64x4& d) { *this = bit_cast<gint32x8>(d); return *this; }

inline int32<8>::int32(const gint8x32& d) : gint32x8(bit_cast<gint32x8>(d)) {}
inline int32<8>::int32(const gint16x16& d): gint32x8(bit_cast<gint32x8>(d)) {}
inline int32<8>::int32(const gint32x8& d) : gint32x8(d) {}
inline int32<8>::int32(const gint64x4& d) : gint32x8(bit_cast<gint32x8>(d)) {}
inline int32<8>& int32<8>::operator=(const gint8x32& d) { gint32x8::operator=(d); return *this; }
inline int32<8>& int32<8>::operator=(const gint16x16& d){ gint32x8::operator=(d); return *this; }
inline int32<8>& int32<8>::operator=(const gint32x8& d) { gint32x8::operator=(d); return *this; }
inline int32<8>& int32<8>::operator=(const gint64x4& d) { gint32x8::operator=(d); return *this; }

inline uint32<8>::uint32(const gint8x32& d) : gint32x8(bit_cast<gint32x8>(d)) {}
inline uint32<8>::uint32(const gint16x16& d): gint32x8(bit_cast<gint32x8>(d)) {}
inline uint32<8>::uint32(const gint32x8& d) : gint32x8(d) {}
inline uint32<8>::uint32(const gint64x4& d) : gint32x8(bit_cast<gint32x8>(d)) {}
inline uint32<8>& uint32<8>::operator=(const gint8x32& d) { gint32x8::operator=(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const gint16x16& d){ gint32x8::operator=(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const gint32x8& d) { gint32x8::operator=(d); return *this; }
inline uint32<8>& uint32<8>::operator=(const gint64x4& d) { gint32x8::operator=(d); return *this; }

inline gint32<8>::gint32(const float32x8& d)
{
    *this = bit_cast<gint32x8>(d);
}

inline gint32x8 gint32x8::zero()
{
    return uint32x8::make_const(0);
}

inline gint32x8 gint32x8::ones()
{
    return uint32x8::make_const(0xffffffff);
}

inline int32x8 int32x8::load_broadcast(const int32_t* v0)
{
    return uint32x8::load_broadcast(reinterpret_cast<const uint32_t*>(v0));
}

inline int32x8 int32x8::set_broadcast(int32_t v0)
{
    return uint32x8::set_broadcast(v0);
}

inline int32x8 int32x8::make_const(int32_t v0)
{
    return uint32x8::make_const(v0);
}

inline int32x8 int32x8::make_const(int32_t v0, int32_t v1)
{
    return uint32x8::make_const(v0, v1);
}

inline int32x8 int32x8::make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
{
    return uint32x8::make_const(v0, v1, v2, v3);
}

inline int32x8 int32x8::make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3,
                                   int32_t v4, int32_t v5, int32_t v6, int32_t v7)
{
    return uint32x8::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline uint32x8 uint32x8::load_broadcast(const uint32_t* v0)
{
    return uint32x8::set_broadcast(*v0);
}

inline uint32x8 uint32x8::set_broadcast(uint32_t v0)
{
    uint32x4 a = _mm_cvtsi32_si128(v0);
    return _mm256_broadcastd_epi32(a);
}

inline uint32x8 uint32x8::make_const(uint32_t v0)
{
    return uint32x8::make_const(v0, v0, v0, v0, v0, v0, v0, v0);
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1)
{
    return uint32x8::make_const(v0, v1, v0, v1, v0, v1, v0, v1);
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
    return uint32x8::make_const(v0, v1, v2, v3, v0, v1, v2, v3);
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3,
                                     uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7)
{
    return _mm256_set_epi32(v7, v6, v5, v4, v3, v2, v1, v0);
}

inline mask_int32x8::operator gint32x8() const
{
    return d_;
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
