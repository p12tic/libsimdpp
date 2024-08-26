/*  Copyright (C) 2011-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_CORE_EXTRACT_BITS_H
#define LIBSIMDPP_SIMD_CORE_EXTRACT_BITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/extract_bits.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Extracts a bit from each element of a vector.

    This operation is only sensible if each element within the vector is either
    all zeros or all ones.

    For 8-bit version:

    @code
    r = ((a[0] & 0x??) ? 0x01 : 0) |
        ((a[1] & 0x??) ? 0x02 : 0) |
        ...
        ((a[15] & 0x??) ? 0x80 : 0)
    @endcode
*/
template<class V>
SIMDPP_INL uint16_t extract_bits_any(const any_vec8<16, V>& a)
{
    return detail::insn::i_extract_bits_any(uint8<16>(a));
}
template<class V>
SIMDPP_INL uint32_t extract_bits_any(const any_vec8<32, V>& a)
{
    return detail::insn::i_extract_bits_any(uint8<32>(a));
}
template<class V>
SIMDPP_INL uint8_t extract_bits_any(const any_vec16<8, V>& a)
{
    return detail::insn::i_extract_bits_any(uint16<8>(a));
}
template<class V>
SIMDPP_INL uint16_t extract_bits_any(const any_vec16<16, V>& a)
{
    return detail::insn::i_extract_bits_any(uint16<16>(a));
}
template<class V>
SIMDPP_INL uint8_t extract_bits_any(const any_vec32<4, V>& a)
{
    return detail::insn::i_extract_bits_any(uint32<4>(a));
}
template<class V>
SIMDPP_INL uint8_t extract_bits_any(const any_vec32<8, V>& a)
{
    return detail::insn::i_extract_bits_any(uint32<8>(a));
}
template<class V>
SIMDPP_INL uint8_t extract_bits_any(const any_vec64<2, V>& a)
{
    return detail::insn::i_extract_bits_any(uint64<2>(a));
}
template<class V>
SIMDPP_INL uint8_t extract_bits_any(const any_vec64<4, V>& a)
{
    return detail::insn::i_extract_bits_any(uint64<4>(a));
}


/** Extracts specific bit from each byte of each element of a int8x16 vector.

    @code
    r = (a[0] & 0x80 >> 7) | (a[1] & 0x80 >> 6) | ...  | (a[15] & 0x80 << 8)
    @endcode
*/
template<unsigned id> SIMDPP_INL
uint16_t extract_bits(const uint8<16>& a)
{
    static_assert(id < 8, "index out of bounds");
    return detail::insn::i_extract_bits<id>(a);
}
template<unsigned id> SIMDPP_INL
uint32_t extract_bits(const uint8<32>& a)
{
    static_assert(id < 8, "index out of bounds");
    return detail::insn::i_extract_bits<id>(a);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif


