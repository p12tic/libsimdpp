/*  Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/simd.h>
#include "../utils/test_results_set.h"
#include "../utils/test_helpers.h"
#include "../common/vectors.h"
#include "../common/masks.h"


template<class V, unsigned B>
void test_expr_compare_v(TestReporter& ts)
{
    SIMDPP_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simdpp;

    for (unsigned i = 0; i < 4; ++i) {
        V a = load(v.pu8+(i*4+0)*B);
        V b = load(v.pu8+(i*4+1)*B);

        // operators
        TEST_EQUAL(ts, cmp_eq(a, b), a == b);
        TEST_EQUAL(ts, cmp_lt(a, b), a < b);
        TEST_EQUAL(ts, cmp_le(a, b), a <= b);
        TEST_EQUAL(ts, cmp_gt(a, b), a > b);
        TEST_EQUAL(ts, cmp_ge(a, b), a >= b);

        // scalar arguments not implemented yet
        TEST_EQUAL(ts, cmp_eq(a, make_int<V>(2)), a == 2);
        TEST_EQUAL(ts, cmp_lt(a, make_int<V>(2)), a < 2);
        TEST_EQUAL(ts, cmp_le(a, make_int<V>(2)), a <= 2);
        TEST_EQUAL(ts, cmp_gt(a, make_int<V>(2)), a > 2);
        TEST_EQUAL(ts, cmp_ge(a, make_int<V>(2)), a >= 2);

        TEST_EQUAL(ts, cmp_eq(a, make_float<V>(2.2)), a == 2.2);
        TEST_EQUAL(ts, cmp_lt(a, make_float<V>(2.2)), a < 2.2);
        TEST_EQUAL(ts, cmp_le(a, make_float<V>(2.2)), a <= 2.2);
        TEST_EQUAL(ts, cmp_gt(a, make_float<V>(2.2)), a > 2.2);
        TEST_EQUAL(ts, cmp_ge(a, make_float<V>(2.2)), a >= 2.2);
    }
}

template<unsigned B>
void test_expr_compare_n(TestReporter& tr)
{
    using namespace simdpp;

    test_expr_compare_v<uint8<B>, B>(tr);
    test_expr_compare_v<int8<B>, B>(tr);

    test_expr_compare_v<uint16<B/2>, B>(tr);
    test_expr_compare_v<int16<B/2>, B>(tr);

    test_expr_compare_v<uint32<B/4>, B>(tr);
    test_expr_compare_v<int32<B/4>, B>(tr);

#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64
    test_expr_compare_v<uint64<B/8>, B>(tr);
    test_expr_compare_v<int64<B/8>, B>(tr);
#endif

    test_expr_compare_v<float32<B/4>, B>(tr);
    test_expr_compare_v<float64<B/8>, B>(tr);
}

void test_expr_compare(TestReporter& tr)
{
    test_expr_compare_n<16>(tr);
    test_expr_compare_n<32>(tr);
    test_expr_compare_n<64>(tr);
}
