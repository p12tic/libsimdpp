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

template<unsigned B>
void test_bitwise_n(TestCase& tc)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    uint64_n a11 = make_uint(0x0f0ff0f0ffff0000, 0x0f0ff0f0ffff0000);
    uint64_n a12 = make_uint(0xffffffffffffffff, 0x0000000000000000);

    float64_n b11, b12;
    b11 = a11;  b12 = a12;

    float32_n c11, c12;
    c11 = a11;  c12 = a12;

    TEST_PUSH(tc, uint64_n,  bit_and(a11, a12));
    TEST_PUSH(tc, float64_n, bit_and(b11, b12));
    TEST_PUSH(tc, float32_n, bit_and(c11, c12));

    TEST_PUSH(tc, uint64_n,  bit_andnot(a11, a12));
    TEST_PUSH(tc, float64_n, bit_andnot(b11, b12));
    TEST_PUSH(tc, float32_n, bit_andnot(c11, c12));

    TEST_PUSH(tc, uint64_n,  bit_or(a11, a12));
    TEST_PUSH(tc, float64_n, bit_or(b11, b12));
    TEST_PUSH(tc, float32_n, bit_or(c11, c12));

    TEST_PUSH(tc, uint64_n,  bit_xor(a11, a12));
    TEST_PUSH(tc, float64_n, bit_xor(b11, b12));
    TEST_PUSH(tc, float32_n, bit_xor(c11, c12));

    TEST_PUSH(tc, uint64_n,  bit_not(a11));
    tc.reset_seq();

    // masks
    Vectors<B,4> v;
    Masks<B,4> m;

    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++) {

            TEST_PUSH(tc, uint8_n,   bit_and(v.u8[i], m.u8[j]));
            TEST_PUSH(tc, uint16_n,  bit_and(v.u16[i], m.u16[j]));
            TEST_PUSH(tc, uint32_n,  bit_and(v.u32[i], m.u32[j]));
            TEST_PUSH(tc, uint64_n,  bit_and(v.u64[i], m.u64[j]));
            TEST_PUSH(tc, float32_n, bit_and(v.f32[i], m.f32[j]));
            TEST_PUSH(tc, float64_n, bit_and(v.f64[i], m.f64[j]));

            TEST_PUSH(tc, uint8_n,   bit_andnot(v.u8[i], m.u8[j]));
            TEST_PUSH(tc, uint16_n,  bit_andnot(v.u16[i], m.u16[j]));
            TEST_PUSH(tc, uint32_n,  bit_andnot(v.u32[i], m.u32[j]));
            TEST_PUSH(tc, uint64_n,  bit_andnot(v.u64[i], m.u64[j]));
            TEST_PUSH(tc, float32_n, bit_andnot(v.f32[i], m.f32[j]));
            TEST_PUSH(tc, float64_n, bit_andnot(v.f64[i], m.f64[j]));

            // masks
            TEST_PUSH(tc, uint8_n,   bit_and(m.u8[i], m.u8[j]));
            TEST_PUSH(tc, uint16_n,  bit_and(m.u16[i], m.u16[j]));
            TEST_PUSH(tc, uint32_n,  bit_and(m.u32[i], m.u32[j]));
            TEST_PUSH(tc, uint64_n,  bit_and(m.u64[i], m.u64[j]));
            TEST_PUSH(tc, float32_n, bit_and(m.f32[i], m.f32[j]));
            TEST_PUSH(tc, float64_n, bit_and(m.f64[i], m.f64[j]));

            TEST_PUSH(tc, uint8_n,   bit_andnot(m.u8[i], m.u8[j]));
            TEST_PUSH(tc, uint16_n,  bit_andnot(m.u16[i], m.u16[j]));
            TEST_PUSH(tc, uint32_n,  bit_andnot(m.u32[i], m.u32[j]));
            TEST_PUSH(tc, uint64_n,  bit_andnot(m.u64[i], m.u64[j]));
            TEST_PUSH(tc, float32_n, bit_andnot(m.f32[i], m.f32[j]));
            TEST_PUSH(tc, float64_n, bit_andnot(m.f64[i], m.f64[j]));

            TEST_PUSH(tc, uint8_n,   bit_or(m.u8[i], m.u8[j]));
            TEST_PUSH(tc, uint16_n,  bit_or(m.u16[i], m.u16[j]));
            TEST_PUSH(tc, uint32_n,  bit_or(m.u32[i], m.u32[j]));
            TEST_PUSH(tc, uint64_n,  bit_or(m.u64[i], m.u64[j]));
            TEST_PUSH(tc, float32_n, bit_or(m.f32[i], m.f32[j]));
            TEST_PUSH(tc, float64_n, bit_or(m.f64[i], m.f64[j]));

            TEST_PUSH(tc, uint8_n,   bit_xor(m.u8[i], m.u8[j]));
            TEST_PUSH(tc, uint16_n,  bit_xor(m.u16[i], m.u16[j]));
            TEST_PUSH(tc, uint32_n,  bit_xor(m.u32[i], m.u32[j]));
            TEST_PUSH(tc, uint64_n,  bit_xor(m.u64[i], m.u64[j]));
            TEST_PUSH(tc, float32_n, bit_xor(m.f32[i], m.f32[j]));
            TEST_PUSH(tc, float64_n, bit_xor(m.f64[i], m.f64[j]));

        }
        TEST_PUSH(tc, uint8_n,  bit_not(m.u8[i]));
        TEST_PUSH(tc, uint16_n, bit_not(m.u16[i]));
        TEST_PUSH(tc, uint32_n, bit_not(m.u32[i]));
        TEST_PUSH(tc, uint64_n, bit_not(m.u64[i]));
        TEST_PUSH(tc, float32_n, bit_not(m.f32[i]));
        TEST_PUSH(tc, float64_n, bit_not(m.f64[i]));
    }
}

void test_bitwise(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "bitwise");
    test_bitwise_n<16>(tc);
    test_bitwise_n<32>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
