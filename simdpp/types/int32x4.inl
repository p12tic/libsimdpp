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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int32x4.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/permute4.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<class E> gint32<4>::gint32(const gint8<16,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); }
template<class E> gint32<4>::gint32(const gint16<8,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); }
template<class E> gint32<4>::gint32(const gint32<4,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); }
template<class E> gint32<4>::gint32(const gint64<2,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); }
template<class E> gint32<4>& gint32<4>::operator=(const gint8<16,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); return *this; }
template<class E> gint32<4>& gint32<4>::operator=(const gint16<8,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); return *this; }
template<class E> gint32<4>& gint32<4>::operator=(const gint32<4,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); return *this; }
template<class E> gint32<4>& gint32<4>::operator=(const gint64<2,E>& d) { *this = bit_cast<gint32<4>>(d.eval()); return *this; }

template<class E> int32<4>::int32(const gint8<16,E>& d) : gint32(d) {}
template<class E> int32<4>::int32(const gint16<8,E>& d) : gint32(d) {}
template<class E> int32<4>::int32(const gint32<4,E>& d) : gint32(d) {}
template<class E> int32<4>::int32(const gint64<2,E>& d) : gint32(d) {}
template<class E> int32<4>& int32<4>::operator=(const gint8<16,E>& d) { gint32::operator=(d); return *this; }
template<class E> int32<4>& int32<4>::operator=(const gint16<8,E>& d) { gint32::operator=(d); return *this; }
template<class E> int32<4>& int32<4>::operator=(const gint32<4,E>& d) { gint32::operator=(d); return *this; }
template<class E> int32<4>& int32<4>::operator=(const gint64<2,E>& d) { gint32::operator=(d); return *this; }

template<class E> uint32<4>::uint32(const gint8<16,E>& d) : gint32(d) {}
template<class E> uint32<4>::uint32(const gint16<8,E>& d) : gint32(d) {}
template<class E> uint32<4>::uint32(const gint32<4,E>& d) : gint32(d) {}
template<class E> uint32<4>::uint32(const gint64<2,E>& d) : gint32(d) {}
template<class E> uint32<4>& uint32<4>::operator=(const gint8<16,E>& d) { gint32::operator=(d); return *this; }
template<class E> uint32<4>& uint32<4>::operator=(const gint16<8,E>& d) { gint32::operator=(d); return *this; }
template<class E> uint32<4>& uint32<4>::operator=(const gint32<4,E>& d) { gint32::operator=(d); return *this; }
template<class E> uint32<4>& uint32<4>::operator=(const gint64<2,E>& d) { gint32::operator=(d); return *this; }

inline gint32<4>::gint32(const float32x4& d)
{
#if SIMDPP_USE_NULL
    u32(0) = bit_cast<uint32_t>(d.el(0));
    u32(1) = bit_cast<uint32_t>(d.el(1));
    u32(2) = bit_cast<uint32_t>(d.el(2));
    u32(3) = bit_cast<uint32_t>(d.el(3));
#elif SIMDPP_USE_NEON
    operator=(bit_cast<gint32x4>(d));
#elif SIMDPP_USE_SSE2
    operator=(_mm_castps_si128(d));
#elif SIMDPP_USE_ALTIVEC
    __vector float df = d;
    operator=((__vector uint32_t)(df));
#endif
}

inline gint32x4 gint32x4::zero()
{
    return (uint32<4>) make_uint(0);
}

inline gint32x4 gint32x4::ones()
{
    return (uint32<4>) make_uint(0xffffffff);
}

inline mask_int32<4>::mask_int32(const maskdata_int32<4>& d) : uint32<4>(d), mask_(d) {}

#if SIMDPP_USE_SSE2
inline mask_int32<4>::mask_int32(__m128i d)   : uint32<4>(d), mask_(d) {}
inline mask_int32<4>::mask_int32(gint32<4> d) : uint32<4>(d), mask_(d) {}
#elif SIMDPP_USE_NEON
inline mask_int32<4>::mask_int32(uint32x4_t d) : uint32<4>(d), mask_(d) {}
inline mask_int32<4>::mask_int32(gint32<4> d)  : uint32<4>(d), mask_(d) {}
#elif SIMDPP_USE_ALTIVEC
inline mask_int32<4>::mask_int32(__vector uint32_t d) : uint32<4>(d), mask_(d) {}
inline mask_int32<4>::mask_int32(gint32<4> d)         : uint32<4>(d), mask_(d) {}
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
