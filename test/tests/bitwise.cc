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

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

void test_bitwise(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "bitwise");

    using namespace simdpp;

    uint64x4 a11 = uint64x4::make_const(0x0f0ff0f0ffff0000, 0x0f0ff0f0ffff0000);
    uint64x4 a12 = uint64x4::make_const(0xffffffffffffffff, 0x0000000000000000);

    float64x4 b11(a11);
    float64x4 b12(a12);

    float32x8 c11 = float32x8(a11);
    float32x8 c12 = float32x8(a12);

    TEST_PUSH16X2_2(tc, uint64x4,  bit_and, a11, a12);
    TEST_PUSH16X2_2(tc, float64x4, bit_and, b11, b12);
    TEST_PUSH16X2_2(tc, float32x8, bit_and, c11, c12);

    TEST_PUSH16X2_2(tc, uint64x4,  bit_andnot, a11, a12);
    TEST_PUSH16X2_2(tc, float64x4, bit_andnot, b11, b12);
    TEST_PUSH16X2_2(tc, float32x8, bit_andnot, c11, c12);

    TEST_PUSH16X2_2(tc, uint64x4,  bit_or, a11, a12);
    TEST_PUSH16X2_2(tc, float64x4, bit_or, b11, b12);
    TEST_PUSH16X2_2(tc, float32x8, bit_or, c11, c12);

    TEST_PUSH16X2_2(tc, uint64x4,  bit_xor, a11, a12);
    TEST_PUSH16X2_2(tc, float64x4, bit_xor, b11, b12);
    TEST_PUSH16X2_2(tc, float32x8, bit_xor, c11, c12);

    TEST_PUSH16X2_1(tc, uint64x4,  bit_not, a11);
}

} // namespace SIMDPP_ARCH_NAMESPACE
