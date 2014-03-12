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
    return (uint8x16) make_uint(0);
}

inline gint8x16 gint8x16::ones()
{
    return (uint8x16) make_uint(0xff);
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
