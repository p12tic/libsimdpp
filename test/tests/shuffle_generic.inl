/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_SHUFFLE_GENERIC_H
#define LIBSIMDPP_TEST_TESTS_SHUFFLE_GENERIC_H

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned i>
struct Test_permute2 {
    static constexpr unsigned limit = 4;
    static void test(TestCase& tc, V a)
    {
        constexpr unsigned s0 = i / 2 % 2;
        constexpr unsigned s1 = i % 2;

        a = simdpp::permute<s0,s1>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute4 {
    static constexpr unsigned limit = 256;
    static void test(TestCase& tc, V a)
    {
        constexpr unsigned s0 = i / 64 % 4;
        constexpr unsigned s1 = i / 16 % 4;
        constexpr unsigned s2 = i / 4 % 4;
        constexpr unsigned s3 = i % 4;

        a = simdpp::permute<s0,s1,s2,s3>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle21 {
    static constexpr unsigned limit = 4;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr unsigned s0 = i / 2 % 2;
        constexpr unsigned s1 = i % 2;

        a = simdpp::shuffle1<s0,s1>(a, b);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle42 {
    static constexpr unsigned limit = 256;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr unsigned s0 = i / 64 % 4;
        constexpr unsigned s1 = i / 16 % 4;
        constexpr unsigned s2 = i / 4 % 4;
        constexpr unsigned s3 = i % 4;

        a = simdpp::shuffle2<s0,s1,s2,s3>(a, b);
        TEST_PUSH(tc, V, a);
    }
};

void test_shuffle_generic(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "shuffle_generic");

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

    // There are no permute instructions for int8x16

    // int16x8
    TemplateTestHelper<Test_permute2, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_permute4, uint16x8>::run(tc, u16[0]);

    // int32x4
    TemplateTestHelper<Test_permute2, uint32x4>::run(tc, u32[0]);
    TemplateTestHelper<Test_permute4, uint32x4>::run(tc, u32[0]);
    TemplateTestHelper<Test_shuffle42, uint32x4>::run(tc, u32[0], u32[1]);

    // int64x2
    TemplateTestHelper<Test_permute2, uint64x2>::run(tc, u64[0]);
    TemplateTestHelper<Test_shuffle21, uint64x2>::run(tc, u64[0], u64[1]);

    // float32x4
    TemplateTestHelper<Test_permute2, float32x4>::run(tc, f32[0]);
    TemplateTestHelper<Test_permute4, float32x4>::run(tc, f32[0]);
    TemplateTestHelper<Test_shuffle42, float32x4>::run(tc, f32[0], f32[1]);

    // float64x2
    TemplateTestHelper<Test_permute2, float64x2>::run(tc, f64[0]);
    TemplateTestHelper<Test_shuffle21, float64x2>::run(tc, f64[0], f64[1]);

    // int16x16
    TemplateTestHelper<Test_permute2, uint16x16>::run(tc, du16[0]);
    TemplateTestHelper<Test_permute4, uint16x16>::run(tc, du16[0]);

    // int32x8
    TemplateTestHelper<Test_permute2, uint32x8>::run(tc, du32[0]);
    TemplateTestHelper<Test_permute4, uint32x8>::run(tc, du32[0]);
    TemplateTestHelper<Test_shuffle42, uint32x8>::run(tc, du32[0], du32[1]);

    // int64x4
    TemplateTestHelper<Test_permute2, uint64x4>::run(tc, du64[0]);
    TemplateTestHelper<Test_shuffle21, uint64x4>::run(tc, du64[0], du64[1]);

    // float32x8
    TemplateTestHelper<Test_permute2, float32x8>::run(tc, df32[0]);
    TemplateTestHelper<Test_permute4, float32x8>::run(tc, df32[0]);
    TemplateTestHelper<Test_shuffle42, float32x8>::run(tc, df32[0], df32[1]);

    // float64x4
    TemplateTestHelper<Test_permute2, float64x4>::run(tc, df64[0]);
    TemplateTestHelper<Test_shuffle21, float64x4>::run(tc, df64[0], df64[1]);
}

SIMDPP_ARCH_NAMESPACE_END

#endif
