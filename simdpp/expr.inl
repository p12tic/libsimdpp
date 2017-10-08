/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_TYPES_GENERIC_INL
#define LIBSIMDPP_SIMD_TYPES_GENERIC_INL

#include <simdpp/setup_arch.h>
#include <simdpp/expr.h>
#include <simdpp/detail/expr/bit_and.h>
#include <simdpp/detail/expr/bit_andnot.h>
#include <simdpp/detail/expr/bit_not.h>
#include <simdpp/detail/expr/bit_or.h>
#include <simdpp/detail/expr/blend.h>
#include <simdpp/detail/expr/f_abs.h>
#include <simdpp/detail/expr/f_add.h>
#include <simdpp/detail/expr/f_fmadd.h>
#include <simdpp/detail/expr/f_fmsub.h>
#include <simdpp/detail/expr/f_mul.h>
#include <simdpp/detail/expr/f_neg.h>
#include <simdpp/detail/expr/f_sub.h>
#include <simdpp/detail/expr/i_abs.h>
#include <simdpp/detail/expr/i_add.h>
#include <simdpp/detail/expr/i_add_sat.h>
#include <simdpp/detail/expr/i_mul.h>
#include <simdpp/detail/expr/i_mull.h>
#include <simdpp/detail/expr/i_neg.h>
#include <simdpp/detail/expr/i_sub.h>
#include <simdpp/detail/expr/i_sub_sat.h>
#include <simdpp/detail/expr/scalar.h>
#include <simdpp/detail/expr/splat_n.h>
#include <simdpp/detail/expr/test_bits.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<class VE>
template<class R> SIMDPP_INL
R expr_scalar_bitwise<VE>::eval() const { return detail::expr_eval_scalar_bitwise<R>(e); }

template<class VE>
template<class R> SIMDPP_INL
R expr_scalar<VE>::eval() const { return detail::expr_eval_scalar<R>(e); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_bit_and<E1,E2>::eval() const { return detail::expr_eval_bit_and<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_bit_andnot<E1,E2>::eval() const { return detail::expr_eval_bit_andnot<R>(a, b); }
template<class E>
template<class R> SIMDPP_INL
R expr_bit_not<E>::eval() const { return detail::expr_eval_bit_not<R>(a); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_bit_or<E1,E2>::eval() const { return detail::expr_eval_bit_or<R>(a, b); }

/*template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_bit_xor<E1,E2>::eval() const { return detail::expr_eval_bit_xor<R>(a, b); }
*/

template<class E1, class E2, class E3>
template<class R> SIMDPP_INL
R expr_blend<E1,E2,E3>::eval() const { return detail::expr_eval_blend<R>(on, off, mask); }

template<unsigned S, class E>
template<class R> SIMDPP_INL
R expr_splat2<S,E>::eval() const { return detail::expr_eval_splat2<R,S>(a); }

template<unsigned S, class E>
template<class R> SIMDPP_INL
R expr_splat4<S,E>::eval() const { return detail::expr_eval_splat4<R,S>(a); }

template<unsigned S, class E>
template<class R> SIMDPP_INL
R expr_splat8<S,E>::eval() const { return detail::expr_eval_splat8<R,S>(a); }

template<unsigned S, class E>
template<class R> SIMDPP_INL
R expr_splat16<S,E>::eval() const { return detail::expr_eval_splat16<R,S>(a); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_add<E1,E2>::eval() const { return detail::expr_eval_add<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_add_sat<E1,E2>::eval() const { return detail::expr_eval_add_sat<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_sub<E1,E2>::eval() const { return detail::expr_eval_sub<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_sub_sat<E1,E2>::eval() const { return detail::expr_eval_sub_sat<R>(a, b); }

template<class E>
template<class R> SIMDPP_INL
R expr_abs<E>::eval() const { return detail::expr_eval_abs<R>(a); }

template<class E>
template<class R> SIMDPP_INL
R expr_neg<E>::eval() const { return detail::expr_eval_neg<R>(a); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_mul<E1,E2>::eval() const { return detail::expr_eval_mul<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_mul_lo<E1,E2>::eval() const { return detail::expr_eval_mul_lo<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_mul_hi<E1,E2>::eval() const { return detail::expr_eval_mul_hi<R>(a, b); }

template<class E1, class E2>
template<class R> SIMDPP_INL
R expr_mull<E1,E2>::eval() const { return detail::expr_eval_mull<R>(a, b); }

template<class E1, class E2, class E3>
template<class R> SIMDPP_INL
R expr_fmadd<E1,E2,E3>::eval() const { return detail::expr_eval_fmadd<R>(a, b, c); }

template<class E1, class E2, class E3>
template<class R> SIMDPP_INL
R expr_fmsub<E1,E2,E3>::eval() const { return detail::expr_eval_fmsub<R>(a, b, c); }

/*template<unsigned S, class E>
template<class R> SIMDPP_INL
R expr_imm_shift_l<S,E>::eval() const { return detail::expr_eval_imm_shift_l<R,S>(a, b); }

template<unsigned S, class E>
template<class R> SIMDPP_INL
R expr_imm_shift_r<S,E>::eval() const { return detail::expr_eval_imm_shift_r<R,S>(a); }
*/
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
