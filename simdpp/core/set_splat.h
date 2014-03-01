/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_SET_SPLAT_H
#define LIBSIMDPP_SIMDPP_CORE_SET_SPLAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/set_splat.h>
#include <simdpp/detail/insn/set_splat_mem_impl.inl>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
template<class V = expr_vec_set_splat<int>>
V splat(int x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<unsigned>>
V splat(unsigned x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<int64_t>>
V splat(int64_t x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<uint64_t>>
V splat(uint64_t x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<float>>
V splat(float x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}

template<class V = expr_vec_set_splat<double>>
V splat(double x)
{
    static_assert((is_vector<V>::value && !is_mask<V>::value) ||
                      detail::is_expr_vec_set_splat<V>::value,
                  "V must be a non-mask vector");
    return detail::insn::i_set_splat_dispatch<V>::run(x);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

