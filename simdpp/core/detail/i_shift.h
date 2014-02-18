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

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_I_SHIFT_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_I_SHIFT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// forward declarations

// 8 bits static
template<unsigned count, unsigned N> gint8<N> shift_l(gint8<N>);
template<unsigned count>             gint8x16 shift_l(gint8x16);
#if SIMDPP_USE_AVX2
template<unsigned count>             gint8x32 shift_l(gint8x32);
#endif

template<unsigned count, unsigned N> uint8<N> shift_r(uint8<N>);
template<unsigned count>             uint8x16 shift_r(uint8x16);
#if SIMDPP_USE_AVX2
template<unsigned count>             uint8x32 shift_r(uint8x32);
#endif

template<unsigned count, unsigned N> int8<N> shift_r(int8<N>);
template<unsigned count>             int8x16 shift_r(int8x16);
#if SIMDPP_USE_AVX2
template<unsigned count>             int8x32 shift_r(int8x32);
#endif

// 16 bits static

template<unsigned count, unsigned N> gint16<N> shift_l(gint16<N>);
template<unsigned count>             gint16x8 shift_l(gint16x8);
#if SIMDPP_USE_AVX2
template<unsigned count>             gint16x16 shift_l(gint16x16);
#endif

template<unsigned count, unsigned N> uint16<N> shift_r(uint16<N>);
template<unsigned count>             uint16x8 shift_r(uint16x8);
#if SIMDPP_USE_AVX2
template<unsigned count>             uint16x16 shift_r(uint16x16);
#endif

template<unsigned count, unsigned N> int16<N> shift_r(int16<N>);
template<unsigned count>             int16x8 shift_r(int16x8);
#if SIMDPP_USE_AVX2
template<unsigned count>             int16x16 shift_r(int16x16);
#endif

// 32 bits static

template<unsigned count, unsigned N> gint32<N> shift_l(gint32<N>);
template<unsigned count>             gint32x4 shift_l(gint32x4);
#if SIMDPP_USE_AVX2
template<unsigned count>             gint32x8 shift_l(gint32x8);
#endif

template<unsigned count, unsigned N> uint32<N> shift_r(uint32<N>);
template<unsigned count>             uint32x4 shift_r(uint32x4);
#if SIMDPP_USE_AVX2
template<unsigned count>             uint32x8 shift_r(uint32x8);
#endif

template<unsigned count, unsigned N> int32<N> shift_r(int32<N>);
template<unsigned count>             int32x4 shift_r(int32x4);
#if SIMDPP_USE_AVX2
template<unsigned count>             int32x8 shift_r(int32x8);
#endif

// 64 bits static

template<unsigned count, unsigned N> gint64<N> shift_l(gint64<N>);
template<unsigned count>             gint64x2 shift_l(gint64x2);
#if SIMDPP_USE_AVX2
template<unsigned count>             gint64x4 shift_l(gint64x4);
#endif

template<unsigned count, unsigned N> uint64<N> shift_r(uint64<N>);
template<unsigned count>             uint64x2 shift_r(uint64x2);
#if SIMDPP_USE_AVX2
template<unsigned count>             uint64x4 shift_r(uint64x4);
#endif

template<unsigned count, unsigned N> int64<N> shift_r(int64<N>);
template<unsigned count>             int64x2 shift_r(int64x2);
#if SIMDPP_USE_AVX2
template<unsigned count>             int64x4 shift_r(int64x4);
#endif



// 16 bits dynamic

template<unsigned N> gint16<N> shift_l(gint16<N>, unsigned);
inline               gint16x8 shift_l(gint16x8, unsigned);
#if SIMDPP_USE_AVX2
inline               gint16x16 shift_l(gint16x16, unsigned);
#endif

template<unsigned N> uint16<N> shift_r(uint16<N>, unsigned);
inline               uint16x8 shift_r(uint16x8, unsigned);
#if SIMDPP_USE_AVX2
inline               uint16x16 shift_r(uint16x16, unsigned);
#endif

template<unsigned N> int16<N> shift_r(int16<N>, unsigned);
inline               int16x8 shift_r(int16x8, unsigned);
#if SIMDPP_USE_AVX2
inline               int16x16 shift_r(int16x16, unsigned);
#endif

// 64 bits dynamic

template<unsigned N> gint64<N> shift_l(gint64<N>, unsigned);
inline               gint64x2 shift_l(gint64x2, unsigned);
#if SIMDPP_USE_AVX2
inline               gint64x4 shift_l(gint64x4, unsigned);
#endif

template<unsigned N> uint64<N> shift_r(uint64<N>, unsigned);
inline               uint64x2 shift_r(uint64x2, unsigned);
#if SIMDPP_USE_AVX2
inline               uint64x4 shift_r(uint64x4, unsigned);
#endif

template<unsigned N> int64<N> shift_r(int64<N>, unsigned);
inline               int64x2 shift_r(int64x2, unsigned);
#if SIMDPP_USE_AVX2
inline               int64x4 shift_r(int64x4, unsigned);
#endif

namespace detail {

template<unsigned count, class V>
struct shift_u8_mask;

template<class V>
struct shift_u8_mask<0,V> { V operator()() { return V::make_const(0x00); } };
template<class V>
struct shift_u8_mask<1,V> { V operator()() { return V::make_const(0x01); } };
template<class V>
struct shift_u8_mask<2,V> { V operator()() { return V::make_const(0x03); } };
template<class V>
struct shift_u8_mask<3,V> { V operator()() { return V::make_const(0x07); } };
template<class V>
struct shift_u8_mask<4,V> { V operator()() { return V::make_const(0x0f); } };
template<class V>
struct shift_u8_mask<5,V> { V operator()() { return V::make_const(0x1f); } };
template<class V>
struct shift_u8_mask<6,V> { V operator()() { return V::make_const(0x3f); } };
template<class V>
struct shift_u8_mask<7,V> { V operator()() { return V::make_const(0x7f); } };
template<class V>
struct shift_u8_mask<8,V> { V operator()() { return V::make_const(0xff); } };

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

