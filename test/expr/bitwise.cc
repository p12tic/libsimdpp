/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/simd.h>
#include "../utils/test_results_set.h"
#include "../utils/test_helpers.h"
#include "../utils/test_reporter.h"
#include "../common/vectors.h"
#include "../common/masks.h"

void test_expr_bitwise(TestReporter& ts)
{
    SIMDPP_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simdpp;

    for (unsigned i = 0; i < 4; ++i) {
        uint8<16> a = v.u8[i*4];
        uint8<16> b = v.u8[i*4+1];
        float32<4> q = v.f32[i*4+2];
        float32<4> p = v.f32[i*4+3];

        // operators
        TEST_EQUAL(ts, bit_and(a, b), a & b);
        TEST_EQUAL(ts, bit_or(a, b), a | b);
        TEST_EQUAL(ts, bit_xor(a, b), a ^ b);
        TEST_EQUAL(ts, bit_andnot(a, b), a & ~b);

        TEST_EQUAL(ts, bit_and(a, bit_or(q, p)), a & (q | p));
        TEST_EQUAL(ts, bit_xor(q, make_uint<uint32x4>(0x12341234)),
                   q ^ 0x12341234);
    }
}
