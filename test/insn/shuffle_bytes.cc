/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

/*
    We don't need exhaustive testing because each byte is generated separately.
*/
template<class V, unsigned i>
struct Test_permute_bytes16_x2 {
    static const unsigned limit = 2;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s>(mask);
        V r = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute_bytes16_x4 {
    static const unsigned limit = 4;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s>(mask);
        V r = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute_bytes16_x8 {
    static const unsigned limit = 8;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
        V r = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute_bytes16_x16 {
    static const unsigned limit = 16;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s>(mask);
        V r = simdpp::permute_bytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};
template<class V, unsigned i>
struct Test_shuffle_bytes16_x2 {
    static const unsigned limit = 4;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s>(mask);
        V r = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle_bytes16_x4 {
    static const unsigned limit = 8;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s>(mask);
        V r = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle_bytes16_x8 {
    static const unsigned limit = 16;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s>(mask);
        V r = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle_bytes16_x16 {
    static const unsigned limit = 32;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = i;

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s>(mask);
        V r = simdpp::shuffle_bytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

#if SIMDPP_X86 && (defined(__clang__) && (__clang_major__ == 3) && (__clang_minor__ <= 7) && (__clang_minor__ >= 6))
// BUG: Clang 3.7 and 3.6 incorrectly optimize certain cases of constant mask
// when the values are available for the compiler to collapse. The bug happens
// on x86-only. Since creating a mask which effectively results in a nop is
// extremely unlikely we just disable the tests.
#define BUGGY_ZBYTES_CONTSTANT_PROPAGATION 1
#else
#define BUGGY_ZBYTES_CONTSTANT_PROPAGATION 0
#endif

template<class V, unsigned i>
struct Test_permute_zbytes16_x2 {
    static const unsigned limit = 3;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s1>(mask);
        V r = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute_zbytes16_x4 {
    static const unsigned limit = 5;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s1>(mask);
        V r = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute_zbytes16_x8 {
    static const unsigned limit = 9;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s1>(mask);
        V r = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_permute_zbytes16_x16 {
    static const unsigned limit = 17;
    static void test(TestResultsSet& tc, const V& a)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s1>(mask);
        V r = simdpp::permute_zbytes16(a, mask);
        TEST_PUSH(tc, V, r);
    }
};
template<class V, unsigned i>
struct Test_shuffle_zbytes16_x2 {
    static const unsigned limit = 5;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s1>(mask);
        V r = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle_zbytes16_x4 {
    static const unsigned limit = 9;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s1>(mask);
        V r = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle_zbytes16_x8 {
    static const unsigned limit = 17;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s1>(mask);
        V r = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle_zbytes16_x16 {
    static const unsigned limit = 33;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const int s = (int) i - 1;
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        const int s1 = s == -1 ? 0 : s;
#else
        const int s1 = s;
#endif

        typename V::uint_vector_type mask;
        mask = simdpp::make_shuffle_bytes16_mask<s,s,s,s,s,s,s,s,
                                                 s,s,s,s,s,s,s,s1>(mask);
        V r = simdpp::shuffle_zbytes16(a, b, mask);
        TEST_PUSH(tc, V, r);
    }
};


void test_shuffle_bytes(TestResults& res, TestReporter& tr)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSSE3 || SIMDPP_USE_NEON
    TestResultsSet& tc = res.new_results_set("shuffle_bytes");

    using namespace simdpp;

    Vectors<32,2> v;

    // Vectors with 8-bit integer elements
    TemplateTestHelper<Test_permute_bytes16_x2, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_permute_bytes16_x8, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_permute_bytes16_x16, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x8, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x16, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x8, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x16, uint8x32>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x8, uint8x32>::run(tc, v.u8[0], v.u8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x16, uint8x32>::run(tc, v.u8[0], v.u8[1]);

    // Vectors with 16-bit integer elements
    TemplateTestHelper<Test_permute_bytes16_x2, uint16x16>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint16x16>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_permute_bytes16_x8, uint16x16>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint16x16>::run(tc, v.u16[0], v.u16[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint16x16>::run(tc, v.u16[0], v.u16[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x8, uint16x16>::run(tc, v.u16[0], v.u16[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint16x16>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint16x16>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_permute_zbytes16_x8, uint16x16>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint16x16>::run(tc, v.u16[0], v.u16[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint16x16>::run(tc, v.u16[0], v.u16[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x8, uint16x16>::run(tc, v.u16[0], v.u16[1]);

    // Vectors with 32-bit integer elements
    TemplateTestHelper<Test_permute_bytes16_x2, uint32x8>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint32x8>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint32x8>::run(tc, v.u32[0], v.u32[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint32x8>::run(tc, v.u32[0], v.u32[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint32x8>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint32x8>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint32x8>::run(tc, v.u32[0], v.u32[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint32x8>::run(tc, v.u32[0], v.u32[1]);

    // Vectors with 32-bit floating-point elements
    TemplateTestHelper<Test_permute_bytes16_x2, float32x8>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, float32x8>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, float32x8>::run(tc, v.f32[0], v.f32[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, float32x8>::run(tc, v.f32[0], v.f32[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, float32x8>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, float32x8>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, float32x8>::run(tc, v.f32[0], v.f32[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, float32x8>::run(tc, v.f32[0], v.f32[1]);

    // some tests whether the permute mask itself is correctly generated
    {
#if BUGGY_ZBYTES_CONTSTANT_PROPAGATION
        uint16x16 mask = make_shuffle_bytes16_mask<0,-1,-1,-1>(mask);
        uint16x16 r1 = make_uint(0x0100, 0, 0, 0, 0x0908, 0, 0, 0,
                                 0x1110, 0, 0, 0, 0x1918, 0, 0, 0);
#else
        uint16x16 mask = make_shuffle_bytes16_mask<-1,-1,-1,-1>(mask);
        uint16x16 r1 = make_zero();
#endif
        uint16x16 r2 = permute_zbytes16(v.u16[0], mask);
        TEST_EQUAL(tr, r1, r2);
    }
    {
        uint16x16 mask = make_shuffle_bytes16_mask<0,1,2,3>(mask);
        uint16x16 r1 = permute4<0,1,2,3>(v.u16[0]);
        uint16x16 r2 = permute_bytes16(v.u16[0], mask);
        TEST_EQUAL(tr, r1, r2);
    }
    {
        uint32x8 mask = make_shuffle_bytes16_mask<0,1,2,3>(mask);
        uint32x8 r1 = permute4<0,1,2,3>(v.u32[0]);
        uint32x8 r2 = permute_zbytes16(v.u32[0], mask);
        TEST_EQUAL(tr, r1, r2);
    }
#else
    (void) res;
    (void) tr;
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE
