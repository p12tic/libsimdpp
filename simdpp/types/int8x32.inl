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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X32_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT8X32_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int8x32.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2
/*
inline gint8<32>::gint8(const gint16x16& d) { *this = bit_cast<gint8x32>(d); }
inline gint8<32>::gint8(const gint32x8& d) { *this = bit_cast<gint8x32>(d); }
inline gint8<32>::gint8(const gint64x4& d) { *this = bit_cast<gint8x32>(d); }
inline gint8<32>& gint8<32>::operator=(const gint16x16& d) { *this = bit_cast<gint8x32>(d); return *this; }
inline gint8<32>& gint8<32>::operator=(const gint32x8& d) { *this = bit_cast<gint8x32>(d); return *this; }
inline gint8<32>& gint8<32>::operator=(const gint64x4& d) { *this = bit_cast<gint8x32>(d); return *this; }

inline int8<32>::int8(const gint8x32& d) : gint8x32(d) {}
inline int8<32>::int8(const gint16x16& d): gint8x32(bit_cast<gint8x32>(d)) {}
inline int8<32>::int8(const gint32x8& d) : gint8x32(bit_cast<gint8x32>(d)) {}
inline int8<32>::int8(const gint64x4& d) : gint8x32(bit_cast<gint8x32>(d)) {}
inline int8<32>& int8<32>::operator=(const gint8x32& d) { gint8x32::operator=(d); return *this; }
inline int8<32>& int8<32>::operator=(const gint16x16& d){ gint8x32::operator=(d); return *this; }
inline int8<32>& int8<32>::operator=(const gint32x8& d) { gint8x32::operator=(d); return *this; }
inline int8<32>& int8<32>::operator=(const gint64x4& d) { gint8x32::operator=(d); return *this; }

inline uint8<32>::uint8(const gint8x32& d) : gint8x32(d) {}
inline uint8<32>::uint8(const gint16x16& d): gint8x32(bit_cast<gint8x32>(d)) {}
inline uint8<32>::uint8(const gint32x8& d) : gint8x32(bit_cast<gint8x32>(d)) {}
inline uint8<32>::uint8(const gint64x4& d) : gint8x32(bit_cast<gint8x32>(d)) {}
inline uint8<32>& uint8<32>::operator=(const gint8x32& d) { gint8x32::operator=(d); return *this; }
inline uint8<32>& uint8<32>::operator=(const gint16x16& d){ gint8x32::operator=(d); return *this; }
inline uint8<32>& uint8<32>::operator=(const gint32x8& d) { gint8x32::operator=(d); return *this; }
inline uint8<32>& uint8<32>::operator=(const gint64x4& d) { gint8x32::operator=(d); return *this; }
*/
inline gint8x32 gint8x32::zero()
{
    return (uint8<32>) make_uint(0);
}

inline gint8x32 gint8x32::ones()
{
    return (uint8<32>) make_uint(0xff);
}

inline mask_int8x32::operator gint8x32() const
{
    return d_;
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
