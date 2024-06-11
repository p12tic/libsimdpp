/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_COMBINE_H
#define LIBSIMDPP_SIMDPP_CORE_COMBINE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/combine.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Combines two vectors into one twice as large. This function is useful when
    the ISA supports multiple vector sizes and the user does some operations
    with vectors that are narrower than the widest native vector.

    For example, on AVX, two __m128 vectors can be combined into a __m256
    vector.

    @todo icost
*/
template<unsigned N> SIMDPP_INL
uint8<N*2> combine(const uint8<N>& a1, const uint8<N>& a2)
{
    return detail::insn::i_combine<uint8<N*2>>(a1, a2);
}

template<unsigned N> SIMDPP_INL
uint16<N*2> combine(const uint16<N>& a1, const uint16<N>& a2)
{
    return detail::insn::i_combine<uint16<N*2>>(a1, a2);
}

template<unsigned N> SIMDPP_INL
uint32<N*2> combine(const uint32<N>& a1, const uint32<N>& a2)
{
    return detail::insn::i_combine<uint32<N*2>>(a1, a2);
}

template<unsigned N> SIMDPP_INL
uint64<N*2> combine(const uint64<N>& a1, const uint64<N>& a2)
{
    return detail::insn::i_combine<uint64<N*2>>(a1, a2);
}

template<unsigned N> SIMDPP_INL
int8<N*2> combine(const int8<N>& a1, const int8<N>& a2)
{
    return detail::insn::i_combine<uint8<N*2>>(uint8<N>(a1),
                                               uint8<N>(a2));
}

template<unsigned N> SIMDPP_INL
int16<N*2> combine(const int16<N>& a1, const int16<N>& a2)
{
    return detail::insn::i_combine<uint16<N*2>>(uint16<N>(a1),
                                                uint16<N>(a2));
}

template<unsigned N> SIMDPP_INL
int32<N*2> combine(const int32<N>& a1, const int32<N>& a2)
{
    return detail::insn::i_combine<uint32<N*2>>(uint32<N>(a1),
                                                uint32<N>(a2));
}

template<unsigned N> SIMDPP_INL
int64<N*2> combine(const int64<N>& a1, const int64<N>& a2)
{
    return detail::insn::i_combine<uint64<N*2>>(uint64<N>(a1),
                                                uint64<N>(a2));
}

template<unsigned N> SIMDPP_INL
float32<N*2> combine(const float32<N>& a1, const float32<N>& a2)
{
    return detail::insn::i_combine<float32<N*2>>(a1, a2);
}

template<unsigned N> SIMDPP_INL
float64<N*2> combine(const float64<N>& a1, const float64<N>& a2)
{
    return detail::insn::i_combine<float64<N*2>>(a1, a2);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
