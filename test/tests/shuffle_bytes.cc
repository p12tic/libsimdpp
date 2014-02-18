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
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

/*
    We don't need exhaustive testing because each byte is generated separately.
*/
template<class V, unsigned i>
struct Test_permute_bytes16_x2 {
    static constexpr unsigned limit = 2;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s>(mask);
        a = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute_bytes16_x4 {
    static constexpr unsigned limit = 4;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s>(mask);
        a = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute_bytes16_x8 {
    static constexpr unsigned limit = 8;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
        a = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute_bytes16_x16 {
    static constexpr unsigned limit = 16;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s>(mask);
        a = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};
template<class V, unsigned i>
struct Test_shuffle_bytes16_x2 {
    static constexpr unsigned limit = 2;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s>(mask);
        a = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle_bytes16_x4 {
    static constexpr unsigned limit = 4;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s>(mask);
        a = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle_bytes16_x8 {
    static constexpr unsigned limit = 8;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
        a = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle_bytes16_x16 {
    static constexpr unsigned limit = 16;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = i;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s>(mask);
        a = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};
template<class V, unsigned i>
struct Test_permute_zbytes16_x2 {
    static constexpr unsigned limit = 3;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s>(mask);
        a = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute_zbytes16_x4 {
    static constexpr unsigned limit = 5;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s>(mask);
        a = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute_zbytes16_x8 {
    static constexpr unsigned limit = 9;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
        a = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_permute_zbytes16_x16 {
    static constexpr unsigned limit = 17;
    static void test(TestCase& tc, V a)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s>(mask);
        a = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, a);
    }
};
template<class V, unsigned i>
struct Test_shuffle_zbytes16_x2 {
    static constexpr unsigned limit = 5;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s>(mask);
        a = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle_zbytes16_x4 {
    static constexpr unsigned limit = 9;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s>(mask);
        a = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle_zbytes16_x8 {
    static constexpr unsigned limit = 17;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
        a = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_shuffle_zbytes16_x16 {
    static constexpr unsigned limit = 33;
    static void test(TestCase& tc, V a, V b)
    {
        constexpr int s = (int) i - 1;

        typename V::int_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s>(mask);
        a = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, a);
    }
};


void test_shuffle_bytes(TestResults& res)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSSE3 || SIMDPP_USE_NEON
    TestCase& tc = NEW_TEST_CASE(res, "shuffle_bytes");

    using namespace simdpp;

    Vectors<32*2> v;

    // Vectors with 8-bit integer elements
    TemplateTestHelper<Test_permute_bytes16_x2, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_permute_bytes16_x8, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_permute_bytes16_x16, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x8, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x16, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x8, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x16, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x8, uint8x32>::run(tc, v.du8[0], v.du8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x16, uint8x32>::run(tc, v.du8[0], v.du8[1]);

    // Vectors with 16-bit integer elements
    TemplateTestHelper<Test_permute_bytes16_x2, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_permute_bytes16_x8, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint16x16>::run(tc, v.du16[0], v.du16[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint16x16>::run(tc, v.du16[0], v.du16[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x8, uint16x16>::run(tc, v.du16[0], v.du16[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_permute_zbytes16_x8, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint16x16>::run(tc, v.du16[0], v.du16[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint16x16>::run(tc, v.du16[0], v.du16[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x8, uint16x16>::run(tc, v.du16[0], v.du16[1]);

    // Vectors with 32-bit integer elements
    TemplateTestHelper<Test_permute_bytes16_x2, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint32x8>::run(tc, v.du32[0], v.du32[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint32x8>::run(tc, v.du32[0], v.du32[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint32x8>::run(tc, v.du32[0], v.du32[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint32x8>::run(tc, v.du32[0], v.du32[1]);

    // Vectors with 32-bit floating-point elements
    TemplateTestHelper<Test_permute_bytes16_x2, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, float32x8>::run(tc, v.df32[0], v.df32[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, float32x8>::run(tc, v.df32[0], v.df32[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, float32x8>::run(tc, v.df32[0], v.df32[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, float32x8>::run(tc, v.df32[0], v.df32[1]);

    // some tests whether the permute mask itself is correctly generated
    {
        uint16x16 mask = make_shuffle_bytes16_mask<-1,-1,-1,-1>(mask);
        uint16x16 r1 = uint16x16::zero();
        uint16x16 r2 = permute_zbytes16(v.du16[0], mask);
        TEST_PUSH(tc, uint16x16, cmp_eq(r1, r2));
    }
    {
        uint16x16 mask = make_shuffle_bytes16_mask<0,1,2,3>(mask);
        uint16x16 r1 = permute4<0,1,2,3>(v.du16[0]);
        uint16x16 r2 = permute_bytes16(v.du16[0], mask);
        TEST_PUSH(tc, uint16x16, cmp_eq(r1, r2));
    }
    {
        uint32x8 mask = make_shuffle_bytes16_mask<0,1,2,3>(mask);
        uint32x8 r1 = permute4<0,1,2,3>(v.du32[0]);
        uint32x8 r2 = permute_zbytes16(v.du32[0], mask);
        TEST_PUSH(tc, uint32x8, cmp_eq(r1, r2));
    }
#else
    (void) res;
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE
