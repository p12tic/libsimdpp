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

#ifndef LIBSIMDPP_SIMD_EXPR_H
#define LIBSIMDPP_SIMD_EXPR_H

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <type_traits>

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

struct expr_vec_load_splat {
    const void* a;
};

template<class VE>
struct expr_vec_set_splat {
    VE a;
};

template<class VE, unsigned N>
struct expr_vec_make_const {
    VE a[N];
};

struct expr_vec_load {
    const void* ptr;
};

template<class E1, class E2>
struct expr_add {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_adds {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_sub {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_subs {
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
