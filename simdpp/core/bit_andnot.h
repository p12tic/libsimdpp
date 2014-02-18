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

#ifndef LIBSIMDPP_SIMDPP_CORE_BIT_ANDNOT_H
#define LIBSIMDPP_SIMDPP_CORE_BIT_ANDNOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_andnot.h>
#include <simdpp/detail/expr/bit_andnot.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes bitwise AND NOT of integer vectors.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
gint8<N, gint8<N>> bit_andnot(gint8<N,E1> a, gint8<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
gint8<N, gint8<N>> bit_andnot(gint8<N,E1> a, gint16<N/2,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint8<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint8<N, gint8<N>> bit_andnot(gint8<N,E1> a, gint32<N/4,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint8<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint8<N, gint8<N>> bit_andnot(gint8<N,E1> a, gint64<N/8,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint8<N>(b.eval()));
}

template<unsigned N, class E1, class E2>
gint16<N, gint16<N>> bit_andnot(gint16<N,E1> a, gint8<N*2,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint16<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint16<N, gint16<N>> bit_andnot(gint16<N,E1> a, gint16<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
gint16<N, gint16<N>> bit_andnot(gint16<N,E1> a, gint32<N/2,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint16<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint16<N, gint16<N>> bit_andnot(gint16<N,E1> a, gint64<N/4,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint16<N>(b.eval()));
}

template<unsigned N, class E1, class E2>
gint32<N, gint32<N>> bit_andnot(gint32<N,E1> a, gint8<N*4,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint16<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint32<N, gint32<N>> bit_andnot(gint32<N,E1> a, gint16<N*2,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint16<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint32<N, gint32<N>> bit_andnot(gint32<N,E1> a, gint32<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
gint32<N, gint32<N>> bit_andnot(gint32<N,E1> a, gint64<N/2,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint16<N>(b.eval()));
}

template<unsigned N, class E1, class E2>
gint64<N, gint64<N>> bit_andnot(gint64<N,E1> a, gint8<N*8,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint64<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint64<N, gint64<N>> bit_andnot(gint64<N,E1> a, gint16<N*4,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint64<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint64<N, gint64<N>> bit_andnot(gint64<N,E1> a, gint32<N*2,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), gint64<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
gint64<N, gint64<N>> bit_andnot(gint64<N,E1> a, gint64<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}

// -----------------------------------------------------------------------------
// no point in building expression tree for 8 and 16-bit elements
template<unsigned N, class E1, class E2>
gint8<N, gint8<N>> bit_andnot(gint8<N,E1> a, mask_int8<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
gint16<N, gint16<N>> bit_andnot(gint16<N,E1> a, mask_int16<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
gint32<N, expr_bit_andnot<gint32<N,E1>,
                          mask_int32<N,E2>>> bit_andnot(gint32<N,E1> a,
                                                        mask_int32<N,E2> b)
{
    return { { a, b }, 0 };
}

template<unsigned N, class E1, class E2>
gint64<N, expr_bit_andnot<gint64<N,E1>,
                          mask_int64<N,E2>>> bit_andnot(gint64<N,E1> a,
                                                        mask_int64<N,E2> b)
{
    return { { a, b }, 0 };
}

// -----------------------------------------------------------------------------

template<unsigned N, class E1, class E2>
mask_int8<N, mask_int8<N>> bit_andnot(mask_int8<N,E1> a, mask_int8<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
mask_int16<N, mask_int16<N>> bit_andnot(mask_int16<N,E1> a, mask_int16<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
mask_int32<N, mask_int32<N>> bit_andnot(mask_int32<N,E1> a, mask_int32<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
mask_int64<N, mask_int64<N>> bit_andnot(mask_int64<N,E1> a, mask_int64<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
/// @}

/// @{
/** Computes bitwise AND NOT of floating-point vectors.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
float32<N, float32<N>> bit_andnot(float32<N,E1> a, float32<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
float32<N, float32<N>> bit_andnot(float32<N,E1> a, gint32<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), float32<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
float32<N, expr_bit_andnot<float32<N,E1>,
                           mask_float32<N,E2>>> bit_andnot(float32<N,E1> a,
                                                           mask_float32<N,E2> b)
{
    return { { a, b }, 0 };
}
template<unsigned N, class E1, class E2>
mask_float32<N, mask_float32<N>> bit_andnot(mask_float32<N,E1> a,
                                            mask_float32<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}

// -----------------------------------------------------------------------------

template<unsigned N, class E1, class E2>
float64<N, float64<N>> bit_andnot(float64<N,E1> a, float64<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
template<unsigned N, class E1, class E2>
float64<N, float64<N>> bit_andnot(float64<N,E1> a, gint64<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), float64<N>(b.eval()));
}
template<unsigned N, class E1, class E2>
float64<N, expr_bit_andnot<float64<N,E1>,
                           mask_float64<N,E2>>> bit_andnot(float64<N,E1> a,
                                                           mask_float64<N,E2> b)
{
    return { { a, b }, 0 };
}
template<unsigned N, class E1, class E2>
mask_float64<N, mask_float64<N>> bit_andnot(mask_float64<N,E1> a,
                                            mask_float64<N,E2> b)
{
    return detail::insn::i_bit_andnot(a.eval(), b.eval());
}
/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

