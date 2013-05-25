/*  libsimdpp
    Copyright (C) 2011-2012  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_MATH_FP_H
#define LIBSIMDPP_TEST_TESTS_MATH_FP_H

namespace SIMDPP_ARCH_NAMESPACE {

void test_math_fp(TestResults& res)
{
    // TODO sqrt_e sqrt_rh rcp_e rcp_rh

    TestCase& tc = NEW_TEST_CASE(res, "math_fp");

#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    TestCase& tc64 = NEW_TEST_CASE(res, "math_fp_f64");
#endif

    using namespace simdpp;

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    //float32x4
    {
        float32x4 s[] = {
            float32x4::make_const(0.0f, -0.0f, 0.0f, -0.0f),
            float32x4::make_const(1.0f, 2.0f, 3.0f, 4.0f),
            float32x4::make_const(-1.0f, -2.0f, -3.0f, -4.0f),
            float32x4::make_const(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            float32x4::make_const(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            float32x4::make_const(nanf, nanf, nanf, nanf),
            float32x4::make_const(inff, inff, inff, inff),
            float32x4::make_const(-inff, -inff, -inff, -inff),
        };

        TEST_ALL_COMB_HELPER(tc, float32x4, add, s, 4);
        TEST_ALL_COMB_HELPER(tc, float32x4, sub, s, 4);
        TEST_ALL_COMB_HELPER(tc, float32x4, mul, s, 4);
        tc.set_precision(1);
        TEST_ALL_COMB_HELPER(tc, float32x4, div, s, 4);
        tc.unset_precision();

        TEST_ARRAY_HELPER1(tc, float32x4, abs, s);
        TEST_ARRAY_HELPER1(tc, float32x4, sign, s);
        TEST_ARRAY_HELPER1(tc, float32x4, neg, s);

        float32x4 snan[] = {
            float32x4::make_const(1.0f, 2.0f, 3.0f, 4.0f),
            float32x4::make_const(-1.0f, -2.0f, -3.0f, -4.0f),
            float32x4::make_const(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            float32x4::make_const(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            float32x4::make_const(inff, inff, inff, inff),
            float32x4::make_const(-inff, -inff, -inff, -inff),
        };
        TEST_ALL_COMB_HELPER(tc, float32x4, min, snan, 4);
        TEST_ALL_COMB_HELPER(tc, float32x4, max, snan, 4);
    }

#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    //float64x2
    {
        float64x2 s[] = {
            float64x2::make_const(0.0, -0.0),
            float64x2::make_const(1.0, 2.0),
            float64x2::make_const(3.0, 4.0),
            float64x2::make_const(-1.0, -2.0),
            float64x2::make_const(-3.0, -4.0),
            float64x2::make_const(63100000000000000.0, 63100000000000004.0),
            float64x2::make_const(63100000000000008.0, 63100000000000012.0),
            float64x2::make_const(-63100000000000000.0, -63100000000000004.0),
            float64x2::make_const(-63100000000000008.0, -63100000000000012.0),
            float64x2::make_const(nan, nan),
            float64x2::make_const(inf, inf),
            float64x2::make_const(-inf, -inf),
        };

        TEST_ALL_COMB_HELPER(tc64, float64x2, add, s, 4);
        TEST_ALL_COMB_HELPER(tc64, float64x2, sub, s, 4);
        TEST_ALL_COMB_HELPER(tc64, float64x2, mul, s, 4);
        TEST_ALL_COMB_HELPER(tc64, float64x2, div, s, 4);

        TEST_ARRAY_HELPER1(tc64, float64x2, abs, s);
        TEST_ARRAY_HELPER1(tc64, float64x2, sign, s);
        TEST_ARRAY_HELPER1(tc64, float64x2, neg, s);

        float64x2 snan[] = {
            float64x2::make_const(1.0, 2.0),
            float64x2::make_const(3.0, 4.0),
            float64x2::make_const(-1.0, -2.0),
            float64x2::make_const(-3.0, -4.0),
            float64x2::make_const(63100000000000000.0, 63100000000000004.0),
            float64x2::make_const(63100000000000008.0, 63100000000000012.0),
            float64x2::make_const(-63100000000000000.0, -63100000000000004.0),
            float64x2::make_const(-63100000000000008.0, -63100000000000012.0),
            float64x2::make_const(inf, inf),
            float64x2::make_const(-inf, -inf),
        };
        TEST_ALL_COMB_HELPER(tc64, float64x2, min, snan, 4);
        TEST_ALL_COMB_HELPER(tc64, float64x2, max, snan, 4);
    }
#else
    (void) nan; (void) inf;
#endif
}

SIMDPP_ARCH_NAMESPACE_END

#endif
