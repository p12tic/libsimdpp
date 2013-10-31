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
#include <limits>

namespace SIMDPP_ARCH_NAMESPACE {

#define TEST_COMPARE_TESTER_HELPER(TC, T, L, R)                     \
{                                                                   \
    TEST_ARRAY_HELPER16X2_2(TC, T, cmp_eq, L, R);                        \
    TEST_ARRAY_HELPER16X2_2(TC, T, cmp_lt, L, R);                        \
    TEST_ARRAY_HELPER16X2_2(TC, T, cmp_gt, L, R);                        \
}

void test_compare(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "compare");

    using namespace simdpp;

    //int8x32
    {
    uint8x32 sl[] = {
        uint8x32::make_const(0x11, 0x22, 0x33, 0xff),
        uint8x32::make_const(0xcc, 0xdd, 0xee, 0xff),
        uint8x32::make_const(0x01, 0x00, 0xff, 0xfe),
    };
    uint8x32 sr[] = {
        uint8x32::make_const(0x22, 0x22, 0x22, 0x22),
        uint8x32::make_const(0xee, 0xee, 0xee, 0xee),
        uint8x32::make_const(0x00, 0x00, 0x00, 0x00),
    };

    TEST_COMPARE_TESTER_HELPER(tc, int8x32, sl, sr);
    TEST_COMPARE_TESTER_HELPER(tc, uint8x32, sl, sr);
    }

    //int16x16
    {
        uint16x16 sl[] = {
            uint16x16::make_const(0x1111, 0x2222, 0x3333, 0x3333),
            uint16x16::make_const(0xdddd, 0xeeee, 0xffff, 0xcccc),
            uint16x16::make_const(0x0001, 0x0000, 0xffff, 0xfffe),
        };
        uint16x16 sr[] = {
            uint16x16::make_const(0x2222, 0x2222, 0x2222, 0x2222),
            uint16x16::make_const(0xeeee, 0xeeee, 0xeeee, 0xeeee),
            uint16x16::make_const(0x0000, 0x0000, 0x0000, 0x0000),
        };

        TEST_COMPARE_TESTER_HELPER(tc, int16x16, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint16x16, sl, sr);
    }

    //int32x8
    {
        uint32x8 sl[] = {
            uint32x8::make_const(0x11111111, 0x22222222, 0x33333333, 0x33333333),
            uint32x8::make_const(0xdddddddd, 0xeeeeeeee, 0xffffffff, 0xcccccccc),
            uint32x8::make_const(0x00000000, 0x00000001, 0xffffffff, 0xfffffffe),
        };
        uint32x8 sr[] = {
            uint32x8::make_const(0x22222222, 0x22222222, 0x22222222, 0x22222222),
            uint32x8::make_const(0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee),
            uint32x8::make_const(0x00000000, 0x00000000, 0x00000000, 0x00000000),
        };

        TEST_COMPARE_TESTER_HELPER(tc, int32x8, sl, sr);
        TEST_COMPARE_TESTER_HELPER(tc, uint32x8, sl, sr);
    }

    //int64x2 not available

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    //float32x8
    {
        float32x8 sl[] = {
            float32x8::make_const(0.0f, 1.0f, 2.0f, inff),
            float32x8::make_const(0.0f, 1.0f, 2.0f, inff),
            float32x8::make_const(-0.0f, -1.0f, -2.0f, -inff),
            float32x8::make_const(0.0f, 1.0f, -inff, inff),
            float32x8::make_const(0.0f, 1.0f, -0.0f, -1.0f),
            float32x8::make_const(nanf, 0.0, -inff, inff),
        };
        float32x8 sr[] = {
            float32x8::make_const(1.0f, 1.0f, 1.0f, 1.0f),
            float32x8::make_const(-1.0f, -1.0f, -1.0f, -1.0f),
            float32x8::make_const(-1.0f, -1.0f, -1.0f, -1.0f),
            float32x8::make_const(inff, inff, inff, inff),
            float32x8::make_const(nanf, nanf, nanf, nanf),
            float32x8::make_const(nanf, nanf, nanf, nanf),
        };

        TEST_COMPARE_TESTER_HELPER(tc, float32x8, sl, sr);
        TEST_ARRAY_HELPER16X2_2(tc, float32x8, cmp_neq, sl, sr);
        TEST_ARRAY_HELPER16X2_2(tc, float32x8, cmp_le, sl, sr);
        TEST_ARRAY_HELPER16X2_2(tc, float32x8, cmp_ge, sl, sr);
    }

    //float64x4
    {
        float64x4 sl[] = {
            float64x4::make_const(0.0, 1.0),
            float64x4::make_const(2.0, inf),
            float64x4::make_const(0.0, 1.0),
            float64x4::make_const(2.0, inf),
            float64x4::make_const(-0.0, -1.0),

            float64x4::make_const(-2.0, -inf),
            float64x4::make_const(0.0, 1.0),
            float64x4::make_const(-inf, inf),
            float64x4::make_const(0.0, 1.0),
            float64x4::make_const(-0.0, -1.0),

            float64x4::make_const(nan, 0.0),
            float64x4::make_const(-inf, inf),
        };
        float64x4 sr[] = {
            float64x4::make_const(1.0, 1.0),
            float64x4::make_const(.0, 1.0),
            float64x4::make_const(-1.0, -1.0),
            float64x4::make_const(-1.0, -1.0),
            float64x4::make_const(-1.0, -1.0),

            float64x4::make_const(-1.0, -1.0),
            float64x4::make_const(inf, inf),
            float64x4::make_const(inf, inf),
            float64x4::make_const(nan, nan),
            float64x4::make_const(nan, nan),

            float64x4::make_const(nan, nan),
            float64x4::make_const(nan, nan),
        };

        TEST_COMPARE_TESTER_HELPER(tc, float64x4, sl, sr);
        TEST_ARRAY_HELPER16X2_2(tc, float64x4, cmp_neq, sl, sr);
        TEST_ARRAY_HELPER16X2_2(tc, float64x4, cmp_le, sl, sr);
        TEST_ARRAY_HELPER16X2_2(tc, float64x4, cmp_ge, sl, sr);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
