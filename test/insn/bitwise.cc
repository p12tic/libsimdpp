/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include "../common/masks.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, class V32I>
void test_bitwise_type(TestResultsSet& tc, TestReporter& tr)
{
    using namespace simdpp;

    TestData<V32I> s;
    s.add(make_uint(0xffff0000, 0x00000000, 0xff000000, 0x00000000));
    s.add(make_uint(0x00ffff00, 0x00000000, 0x0000ff00, 0x00000000));
    s.add(make_uint(0x0000ffff, 0x00000000, 0x000000ff, 0x00000000));
    s.add(make_uint(0x0000ffff, 0xffffffff, 0x00ffffff, 0xffffffff));
    s.add(make_uint(0xff0000ff, 0xffffffff, 0xffff00ff, 0xffffffff));
    s.add(make_uint(0xffff0000, 0xffffffff, 0xffffff00, 0xffffffff));
    s.add(make_uint(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));
    s.add(make_uint(0x00000000, 0x00000000, 0x00000000, 0x00000000));

    TEST_PUSH_ALL_COMB_OP2(tc, V, bit_and, s);
    TEST_PUSH_ALL_COMB_OP2(tc, V, bit_andnot, s);
    TEST_PUSH_ALL_COMB_OP2(tc, V, bit_or, s);
    TEST_PUSH_ALL_COMB_OP2(tc, V, bit_xor, s);
    TEST_PUSH_ALL_COMB_OP1(tc, V, bit_not, s);

    TestData<V> sl;
    sl.add(make_uint(0));
    sl.add(make_uint(0, 0, 0, 1));
    sl.add(make_uint(0, 0, 1, 0));
    sl.add(make_uint(0, 1, 0, 0));
    sl.add(make_uint(1, 0, 0, 0));
    sl.add(make_uint(1, 1, 1, 1));

    TEST_PUSH_ARRAY_OP1_T(tc, bool, V, test_bits_any, sl);

    TEST_EQUAL_ALL_COMB_OP2_EXPLICIT(tr, V,
                                     test_bits_any(bit_and(ARG1, ARG2).eval()),
                                     test_bits_any(bit_and(ARG1, ARG2)), sl);

    TEST_EQUAL_ALL_COMB_OP2_EXPLICIT(tr, V,
                                     test_bits_any(bit_andnot(ARG1, ARG2).eval()),
                                     test_bits_any(bit_andnot(ARG1, ARG2)), sl);
}

template<class V, class V32I>
void test_popcnt_type(TestResultsSet& tc)
{
    using namespace simdpp;

    TestData<V32I> s;
    s.add(make_uint(0xffff0000, 0x00000000, 0xff000000, 0x00000000));
    s.add(make_uint(0x00ffff00, 0x00000000, 0x0000ff00, 0x00000000));
    s.add(make_uint(0x0000ffff, 0x00000000, 0x000000ff, 0x00000000));
    s.add(make_uint(0x0000ffff, 0xffffffff, 0x00ffffff, 0xffffffff));
    s.add(make_uint(0xff0000ff, 0xffffffff, 0xffff00ff, 0xffffffff));
    s.add(make_uint(0xffff0000, 0xffffffff, 0xffffff00, 0xffffffff));
    s.add(make_uint(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));
    s.add(make_uint(0x00000000, 0x00000000, 0x00000000, 0x00000000));

    TEST_PUSH_ARRAY_OP1(tc, V, popcnt, s);
    TEST_PUSH_ARRAY_OP1_T(tc, unsigned, V, reduce_popcnt, s);
}

template<unsigned B>
void test_bitwise_n(TestResultsSet& tc, TestReporter& tr)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    test_bitwise_type<uint8_n, uint32_n>(tc, tr);
    test_bitwise_type<uint16_n, uint32_n>(tc, tr);
    test_bitwise_type<uint32_n, uint32_n>(tc, tr);
    test_bitwise_type<uint64_n, uint32_n>(tc, tr);
    test_bitwise_type<float32_n, uint32_n>(tc, tr);
    test_bitwise_type<float64_n, uint32_n>(tc, tr);

    test_popcnt_type<uint8_n, uint32_n>(tc);
    test_popcnt_type<uint16_n, uint32_n>(tc);
    test_popcnt_type<uint32_n, uint32_n>(tc);
    test_popcnt_type<uint64_n, uint32_n>(tc);

    // masks
    Vectors<B,4> v;
    Masks<B,4> m;

    tc.reset_seq();
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

void test_bitwise(TestResults& res, TestReporter& tr)
{
    TestResultsSet& tc = res.new_results_set("bitwise");
    test_bitwise_n<16>(tc, tr);
    test_bitwise_n<32>(tc, tr);
    test_bitwise_n<64>(tc, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
