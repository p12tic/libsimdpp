/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

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
void test_expr_math_int_v(TestReporter& ts)
{
    SIMDPP_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simdpp;

    for (unsigned i = 0; i < 4; ++i) {
        V a = load(v.pu8+(i*4+0)*B);
        V b = load(v.pu8+(i*4+1)*B);
        V c = load(v.pu8+(i*4+2)*B);

        // operators
        TEST_CMP_VEC(ts, add(a, b), a + b);
        TEST_CMP_VEC(ts, add(a, mul_lo(b, c)), a + b * c);
        TEST_CMP_VEC(ts, add(a, sub(b, c)), a + (b - c));
        //TEST_CMP_VEC(ts, add(a, neg(b)), a + neg(b));
        TEST_CMP_VEC(ts, mul_lo(a, b), a * b);
        TEST_CMP_VEC(ts, mul_lo(a, mul_lo(b, c)), a * b * c);
        TEST_CMP_VEC(ts, mul_lo(a, sub(b, c)), a * (b - c));
        //TEST_CMP_VEC(ts, mul_lo(a, neg(b)), a * neg(b));
        TEST_CMP_VEC(ts, mul_lo(a, sub(b, bit_not(c))), a * (b - ~c));
        TEST_CMP_VEC(ts, shift_l(a, 4), a << 4);
        TEST_CMP_VEC(ts, shift_r(a, 4), a >> 4);
        TEST_CMP_VEC(ts, shift_l<4>(a), a << 4);
        TEST_CMP_VEC(ts, shift_r<4>(a), a >> 4);

        // expressions
        TEST_CMP_VEC(ts, add(a, add(b, c)), add(a, add(b, c).eval()));
        TEST_CMP_VEC(ts, add(add(b, c), a), add(add(b, c).eval(), a));
        TEST_CMP_VEC(ts, sub(a, sub(b, c)), sub(a, sub(b, c).eval()));
        TEST_CMP_VEC(ts, sub(sub(b, c), a), sub(sub(b, c).eval(), a));
        //TEST_CMP_VEC(ts, add_sat(a, add_sat(b, c)), add_sat(a, add_sat(b, c).eval()));
        //TEST_CMP_VEC(ts, add_sat(add_sat(b, c), a), add_sat(add_sat(b, c).eval(), a));
        //TEST_CMP_VEC(ts, sub_sat(a, sub_sat(b, c)), sub_sat(a, sub_sat(b, c).eval()));
        //TEST_CMP_VEC(ts, sub_sat(sub_sat(b, c), a), sub_sat(sub_sat(b, c).eval(), a));
        TEST_CMP_VEC(ts, mul_lo(a, mul_lo(b, c)), mul_lo(a, mul_lo(b, c).eval()));
        TEST_CMP_VEC(ts, mul_lo(mul_lo(b, c), a), mul_lo(mul_lo(b, c).eval(), a));
        //TEST_CMP_VEC(ts, abs(add(a, b)), abs(add(a, b).eval()));
        //TEST_CMP_VEC(ts, neg(add(a, b)), neg(add(a, b).eval()));

        // scalar arguments
        TEST_CMP_VEC(ts, add(a, make_float<V>(1234.1234f)), a + 1234.1234f);
        TEST_CMP_VEC(ts, add(make_float<V>(1234.1234f), a), 1234.1234f + a);
        TEST_CMP_VEC(ts, add(a, make_int<V>(1234)), a + 1234);
        TEST_CMP_VEC(ts, add(make_int<V>(1234), a), 1234 + a);
        // TEST_CMP_VEC(ts, add(a, make_int<V>(1234ll)), a + 1234ll);
        // TEST_CMP_VEC(ts, add(make_int<V>(1234ll), a), 1234ll + a);
        TEST_CMP_VEC(ts, add(a, make_int<V>(0x80000000)), a + 0x80000000);
        TEST_CMP_VEC(ts, add(make_int<V>(0x80000000), a), 0x80000000 + a);
        TEST_CMP_VEC(ts, add(a, make_uint<V>(0x80000000)), a + 0x80000000);
        TEST_CMP_VEC(ts, add(make_uint<V>(0x80000000), a), 0x80000000 + a);
        TEST_CMP_VEC(ts, add(a, make_int<V>(0xf12341234)), a + 0xf12341234);
        TEST_CMP_VEC(ts, add(make_int<V>(0xf12341234), a), 0xf12341234 + a);
        // TEST_CMP_VEC(ts, add(a, make_int<V>(0xf12341234ull)), a + 0xf12341234ull);
        // TEST_CMP_VEC(ts, add(make_int<V>(0xf12341234ull), a), 0xf12341234ull + a);
    }
}


void test_expr_math_int(TestReporter& ts)
{
    using namespace simdpp;

    test_expr_math_int_v<int16<8>, 16>(ts);
    test_expr_math_int_v<uint16<8>, 16>(ts);
    test_expr_math_int_v<uint32<4>, 16>(ts);
}
