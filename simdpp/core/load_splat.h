/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_SPLAT_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_SPLAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/load_splat.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Loads a value from a memory location and broadcasts it to all elements of a
    vector.

    @code
    r0 = *p
    ...
    rN = *p
    @endcode

    @a p must have the alignment of the element of the target vector.
*/
// FIXME: return empty expression
template<class V = expr_vec_load_splat> SIMDPP_INL
V load_splat(const void* p)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_load_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_load_splat_dispatch<V>::run(p);
}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

