/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_EXPR_H
#define LIBSIMDPP_SIMD_EXPR_H

#include <simdpp/setup_arch.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// -----------------------------------------------------------------------------

template<class E1, class E2>
struct expr_bit_and {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_bit_andnot {
    E1 a;
    E2 b;
};

template<class E>
struct expr_bit_not {
    E a;
};

template<class E1, class E2>
struct expr_bit_or {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_bit_xor {
    E1 a;
    E2 b;
};

template<class E1, class E2, class E3>
struct expr_blend {
    E1 on;
    E2 off;
    E3 mask;
};

template<unsigned S, class E>
struct expr_splat2 {
    E a;
};

template<unsigned S, class E>
struct expr_splat4 {
    E a;
};

template<unsigned S, class E>
struct expr_splat8 {
    E a;
};

template<unsigned S, class E>
struct expr_splat16 {
    E a;
};

template<class E>
struct expr_vec_construct {
    E& expr() { return static_cast<E&>(*this); }
    const E& expr() const { return static_cast<const E&>(*this); }
};

struct expr_vec_load_splat : expr_vec_construct<expr_vec_load_splat> {
    const void* a;
};

template<class VE>
struct expr_vec_set_splat : expr_vec_construct<expr_vec_set_splat<VE>> {
    VE a;
};

template<class VE, unsigned N>
struct expr_vec_make_const : expr_vec_construct<expr_vec_make_const<VE,N>> {
    VE a[N];
    VE val(unsigned n) const { return a[n%N]; }
};

struct expr_vec_load : expr_vec_construct<expr_vec_load> {
    const char* a;
};

struct expr_vec_load_u : expr_vec_construct<expr_vec_load_u> {
    const char* a;
};

template<class E1, class E2>
struct expr_add {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_add_sat {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_sub {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_sub_sat {
    E1 a;
    E2 b;
};

template<class E>
struct expr_abs {
    E a;
};

template<class E>
struct expr_neg {
    E a;
};

template<class E1, class E2>
struct expr_mul {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_mul_lo {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_mul_hi {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_mull {
    E1 a;
    E2 b;
};

template<class E1, class E2, class E3>
struct expr_fmadd { // a * b + c
    E1 a;
    E2 b;
    E3 c;
};

template<class E1, class E2, class E3>
struct expr_fmsub { // a * b - c
    E1 a;
    E2 b;
    E3 c;
};

template<unsigned S, class E>
struct expr_imm_shift_l {
    E a;
    static const unsigned shift = S;
};

template<unsigned S, class E>
struct expr_imm_shift_r {
    E a;
    static const unsigned shift = S;
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
