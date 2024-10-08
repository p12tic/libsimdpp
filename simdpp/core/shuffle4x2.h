/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_SHUFFLE4x2_H
#define LIBSIMDPP_SIMDPP_CORE_SHUFFLE4x2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/shuffle4x2.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Selects 32-bit values from two vectors.
    The selector values must be in range [0; 7].

    @code
    For each 128-bit segment:
    ab = [ a..b ]
    r0 = ab[s0]
    r1 = ab[s1]
    r2 = ab[s2]
    r3 = ab[s3]
    @endcode
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N,
         class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2>::type
    shuffle4x2(const any_vec32<N,V1>& a, const any_vec32<N,V2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
    typename detail::get_expr2_nomask_nosign<V1,V2>::type a0 = a.wrapped(),
                                                          b0 = b.wrapped();
    return detail::insn::i_shuffle4x2<s0,s1,s2,s3>(a0, b0);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE2(V1, a, b);
#endif
}

/** Selects 64-bit values from two vectors.
    The selector values must be in range [0; 7].

    @code
    For each 256-bit segment:
    ab = [ a..b ]
    r0 = ab[s0]
    r1 = ab[s1]
    r2 = ab[s2]
    r3 = ab[s3]
    @endcode
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N,
         class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2>::type
    shuffle4x2(const any_vec64<N,V1>& a, const any_vec64<N,V2>& b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    static_assert(s0 < 8 && s1 < 8 && s2 < 8 && s3 < 8, "Selector out of range");
    typename detail::get_expr2_nomask_nosign<V1,V2>::type a0 = a.wrapped(),
                                                          b0 = b.wrapped();
    return detail::insn::i_shuffle4x2<s0,s1,s2,s3>(a0, b0);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE2(V1, a, b);
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

