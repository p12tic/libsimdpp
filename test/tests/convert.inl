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
