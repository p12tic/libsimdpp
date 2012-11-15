/*  libsimdpp
    Copyright (C) 2011-2012  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_COMPARE_H
#define LIBSIMDPP_TEST_TESTS_COMPARE_H

#include <limits>

namespace SIMDPP_ARCH_NAMESPACE {

#define TEST_COMPARE_TESTER_HELPER(TC, T, L, R)                     \
{                                                                   \
    TEST_ARRAY_HELPER2(TC, T, cmp_eq, L, R);                        \
    TEST_ARRAY_HELPER2(TC, T, cmp_lt, L, R);                        \
    TEST_ARRAY_HELPER2(TC, T, cmp_gt, L, R);                        \
}

void test_compare(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "compare");

#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    TestCase& tc64 = NEW_TEST_CASE(res, "compare_f64");
#endif

    using namespace simdpp;

    //int8x16
    {
    uint8x16 sl[] = {
        uint8x16::make_const(0x11, 0x22, 0x33, 0xff),
        uint8x16::make_const(0xcc, 0xdd, 0xee, 0xff),
        uint8x16::make_const(0x01, 0x00, 0xff, 0xfe),
    };
    uint8x16 sr[] = {
        uint8x16::make_const(0x22, 0x22, 0x22, 0x22),
        uint8x16::make_const(0xee, 0xee, 0xee, 0xee),
        uint8x16::make_const(0x00, 0x00, 0x00, 0x00),
    };

    TEST_COMPARE_TESTER_HELPER(tc, int8x16, sl, sr);
    TEST_COMPARE_TESTER_HELPER(tc, uint8x16, sl, sr);
    }

    //int16x8
    {
        uint16x8 sl[] = {
            uint16x8::make_const(0x1111, 0x2222, 0x3333, 0x3333),
            uint16x8::make_const(0xdddd, 0xeeee, 0xffff, 0xcccc),
            uint16x8::make_const(0x0001, 0x0000, 0xffff, 0xfffe),
        };
        uint16x8 sr[] = {
            uint16x8::make_const(0x2222, 0x2222, 0x2222, 0x2222),
            uint16x8::make_const(0xeeee, 0xeeee, 0xeeee, 0xeeee),
            uint16x8::make_const(0x0000, 0x0000, 0x0000, 0x0000),
        };

        TEST_COMPARE_TESTER_HELPER(tc, int16x8, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint16x8, sl, sr);
    }

    //int32x4
    {
        uint32x4 sl[] = {
            uint32x4::make_const(0x11111111, 0x22222222, 0x33333333, 0x33333333),
            uint32x4::make_const(0xdddddddd, 0xeeeeeeee, 0xffffffff, 0xcccccccc),
            uint32x4::make_const(0x00000000, 0x00000001, 0xffffffff, 0xfffffffe),
        };
        uint32x4 sr[] = {
            uint32x4::make_const(0x22222222, 0x22222222, 0x22222222, 0x22222222),
            uint32x4::make_const(0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee),
            uint32x4::make_const(0x00000000, 0x00000000, 0x00000000, 0x00000000),
        };

        TEST_COMPARE_TESTER_HELPER(tc, int32x4, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint32x4, sl, sr);
    }

    //int64x2 not available

    auto nanf = [](){ return std::numeric_limits<float>::quiet_NaN(); };
    auto nan = [](){ return std::numeric_limits<double>::quiet_NaN(); };
    auto inff = [](){ return std::numeric_limits<float>::infinity(); };
    auto inf = [](){ return std::numeric_limits<double>::infinity(); };

    //float32x4
    {
        float32x4 sl[] = {
            float32x4::make_const(0.0f, 1.0f, 2.0f, inff()),
            float32x4::make_const(0.0f, 1.0f, 2.0f, inff()),
            float32x4::make_const(-0.0f, -1.0f, -2.0f, -inff()),
            float32x4::make_const(0.0f, 1.0f, -inff(), inff()),
            float32x4::make_const(0.0f, 1.0f, -0.0f, -1.0f),
            float32x4::make_const(nanf(), 0.0, -inff(), inff()),
        };
        float32x4 sr[] = {
            float32x4::make_const(1.0f, 1.0f, 1.0f, 1.0f),
            float32x4::make_const(-1.0f, -1.0f, -1.0f, -1.0f),
            float32x4::make_const(-1.0f, -1.0f, -1.0f, -1.0f),
            float32x4::make_const(inff(), inff(), inff(), inff()),
            float32x4::make_const(nanf(), nanf(), nanf(), nanf()),
            float32x4::make_const(nanf(), nanf(), nanf(), nanf()),
        };

        TEST_COMPARE_TESTER_HELPER(tc, float32x4, sl, sr);
    }

#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    //float64x2
    {
        float64x2 sl[] = {
            float64x2::make_const(0.0, 1.0),
            float64x2::make_const(2.0, inf()),
            float64x2::make_const(0.0, 1.0),
            float64x2::make_const(2.0, inf()),
            float64x2::make_const(-0.0, -1.0),

            float64x2::make_const(-2.0, -inf()),
            float64x2::make_const(0.0, 1.0),
            float64x2::make_const(-inf(), inf()),
            float64x2::make_const(0.0, 1.0),
            float64x2::make_const(-0.0, -1.0),

            float64x2::make_const(nan(), 0.0),
            float64x2::make_const(-inf(), inf()),
        };
        float64x2 sr[] = {
            float64x2::make_const(1.0, 1.0),
            float64x2::make_const(.0, 1.0),
            float64x2::make_const(-1.0, -1.0),
            float64x2::make_const(-1.0, -1.0),
            float64x2::make_const(-1.0, -1.0),

            float64x2::make_const(-1.0, -1.0),
            float64x2::make_const(inf(), inf()),
            float64x2::make_const(inf(), inf()),
            float64x2::make_const(nan(), nan()),
            float64x2::make_const(nan(), nan()),

            float64x2::make_const(nan(), nan()),
            float64x2::make_const(nan(), nan()),
        };

        TEST_COMPARE_TESTER_HELPER(tc64, float64x2, sl, sr);
    }
#else
    (void) inf; (void) nan;
#endif
}

SIMDPP_ARCH_NAMESPACE_END

#endif
