/*  Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_POPCNT_H
#define LIBSIMDPP_SIMDPP_CORE_I_POPCNT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_popcnt.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Computes the population count of elements in the vector.

    @code
    r0 = popcnt(a0)
    r1 = popcnt(a1)
    ...
    rN = popcnt(aN)
    @endcode
*/
template<unsigned N> SIMDPP_INL
int8<N> popcnt(const int8<N>& a)
{
    return detail::insn::i_popcnt(uint8<N>(a.eval()));
}

template<unsigned N> SIMDPP_INL
uint8<N> popcnt(const uint8<N>& a)
{
    return detail::insn::i_popcnt(a.eval());
}

template<unsigned N> SIMDPP_INL
int16<N> popcnt(const int16<N>& a)
{
    return detail::insn::i_popcnt(uint16<N>(a.eval()));
}

template<unsigned N> SIMDPP_INL
uint16<N> popcnt(const uint16<N>& a)
{
    return detail::insn::i_popcnt(a.eval());
}

template<unsigned N> SIMDPP_INL
int32<N> popcnt(const int32<N>& a)
{
    return detail::insn::i_popcnt(uint32<N>(a.eval()));
}

template<unsigned N> SIMDPP_INL
uint32<N> popcnt(const uint32<N>& a)
{
    return detail::insn::i_popcnt(a.eval());
}

template<unsigned N> SIMDPP_INL
int64<N> popcnt(const int64<N>& a)
{
    return detail::insn::i_popcnt(uint64<N>(a.eval()));
}

template<unsigned N> SIMDPP_INL
uint64<N> popcnt(const uint64<N>& a)
{
    return detail::insn::i_popcnt(a.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

