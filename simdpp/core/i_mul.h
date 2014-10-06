/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_MUL_H
#define LIBSIMDPP_SIMDPP_CORE_I_MUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/expr/i_mul.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// no 8 bit multiplications in SSE
/** Multiplies 16-bit values and returns the lower part of the multiplication

    @code
    r0 = low(a0 * b0)
    ...
    rN = low(aN * bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class V1, class V2>
_PROMOTED_NOMASK_EXPRESSION_ mul_lo(const any_int16<N,V1>& a,
                                    const any_int16<N,V2>& b);
#else
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2,
                                  expr_mul_lo<uint16<N, typename V1::expr_type>,
                                              uint16<N, typename V2::expr_type>>
                                 >::type
        mul_lo(const any_int16<N,V1>& a,
               const any_int16<N,V2>& b)
{
    return { { a.wrapped(), b.wrapped() }, 0 };
}
#endif

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(mul_lo, expr_mul_lo, any_int16, uint16)

/** Multiplies signed 16-bit values and returns the higher half of the result.

    @code
    r0 = high(a0 * b0)
    ...
    rN = high(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, ALTIVEC, 6}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
int16<N, _DETAIL_> mul_hi(int16<N,E1> a,
                          int16<N,E2> b);
#else
template<unsigned N, class E1, class E2> SIMDPP_INL
int16<N, expr_mul_hi<int16<N,E1>,
                     int16<N,E2>>> mul_hi(int16<N,E1> a,
                                          int16<N,E2> b)
{
    return { { a, b }, 0 };
}
#endif

SIMDPP_SCALAR_ARG_IMPL_EXPR(mul_hi, expr_mul_hi, int16, int16)

/** Multiplies unsigned 16-bit values and returns the higher half of the result.

    @code
    r0 = high(a0 * b0)
    ...
    rN = high(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, ALTIVEC, 6}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
uint16<N, _DETAIL_> mul_hi(uint16<N,E1> a,
                           uint16<N,E2> b);
#else
template<unsigned N, class E1, class E2> SIMDPP_INL
uint16<N, expr_mul_hi<uint16<N,E1>,
                      uint16<N,E2>>> mul_hi(uint16<N,E1> a,
                                            uint16<N,E2> b)
{
    return { { a, b }, 0 };
}
#endif

SIMDPP_SCALAR_ARG_IMPL_EXPR(mul_hi, expr_mul_hi, uint16, uint16)


/** Multiplies 32-bit values and returns the lower half of the result.

    @code
    r0 = low(a0 * b0)
    ...
    rN = low(aN * bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6}
    @icost{ALTIVEC, 8}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12}
    @icost{SSE4.1, AVX, NEON, 2}
    @icost{ALTIVEC, 16}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class V1, class V2>
_PROMOTED_NOMASK_EXPRESSION_ mul_lo(const any_int32<N,V1>& a,
                                    const any_int32<N,V2>& b);
#else
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr2_nomask<V1, V2,
                                  expr_mul_lo<uint32<N, typename V1::expr_type>,
                                              uint32<N, typename V2::expr_type>>
                                 >::type
        mul_lo(const any_int32<N,V1>& a,
               const any_int32<N,V2>& b)
{
    return { { a.wrapped(), b.wrapped() }, 0 };
}
#endif

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(mul_lo, expr_mul_lo, any_int32, uint32)


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

