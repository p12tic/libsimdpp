/*  libsimdpp
    Copyright (C) 2011-2012  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_SHUFFLE_H
#define LIBSIMDPP_TEST_TESTS_SHUFFLE_H

namespace SIMDPP_ARCH_NAMESPACE {

// shuffles within 256-bit vectors are limited to 128-bit halves
template<class V>
struct Shuffle_width {
    static constexpr bool is_256 = (traits<V>::length * traits<V>::num_bits) == 256 ? true : false;
    static constexpr unsigned value = is_256 ? traits<V>::length / 2 : traits<V>::length;
};

template<class V, unsigned i>
struct Test_move_r {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::move_r<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_move_l {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::move_l<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_broadcast {
    static constexpr unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::broadcast<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_align {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a, V b)
    {
        a = simdpp::align<i>(a, b);
        TEST_PUSH(tc, V, a);
    }
};

template<class V>
void test_shuffle_one_type(TestCase &tc, V v1, V v2)
{
    TEST_PUSH(tc, V, zip_lo(v1, v2));
    TEST_PUSH(tc, V, zip_hi(v1, v2));
    TEST_PUSH(tc, V, unzip_lo(v1, v2));
    TEST_PUSH(tc, V, unzip_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_broadcast, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
}

void test_shuffle(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "shuffle");

    using namespace simdpp;

    union {
        uint8_t c[64];
        uint8x16 u8[4];
        uint16x8 u16[4];
        uint32x4 u32[4];
        uint64x2 u64[4];
        float32x4 f32[4];
        float64x2 f64[4];

        uint8x32 du8[4];
        uint16x16 du16[4];
        uint32x8 du32[4];
        uint64x4 du64[4];
        float32x8 df32[4];
        float64x4 df64[4];
    };

    for (unsigned i = 0; i < 64; i++) {
        c[i] = i;
    }

    // TODO blend

    // int8x16
    test_shuffle_one_type<uint8x16>(tc, u8[0], u8[1]);
    test_shuffle_one_type<uint16x8>(tc, u16[0], u16[1]);
    test_shuffle_one_type<uint32x4>(tc, u32[0], u32[1]);
    test_shuffle_one_type<uint64x2>(tc, u64[0], u64[1]);
    test_shuffle_one_type<float32x4>(tc, f32[0], f32[1]);
    test_shuffle_one_type<float64x2>(tc, f64[0], f64[1]);

    test_shuffle_one_type<uint8x32>(tc, du8[0], du8[1]);
    test_shuffle_one_type<uint16x16>(tc, du16[0], du16[1]);
    test_shuffle_one_type<uint32x8>(tc, du32[0], du32[1]);
    test_shuffle_one_type<uint64x4>(tc, du64[0], du64[1]);
    test_shuffle_one_type<float32x8>(tc, df32[0], df32[1]);
    test_shuffle_one_type<float64x4>(tc, df64[0], df64[1]);
}

SIMDPP_ARCH_NAMESPACE_END

#endif
