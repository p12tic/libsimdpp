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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<unsigned N, class E>
gint8<N, gint8<N>> shift_l(gint8<N,E> a, unsigned count);
template<unsigned N, class E>
gint16<N, gint16<N>> shift_l(gint16<N,E> a, unsigned count);
template<unsigned N, class E>
gint32<N, gint32<N>> shift_l(gint32<N,E> a, unsigned count);
template<unsigned N, class E>
gint64<N, gint64<N>> shift_l(gint64<N,E> a, unsigned count);

template<unsigned count, unsigned N, class E>
gint8<N, gint8<N>> shift_l(gint8<N,E> a);
template<unsigned count, unsigned N, class E>
gint16<N, gint16<N>> shift_l(gint16<N,E> a);
template<unsigned count, unsigned N, class E>
gint32<N, gint32<N>> shift_l(gint32<N,E> a);
template<unsigned count, unsigned N, class E>
gint64<N, gint64<N>> shift_l(gint64<N,E> a);

template<unsigned N, class E>
int8<N, int8<N>> shift_r(int8<N,E> a, unsigned count);
template<unsigned N, class E>
int16<N, int16<N>> shift_r(int16<N,E> a, unsigned count);
template<unsigned N, class E>
int32<N, int32<N>> shift_r(int32<N,E> a, unsigned count);
template<unsigned N, class E>
int64<N, int64<N>> shift_r(int64<N,E> a, unsigned count);

template<unsigned count, unsigned N, class E>
int8<N, int8<N>> shift_r(int8<N,E> a);
template<unsigned count, unsigned N, class E>
int16<N, int16<N>> shift_r(int16<N,E> a);
template<unsigned count, unsigned N, class E>
int32<N, int32<N>> shift_r(int32<N,E> a);
template<unsigned count, unsigned N, class E>
int64<N, int64<N>> shift_r(int64<N,E> a);

template<unsigned N, class E>
uint8<N, uint8<N>> shift_r(uint8<N,E> a, unsigned count);
template<unsigned N, class E>
uint16<N, uint16<N>> shift_r(uint16<N,E> a, unsigned count);
template<unsigned N, class E>
uint32<N, uint32<N>> shift_r(uint32<N,E> a, unsigned count);
template<unsigned N, class E>
uint64<N, uint64<N>> shift_r(uint64<N,E> a, unsigned count);

template<unsigned count, unsigned N, class E>
uint8<N, uint8<N>> shift_r(uint8<N,E> a);
template<unsigned count, unsigned N, class E>
uint16<N, uint16<N>> shift_r(uint16<N,E> a);
template<unsigned count, unsigned N, class E>
uint32<N, uint32<N>> shift_r(uint32<N,E> a);
template<unsigned count, unsigned N, class E>
uint64<N, uint64<N>> shift_r(uint64<N,E> a);

namespace detail {
namespace insn {

template<unsigned count, class V>
struct shift_u8_mask;

template<class V>
struct shift_u8_mask<0,V> { V operator()() { return make_uint(0x00); } };
template<class V>
struct shift_u8_mask<1,V> { V operator()() { return make_uint(0x01); } };
template<class V>
struct shift_u8_mask<2,V> { V operator()() { return make_uint(0x03); } };
template<class V>
struct shift_u8_mask<3,V> { V operator()() { return make_uint(0x07); } };
template<class V>
struct shift_u8_mask<4,V> { V operator()() { return make_uint(0x0f); } };
template<class V>
struct shift_u8_mask<5,V> { V operator()() { return make_uint(0x1f); } };
template<class V>
struct shift_u8_mask<6,V> { V operator()() { return make_uint(0x3f); } };
template<class V>
struct shift_u8_mask<7,V> { V operator()() { return make_uint(0x7f); } };
template<class V>
struct shift_u8_mask<8,V> { V operator()() { return make_uint(0xff); } };

} // namespace detail
} // namespace insn
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

