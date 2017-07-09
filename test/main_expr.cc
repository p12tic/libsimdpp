/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "expr/tests.h"
#include <iostream>
#include <cstdlib>

int main()
{
    TestReporter ts(std::cerr);
    main_test_function(ts);
    ts.report_summary();

    return ts.success() ? EXIT_SUCCESS : EXIT_FAILURE;
}
