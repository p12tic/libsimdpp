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
void test_math_float32_n(TestResultsSet& tc, const TestOptions& opts)
{
    (void) opts;

    // TODO sqrt_e sqrt_rh rcp_e rcp_rh
    using namespace simdpp;
    using float32_n = float32<B/4>;

    float nanf = std::numeric_limits<float>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();

    TestData<float32_n> s;
    s.add(make_float(0.0f, -0.0f, 0.0f, -0.0f));
    s.add(make_float(1.0f, 2.0f, 3.0f, 4.0f));
    s.add(make_float(-1.0f, -2.0f, -3.0f, -4.0f));
    s.add(make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f));
    s.add(make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f));
    s.add(make_float(nanf, nanf, nanf, nanf));
    s.add(make_float(inff, inff, inff, inff));
    s.add(make_float(-inff, -inff, -inff, -inff));

    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, sub, s);

#if __PPC__
    // on PPC Altivec the following operations return non-standard results:
    //  - +0.0 * -0.0 -> +0.0 (correct -0.0)
    //  - 1.0 / 0.0 -> nan (correct inf)
    //  - 1.0 / inf -> nan (correct 0.0)
    TestData<float32_n> s2;
    s2.add(make_float(1.0f, 2.0f, 3.0f, 4.0f));
    s2.add(make_float(-1.0f, -2.0f, -3.0f, -4.0f));
    s2.add(make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f));
    s2.add(make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f));

    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, mul, s2);

    tc.set_precision(1);
    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, div, s2);
    tc.unset_precision();
#else
    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, mul, s);
    tc.set_precision(1);
    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, div, s);
    tc.unset_precision();
#endif

    TEST_PUSH_ARRAY_OP1(tc, float32_n, abs, s);
    TEST_PUSH_ARRAY_OP1(tc, float32_n, sign, s);
    TEST_PUSH_ARRAY_OP1(tc, float32_n, neg, s);

    tc.set_fp_zero_equal();
    TEST_PUSH_ARRAY_OP1(tc, float32_n, trunc, s);
    TEST_PUSH_ARRAY_OP1(tc, float32_n, floor, s);
    TEST_PUSH_ARRAY_OP1(tc, float32_n, ceil, s);
    tc.unset_fp_zero_equal();

#if (SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4 || SIMDPP_USE_NULL) && !SIMDPP_USE_AVX512F
    tc.set_fp_zero_equal();
    TEST_PUSH_ALL_COMB_OP3(tc, float32_n, fmadd, s);
    TEST_PUSH_ALL_COMB_OP3(tc, float32_n, fmsub, s);
    tc.unset_fp_zero_equal();
#endif

    TestData<float32_n> snan;
    snan.add(make_float(1.0f, 2.0f, 3.0f, 4.0f));
    snan.add(make_float(-1.0f, -2.0f, -3.0f, -4.0f));
    snan.add(make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f));
    snan.add(make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f));
    snan.add(make_float(inff, inff, inff, inff));
    snan.add(make_float(-inff, -inff, -inff, -inff));

    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, min, snan);
    TEST_PUSH_ALL_COMB_OP2(tc, float32_n, max, snan);

    // Depending on the reduction order precision errors may occur.
    tc.set_precision(2);
    TEST_PUSH_ALL_COMB_OP1_T(tc, float, float32_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, float, float32_n, reduce_mul, s);
    tc.unset_precision();

    TEST_PUSH_ALL_COMB_OP1_T(tc, float, float32_n, reduce_min, snan);
    TEST_PUSH_ALL_COMB_OP1_T(tc, float, float32_n, reduce_max, snan);
}

