/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_SET_SPLAT_H
#define LIBSIMDPP_SIMDPP_CORE_SET_SPLAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/set_splat.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Loads a value from a register and broadcasts it to all elements of a vector.
    The argument value is converted to the element of the resulting vector using
    standard conversions.

    @code
    r0 = a
    ...
    rN = a
    @endcode
*/
// FIXME: return empty expression
template<class V = expr_vec_set_splat<int>> SIMDPP_INL
V splat(int x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<unsigned>> SIMDPP_INL
V splat(unsigned x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<int64_t>> SIMDPP_INL
V splat(int64_t x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<uint64_t>> SIMDPP_INL
V splat(uint64_t x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<float>> SIMDPP_INL
V splat(float x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<double>> SIMDPP_INL
V splat(double x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}
/// @}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

