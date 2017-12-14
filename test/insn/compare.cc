/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>
#include <limits>

namespace SIMDPP_ARCH_NAMESPACE {

#define TEST_COMPARE_TESTER_HELPER(TC, T, L, R)                     \
{                                                                   \
    TEST_PUSH_ARRAY_OP2(TC, T, cmp_eq, L, R);                        \
    TEST_PUSH_ARRAY_OP2(TC, T, cmp_lt, L, R);                        \
    TEST_PUSH_ARRAY_OP2(TC, T, cmp_gt, L, R);                        \
    TEST_PUSH_ARRAY_OP2(TC, T, cmp_ge, L, R);                        \
    TEST_PUSH_ARRAY_OP2(TC, T, cmp_le, L, R);                        \
}

template<unsigned B>
void test_compare_n(TestResultsSet& tc)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using int8_n = int8<B>;
    using uint16_n = uint16<B/2>;
    using int16_n = int16<B/2>;
    using uint32_n = uint32<B/4>;
    using int32_n = int32<B/4>;
#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64
    using uint64_n = uint64<B/8>;
    using int64_n = int64<B/8>;
#endif
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    //int8x32
    {
        TestData<uint8_n> sl;
        sl.add(make_uint(0x11, 0x22, 0x33, 0xff));
        sl.add(make_uint(0xcc, 0xdd, 0xee, 0xff));
        sl.add(make_uint(0x01, 0x00, 0xff, 0xfe));

        TestData<uint8_n> sr;
        sr.add(make_uint(0x22, 0x22, 0x22, 0x22));
        sr.add(make_uint(0xee, 0xee, 0xee, 0xee));
        sr.add(make_uint(0x00, 0x00, 0x00, 0x00));

        TEST_COMPARE_TESTER_HELPER(tc, int8_n, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint8_n, sl, sr);
    }

    //int16_n
    {
        TestData<uint16_n> sl;
        sl.add(make_uint(0x1111, 0x2222, 0x3333, 0x3333));
        sl.add(make_uint(0xdddd, 0xeeee, 0xffff, 0xcccc));
        sl.add(make_uint(0x0001, 0x0000, 0xffff, 0xfffe));

        TestData<uint16_n> sr;
        sr.add(make_uint(0x2222, 0x2222, 0x2222, 0x2222));
        sr.add(make_uint(0xeeee, 0xeeee, 0xeeee, 0xeeee));
        sr.add(make_uint(0x0000, 0x0000, 0x0000, 0x0000));

        TEST_COMPARE_TESTER_HELPER(tc, int16_n, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint16_n, sl, sr);
    }

    //int32_n
    {
        TestData<uint32_n> sl;
        sl.add(make_uint(0x11111111, 0x22222222, 0x33333333, 0x33333333));
        sl.add(make_uint(0xdddddddd, 0xeeeeeeee, 0xffffffff, 0xcccccccc));
        sl.add(make_uint(0x00000000, 0x00000001, 0xffffffff, 0xfffffffe));

        TestData<uint32_n> sr;
        sr.add(make_uint(0x22222222, 0x22222222, 0x22222222, 0x22222222));
        sr.add(make_uint(0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee));
        sr.add(make_uint(0x00000000, 0x00000000, 0x00000000, 0x00000000));

        TEST_COMPARE_TESTER_HELPER(tc, int32_n, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint32_n, sl, sr);
    }

#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64
    //int64_n
    {
        TestData<uint64_n> sl;
        sl.add(make_uint(0x1111111111111111, 0x2222222222222222, 0x3333333333333333, 0x3333333333333333));
        sl.add(make_uint(0xdddddddddddddddd, 0xeeeeeeeeeeeeeeee, 0xffffffffffffffff, 0xcccccccccccccccc));
        sl.add(make_uint(0x0000000000000000, 0x0000000000000001, 0xffffffffffffffff, 0xfffffffffffffffe));

        TestData<uint64_n> sr;
        sr.add(make_uint(0x2222222222222222));
        sr.add(make_uint(0xeeeeeeeeeeeeeeee));
        sr.add(make_uint(0x0000000000000000));

        TEST_COMPARE_TESTER_HELPER(tc, int64_n, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint64_n, sl, sr);
    }
#endif

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    //float32_n
    {
        TestData<float32_n> sl;
        sl.add(make_float(0.0f, 1.0f, 2.0f, inff));
        sl.add(make_float(0.0f, 1.0f, 2.0f, inff));
        sl.add(make_float(-0.0f, -1.0f, -2.0f, -inff));
        sl.add(make_float(0.0f, 1.0f, -inff, inff));
        sl.add(make_float(0.0f, 1.0f, -0.0f, -1.0f));
        sl.add(make_float(nanf, 0.0, -inff, inff));

        TestData<float32_n> sr;
        sr.add(make_float(1.0f, 1.0f, 1.0f, 1.0f));
        sr.add(make_float(-1.0f, -1.0f, -1.0f, -1.0f));
        sr.add(make_float(-1.0f, -1.0f, -1.0f, -1.0f));
        sr.add(make_float(inff, inff, inff, inff));
        sr.add(make_float(nanf, nanf, nanf, nanf));
        sr.add(make_float(nanf, nanf, nanf, nanf));

        TEST_COMPARE_TESTER_HELPER(tc, float32_n, sl, sr);
        TEST_PUSH_ARRAY_OP2(tc, float32_n, cmp_neq, sl, sr);
        TEST_PUSH_ARRAY_OP2(tc, float32_n, cmp_le, sl, sr);
        TEST_PUSH_ARRAY_OP2(tc, float32_n, cmp_ge, sl, sr);
    }

    //float64_n
    {
        TestData<float64_n> sl;
        sl.add(make_float(0.0, 1.0));
        sl.add(make_float(2.0, inf));
        sl.add(make_float(0.0, 1.0));
        sl.add(make_float(2.0, inf));
        sl.add(make_float(-0.0, -1.0));

        sl.add(make_float(-2.0, -inf));
        sl.add(make_float(0.0, 1.0));
        sl.add(make_float(-inf, inf));
        sl.add(make_float(0.0, 1.0));
        sl.add(make_float(-0.0, -1.0));

        sl.add(make_float(nan, 0.0));
        sl.add(make_float(-inf, inf));

        TestData<float64_n> sr;
        sr.add(make_float(1.0, 1.0));
        sr.add(make_float(.0, 1.0));
        sr.add(make_float(-1.0, -1.0));
        sr.add(make_float(-1.0, -1.0));
        sr.add(make_float(-1.0, -1.0));

        sr.add(make_float(-1.0, -1.0));
        sr.add(make_float(inf, inf));
        sr.add(make_float(inf, inf));
        sr.add(make_float(nan, nan));
        sr.add(make_float(nan, nan));

        sr.add(make_float(nan, nan));
        sr.add(make_float(nan, nan));

        TEST_COMPARE_TESTER_HELPER(tc, float64_n, sl, sr);
        TEST_PUSH_ARRAY_OP2(tc, float64_n, cmp_neq, sl, sr);
        TEST_PUSH_ARRAY_OP2(tc, float64_n, cmp_le, sl, sr);
        TEST_PUSH_ARRAY_OP2(tc, float64_n, cmp_ge, sl, sr);
    }
}

void test_compare(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("compare");
    test_compare_n<16>(tc);
    test_compare_n<32>(tc);
    test_compare_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
