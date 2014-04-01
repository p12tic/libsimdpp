/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned i>
struct Test_permute2 {
    static constexpr unsigned limit = 4;
    static void test(TestCase& tc, V a)
    {
        constexpr unsigned s0 = i / 2 % 2;
        constexpr unsigned s1 = i % 2;

        a = simdpp::permute2<s0,s1>(a);
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

        a = simdpp::permute4<s0,s1,s2,s3>(a);
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

    Vectors<16*4> v;

    // There are no permute instructions for int8x16

    // int16x8
    TemplateTestHelper<Test_permute2, uint16x8>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_permute4, uint16x8>::run(tc, v.u16[0]);

    // int32x4
    TemplateTestHelper<Test_permute2, uint32x4>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_permute4, uint32x4>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_shuffle42, uint32x4>::run(tc, v.u32[0], v.u32[1]);

    // int64x2
    TemplateTestHelper<Test_permute2, uint64x2>::run(tc, v.u64[0]);
    TemplateTestHelper<Test_shuffle21, uint64x2>::run(tc, v.u64[0], v.u64[1]);

    // float32x4
    TemplateTestHelper<Test_permute2, float32x4>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_permute4, float32x4>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_shuffle42, float32x4>::run(tc, v.f32[0], v.f32[1]);

    // float64x2
    TemplateTestHelper<Test_permute2, float64x2>::run(tc, v.f64[0]);
    TemplateTestHelper<Test_shuffle21, float64x2>::run(tc, v.f64[0], v.f64[1]);

    // int16x16
    TemplateTestHelper<Test_permute2, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_permute4, uint16x16>::run(tc, v.du16[0]);

    // int32x8
    TemplateTestHelper<Test_permute2, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_permute4, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_shuffle42, uint32x8>::run(tc, v.du32[0], v.du32[1]);

    // int64x4
    TemplateTestHelper<Test_permute2, uint64x4>::run(tc, v.du64[0]);
    TemplateTestHelper<Test_shuffle21, uint64x4>::run(tc, v.du64[0], v.du64[1]);

    // float32x8
    TemplateTestHelper<Test_permute2, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_permute4, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_shuffle42, float32x8>::run(tc, v.df32[0], v.df32[1]);

    // float64x4
    TemplateTestHelper<Test_permute2, float64x4>::run(tc, v.df64[0]);
    TemplateTestHelper<Test_shuffle21, float64x4>::run(tc, v.df64[0], v.df64[1]);
}

} // namespace SIMDPP_ARCH_NAMESPACE
