/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_MATH_ACCURACY_CHECKS_H
#define SIMDPP_TEST_MATH_ACCURACY_CHECKS_H

#include <simdpp/simd.h>
#include <vector>

namespace SIMDPP_ARCH_NAMESPACE {

void main_check_accuracy(const std::string& check_name);
void check_log2_approx_accuracy();
void check_log2_approx_positive_finite_accuracy();

} // namespace SIMDPP_ARCH_NAMESPACE

std::vector<simdpp::detail::FnVersion> get_run_archs();

#endif
