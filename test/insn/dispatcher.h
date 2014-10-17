/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/dispatch/arch.h>

simdpp::Arch get_supported_arch(); // in main_dispatcher.cc
simdpp::Arch test_dispatcher();

int test_dispatcher1(int arg);
int test_dispatcher2(int arg, int arg2);
int test_dispatcher3(int arg, int arg2, int arg3);
int test_dispatcher4(int arg, int arg2, int arg3, int arg4);
