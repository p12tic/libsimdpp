/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned i>
struct Test_permute2 {
    static const unsigned limit = 4;
    static void test(TestCase& tc, V a)
    {
        const unsigned s0 = i / 2 % 2;
        const unsigned s1 = i % 2;

        a = simdpp::permute<s0,s1>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute4 {
    static const unsigned limit = 256;
    static void test(TestCase& tc, V a)
    {
        const unsigned s0 = i / 64 % 4;
        const unsigned s1 = i / 16 % 4;
        const unsigned s2 = i / 4 % 4;
        const unsigned s3 = i % 4;

        a = simdpp::permute<s0,s1,s2,s3>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle21 {
    static const unsigned limit = 4;
    static void test(TestCase& tc, V a, V b)
    {
        const unsigned s0 = i / 2 % 2;
        const unsigned s1 = i % 2;

        a = simdpp::shuffle1<s0,s1>(a, b);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle42 {
    static const unsigned limit = 256;
    static void test(TestCase& tc, V a, V b)
    {
        const unsigned s0 = i / 64 % 4;
        const unsigned s1 = i / 16 % 4;
        const unsigned s2 = i / 4 % 4;
        const unsigned s3 = i % 4;

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

} // namespace SIMDPP_ARCH_NAMESPACE
