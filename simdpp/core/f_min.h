/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_MIN_H
#define LIBSIMDPP_SIMDPP_CORE_F_MIN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_min.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// note: SSE doesn't provide a way to propagate NaNs in min/max
/** Computes minimum of the values in two vectors. If at least one of the
    values is NaN, or both values are zeroes, it is unspecified which value
    will be returned.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)

    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
float32<N, float32<N>> min(float32<N,E1> a, float32<N,E2> b)
{
    return detail::insn::i_min(a.eval(), b.eval());
}

/** Computes minima of the values in two vectors. If at least one of the values
    is NaN, or both values are zeroes, it is unspecified which value will be
    returned.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
template<unsigned N, class E1, class E2>
float64<N, float64<N>> min(float64<N,E1> a, float64<N,E2> b)
{
    return detail::insn::i_min(a.eval(), b.eval());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

