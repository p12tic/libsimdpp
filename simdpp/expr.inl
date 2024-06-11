/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_TYPES_GENERIC_INL
#define LIBSIMDPP_SIMD_TYPES_GENERIC_INL

#include <simdpp/setup_arch.h>
#include <simdpp/expr.h>
#include <simdpp/detail/expr/scalar.h>
#include <simdpp/detail/expr/test_bits.h>
#include <simdpp/detail/expr/vec.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, class E> struct expr_eval_wrapper {
static SIMDPP_INL R eval(const E& e) { return expr_eval<R, E>::eval(e); }
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
