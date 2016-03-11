/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_INT32_H
#define LIBSIMDPP_SIMDPP_CORE_TO_INT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/to_int32.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Sign extends the first 8 values of a signed int16x16 vector to 32-bits

    @code
    r0 = (int32_t) a0
    ...
    r7 = (int32_t) a7
    @endcode
    @icost{SSE4.1-AVX, 3}
    @icost{SSE2-SSSE3, 4}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
int32<N> to_int32(const int16<N,E>& a)
{
    return detail::insn::i_to_int32(a.eval());
}

// TODO: document
template<unsigned N, class E> SIMDPP_INL
uint32<N> to_uint32(const uint16<N,E>& a)
{
    return (uint32<N>) detail::insn::i_to_int32(int16<N>(a.eval())); // FIXME
}

#if !SIMDPP_DISABLE_DEPRECATED
template<unsigned N, class E> SIMDPP_INL
uint32<N> to_int32(const uint16<N,E>& a)
{
    return to_uint32(a);
}
#endif

/** Converts the values of a float32x4 vector into signed int32_t
    representation using truncation if only an inexact conversion can be
    performed. The behavior is undefined if the value can not be represented in
    the result type.

    SSE specific:
    If the value can not be represented by int32_t, @c 0x80000000 is returned
    TODO: NaN handling

    NEON, ALTIVEC specific:
    If the value can not be represented by int32_t, either @c 0x80000000 or @c
    0x7fffffff is returned depending on the sign of the operand (saturation
    occurs). Conversion of NaNs results in @a 0.

    @code
    r0 = (int32_t) a0
    ...
    rN = (int32_t) aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
int32<N> to_int32(const float32<N,E>& a)
{
    return detail::insn::i_to_int32(a.eval());
}

/** Converts the values of a doublex2 vector into int32_t representation using
    truncation. The behavior is undefined if the value can not be represented
    in the result type.

    SSE specific:
    If the value can not be represented by int32_t, @c 0x80000000 is returned
    @todo NaN handling

    NEON VFP specific:
    If the value can not be represented by int32_t, either @c 0x80000000 or @c
    0x7fffffff is returned depending on the sign of the operand. Conversion of
    NaNs results in @a 0.

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @code
    r0 = (int32_t) a0
    r1 = (int32_t) a1
    r2 = (int32_t) a2
    r3 = (int32_t) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
*/
template<unsigned N, class E> SIMDPP_INL
int32<N> to_int32(const float64<N,E>& a)
{
    return detail::insn::i_to_int32(a.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

