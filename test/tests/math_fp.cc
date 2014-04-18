/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {


template<unsigned B>
void test_math_fp_n(TestSuite& tc, TestSuite& ts_fma)
{
    // TODO sqrt_e sqrt_rh rcp_e rcp_rh
    (void) ts_fma;

    using namespace simdpp;

    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    // Vectors with 32-bit floating-point elements
    {
        float32_n s[] = {
            (float32_n) make_float(0.0f, -0.0f, 0.0f, -0.0f),
            (float32_n) make_float(1.0f, 2.0f, 3.0f, 4.0f),
            (float32_n) make_float(-1.0f, -2.0f, -3.0f, -4.0f),
            (float32_n) make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            (float32_n) make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            (float32_n) make_float(nanf, nanf, nanf, nanf),
            (float32_n) make_float(inff, inff, inff, inff),
            (float32_n) make_float(-inff, -inff, -inff, -inff),
        };

        TEST_ALL_COMB_HELPER2(tc, float32_n, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, float32_n, sub, s, 4);
        TEST_ALL_COMB_HELPER2(tc, float32_n, mul, s, 4);
        tc.set_precision(1);
        TEST_ALL_COMB_HELPER2(tc, float32_n, div, s, 4);
        tc.unset_precision();

        TEST_ARRAY_HELPER1(tc, float32_n, abs, s);
        TEST_ARRAY_HELPER1(tc, float32_n, sign, s);
        TEST_ARRAY_HELPER1(tc, float32_n, neg, s);

#if SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4 || SIMDPP_USE_NULL
        TEST_ALL_COMB_HELPER3(ts_fma, float32_n, fmadd, s, 4);
        TEST_ALL_COMB_HELPER3(ts_fma, float32_n, fmsub, s, 4);
#endif
        float32_n snan[] = {
            (float32_n) make_float(1.0f, 2.0f, 3.0f, 4.0f),
            (float32_n) make_float(-1.0f, -2.0f, -3.0f, -4.0f),
            (float32_n) make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            (float32_n) make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            (float32_n) make_float(inff, inff, inff, inff),
            (float32_n) make_float(-inff, -inff, -inff, -inff),
        };
        TEST_ALL_COMB_HELPER2(tc, float32_n, min, snan, 4);
        TEST_ALL_COMB_HELPER2(tc, float32_n, max, snan, 4);


    }

    // Vectors with 64-bit floating-point elements
    {
        float64_n s[] = {
            (float64_n) make_float(0.0, -0.0),
            (float64_n) make_float(1.0, 2.0),
            (float64_n) make_float(3.0, 4.0),
            (float64_n) make_float(-1.0, -2.0),
            (float64_n) make_float(-3.0, -4.0),
            (float64_n) make_float(63100000000000000.0, 63100000000000004.0),
            (float64_n) make_float(63100000000000008.0, 63100000000000012.0),
            (float64_n) make_float(-63100000000000000.0, -63100000000000004.0),
            (float64_n) make_float(-63100000000000008.0, -63100000000000012.0),
            (float64_n) make_float(nan, nan),
            (float64_n) make_float(inf, inf),
            (float64_n) make_float(-inf, -inf),
        };

        TEST_ALL_COMB_HELPER2(tc, float64_n, add, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, sub, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, mul, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, div, s, 8);

        TEST_ARRAY_HELPER1(tc, float64_n, abs, s);
        TEST_ARRAY_HELPER1(tc, float64_n, sign, s);
        TEST_ARRAY_HELPER1(tc, float64_n, neg, s);

#if SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4 || SIMDPP_USE_NULL
        TEST_ALL_COMB_HELPER3(ts_fma, float64_n, fmadd, s, 8);
        TEST_ALL_COMB_HELPER3(ts_fma, float64_n, fmsub, s, 8);
#endif

        float64_n snan[] = {
            (float64_n) make_float(1.0, 2.0),
            (float64_n) make_float(3.0, 4.0),
            (float64_n) make_float(-1.0, -2.0),
            (float64_n) make_float(-3.0, -4.0),
            (float64_n) make_float(63100000000000000.0, 63100000000000004.0),
            (float64_n) make_float(63100000000000008.0, 63100000000000012.0),
            (float64_n) make_float(-63100000000000000.0, -63100000000000004.0),
            (float64_n) make_float(-63100000000000008.0, -63100000000000012.0),
            (float64_n) make_float(inf, inf),
            (float64_n) make_float(-inf, -inf),
        };
        TEST_ALL_COMB_HELPER2(tc, float64_n, min, snan, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, max, snan, 8);
    }
}

void test_math_fp(TestResults& res)
{
    TestSuite& ts = NEW_TEST_SUITE(res, "math_fp");
    TestSuite& ts_fma = NEW_TEST_SUITE(res, "math_fp.fma");
    test_math_fp_n<16>(ts, ts_fma);
    test_math_fp_n<32>(ts, ts_fma);
    test_math_fp_n<64>(ts, ts_fma);
}

} // namespace SIMDPP_ARCH_NAMESPACE