template<unsigned B>
void test_math_float64_n(TestResultsSet& tc, const TestOptions& opts)
{
    (void) opts;

    using namespace simdpp;
    using float64_n = float64<B/8>;

    double nan = std::numeric_limits<double>::quiet_NaN();
    double inf = std::numeric_limits<double>::infinity();

    TestData<float64_n> s;
    s.add(make_float(0.0, -0.0));
    s.add(make_float(1.0, 2.0));
    s.add(make_float(3.0, 4.0));
    s.add(make_float(-1.0, -2.0));
    s.add(make_float(-3.0, -4.0));
    s.add(make_float(63100000000000000.0, 63100000000000004.0));
    s.add(make_float(63100000000000008.0, 63100000000000012.0));
    s.add(make_float(-63100000000000000.0, -63100000000000004.0));
    s.add(make_float(-63100000000000008.0, -63100000000000012.0));
    s.add(make_float(nan, nan));
    s.add(make_float(inf, inf));
    s.add(make_float(-inf, -inf));

    TEST_PUSH_ALL_COMB_OP2(tc, float64_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, float64_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, float64_n, mul, s);
    TEST_PUSH_ALL_COMB_OP2(tc, float64_n, div, s);

    TEST_PUSH_ARRAY_OP1(tc, float64_n, abs, s);
    TEST_PUSH_ARRAY_OP1(tc, float64_n, sign, s);
    TEST_PUSH_ARRAY_OP1(tc, float64_n, neg, s);

    tc.set_fp_zero_equal();
    TEST_PUSH_ARRAY_OP1(tc, float64_n, trunc, s);
    TEST_PUSH_ARRAY_OP1(tc, float64_n, floor, s);
    TEST_PUSH_ARRAY_OP1(tc, float64_n, ceil, s);
    tc.unset_fp_zero_equal();

    TestData<float64_n> snan;
    snan.add(make_float(1.0, 2.0));
    snan.add(make_float(3.0, 4.0));
    snan.add(make_float(-1.0, -2.0));
    snan.add(make_float(-3.0, -4.0));
    snan.add(make_float(63100000000000000.0, 63100000000000004.0));
    snan.add(make_float(63100000000000008.0, 63100000000000012.0));
    snan.add(make_float(-63100000000000000.0, -63100000000000004.0));
    snan.add(make_float(-63100000000000008.0, -63100000000000012.0));
    snan.add(make_float(inf, inf));
    snan.add(make_float(-inf, -inf));

    TEST_PUSH_ALL_COMB_OP2(tc, float64_n, min, snan);
    TEST_PUSH_ALL_COMB_OP2(tc, float64_n, max, snan);

#if (SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4 || SIMDPP_USE_NULL) && !SIMDPP_USE_AVX512F
    tc.set_fp_zero_equal();
    // Certain simulators can't handle NaNs and infinity in this instruction
    if (opts.is_simulator) {

        TestData<float64_n> snan;
        snan.add(make_float(1.0, 2.0));
        snan.add(make_float(3.0, 4.0));
        snan.add(make_float(-1.0, -2.0));
        snan.add(make_float(-3.0, -4.0));
        snan.add(make_float(63100000000000000.0, 63100000000000004.0));
        snan.add(make_float(63100000000000008.0, 63100000000000012.0));
        snan.add(make_float(-63100000000000000.0, -63100000000000004.0));
        snan.add(make_float(-63100000000000008.0, -63100000000000012.0));

        TEST_PUSH_ALL_COMB_OP3(tc, float64_n, fmadd, snan);
        TEST_PUSH_ALL_COMB_OP3(tc, float64_n, fmsub, snan);
    } else {
#if defined(_MSC_VER) && _MSC_VER < 1900
        // looks like MSVC 2013 has a bug in fma() implementation
        tc.set_precision(1);
#endif
        TEST_PUSH_ALL_COMB_OP3(tc, float64_n, fmadd, s);
        TEST_PUSH_ALL_COMB_OP3(tc, float64_n, fmsub, s);
#if defined(_MSC_VER) && _MSC_VER < 1900
        tc.unset_precision();
#endif
    }
    tc.unset_fp_zero_equal();
#endif

    // Depending on the reduction order precision errors may occur.
    tc.set_precision(2);
    TEST_PUSH_ALL_COMB_OP1_T(tc, double, float64_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, double, float64_n, reduce_mul, s);
    tc.unset_precision();
    TEST_PUSH_ALL_COMB_OP1_T(tc, double, float64_n, reduce_min, snan);
    TEST_PUSH_ALL_COMB_OP1_T(tc, double, float64_n, reduce_max, snan);
}

void test_math_fp(TestResults& res, const TestOptions& opts)
{
    TestResultsSet& ts = res.new_results_set("math_fp");
    test_math_float32_n<16>(ts, opts);
    test_math_float64_n<16>(ts, opts);
    test_math_float32_n<32>(ts, opts);
    test_math_float64_n<32>(ts, opts);
    test_math_float32_n<64>(ts, opts);
    test_math_float64_n<64>(ts, opts);
}

} // namespace SIMDPP_ARCH_NAMESPACE
