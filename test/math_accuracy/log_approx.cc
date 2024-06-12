/*  Copyright (C) 2011-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/simd.h>
#include <simdpp/math/log2_approx.h>
#include "accuracy_checker.h"

namespace SIMDPP_ARCH_NAMESPACE {

void check_log2_approx_positive_finite_accuracy()
{
    auto expected_func = [](const float* src, float* dst, std::size_t size) {
        #pragma omp parallel for
        for (std::size_t i = 0; i < size; ++i) {
            *dst++ = std::log2(*src++);
        }
    };

    auto check_func = [](const float* src, float* dst, std::size_t size) {
        #pragma omp parallel for
        for (std::size_t i = 0; i < size; i += simdpp::float32v::length) {
            simdpp::float32v v = simdpp::load(src);
            v = simdpp::log2_approx_positive_finite(v);
            simdpp::store(dst, v);

            src += simdpp::float32v::length;
            dst += simdpp::float32v::length;
        }
    };

    AccuracyChecker<float> checker;
    // note that min() selects first normal value.
    checker.set_bounds({{std::numeric_limits<float>::min(), std::numeric_limits<float>::max()}});
    checker.run_check(expected_func, check_func);
    checker.describe("log2_approx_positive_finite(float32)");
}

void check_log2_approx_accuracy()
{
    auto expected_func = [](const float* src, float* dst, std::size_t size) {
        for (std::size_t i = 0; i < size; ++i) {
            *dst++ = std::log2(*src++);
        }
    };

    auto check_func = [](const float* src, float* dst, std::size_t size) {
        for (std::size_t i = 0; i < size; i += simdpp::float32v::length) {
            simdpp::float32v v = simdpp::load(src);
            v = simdpp::log2_approx(v);
            simdpp::store(dst, v);

            src += simdpp::float32v::length;
            dst += simdpp::float32v::length;
        }
    };

    AccuracyChecker<float> checker;
    checker.set_bounds({{std::numeric_limits<float>::min(), std::numeric_limits<float>::max()}});
    checker.run_check(expected_func, check_func);
    checker.describe("log2_approx(float32)");
}

} // namespace SIMDPP_ARCH_NAMESPACE
