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

// this file contains forward declarations of shift functions for internal use
// from within shift implementation

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned N> SIMDPP_INL
uint8<N> shift_l(const uint8<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
uint16<N> shift_l(const uint16<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
uint32<N> shift_l(const uint32<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
uint64<N> shift_l(const uint64<N>& a, unsigned count);

template<unsigned N> SIMDPP_INL
uint8<N> shift_l(const uint8<N>& a, const uint8<N>& count);
template<unsigned N> SIMDPP_INL
uint16<N> shift_l(const uint16<N>& a, const uint16<N>& count);
template<unsigned N> SIMDPP_INL
uint32<N> shift_l(const uint32<N>& a, const uint32<N>& count);

template<unsigned count, unsigned N> SIMDPP_INL
uint8<N> shift_l(const uint8<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
uint16<N> shift_l(const uint16<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
uint32<N> shift_l(const uint32<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
uint64<N> shift_l(const uint64<N>& a);

template<unsigned N> SIMDPP_INL
int8<N> shift_r(const int8<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
int16<N> shift_r(const int16<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
int32<N> shift_r(const int32<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
int64<N> shift_r(const int64<N>& a, unsigned count);

template<unsigned N> SIMDPP_INL
int8<N> shift_r(const int8<N>& a, const uint8<N>& count);
template<unsigned N> SIMDPP_INL
int16<N> shift_r(const int16<N>& a, const uint16<N>& count);
template<unsigned N> SIMDPP_INL
int32<N> shift_r(const int32<N>& a, const uint32<N>& count);

template<unsigned count, unsigned N> SIMDPP_INL
int8<N> shift_r(const int8<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
int16<N> shift_r(const int16<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
int32<N> shift_r(const int32<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
int64<N> shift_r(const int64<N>& a);

template<unsigned N> SIMDPP_INL
uint8<N> shift_r(const uint8<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
uint16<N> shift_r(const uint16<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
uint32<N> shift_r(const uint32<N>& a, unsigned count);
template<unsigned N> SIMDPP_INL
uint64<N> shift_r(const uint64<N>& a, unsigned count);

template<unsigned N> SIMDPP_INL
uint8<N> shift_r(const uint8<N>& a, const uint8<N>& count);
template<unsigned N> SIMDPP_INL
uint16<N> shift_r(const uint16<N>& a, const uint16<N>& count);
template<unsigned N> SIMDPP_INL
uint32<N> shift_r(const uint32<N>& a, const uint32<N>& count);

template<unsigned count, unsigned N> SIMDPP_INL
uint8<N> shift_r(const uint8<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
uint16<N> shift_r(const uint16<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
uint32<N> shift_r(const uint32<N>& a);
template<unsigned count, unsigned N> SIMDPP_INL
uint64<N> shift_r(const uint64<N>& a);

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

