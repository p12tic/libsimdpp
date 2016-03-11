/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_INT16_H
#define LIBSIMDPP_SIMDPP_CORE_TO_INT16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/to_int16.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/** Sign extends the 16 values of a signed int8x16 vector to 16-bits

    @code
    r0 = (int16_t) a0
    ...
    r15 = (int16_t) a15
    @endcode

    @icost{SSE4.1-AVX, 3}
    @icost{SSE2-SSSE3, 4}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
int16<N> to_int16(const int8<N,E>& a)
{
    return detail::insn::i_to_int16(a.eval());
}

/** Extends the 16 values of a unsigned int8x16 vector to 16-bits

    @code
    r0 = (uint16_t) a0
    ...
    r15 = (uint16_t) a15
    @endcode
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
uint16<N> to_uint16(const uint8<N,E>& a)
{
    return detail::insn::i_to_uint16(a.eval());
}

#if !SIMDPP_DISABLE_DEPRECATED
template<unsigned N, class E> SIMDPP_INL
uint16<N> to_int16(const uint8<N,E>& a)
{
    return to_uint16(a);
}
#endif

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

