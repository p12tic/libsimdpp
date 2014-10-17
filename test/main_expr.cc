/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "expr/tests.h"

int main()
{
    SeqTestSuite ts;
    main_test_function(ts);
    if (!ts.success()) {
        return 1;
    }
    return 0;
}
