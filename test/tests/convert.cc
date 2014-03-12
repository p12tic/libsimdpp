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

void test_convert(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "convert");

    using namespace simdpp;

    //int8x16
    {
    int8x16 s[] = {
        make_uint<uint8x16>(0x00, 0x11, 0x22, 0x33),
        make_uint<uint8x16>(0xcc, 0xdd, 0xee, 0xff),
    };
    TEST_ARRAY_HELPER1_T(tc, int16x16, int8x16, to_int16, s);
    TEST_ARRAY_HELPER1_T(tc, int16x16, uint8x16, to_int16, s);
    }

    //int16x8
    {
    int16x8 s[] = {
        make_uint<uint16x8>(0x0000, 0x1111, 0x2222, 0x3333),
        make_uint<uint16x8>(0xcccc, 0xdddd, 0xeeee, 0xffff),
    };
    TEST_ARRAY_HELPER1_T(tc, int32x8, int16x8, to_int32, s);
    TEST_ARRAY_HELPER1_T(tc, int32x8, uint16x8, to_int32, s);
    }

    //int32x4
    {
    int32x4 s[] = {
        make_uint<uint32x4>(0x00000000, 0x11111111),
        make_uint<uint32x4>(0x22222222, 0x33333333),
        make_uint<uint32x4>(0xcccccccc, 0xeeeeeeee),
        make_uint<uint32x4>(0xdddddddd, 0xffffffff),
    };
    TEST_ARRAY_HELPER1_T(tc, int64x4, int32x4, to_int64, s);
    TEST_ARRAY_HELPER1_T(tc, int64x4, uint32x4, to_int64, s);

    int32x4 sf[] = {
        make_uint<int32x4>(1, 100),
        make_uint<int32x4>(-1, -100),
        make_uint<int32x4>(0, -15),
        make_uint<int32x4>(63100000, 63100001),
        make_uint<int32x4>(63100002, 63100003),
        make_uint<int32x4>(-63100000, -63100001),
        make_uint<int32x4>(-63100002, -63100003),
    };

    TEST_ARRAY_HELPER1_T(tc, float32x4, int32x4, to_float32, sf);
    TEST_ARRAY_HELPER1_T(tc, float64x4, int32x4, to_float64, sf);
    }

    //float32x4
    {
    float32x4 sf[] = {
        make_float<float32x4>(1.0, 100.0),
        make_float<float32x4>(-1.0, -100.0),
        make_float<float32x4>(0.0, -15.0),
        make_float<float32x4>(1.0, 1.1),
        make_float<float32x4>(-1.0, -1.1),
        make_float<float32x4>(63100000.0, 63100000.0),
        make_float<float32x4>(63100002.0, 63100003.0),
        make_float<float32x4>(-63100000.0, -63100001.0),
        make_float<float32x4>(-63100002.0, -63100003.0),
    };

    TEST_ARRAY_HELPER1_T(tc, int32x4, float32x4, to_int32, sf);
    }

    //float64x2
    {
    float64x4 sf[] = {
        make_float<float64x4>(1.0, 100.0),
        make_float<float64x4>(-1.0, -100.0),
        make_float<float64x4>(0.0, -15.0),
        make_float<float64x4>(1.0, 1.1),
        make_float<float64x4>(-1.0, -1.1),
        make_float<float64x4>(63100000.0, 63100000.0),
        make_float<float64x4>(63100002.0, 63100003.0),
        make_float<float64x4>(-63100000.0, -63100001.0),
        make_float<float64x4>(-63100002.0, -63100003.0),
    };

    TEST_ARRAY_HELPER1_T(tc, int32x4, float64x4, to_int32, sf);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
