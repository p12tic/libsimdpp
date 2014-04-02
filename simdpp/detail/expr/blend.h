/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_BLEND_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_BLEND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/blend.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

// see doc/expressions.txt for the list of combinations of expression arguments
// we must cover

/*  mask_int8, mask_int8, mask_int8
    uint8, uint8, uint8
    uint8, uint8, mask_int8
*/

template<unsigned N, class E1, class E2, class E3>
mask_int8<N> expr_eval(expr_blend<mask_int8<N,E1>,
                                  mask_int8<N,E2>,
                                  mask_int8<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint8<N> expr_eval(expr_blend<uint8<N,E1>,
                              uint8<N,E2>,
                              uint8<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint8<N> expr_eval(expr_blend<uint8<N,E1>,
                              uint8<N,E2>,
                              mask_int8<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

/*  mask_int16, mask_int16, mask_int16
    uint16, uint16, uint16
    uint16, uint16, mask_int16
*/

template<unsigned N, class E1, class E2, class E3>
mask_int16<N> expr_eval(expr_blend<mask_int16<N,E1>,
                                   mask_int16<N,E2>,
                                   mask_int16<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint16<N> expr_eval(expr_blend<uint16<N,E1>,
                               uint16<N,E2>,
                               uint16<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint16<N> expr_eval(expr_blend<uint16<N,E1>,
                               uint16<N,E2>,
                               mask_int16<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

/*  mask_int32, mask_int32, mask_int32
    mask_float32, mask_float32, mask_float32
    uint32, uint32, uint32
    uint32, uint32, mask_int32
    float32, float32, float32
    float32, float32, mask_float32
*/

template<unsigned N, class E1, class E2, class E3>
mask_int32<N> expr_eval(expr_blend<mask_int32<N,E1>,
                                   mask_int32<N,E2>,
                                   mask_int32<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
mask_float32<N> expr_eval(expr_blend<mask_float32<N,E1>,
                                     mask_float32<N,E2>,
                                     mask_float32<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint32<N> expr_eval(expr_blend<uint32<N,E1>,
                               uint32<N,E2>,
                               uint32<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint32<N> expr_eval(expr_blend<uint32<N,E1>,
                               uint32<N,E2>,
                               mask_int32<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
float32<N> expr_eval(expr_blend<float32<N,E1>,
                                float32<N,E2>,
                                float32<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
float32<N> expr_eval(expr_blend<float32<N,E1>,
                                float32<N,E2>,
                                mask_float32<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
mask_int64<N> expr_eval(expr_blend<mask_int64<N,E1>,
                                   mask_int64<N,E2>,
                                   mask_int64<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

/*  mask_int64, mask_int64, mask_int64
    mask_float64, mask_float64, mask_float64
    uint64, uint64, uint64
    uint64, uint64, mask_int64
    float64, float64, float64
    float64, float64, mask_float64
*/

template<unsigned N, class E1, class E2, class E3>
mask_float64<N> expr_eval(expr_blend<mask_float64<N,E1>,
                                     mask_float64<N,E2>,
                                     mask_float64<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint64<N> expr_eval(expr_blend<uint64<N,E1>,
                               uint64<N,E2>,
                               uint64<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
uint64<N> expr_eval(expr_blend<uint64<N,E1>,
                               uint64<N,E2>,
                               mask_int64<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
float64<N> expr_eval(expr_blend<float64<N,E1>,
                                float64<N,E2>,
                                float64<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}

template<unsigned N, class E1, class E2, class E3>
float64<N> expr_eval(expr_blend<float64<N,E1>,
                                float64<N,E2>,
                                mask_float64<N,E3>> q)
{
    return insn::i_blend(q.on.eval(), q.off.eval(), q.mask.eval());
}       

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

