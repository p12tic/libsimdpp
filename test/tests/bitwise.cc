/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include "../common/vectors.h"
#include "../common/masks.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

void test_bitwise(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "bitwise");

    using namespace simdpp;

    uint64x4 a11 = make_uint(0x0f0ff0f0ffff0000, 0x0f0ff0f0ffff0000);
    uint64x4 a12 = make_uint(0xffffffffffffffff, 0x0000000000000000);

    float64x4 b11(a11);
    float64x4 b12(a12);

    float32x8 c11 = bit_cast<float32x8>(a11);
    float32x8 c12 = bit_cast<float32x8>(a12);

    TEST_PUSH(tc, uint64x4,  bit_and(a11, a12));
    TEST_PUSH(tc, float64x4, bit_and(b11, b12));
    TEST_PUSH(tc, float32x8, bit_and(c11, c12));

    TEST_PUSH(tc, uint64x4,  bit_andnot(a11, a12));
    TEST_PUSH(tc, float64x4, bit_andnot(b11, b12));
    TEST_PUSH(tc, float32x8, bit_andnot(c11, c12));

    TEST_PUSH(tc, uint64x4,  bit_or(a11, a12));
    TEST_PUSH(tc, float64x4, bit_or(b11, b12));
    TEST_PUSH(tc, float32x8, bit_or(c11, c12));

    TEST_PUSH(tc, uint64x4,  bit_xor(a11, a12));
    TEST_PUSH(tc, float64x4, bit_xor(b11, b12));
    TEST_PUSH(tc, float32x8, bit_xor(c11, c12));

    TEST_PUSH(tc, uint64x4,  bit_not(a11));
    tc.reset_seq();

    // masks
    Vectors<32*4> v;
    Masks<32*4> m;

    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {

            TEST_PUSH(tc, uint8x32,  bit_and(v.du8[i], m.du8[j]));
            TEST_PUSH(tc, uint16x16, bit_and(v.du16[i], m.du16[j]));
            TEST_PUSH(tc, uint32x8,  bit_and(v.du32[i], m.du32[j]));
            TEST_PUSH(tc, uint64x4,  bit_and(v.du64[i], m.du64[j]));
            TEST_PUSH(tc, float32x8, bit_and(v.df32[i], m.df32[j]));
            TEST_PUSH(tc, float64x4, bit_and(v.df64[i], m.df64[j]));

            TEST_PUSH(tc, uint8x32,  bit_andnot(v.du8[i], m.du8[j]));
            TEST_PUSH(tc, uint16x16, bit_andnot(v.du16[i], m.du16[j]));
            TEST_PUSH(tc, uint32x8,  bit_andnot(v.du32[i], m.du32[j]));
            TEST_PUSH(tc, uint64x4,  bit_andnot(v.du64[i], m.du64[j]));
            TEST_PUSH(tc, float32x8, bit_andnot(v.df32[i], m.df32[j]));
            TEST_PUSH(tc, float64x4, bit_andnot(v.df64[i], m.df64[j]));

            // masks
            TEST_PUSH(tc, uint8x32,  bit_and(m.du8[i], m.du8[j]));
            TEST_PUSH(tc, uint16x16, bit_and(m.du16[i], m.du16[j]));
            TEST_PUSH(tc, uint32x8,  bit_and(m.du32[i], m.du32[j]));
            TEST_PUSH(tc, uint64x4,  bit_and(m.du64[i], m.du64[j]));
            TEST_PUSH(tc, float32x8, bit_and(m.df32[i], m.df32[j]));
            TEST_PUSH(tc, float64x4, bit_and(m.df64[i], m.df64[j]));

            TEST_PUSH(tc, uint8x32,  bit_andnot(m.du8[i], m.du8[j]));
            TEST_PUSH(tc, uint16x16, bit_andnot(m.du16[i], m.du16[j]));
            TEST_PUSH(tc, uint32x8,  bit_andnot(m.du32[i], m.du32[j]));
            TEST_PUSH(tc, uint64x4,  bit_andnot(m.du64[i], m.du64[j]));
            TEST_PUSH(tc, float32x8, bit_andnot(m.df32[i], m.df32[j]));
            TEST_PUSH(tc, float64x4, bit_andnot(m.df64[i], m.df64[j]));

            TEST_PUSH(tc, uint8x32,  bit_or(m.du8[i], m.du8[j]));
            TEST_PUSH(tc, uint16x16, bit_or(m.du16[i], m.du16[j]));
            TEST_PUSH(tc, uint32x8,  bit_or(m.du32[i], m.du32[j]));
            TEST_PUSH(tc, uint64x4,  bit_or(m.du64[i], m.du64[j]));
            TEST_PUSH(tc, float32x8, bit_or(m.df32[i], m.df32[j]));
            TEST_PUSH(tc, float64x4, bit_or(m.df64[i], m.df64[j]));

            TEST_PUSH(tc, uint8x32,  bit_xor(m.du8[i], m.du8[j]));
            TEST_PUSH(tc, uint16x16, bit_xor(m.du16[i], m.du16[j]));
            TEST_PUSH(tc, uint32x8,  bit_xor(m.du32[i], m.du32[j]));
            TEST_PUSH(tc, uint64x4,  bit_xor(m.du64[i], m.du64[j]));
            TEST_PUSH(tc, float32x8, bit_xor(m.df32[i], m.df32[j]));
            TEST_PUSH(tc, float64x4, bit_xor(m.df64[i], m.df64[j]));

        }
        TEST_PUSH(tc, uint8x32, bit_not(m.du8[i]));
        TEST_PUSH(tc, uint16x16, bit_not(m.du16[i]));
        TEST_PUSH(tc, uint32x8, bit_not(m.du32[i]));
        TEST_PUSH(tc, uint64x4, bit_not(m.du64[i]));
        TEST_PUSH(tc, float32x8, bit_not(m.df32[i]));
        TEST_PUSH(tc, float64x4, bit_not(m.df64[i]));
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
