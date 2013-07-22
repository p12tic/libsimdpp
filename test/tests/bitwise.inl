/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_BITWISE_H
#define LIBSIMDPP_TEST_TESTS_BITWISE_H

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

    TEST_PUSH32_2(tc, uint64x4,  bit_and, a11, a12);
    TEST_PUSH32_2(tc, float64x4, bit_and, b11, b12);
    TEST_PUSH32_2(tc, float32x8, bit_and, c11, c12);

    TEST_PUSH32_2(tc, uint64x4,  bit_andnot, a11, a12);
    TEST_PUSH32_2(tc, float64x4, bit_andnot, b11, b12);
    TEST_PUSH32_2(tc, float32x8, bit_andnot, c11, c12);

    TEST_PUSH32_2(tc, uint64x4,  bit_or, a11, a12);
    TEST_PUSH32_2(tc, float64x4, bit_or, b11, b12);
    TEST_PUSH32_2(tc, float32x8, bit_or, c11, c12);

    TEST_PUSH32_2(tc, uint64x4,  bit_xor, a11, a12);
    TEST_PUSH32_2(tc, float64x4, bit_xor, b11, b12);
    TEST_PUSH32_2(tc, float32x8, bit_xor, c11, c12);

    TEST_PUSH32_1(tc, uint64x4,  bit_not, a11);
}

SIMDPP_ARCH_NAMESPACE_END

#endif
