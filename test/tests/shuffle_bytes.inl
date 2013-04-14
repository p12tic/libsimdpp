/*  libsimdpp
    Copyright (C) 2011-2012  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_SHUFFLE_BYTES_H
#define LIBSIMDPP_TEST_TESTS_SHUFFLE_BYTES_H

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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

        typename traits<V>::int_vector_type mask;
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

    union {
        uint8_t c[32];
        uint8x16 u8[2];
        uint16x8 u16[2];
        uint32x4 u32[2];
        uint64x2 u64[2];
        float32x4 f32[2];
        float64x2 f64[2];
    };

    for (unsigned i = 0; i < 32; i++) {
        c[i] = i;
    }

    // int8x16
    TemplateTestHelper<Test_permute_bytes16_x2, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_permute_bytes16_x8, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_permute_bytes16_x16, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x8, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x16, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x8, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_permute_zbytes16_x16, uint8x16>::run(tc, u8[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x8, uint8x16>::run(tc, u8[0], u8[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x16, uint8x16>::run(tc, u8[0], u8[1]);

    // int16x8
    TemplateTestHelper<Test_permute_bytes16_x2, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_permute_bytes16_x8, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint16x8>::run(tc, u16[0], u16[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint16x8>::run(tc, u16[0], u16[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x8, uint16x8>::run(tc, u16[0], u16[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_permute_zbytes16_x8, uint16x8>::run(tc, u16[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint16x8>::run(tc, u16[0], u16[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint16x8>::run(tc, u16[0], u16[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x8, uint16x8>::run(tc, u16[0], u16[1]);

    // int32x4
    TemplateTestHelper<Test_permute_bytes16_x2, uint32x4>::run(tc, u32[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, uint32x4>::run(tc, u32[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, uint32x4>::run(tc, u32[0], u32[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, uint32x4>::run(tc, u32[0], u32[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, uint32x4>::run(tc, u32[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, uint32x4>::run(tc, u32[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, uint32x4>::run(tc, u32[0], u32[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, uint32x4>::run(tc, u32[0], u32[1]);

    // float32x4
    TemplateTestHelper<Test_permute_bytes16_x2, float32x4>::run(tc, f32[0]);
    TemplateTestHelper<Test_permute_bytes16_x4, float32x4>::run(tc, f32[0]);
    TemplateTestHelper<Test_shuffle_bytes16_x2, float32x4>::run(tc, f32[0], f32[1]);
    TemplateTestHelper<Test_shuffle_bytes16_x4, float32x4>::run(tc, f32[0], f32[1]);
    TemplateTestHelper<Test_permute_zbytes16_x2, float32x4>::run(tc, f32[0]);
    TemplateTestHelper<Test_permute_zbytes16_x4, float32x4>::run(tc, f32[0]);
    TemplateTestHelper<Test_shuffle_zbytes16_x2, float32x4>::run(tc, f32[0], f32[1]);
    TemplateTestHelper<Test_shuffle_zbytes16_x4, float32x4>::run(tc, f32[0], f32[1]);

    // some tests whether the permute mask itself is correctly generated
    {
        uint16x8 mask = make_shuffle_bytes16_mask<-1,-1,-1,-1>(mask);
        uint16x8 r1 = uint16x8::zero();
        uint16x8 r2 = permute_zbytes16(u16[0], mask);
        TEST_PUSH(tc, uint16x8, cmp_eq(r1, r2));
    }
    {
        uint16x8 mask = make_shuffle_bytes16_mask<0,1,2,3>(mask);
        uint16x8 r1 = permute<0,1,2,3>(u16[0]);
        uint16x8 r2 = permute_bytes16(u16[0], mask);
        TEST_PUSH(tc, uint16x8, cmp_eq(r1, r2));
    }
    {
        uint32x4 mask = make_shuffle_bytes16_mask<0,1,2,3>(mask);
        uint32x4 r1 = permute<0,1,2,3>(u32[0]);
        uint32x4 r2 = permute_zbytes16(u32[0], mask);
        TEST_PUSH(tc, uint32x4, cmp_eq(r1, r2));
    }
#else
    (void) res;
#endif
}

SIMDPP_ARCH_NAMESPACE_END

#endif
