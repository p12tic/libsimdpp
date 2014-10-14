/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SUB_H
#define LIBSIMDPP_SIMDPP_CORE_I_SUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/expr/i_sub.h>
#include <simdpp/detail/get_expr.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Subtracts 8-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2,
                                  expr_sub<uint8<N, typename V1::expr_type>,
                                           uint8<N, typename V2::expr_type>>
                                 >::type
        sub(const any_int8<N,V1>& a,
            const any_int8<N,V2>& b)
{
    return { { a.wrapped(), b.wrapped() }, 0 };
}

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(sub, expr_sub, any_int8, uint8)

/** Subtracts 16-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2,
                                  expr_sub<uint16<N, typename V1::expr_type>,
                                           uint16<N, typename V2::expr_type>>
                                 >::type
        sub(const any_int16<N,V1>& a,
            const any_int16<N,V2>& b)
{
    return { { a.wrapped(), b.wrapped() }, 0 };
}

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(sub, expr_sub, any_int16, uint16)

/** Subtracts 32-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2,
                                  expr_sub<uint32<N, typename V1::expr_type>,
                                           uint32<N, typename V2::expr_type>>
                                 >::type
        sub(const any_int32<N,V1>& a,
            const any_int32<N,V2>& b)
{
    return { { a.wrapped(), b.wrapped() }, 0 };
}

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(sub, expr_sub, any_int32, uint32)

/** Subtracts 64-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 5-6}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 10-11}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2,
                                  expr_sub<uint64<N, typename V1::expr_type>,
                                           uint64<N, typename V2::expr_type>>
                                 >::type
        sub(const any_int64<N,V1>& a,
            const any_int64<N,V2>& b)
{
    return { { a.wrapped(), b.wrapped() }, 0 };
}

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(sub, expr_sub, any_int64, uint64)


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

