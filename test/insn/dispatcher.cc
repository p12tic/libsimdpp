/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#define SIMDPP_USER_ARCH_INFO get_supported_arch()
#include "dispatcher.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

simdpp::Arch test_dispatcher()
{
    return simdpp::this_compile_arch();
}

int test_dispatcher1(int arg)
{
    return arg;
}

int test_dispatcher2(int arg, int arg2)
{
    return arg + arg2;
}

int test_dispatcher3(int arg, int arg2, int arg3)
{
    return arg + arg2 + arg3;
}

int test_dispatcher4(int arg, int arg2, int arg3, int arg4)
{
    return arg + arg2 + arg3 + arg4;
}

} // namespace SIMDPP_ARCH_NAMESPACE

SIMDPP_MAKE_DISPATCHER_RET0(test_dispatcher, simdpp::Arch)
SIMDPP_MAKE_DISPATCHER_RET1(test_dispatcher1, int, int)
SIMDPP_MAKE_DISPATCHER_RET2(test_dispatcher2, int, int, int)
SIMDPP_MAKE_DISPATCHER_RET3(test_dispatcher3, int, int, int, int)
SIMDPP_MAKE_DISPATCHER_RET4(test_dispatcher4, int, int, int, int, int)
