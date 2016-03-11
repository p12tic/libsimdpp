/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_EXPR_H
#define LIBSIMDPP_SIMD_EXPR_H

#include <simdpp/setup_arch.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

// -----------------------------------------------------------------------------
struct expr_empty {};

template<class VE>
struct expr_scalar_bitwise {
    const VE& e;
};

template<class VE>
struct expr_scalar {
    const VE& e;
};

template<class E1, class E2>
struct expr_bit_and {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_bit_andnot {
    const E1& a;
    const E2& b;
};

template<class E>
struct expr_bit_not {
    const E& a;
};

template<class E1, class E2>
struct expr_bit_or {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_bit_xor {
    const E1& a;
    const E2& b;
};

template<class E1, class E2, class E3>
struct expr_blend {
    const E1& on;
    const E2& off;
    const E3& mask;
};

template<unsigned S, class E>
struct expr_splat2 {
    const E& a;
};

template<unsigned S, class E>
struct expr_splat4 {
    const E& a;
};

template<unsigned S, class E>
struct expr_splat8 {
    const E& a;
};

template<unsigned S, class E>
struct expr_splat16 {
    const E& a;
};

template<class E>
struct expr_vec_construct {
    SIMDPP_INL E& expr() { return static_cast<E&>(*this); }
    SIMDPP_INL const E& expr() const { return static_cast<const E&>(*this); }
};

struct expr_vec_load_splat : expr_vec_construct<expr_vec_load_splat> {
    const char* a;

    expr_vec_load_splat(const char* x) : a(x) {}
};

template<class VE>
struct expr_vec_set_splat : expr_vec_construct<expr_vec_set_splat<VE>> {
    VE a;

    expr_vec_set_splat(const VE& x) : a(x) {}
};

template<class VE, unsigned N>
struct expr_vec_make_const : expr_vec_construct<expr_vec_make_const<VE,N>> {
    VE a[N];
    SIMDPP_INL const VE& val(unsigned n) const { return a[n%N]; }
};

// This expression is needed because it's not possible to use
// expr_vec_make_const to initialize floating-point vectors to ones
struct expr_vec_make_ones : expr_vec_construct<expr_vec_make_ones> {};

struct expr_vec_load : expr_vec_construct<expr_vec_load> {
    const char* a;
};

struct expr_vec_load_u : expr_vec_construct<expr_vec_load_u> {
    const char* a;

    expr_vec_load_u(const char* x) : a(x) {}
};

template<class E1, class E2>
struct expr_add {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_add_sat {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_sub {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_sub_sat {
    const E1& a;
    const E2& b;
};

template<class E>
struct expr_abs {
    const E& a;
};

template<class E>
struct expr_neg {
    const E& a;
};

template<class E1, class E2>
struct expr_mul {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_mul_lo {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_mul_hi {
    const E1& a;
    const E2& b;
};

template<class E1, class E2>
struct expr_mull {
    const E1& a;
    const E2& b;
};

template<class E1, class E2, class E3>
struct expr_fmadd { // a * b + c
    const E1& a;
    const E2& b;
    const E3& c;
};

template<class E1, class E2, class E3>
struct expr_fmsub { // a * b - c
    const E1& a;
    const E2& b;
    const E3& c;
};

template<unsigned S, class E>
struct expr_imm_shift_l {
    const E& a;
    static const unsigned shift = S;
};

template<unsigned S, class E>
struct expr_imm_shift_r {
    const E& a;
    static const unsigned shift = S;
};

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
