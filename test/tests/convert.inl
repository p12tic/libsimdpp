/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_CONVERT_H
#define LIBSIMDPP_TEST_TESTS_CONVERT_H

namespace SIMDPP_ARCH_NAMESPACE {

void test_convert(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "convert");

#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    TestCase& tc64 = NEW_TEST_CASE(res, "convert_f64");
#endif

    using namespace simdpp;

    //int8x16
    {
    int8x16 s[] = {
        uint8x16::make_const(0x00, 0x11, 0x22, 0x33),
        uint8x16::make_const(0xcc, 0xdd, 0xee, 0xff),
    };
    TEST_ARRAY_HELPER1_T(tc, int16x8, int8x16, to_int16x8, s);
    TEST_ARRAY_HELPER1_T(tc, int16x8, uint8x16, to_int16x8, s);
    }

    //int16x8
    {
    int16x8 s[] = {
        uint16x8::make_const(0x0000, 0x1111, 0x2222, 0x3333),
        uint16x8::make_const(0xcccc, 0xdddd, 0xeeee, 0xffff),
    };
    TEST_ARRAY_HELPER1_T(tc, int32x4, int16x8, to_int32x4, s);
    TEST_ARRAY_HELPER1_T(tc, int32x4, uint16x8, to_int32x4, s);
    }

    //int32x4
    {
    int32x4 s[] = {
        uint32x4::make_const(0x00000000, 0x11111111),
        uint32x4::make_const(0x22222222, 0x33333333),
        uint32x4::make_const(0xcccccccc, 0xeeeeeeee),
        uint32x4::make_const(0xdddddddd, 0xffffffff),
    };
    TEST_ARRAY_HELPER1_T(tc, int64x2, int32x4, to_int64x2, s);
    TEST_ARRAY_HELPER1_T(tc, int64x2, uint32x4, to_int64x2, s);

    int32x4 sf[] = {
        int32x4::make_const(1, 100),
        int32x4::make_const(-1, -100),
        int32x4::make_const(0, -15),
        int32x4::make_const(63100000, 63100001),
        int32x4::make_const(63100002, 63100003),
        int32x4::make_const(-63100000, -63100001),
        int32x4::make_const(-63100002, -63100003),
    };

    TEST_ARRAY_HELPER1_T(tc, float32x4, int32x4, to_float32x4, sf);
#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    TEST_ARRAY_HELPER1_T(tc64, float64x2, int32x4, to_float64x2, sf);
#endif
    }

    //float32x4
    {
    float32x4 sf[] = {
        float32x4::make_const(1.0, 100.0),
        float32x4::make_const(-1.0, -100.0),
        float32x4::make_const(0.0, -15.0),
        float32x4::make_const(1.0, 1.1),
        float32x4::make_const(-1.0, -1.1),
        float32x4::make_const(63100000.0, 63100000.0),
        float32x4::make_const(63100002.0, 63100003.0),
        float32x4::make_const(-63100000.0, -63100001.0),
        float32x4::make_const(-63100002.0, -63100003.0),
    };

    TEST_ARRAY_HELPER1_T(tc, int32x4, float32x4, to_int32x4, sf);
    }

#if !SIMDPP_USE_NEON || SIMDPP_USE_NEON_VFP_DP
    //float64x2
    {
    float64x2 sf[] = {
        float64x2::make_const(1.0, 100.0),
        float64x2::make_const(-1.0, -100.0),
        float64x2::make_const(0.0, -15.0),
        float64x2::make_const(1.0, 1.1),
        float64x2::make_const(-1.0, -1.1),
        float64x2::make_const(63100000.0, 63100000.0),
        float64x2::make_const(63100002.0, 63100003.0),
        float64x2::make_const(-63100000.0, -63100001.0),
        float64x2::make_const(-63100002.0, -63100003.0),
    };

    TEST_ARRAY_HELPER1_T(tc64, int32x4, float64x2, to_int32x4, sf);
    }
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
