/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_FMSUB_H
#define LIBSIMDPP_SIMDPP_CORE_F_FMSUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_fmsub.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Performs a fused multiply-sutract operation

    @code
    r0 = a0 * b0 - c0
    ...
    rN = aN * bN - cN
    @endcode

    Implemented only on architectures with either @c X86_FMA3 or @c X86_FMA4
    support.
*/
template<unsigned N> SIMDPP_INL
float32<N> fmsub(const float32<N>& a, const float32<N>& b, const float32<N>& c)
{
    return detail::insn::i_fmsub(a, b, c);
}

template<unsigned N> SIMDPP_INL
float64<N> fmsub(const float64<N>& a, const float64<N>& b, const float64<N>& c)
{
    return detail::insn::i_fmsub(a, b, c);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

