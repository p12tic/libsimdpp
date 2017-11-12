/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_EXPR_TESTS_H
#define SIMDPP_TEST_EXPR_TESTS_H

#include "../utils/test_reporter.h"

void main_test_function(TestReporter& ts);
void test_expr_bitwise(TestReporter& ts);
void test_expr_math_float(TestReporter& ts);
void test_expr_math_int(TestReporter& ts);
void test_expr_compare(TestReporter& tr);

#endif
