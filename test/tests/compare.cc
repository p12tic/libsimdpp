/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>
#include <limits>

namespace SIMDPP_ARCH_NAMESPACE {

#define TEST_COMPARE_TESTER_HELPER(TC, T, L, R)                     \
{                                                                   \
    TEST_ARRAY_HELPER2(TC, T, cmp_eq, L, R);                        \
    TEST_ARRAY_HELPER2(TC, T, cmp_lt, L, R);                        \
    TEST_ARRAY_HELPER2(TC, T, cmp_gt, L, R);                        \
}

template<unsigned B>
void test_compare_n(TestSuite& tc)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using int8_n = int8<B>;
    using uint16_n = uint16<B/2>;
    using int16_n = int16<B/2>;
    using uint32_n = uint32<B/4>;
    using int32_n = int32<B/4>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    //int8x32
    {
    uint8_n sl[] = {
        (uint8_n) make_uint(0x11, 0x22, 0x33, 0xff),
        (uint8_n) make_uint(0xcc, 0xdd, 0xee, 0xff),
        (uint8_n) make_uint(0x01, 0x00, 0xff, 0xfe),
    };
    uint8_n sr[] = {
        (uint8_n) make_uint(0x22, 0x22, 0x22, 0x22),
        (uint8_n) make_uint(0xee, 0xee, 0xee, 0xee),
        (uint8_n) make_uint(0x00, 0x00, 0x00, 0x00),
    };

    TEST_COMPARE_TESTER_HELPER(tc, int8_n, sl, sr);
    TEST_COMPARE_TESTER_HELPER(tc, uint8_n, sl, sr);
    }

    //int16_n
    {
        uint16_n sl[] = {
            (uint16_n) make_uint(0x1111, 0x2222, 0x3333, 0x3333),
            (uint16_n) make_uint(0xdddd, 0xeeee, 0xffff, 0xcccc),
            (uint16_n) make_uint(0x0001, 0x0000, 0xffff, 0xfffe),
        };
        uint16_n sr[] = {
            (uint16_n) make_uint(0x2222, 0x2222, 0x2222, 0x2222),
            (uint16_n) make_uint(0xeeee, 0xeeee, 0xeeee, 0xeeee),
            (uint16_n) make_uint(0x0000, 0x0000, 0x0000, 0x0000),
        };

        TEST_COMPARE_TESTER_HELPER(tc, int16_n, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint16_n, sl, sr);
    }

    //int32_n
    {
        uint32_n sl[] = {
            (uint32_n) make_uint(0x11111111, 0x22222222, 0x33333333, 0x33333333),
            (uint32_n) make_uint(0xdddddddd, 0xeeeeeeee, 0xffffffff, 0xcccccccc),
            (uint32_n) make_uint(0x00000000, 0x00000001, 0xffffffff, 0xfffffffe),
        };
        uint32_n sr[] = {
            (uint32_n) make_uint(0x22222222, 0x22222222, 0x22222222, 0x22222222),
            (uint32_n) make_uint(0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee),
            (uint32_n) make_uint(0x00000000, 0x00000000, 0x00000000, 0x00000000),
        };

        TEST_COMPARE_TESTER_HELPER(tc, int32_n, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint32_n, sl, sr);
    }

    //int64_n not available

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    //float32_n
    {
        float32_n sl[] = {
            (float32_n) make_float(0.0f, 1.0f, 2.0f, inff),
            (float32_n) make_float(0.0f, 1.0f, 2.0f, inff),
            (float32_n) make_float(-0.0f, -1.0f, -2.0f, -inff),
            (float32_n) make_float(0.0f, 1.0f, -inff, inff),
            (float32_n) make_float(0.0f, 1.0f, -0.0f, -1.0f),
            (float32_n) make_float(nanf, 0.0, -inff, inff),
        };
        float32_n sr[] = {
            (float32_n) make_float(1.0f, 1.0f, 1.0f, 1.0f),
            (float32_n) make_float(-1.0f, -1.0f, -1.0f, -1.0f),
            (float32_n) make_float(-1.0f, -1.0f, -1.0f, -1.0f),
            (float32_n) make_float(inff, inff, inff, inff),
            (float32_n) make_float(nanf, nanf, nanf, nanf),
            (float32_n) make_float(nanf, nanf, nanf, nanf),
        };

        TEST_COMPARE_TESTER_HELPER(tc, float32_n, sl, sr);
        TEST_ARRAY_HELPER2(tc, float32_n, cmp_neq, sl, sr);
        TEST_ARRAY_HELPER2(tc, float32_n, cmp_le, sl, sr);
        TEST_ARRAY_HELPER2(tc, float32_n, cmp_ge, sl, sr);
    }

    //float64_n
    {
        float64_n sl[] = {
            (float64_n) make_float(0.0, 1.0),
            (float64_n) make_float(2.0, inf),
            (float64_n) make_float(0.0, 1.0),
            (float64_n) make_float(2.0, inf),
            (float64_n) make_float(-0.0, -1.0),

            (float64_n) make_float(-2.0, -inf),
            (float64_n) make_float(0.0, 1.0),
            (float64_n) make_float(-inf, inf),
            (float64_n) make_float(0.0, 1.0),
            (float64_n) make_float(-0.0, -1.0),

            (float64_n) make_float(nan, 0.0),
            (float64_n) make_float(-inf, inf),
        };
        float64_n sr[] = {
            (float64_n) make_float(1.0, 1.0),
            (float64_n) make_float(.0, 1.0),
            (float64_n) make_float(-1.0, -1.0),
            (float64_n) make_float(-1.0, -1.0),
            (float64_n) make_float(-1.0, -1.0),

            (float64_n) make_float(-1.0, -1.0),
            (float64_n) make_float(inf, inf),
            (float64_n) make_float(inf, inf),
            (float64_n) make_float(nan, nan),
            (float64_n) make_float(nan, nan),

            (float64_n) make_float(nan, nan),
            (float64_n) make_float(nan, nan),
        };

        TEST_COMPARE_TESTER_HELPER(tc, float64_n, sl, sr);
        TEST_ARRAY_HELPER2(tc, float64_n, cmp_neq, sl, sr);
        TEST_ARRAY_HELPER2(tc, float64_n, cmp_le, sl, sr);
        TEST_ARRAY_HELPER2(tc, float64_n, cmp_ge, sl, sr);
    }
}

void test_compare(TestResults& res)
{
    TestSuite& tc = NEW_TEST_SUITE(res, "compare");
    test_compare_n<16>(tc);
    test_compare_n<32>(tc);
    test_compare_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
