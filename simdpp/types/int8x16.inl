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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X16_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT8X16_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int8x16.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/altivec/load1.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<class E> gint8<16>::gint8(const gint8<16,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); }
template<class E> gint8<16>::gint8(const gint16<8,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); }
template<class E> gint8<16>::gint8(const gint32<4,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); }
template<class E> gint8<16>::gint8(const gint64<2,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); }
template<class E> gint8<16>& gint8<16>::operator=(const gint8<16,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); return *this; }
template<class E> gint8<16>& gint8<16>::operator=(const gint16<8,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); return *this; }
template<class E> gint8<16>& gint8<16>::operator=(const gint32<4,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); return *this; }
template<class E> gint8<16>& gint8<16>::operator=(const gint64<2,E>& d) { *this = bit_cast<gint8<16>>(d.eval()); return *this; }

template<class E> int8<16>::int8(const gint8<16,E>& d) : gint8(d) {}
template<class E> int8<16>::int8(const gint16<8,E>& d) : gint8(d) {}
template<class E> int8<16>::int8(const gint32<4,E>& d) : gint8(d) {}
template<class E> int8<16>::int8(const gint64<2,E>& d) : gint8(d) {}
template<class E> int8<16>& int8<16>::operator=(const gint8<16,E>& d) { gint8::operator=(d); return *this; }
template<class E> int8<16>& int8<16>::operator=(const gint16<8,E>& d) { gint8::operator=(d); return *this; }
template<class E> int8<16>& int8<16>::operator=(const gint32<4,E>& d) { gint8::operator=(d); return *this; }
template<class E> int8<16>& int8<16>::operator=(const gint64<2,E>& d) { gint8::operator=(d); return *this; }

template<class E> uint8<16>::uint8(const gint8<16,E>& d) : gint8(d) {}
template<class E> uint8<16>::uint8(const gint16<8,E>& d) : gint8(d) {}
template<class E> uint8<16>::uint8(const gint32<4,E>& d) : gint8(d) {}
template<class E> uint8<16>::uint8(const gint64<2,E>& d) : gint8(d) {}
template<class E> uint8<16>& uint8<16>::operator=(const gint8<16,E>& d) { gint8::operator=(d); return *this; }
template<class E> uint8<16>& uint8<16>::operator=(const gint16<8,E>& d) { gint8::operator=(d); return *this; }
template<class E> uint8<16>& uint8<16>::operator=(const gint32<4,E>& d) { gint8::operator=(d); return *this; }
template<class E> uint8<16>& uint8<16>::operator=(const gint64<2,E>& d) { gint8::operator=(d); return *this; }

inline gint8x16 gint8x16::zero()
{
    return uint8x16::make_const(0);
}

inline gint8x16 gint8x16::ones()
{
    return uint8x16::make_const(0xff);
}

inline int8x16 int8x16::load_broadcast(const int8_t* v0)
{
    return uint8x16::load_broadcast(reinterpret_cast<const uint8_t*>(v0));
}

inline int8x16 int8x16::set_broadcast(int8_t v0)
{
    return uint8x16::set_broadcast(v0);
}

inline int8x16 int8x16::make_const(int8_t v0)
{
    return uint8x16::make_const(v0);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1)
{
    return uint8x16::make_const(v0, v1);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3)
{
    return uint8x16::make_const(v0, v1, v2, v3);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7)
{
    return uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                                   int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                                   int8_t v12, int8_t v13, int8_t v14, int8_t v15)
{
    return uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v8, v9, v10, v11, v12, v13, v14, v15);
}

inline uint8x16 uint8x16::load_broadcast(const uint8_t* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(*v0);
#elif SIMDPP_USE_SSE2
    return uint8x16::set_broadcast(*v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u8(v0);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 r = altivec::load1_u(r, v0);
    r = splat<0>(r);
    return r;
#endif
}

inline uint8x16 uint8x16::set_broadcast(uint8_t v0)
{
#if SIMDPP_USE_NULL
    return uint8x16::load_broadcast(&v0);
#elif SIMDPP_USE_SSE2
    uint32_t u0;
    u0 = v0 * 0x01010101;
    return (uint8x16) uint32x4::set_broadcast(u0);
#elif SIMDPP_USE_NEON
    return vdupq_n_u8(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint8_t v[16];
        uint8x16 align;
    };
    v[0] = v0;
    uint8x16 r = altivec::load1(r, v);
    r = splat<0>(r);
    return r;
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v0, v0, v0, v0, v0, v0, v0,
                                v0, v0, v0, v0, v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u8(&v0);
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v1, v0, v1, v0, v1, v0, v1,
                                v0, v1, v0, v1, v0, v1, v0, v1);
#elif SIMDPP_USE_NEON
    union {
        uint16_t vi[1];
        uint8_t v[2];
    };
    v[0] = v0;
    v[1] = v1;
    return uint8x16(vld1q_dup_u16(vi));
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v1, v2, v3, v0, v1, v2, v3,
                                v0, v1, v2, v3, v0, v1, v2, v3);
#elif SIMDPP_USE_NEON
    union {
        uint32_t vi[1];
        uint8_t v[4];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    return uint8x16(vld1q_dup_u32(vi));
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v0, v1, v2, v3, v4, v5, v6, v7);
#elif SIMDPP_USE_NEON
    union {
        uint64_t align;
        uint8_t v[8];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    v[4] = v4;  v[5] = v5;  v[6] = v6;  v[7] = v7;
    uint8x8_t r0 = vld1_u8(v);
    return vcombine_u8(r0, r0);
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                                     uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                                     uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0, v1, v2, v3, v4, v5, v6, v7,
                                    v8, v9, v10, v11, v12, v13, v14, v15);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi8(v15, v14, v13, v12, v11, v10, v9, v8,
                        v7, v6, v5, v4, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint6x16 align;
        uint8_t v[16];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    v[4] = v4;  v[5] = v5;  v[6] = v6;  v[7] = v7;
    v[8] = v8;  v[9] = v9;  v[10] = v10; v[11] = v11;
    v[12] = v12; v[13] = v13; v[14] = v14; v[15] = v15;
    return vld1q_u8(v);
#elif SIMDPP_USE_ALTIVEC
    return (__vector uint8_t){v0, v1, v2, v3, v4, v5, v6, v7,
                              v8, v9, v10, v11, v12, v13, v14, v15};
#endif
}

inline mask_int8<16>::mask_int8(const maskdata_int8<16>& d) : uint8<16>(d), mask_(d) {}

#if SIMDPP_USE_SSE2
inline mask_int8<16>::mask_int8(__m128i d)   : uint8<16>(d), mask_(d) {}
inline mask_int8<16>::mask_int8(gint8<16> d) : uint8<16>(d), mask_(d) {}
#elif SIMDPP_USE_NEON
inline mask_int8<16>::mask_int8(uint8x16_t d) : uint8<16>(d), mask_(d) {}
inline mask_int8<16>::mask_int8(gint8<16> d)  : uint8<16>(d), mask_(d) {}
#elif SIMDPP_USE_ALTIVEC
inline mask_int8<16>::mask_int8(__vector uint8_t d) : uint8<16>(d), mask_(d) {}
inline mask_int8<16>::mask_int8(gint8<16> d)        : uint8<16>(d), mask_(d) {}
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
