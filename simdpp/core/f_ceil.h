/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_CEIL_H
#define LIBSIMDPP_SIMDPP_CORE_F_CEIL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_ceil.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Rounds the values a vector towards positive infinity

    @code
    r0 = ceil(a0)
    ...
    rN = ceil(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, 13-15}
    @icost{NEON, 11-13}

    @par 256-bit version:
    @icost{SSE2, SSE3, SSSE3, 26-28}
    @icost{NEON, 22-24}
    @icost{ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
float32<N, float32<N>> ceil(const float32<N,E>& a)
{
    return detail::insn::i_ceil(a.eval());
}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

