/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_CMP_NEQ_H
#define LIBSIMDPP_SIMDPP_CORE_CMP_NEQ_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/cmp_neq.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {


/** Compares the values of two int8x16 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xff : 0x0
    ...
    rN = (aN != bN) ? 0xff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
mask_int8<N> cmp_neq(const any_int8<N,V1>& a, const any_int8<N,V2>& b)
{
    typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_cmp_neq(ra, rb);
}

SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(cmp_neq, mask_int8, any_int8)

/** Compares the values of two int16x8 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffff : 0x0
    ...
    rN = (aN != bN) ? 0xffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
mask_int16<N> cmp_neq(const any_int16<N,V1>& a, const any_int16<N,V2>& b)
{
    typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_cmp_neq(ra, rb);
}

SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(cmp_neq, mask_int16, any_int16)

/** Compares the values of two int32x4 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
mask_int32<N> cmp_neq(const any_int32<N,V1>& a, const any_int32<N,V2>& b)
{
    typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_cmp_neq(ra, rb);
}

SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(cmp_neq, mask_int32, any_int32)

/** Compares the values of two int64x2 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1, AVX, 2}
    @icost{XOP, 1}
    @icost{NEON, 4}
    @icost{ALTIVEC, 3-5}

    @par 256-bit version:
    @icost{SSE2-SSSE3, AVX, 10}
    @icost{SSE4.1, NEON, 4}
    @icost{AVX2, XOP, 2}
    @icost{NEON, 8}
    @icost{ALTIVEC, 6-8}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
mask_int64<N> cmp_neq(const any_int64<N,V1>& a, const any_int64<N,V2>& b)
{
    typename detail::get_expr2_nosign<V1, V2>::type ra, rb;
    ra = a.wrapped().eval();
    rb = b.wrapped().eval();
    return detail::insn::i_cmp_neq(ra, rb);
}

SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(cmp_neq, mask_int64, any_int64)

/** Compares the values of two float32x4 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 2}

    @par 256-bit version
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, ALTIVEC, 4}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
mask_float32<N> cmp_neq(const any_float32<N,V1>& a, const any_float32<N,V2>& b)
{
    return detail::insn::i_cmp_neq(a.wrapped().eval(), b.wrapped().eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(cmp_neq, mask_float32, any_float32)

/** Compares the values of two float64x2 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
template<unsigned N, class V1, class V2> SIMDPP_INL
mask_float64<N> cmp_neq(const any_float64<N,V1>& a, const any_float64<N,V2>& b)
{
    return detail::insn::i_cmp_neq(a.wrapped().eval(), b.wrapped().eval());
}

SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(cmp_neq, mask_float64, any_float64)

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

