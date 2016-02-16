/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_l(const uint8<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_l(const uint16<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_l(const uint32<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_l(const uint64<N,E>& a, unsigned count);

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_l(const uint8<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_l(const uint16<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_l(const uint32<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_l(const uint64<N,E>& a);

template<unsigned N, class E> SIMDPP_INL
int8<N,expr_empty> shift_r(const int8<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
int16<N,expr_empty> shift_r(const int16<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
int32<N,expr_empty> shift_r(const int32<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
int64<N,expr_empty> shift_r(const int64<N,E>& a, unsigned count);

template<unsigned count, unsigned N, class E> SIMDPP_INL
int8<N,expr_empty> shift_r(const int8<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
int16<N,expr_empty> shift_r(const int16<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
int32<N,expr_empty> shift_r(const int32<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
int64<N,expr_empty> shift_r(const int64<N,E>& a);

template<unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_r(const uint8<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_r(const uint16<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_r(const uint32<N,E>& a, unsigned count);
template<unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_r(const uint64<N,E>& a, unsigned count);

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_r(const uint8<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_r(const uint16<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_r(const uint32<N,E>& a);
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_r(const uint64<N,E>& a);

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
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

