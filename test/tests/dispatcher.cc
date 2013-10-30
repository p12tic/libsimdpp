/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#define SIMDPP_USER_ARCH_INFO get_supported_arch
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
