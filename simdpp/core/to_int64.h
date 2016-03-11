/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_TO_INT64_H
#define LIBSIMDPP_SIMDPP_CORE_TO_INT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/to_int64.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @{
/** Extends the values of a signed int32x4 vector to 64-bits

    @code
    r0 = (int64_t) a0
    ...
    r3 = (int64_t) a3
    @endcode

    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX, 3}
    @icost{NEON, 2}
    @icost{ALTIVEC, 3-4}
*/
template<unsigned N, class E> SIMDPP_INL
int64<N> to_int64(const int32<N,E>& a)
{
    return detail::insn::i_to_int64(a.eval());
}

/** Extends the values of an unsigned int32x4 vector to 64-bits

    @code
    r0 = (uint64_t) a0
    ...
    r3 = (uint64_t) a3
    @endcode

    @icost{SSE2-AVX, 3}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E> SIMDPP_INL
uint64<N> to_uint64(const uint32<N,E>& a)
{
    return detail::insn::i_to_uint64(a.eval());
}

#if !SIMDPP_DISABLE_DEPRECATED
template<unsigned N, class E> SIMDPP_INL
uint64<N> to_int64(const uint32<N,E>& a)
{
    return to_uint64(a);
}
#endif

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

