/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X8_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT16X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int16x8.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<class E> gint16<8>::gint16(const gint8<16,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); }
template<class E> gint16<8>::gint16(const gint16<8,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); }
template<class E> gint16<8>::gint16(const gint32<4,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); }
template<class E> gint16<8>::gint16(const gint64<2,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); }
template<class E> gint16<8>& gint16<8>::operator=(const gint8<16,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); return *this; }
template<class E> gint16<8>& gint16<8>::operator=(const gint16<8,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); return *this; }
template<class E> gint16<8>& gint16<8>::operator=(const gint32<4,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); return *this; }
template<class E> gint16<8>& gint16<8>::operator=(const gint64<2,E>& d) { *this = bit_cast<gint16<8>>(d.eval()); return *this; }

template<class E> int16<8>::int16(const gint8<16,E>& d) : gint16(d) {}
template<class E> int16<8>::int16(const gint16<8,E>& d) : gint16(d) {}
template<class E> int16<8>::int16(const gint32<4,E>& d) : gint16(d) {}
template<class E> int16<8>::int16(const gint64<2,E>& d) : gint16(d) {}
template<class E> int16<8>& int16<8>::operator=(const gint8<16,E>& d) { gint16::operator=(d); return *this; }
template<class E> int16<8>& int16<8>::operator=(const gint16<8,E>& d) { gint16::operator=(d); return *this; }
template<class E> int16<8>& int16<8>::operator=(const gint32<4,E>& d) { gint16::operator=(d); return *this; }
template<class E> int16<8>& int16<8>::operator=(const gint64<2,E>& d) { gint16::operator=(d); return *this; }

template<class E> uint16<8>::uint16(const gint8<16,E>& d) : gint16(d) {}
template<class E> uint16<8>::uint16(const gint16<8,E>& d) : gint16(d) {}
template<class E> uint16<8>::uint16(const gint32<4,E>& d) : gint16(d) {}
template<class E> uint16<8>::uint16(const gint64<2,E>& d) : gint16(d) {}
template<class E> uint16<8>& uint16<8>::operator=(const gint8<16,E>& d) { gint16::operator=(d); return *this; }
template<class E> uint16<8>& uint16<8>::operator=(const gint16<8,E>& d) { gint16::operator=(d); return *this; }
template<class E> uint16<8>& uint16<8>::operator=(const gint32<4,E>& d) { gint16::operator=(d); return *this; }
template<class E> uint16<8>& uint16<8>::operator=(const gint64<2,E>& d) { gint16::operator=(d); return *this; }

inline gint16x8 gint16x8::zero()
{
    return uint16x8::make_const(0);
}

inline gint16x8 gint16x8::ones()
{
    return uint16x8::make_const(0xffff);
}

inline int16x8 int16x8::make_const(int16_t v0)
{
    return uint16x8::make_const(v0);
}

inline int16x8 int16x8::make_const(int16_t v0, int16_t v1)
{
    return uint16x8::make_const(v0, v1);
}

inline int16x8 int16x8::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3)
{
    return uint16x8::make_const(v0, v1, v2, v3);
}

inline int16x8 int16x8::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                                   int16_t v4, int16_t v5, int16_t v6, int16_t v7)
{
    return uint16x8::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline uint16x8 uint16x8::make_const(uint16_t v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint16x8::make_const(v0, v0, v0, v0, v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u16(&v0);
#endif
}

inline uint16x8 uint16x8::make_const(uint16_t v0, uint16_t v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint16x8::make_const(v0, v1, v0, v1, v0, v1, v0, v1);
#elif SIMDPP_USE_NEON
    union {
        uint16_t v[2];
        uint32_t vi[1];
    };
    v[0] = v0;
    v[1] = v1;
    return uint16x8(vld1q_dup_u32(vi));
#endif
}

inline uint16x8 uint16x8::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint16x8::make_const(v0, v1, v2, v3, v0, v1, v2, v3);
#elif SIMDPP_USE_NEON
    union {
        uint64_t align;
        uint16_t v[4];
    };
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
    uint16x4_t r0 = vld1_u16(v);
    return vcombine_u16(r0, r0);
#endif
}

inline uint16x8 uint16x8::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                     uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(v0, v1, v2, v3, v4, v5, v6, v7);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi16(v7, v6, v5, v4, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint16x8 align;
        uint16_t v[8];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    v[4] = v4;  v[5] = v5;  v[6] = v6;  v[7] = v7;
    return vld1q_u16(v);
#elif SIMDPP_USE_ALTIVEC
    return (__vector uint16_t){v0, v1, v2, v3, v4, v5, v6, v7};
#endif
}

inline mask_int16<8>::mask_int16(const maskdata_int16<8>& d) : uint16<8>(d), mask_(d) {}

#if SIMDPP_USE_SSE2
inline mask_int16<8>::mask_int16(__m128i d)   : uint16<8>(d), mask_(d) {}
inline mask_int16<8>::mask_int16(gint16<8> d) : uint16<8>(d), mask_(d) {}
#elif SIMDPP_USE_NEON
inline mask_int16<8>::mask_int16(uint16x8_t d) : uint16<8>(d), mask_(d) {}
inline mask_int16<8>::mask_int16(gint16<8> d)  : uint16<8>(d), mask_(d) {}
#elif SIMDPP_USE_ALTIVEC
inline mask_int16<8>::mask_int16(__vector uint16_t d) : uint16<8>(d), mask_(d) {}
inline mask_int16<8>::mask_int16(gint16<8> d)         : uint16<8>(d), mask_(d) {}
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
