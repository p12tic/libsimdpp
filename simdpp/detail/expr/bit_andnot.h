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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_BIT_ANDNOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_BIT_ANDNOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_andnot.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N, class E1, class E2>
uint32<N> expr_eval(expr_bit_andnot<uint32<N,E1>,
                                    mask_int32<N,E2>> q)
{
    uint32<N> a = q.a.eval();
    mask_int32<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

template<unsigned N, class E1, class E2>
uint64<N> expr_eval(expr_bit_andnot<uint64<N,E1>,
                                    mask_int64<N,E2>> q)
{
    uint64<N> a = q.a.eval();
    mask_int64<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

template<unsigned N, class E1, class E2>
float32<N> expr_eval(expr_bit_andnot<float32<N,E1>,
                                     mask_float32<N,E2>> q)
{
    float32<N> a = q.a.eval();
    mask_float32<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

template<unsigned N, class E1, class E2>
float64<N> expr_eval(expr_bit_andnot<float64<N,E1>,
                                     mask_float64<N,E2>> q)
{
    float64<N> a = q.a.eval();
    mask_float64<N> b = q.b.eval();
    return insn::i_bit_andnot(a, b);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
