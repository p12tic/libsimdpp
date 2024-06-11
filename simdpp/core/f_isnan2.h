/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_ISNAN2_H
#define LIBSIMDPP_SIMDPP_CORE_F_ISNAN2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_isnan2.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Checks whether corresponding elements in either @a a or @a b are IEEE754 NaN.

    @code
    r0 = isnan(a0) || isnan(b0) ? 0xffffffff : 0
    ...
    rN = isnan(aN) || isnan(bN) ? 0xffffffff : 0
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 3}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, ALTIVEC, 6}
*/
template<unsigned N> SIMDPP_INL
mask_float32<N> isnan2(const float32<N>& a, const float32<N>& b)
{
    return detail::insn::i_isnan2(a, b);
}

/** Checks whether corresponding elements in either @a a or @a b are IEEE754
    NaN.

    @code
    r0 = isnan(a0) || isnan(b0) ? 0xffffffffffffffff : 0
    ...
    rN = isnan(aN) || isnan(bN) ? 0xffffffffffffffff : 0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
template<unsigned N> SIMDPP_INL
mask_float64<N> isnan2(const float64<N>& a, const float64<N>& b)
{
    return detail::insn::i_isnan2(a, b);
}


} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

