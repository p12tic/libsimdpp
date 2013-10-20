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

#ifndef SIMDPP_TEST_SIMD_H
#define SIMDPP_TEST_SIMD_H

#include "test_helpers.h"
#include "test_results.h"
#include "traits.h"

#include <stdint.h>
#include <iostream>

namespace SIMDPP_ARCH_NAMESPACE {

void main_test_function(TestResults& res);
void test_compare(TestResults& res);
void test_convert(TestResults& res);
void test_construct(TestResults& res);
void test_bitwise(TestResults& res);
void test_math_fp(TestResults& res);
void test_math_int(TestResults& res);
void test_math_shift(TestResults& res);
void test_memory_load(TestResults& res);
void test_memory_store(TestResults& res);
void test_set(TestResults& res);
void test_shuffle(TestResults& res);
void test_shuffle_bytes(TestResults& res);
void test_shuffle_generic(TestResults& res);
void test_shuffle_transpose(TestResults& res);
void test_transpose(TestResults& res);

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
