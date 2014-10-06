/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_MAKE_FLOAT_H
#define LIBSIMDPP_SIMDPP_CORE_MAKE_FLOAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/make_const.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Creates a vector from floating-point values known at compile-time.
    The result of this function may be assigned or converted to a vector of any
    type: standard conversions are used to convert the arguments. All
    conversions and other overhead is performed at compile-time thus even if the
    minimal optimization level is selected, the function results in a simple
    load from memory.

    The function is not guaranteed to have adequate performance if the
    arguments are not known at compile-time.

    If the vector has fewer elements than the number of the parameters this
    function accepts then the extra values are discarded.

    @par 1 parameter version
    @code
        | 0  1  2  3  ... n  |
    r = [ v0 v0 v0 v0 ... v0 ]
    @endcode

    @par 2 parameters version
    @code
        | 0  1  2  3  ... n  |
    r = [ v0 v1 v0 v1 ... v1 ]
    @endcode

    @par 4 parameters version
    @code
        | 0  1  2  3  ... n  |
    r = [ v0 v1 v2 v3 ... v3 ]
    @endcode

    @par 8 parameters version
    @code
        | 0  1  ..  7  8  ... n  |
    r = [ v0 v1 .. v7 v0  ... v7 ]
    @endcode
*/
// FIXME: return empty expr
template<class V = expr_vec_make_const<double,1>> SIMDPP_INL
V make_float(double v0)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                  detail::is_expr_vec_make_const<V>::value,
                  "V must be a non-mask vector");
    expr_vec_make_const<double,1> a;
    a.a[0] = v0;
    return detail::insn::i_make_const_dispatch<V>::run(a);
}

template<class V = expr_vec_make_const<double,2>> SIMDPP_INL
V make_float(double v0, double v1)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                  detail::is_expr_vec_make_const<V>::value,
                  "V must be a non-mask vector");
    expr_vec_make_const<double,2> a;
    a.a[0] = v0;
    a.a[1] = v1;
    return detail::insn::i_make_const_dispatch<V>::run(a);
}

template<class V = expr_vec_make_const<double,4>> SIMDPP_INL
V make_float(double v0, double v1, double v2, double v3)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                  detail::is_expr_vec_make_const<V>::value,
                  "V must be a non-mask vector");
    expr_vec_make_const<double,4> a;
    a.a[0] = v0;  a.a[1] = v1;  a.a[2] = v2;  a.a[3] = v3;
    return detail::insn::i_make_const_dispatch<V>::run(a);
}

template<class V = expr_vec_make_const<double,8>> SIMDPP_INL
V make_float(double v0, double v1, double v2, double v3,
             double v4, double v5, double v6, double v7)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                  detail::is_expr_vec_make_const<V>::value,
                  "V must be a non-mask vector");
    expr_vec_make_const<double,8> a;
    a.a[0] = v0;  a.a[1] = v1;  a.a[2] = v2;  a.a[3] = v3;
    a.a[4] = v4;  a.a[5] = v5;  a.a[6] = v6;  a.a[7] = v7;
    return detail::insn::i_make_const_dispatch<V>::run(a);
}
/// @}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

