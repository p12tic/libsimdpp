/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {


template<unsigned B>
void test_math_fp_n(TestResultsSet& tc, const TestOptions& opts)
{
    (void) opts;

    // TODO sqrt_e sqrt_rh rcp_e rcp_rh
    using namespace simdpp;

    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    // Vectors with 32-bit floating-point elements
    {
        TestData<float32_n> s(
            make_float(0.0f, -0.0f, 0.0f, -0.0f),
            make_float(1.0f, 2.0f, 3.0f, 4.0f),
            make_float(-1.0f, -2.0f, -3.0f, -4.0f),
            make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            make_float(nanf, nanf, nanf, nanf),
            make_float(inff, inff, inff, inff),
            make_float(-inff, -inff, -inff, -inff)
        );

        TEST_ALL_COMB_HELPER2(tc, float32_n, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, float32_n, sub, s, 4);

#if __PPC__
        if (opts.is_simulator) {
            // QEMU does not multiply or divide special values well
            TestData<float32_n> s2(
                make_float(1.0f, 2.0f, 3.0f, 4.0f),
                make_float(-1.0f, -2.0f, -3.0f, -4.0f),
                make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
                make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f)
            );
            TEST_ALL_COMB_HELPER2(tc, float32_n, mul, s2, 4);
            tc.set_precision(1);
            TEST_ALL_COMB_HELPER2(tc, float32_n, div, s2, 4);
            tc.unset_precision();
        } else {
            TEST_ALL_COMB_HELPER2(tc, float32_n, mul, s, 4);
            tc.set_precision(1);
            TEST_ALL_COMB_HELPER2(tc, float32_n, div, s, 4);
            tc.unset_precision();
        }
#else
        TEST_ALL_COMB_HELPER2(tc, float32_n, mul, s, 4);
        tc.set_precision(1);
        TEST_ALL_COMB_HELPER2(tc, float32_n, div, s, 4);
        tc.unset_precision();
#endif

        TEST_ARRAY_HELPER1(tc, float32_n, abs, s);
        TEST_ARRAY_HELPER1(tc, float32_n, sign, s);
        TEST_ARRAY_HELPER1(tc, float32_n, neg, s);

        tc.set_fp_zero_equal();
        TEST_ARRAY_HELPER1(tc, float32_n, trunc, s);
        TEST_ARRAY_HELPER1(tc, float32_n, floor, s);
        TEST_ARRAY_HELPER1(tc, float32_n, ceil, s);
        tc.unset_fp_zero_equal();

        tc.sync_archs();
#if (SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4 || SIMDPP_USE_NULL) && !SIMDPP_USE_AVX512F
        TEST_ALL_COMB_HELPER3(tc, float32_n, fmadd, s, 4);
        TEST_ALL_COMB_HELPER3(tc, float32_n, fmsub, s, 4);
#endif
        tc.sync_archs();

        TestData<float32_n> snan(
            make_float(1.0f, 2.0f, 3.0f, 4.0f),
            make_float(-1.0f, -2.0f, -3.0f, -4.0f),
            make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            make_float(inff, inff, inff, inff),
            make_float(-inff, -inff, -inff, -inff)
        );
        TEST_ALL_COMB_HELPER2(tc, float32_n, min, snan, 4);
        TEST_ALL_COMB_HELPER2(tc, float32_n, max, snan, 4);

        // Depending on the reduction order precision errors may occur.
        tc.set_precision(2);
        TEST_ALL_COMB_HELPER1_T(tc, float, float32_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, float, float32_n, reduce_mul, s, 1);
        tc.unset_precision();

        TEST_ALL_COMB_HELPER1_T(tc, float, float32_n, reduce_min, snan, 1);
        TEST_ALL_COMB_HELPER1_T(tc, float, float32_n, reduce_max, snan, 1);
    }

    // Vectors with 64-bit floating-point elements
    {
        TestData<float64_n> s(
            make_float(0.0, -0.0),
            make_float(1.0, 2.0),
            make_float(3.0, 4.0),
            make_float(-1.0, -2.0),
            make_float(-3.0, -4.0),
            make_float(63100000000000000.0, 63100000000000004.0),
            make_float(63100000000000008.0, 63100000000000012.0),
            make_float(-63100000000000000.0, -63100000000000004.0),
            make_float(-63100000000000008.0, -63100000000000012.0),
            make_float(nan, nan),
            make_float(inf, inf),
            make_float(-inf, -inf)
        );

        TEST_ALL_COMB_HELPER2(tc, float64_n, add, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, sub, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, mul, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, div, s, 8);

        TEST_ARRAY_HELPER1(tc, float64_n, abs, s);
        TEST_ARRAY_HELPER1(tc, float64_n, sign, s);
        TEST_ARRAY_HELPER1(tc, float64_n, neg, s);

        tc.set_fp_zero_equal();
        TEST_ARRAY_HELPER1(tc, float64_n, trunc, s);
        TEST_ARRAY_HELPER1(tc, float64_n, floor, s);
        TEST_ARRAY_HELPER1(tc, float64_n, ceil, s);
        tc.unset_fp_zero_equal();

        TestData<float64_n> snan(
            make_float(1.0, 2.0),
            make_float(3.0, 4.0),
            make_float(-1.0, -2.0),
            make_float(-3.0, -4.0),
            make_float(63100000000000000.0, 63100000000000004.0),
            make_float(63100000000000008.0, 63100000000000012.0),
            make_float(-63100000000000000.0, -63100000000000004.0),
            make_float(-63100000000000008.0, -63100000000000012.0),
            make_float(inf, inf),
            make_float(-inf, -inf)
        );
        TEST_ALL_COMB_HELPER2(tc, float64_n, min, snan, 8);
        TEST_ALL_COMB_HELPER2(tc, float64_n, max, snan, 8);

        tc.sync_archs();
#if (SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4 || SIMDPP_USE_NULL) && !SIMDPP_USE_AVX512F
        // Certain simulators can't handle NaNs and infinity in this instruction
        if (opts.is_simulator) {

            TestData<float64_n> snan(
                make_float(1.0, 2.0),
                make_float(3.0, 4.0),
                make_float(-1.0, -2.0),
                make_float(-3.0, -4.0),
                make_float(63100000000000000.0, 63100000000000004.0),
                make_float(63100000000000008.0, 63100000000000012.0),
                make_float(-63100000000000000.0, -63100000000000004.0),
                make_float(-63100000000000008.0, -63100000000000012.0)
            );

            TEST_ALL_COMB_HELPER3(tc, float64_n, fmadd, snan, 8);
            TEST_ALL_COMB_HELPER3(tc, float64_n, fmsub, snan, 8);
        } else {
            TEST_ALL_COMB_HELPER3(tc, float64_n, fmadd, s, 8);
            TEST_ALL_COMB_HELPER3(tc, float64_n, fmsub, s, 8);
        }
#endif
        tc.sync_archs();

        // Depending on the reduction order precision errors may occur.
        tc.set_precision(2);
        TEST_ALL_COMB_HELPER1_T(tc, double, float64_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, double, float64_n, reduce_mul, s, 1);
        tc.unset_precision();
        TEST_ALL_COMB_HELPER1_T(tc, double, float64_n, reduce_min, snan, 1);
        TEST_ALL_COMB_HELPER1_T(tc, double, float64_n, reduce_max, snan, 1);
    }
}

void test_math_fp(TestResults& res, const TestOptions& opts)
{
    TestResultsSet& ts = res.new_results_set("math_fp");
    test_math_fp_n<16>(ts, opts);
    test_math_fp_n<32>(ts, opts);
    test_math_fp_n<64>(ts, opts);
}

} // namespace SIMDPP_ARCH_NAMESPACE
