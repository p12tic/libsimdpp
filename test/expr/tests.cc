/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "tests.h"

void main_test_function(TestReporter& ts)
{
    test_expr_bitwise(ts);
    test_expr_math_float(ts);
    test_expr_math_int(ts);
    test_expr_compare(ts);
}

