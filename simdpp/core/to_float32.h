/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_FLOAT32_H
#define LIBSIMDPP_SIMDPP_CORE_TO_FLOAT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/to_float32.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/// @{
/** Converts 32-bit integer values to 32-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the current rounding mode is
    used.

    NEON, ALTIVEC specific:

    If only inexact conversion can be performed, round to nearest mode is used.

    @code
    r0 = (float) a0
    ...
    rN = (float) aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
float32<N> to_float32(const int32<N,E>& a)
{
    return detail::insn::i_to_float32(a.eval());
}

/** Converts 64-bit float values to 32-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is truncated.

    @par 128-bit version:
    @code
    r0 = (float) a0
    r1 = (float) a1
    r2 = 0.0f
    r3 = 0.0f
    @endcode

    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @code
    r0 = (float) a0
    ...
    r3 = (float) a3
    r4 = 0.0f
    ...
    r7 = 0.0f
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
template<unsigned N, class E> SIMDPP_INL
float32<N> to_float32(const float64<N,E>& a)
{
    return detail::insn::i_to_float32(a.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

