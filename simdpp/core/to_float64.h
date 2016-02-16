/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_FLOAT64_H
#define LIBSIMDPP_SIMDPP_CORE_TO_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/to_float64.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/// @{
/** Converts the 32-bit integer values to 64-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is rounded to the
    nearest representable value.

    @par 256-bit version:
    @code
    r0 = (double) a0
    ...
    r3 = (double) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
template<unsigned N, class E> SIMDPP_INL
float64<N> to_float64(const int32<N,E>& a)
{
    return detail::insn::i_to_float64(a.eval());
}

/** Converts the 32-bit float values to 64-bit float values.

    SSE specific:

    If only inexact conversion can be performed, the value is rounded according
    to the current rounding mode.

    NEON specific:

    If only inexact conversion can be performed, the value is rounded to the
    nearest representable value.

    @par 256-bit version:
    @code
    r0 = (double) a0
    ...
    r3 = (double) a3
    @endcode

    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}
*/
template<unsigned N, class E> SIMDPP_INL
float64<N> to_float64(const float32<N,E>& a)
{
    return detail::insn::i_to_float64(a.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

