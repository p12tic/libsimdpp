/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_NOT_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_NOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_not.h>
#include <simdpp/detail/expr/bit_not.h>
#include <simdpp/detail/get_expr.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes bitwise NOT of an integer or floating-point vector

    @code
    r = ~a
    @endcode

    @todo icost
*/
template<unsigned N, class V>
typename detail::get_expr<V, void>::empty
    bit_not(const any_vec<N,V>& a)
{
    typename detail::get_expr_nosign<V, void>::type ra;
    ra = a.vec().eval();
    return detail::insn::i_bit_not(ra);
}

/* FIXME
template<unsigned N, class E>
mask_int32<N, expr_bit_not<mask_int32<N,E>>> bit_not(mask_int32<N,E> a)
{
    return { { a }, 0 };
}
template<unsigned N, class E>
mask_int64<N, expr_bit_not<mask_int64<N,E>>> bit_not(mask_int64<N,E> a)
{
    return { { a }, 0 };
}
/// @}


template<unsigned N, class E>
mask_float32<N, expr_bit_not<mask_float32<N,E>>> bit_not(mask_float32<N,E> a)
{
    return { { a }, 0 };
}
template<unsigned N, class E>
mask_float64<N, expr_bit_not<mask_float64<N,E>>> bit_not(mask_float64<N,E> a)
{
    return { { a }, 0 };
}
/// @}*/

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

