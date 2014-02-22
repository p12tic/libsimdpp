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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_BROADCAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_BROADCAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/splat_n.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N, unsigned s, class E>
gint8<N> expr_eval(expr_splat16<s,gint8<N,E>> q)
{
    gint8<N> a = q.a.eval();
    return insn::i_splat16<s>(a);
}

template<unsigned N, unsigned s, class E>
gint16<N> expr_eval(expr_splat8<s,gint16<N,E>> q)
{
    gint16<N> a = q.a.eval();
    return insn::i_splat8<s>(a);
}

template<unsigned N, unsigned s, class E>
gint32<N> expr_eval(expr_splat4<s,gint32<N,E>> q)
{
    gint32<N> a = q.a.eval();
    return insn::i_splat4<s>(a);
}

template<unsigned N, unsigned s, class E>
gint64<N> expr_eval(expr_splat2<s,gint64<N,E>> q)
{
    gint64<N> a = q.a.eval();
    return insn::i_splat2<s>(a);
}

template<unsigned N, unsigned s, class E>
float32<N> expr_eval(expr_splat4<s,float32<N,E>> q)
{
    float32<N> a = q.a.eval();
    return insn::i_splat4<s>(a);
}

template<unsigned N, unsigned s, class E>
float64<N> expr_eval(expr_splat2<s,float64<N,E>> q)
{
    float64<N> a = q.a.eval();
    return insn::i_splat2<s>(a);
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

