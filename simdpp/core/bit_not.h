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

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes bitwise NOT of an integer vector

    @code
    r = ~a
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E>
gint8<N, gint8<N>> bit_not(gint8<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}
template<unsigned N, class E>
gint16<N, gint16<N>> bit_not(gint16<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}
template<unsigned N, class E>
gint32<N, gint32<N>> bit_not(gint32<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}
template<unsigned N, class E>
gint64<N, gint64<N>> bit_not(gint64<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}

template<unsigned N, class E>
mask_int8<N, mask_int8<N>> bit_not(mask_int8<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}
template<unsigned N, class E>
mask_int16<N, mask_int16<N>> bit_not(mask_int16<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}
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

/// @{
/** Computes bitwise NOT of a floating-point vector

    @code
    r = ~a
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E>
float32<N, float32<N>> bit_not(float32<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}
template<unsigned N, class E>
float64<N, float64<N>> bit_not(float64<N,E> a)
{
    return detail::insn::i_bit_not(a.eval());
}

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
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

