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
#include <simdpp/detail/insn/i_mul_lo.h>
#include <simdpp/detail/insn/i_mul_hi.h>
#include <simdpp/core/detail/get_expr_uint.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

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
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr_uint<V1, V2>::type
        mul_lo(const any_int16<N,V1>& a,
               const any_int16<N,V2>& b)
{
    typename detail::get_expr_uint<V1, V2>::v1_final_type ra;
    typename detail::get_expr_uint<V1, V2>::v2_final_type rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_mul_lo(ra, rb);
}

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(mul_lo, expr_mul_lo, any_int16, int16<N>)

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
template<unsigned N> SIMDPP_INL
int16<N> mul_hi(const int16<N>& a, const int16<N>& b)
{
    return detail::insn::i_mul_hi(a.wrapped().eval(), b.wrapped().eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC(mul_hi, int16, int16)

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
template<unsigned N> SIMDPP_INL
uint16<N> mul_hi(const uint16<N>& a, const uint16<N>& b)
{
    return detail::insn::i_mul_hi(a.wrapped().eval(), b.wrapped().eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC(mul_hi, uint16, uint16)


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
template<unsigned N, class V1, class V2> SIMDPP_INL
typename detail::get_expr_uint<V1, V2>::type
        mul_lo(const any_int32<N,V1>& a, const any_int32<N,V2>& b)
{
    typename detail::get_expr_uint<V1, V2>::v1_final_type ra;
    typename detail::get_expr_uint<V1, V2>::v2_final_type rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_mul_lo(ra, rb);
}

SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(mul_lo, expr_mul_lo, any_int32, int32<N>)


} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

