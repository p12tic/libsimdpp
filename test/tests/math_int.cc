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

void test_math_int(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "math_int");

    using namespace simdpp;

    //int8x16
    {
        uint8x16 s[] = {
            uint8x16::make_const(0x11, 0x22, 0x33, 0x44),
            uint8x16::make_const(0xcc, 0xdd, 0xee, 0xff),
            uint8x16::make_const(0x00, 0x01, 0x02, 0x03),
            uint8x16::make_const(0xfc, 0xfd, 0xfe, 0xff),
            uint8x16::make_const(0x7e, 0x7f, 0x80, 0x81),

            uint8x16::make_const(0x11, 0x22, 0x33, 0x44),
            uint8x16::make_const(0xcc, 0xdd, 0xee, 0xff),
            uint8x16::make_const(0x00, 0x01, 0x02, 0x03),
            uint8x16::make_const(0xfc, 0xfd, 0xfe, 0xff),
            uint8x16::make_const(0x7e, 0x7f, 0x80, 0x81),
        };

        TEST_ALL_COMB_HELPER(tc, int8x16, add, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, adds, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, sub, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, subs, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, min, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, max, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, avg, s, 1);
        TEST_ALL_COMB_HELPER(tc, int8x16, avg_trunc, s, 1);

        TEST_ALL_COMB_HELPER(tc, uint8x16, add, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, adds, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, sub, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, subs, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, min, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, max, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, avg, s, 1);
        TEST_ALL_COMB_HELPER(tc, uint8x16, avg_trunc, s, 1);

        TEST_ARRAY_HELPER1(tc, int8x16, neg, s);
        TEST_ARRAY_HELPER1(tc, int8x16, abs, s);

        // this one can't contain zeros
        uint8x16 s2[] = {
            uint8x16::make_const(0x01, 0x02, 0x03, 0x04),
            uint8x16::make_const(0x07, 0x0a, 0x0d, 0x12),
            uint8x16::make_const(0x13, 0x15, 0x1d, 0x22),
            uint8x16::make_const(0x27, 0x34, 0x46, 0x68),
            uint8x16::make_const(0x7e, 0x7f, 0x80, 0x81),

            uint8x16::make_const(0x91, 0x9a, 0xa1, 0xa4),
            uint8x16::make_const(0xa6, 0xaa, 0xb2, 0xb7),
            uint8x16::make_const(0xb8, 0xbf, 0xc1, 0xc3),
            uint8x16::make_const(0xc6, 0xce, 0xd2, 0xd5),
            uint8x16::make_const(0xda, 0xf2, 0xfa, 0xff),
        };

        TEST_ALL_COMB_HELPER(tc, uint8x16, div_p<8>, s2, 1);

        uint8x16 s3[] = {
            uint8x16::make_const(0x01, 0x02, 0x03, 0x04),
            uint8x16::make_const(0x05, 0x06, 0x07, 0x08),
            uint8x16::make_const(0x09, 0x0a, 0x0b, 0x0c),
            uint8x16::make_const(0x0d, 0x0e, 0x0f, 0x0f),
        };
        TEST_ALL_COMB_HELPER(tc, uint8x16, div_p<4>, s3, 1);
    }

    //int16x8
    {
        uint16x8 s[] = {
            uint16x8::make_const(0x1111, 0x2222, 0x3333, 0x4444),
            uint16x8::make_const(0xcccc, 0xdddd, 0xeeee, 0xffff),
            uint16x8::make_const(0x0000, 0x0001, 0x0002, 0x0003),
            uint16x8::make_const(0xfffc, 0xfffd, 0xfffe, 0xffff),
            uint16x8::make_const(0x7ffe, 0x7fff, 0x8000, 0x8001),

            uint16x8::make_const(0x1111, 0x2222, 0x3333, 0x4444),
            uint16x8::make_const(0xcccc, 0xdddd, 0xeeee, 0xffff),
            uint16x8::make_const(0x0000, 0x0001, 0x0002, 0x0003),
            uint16x8::make_const(0xfffc, 0xfffd, 0xfffe, 0xffff),
            uint16x8::make_const(0x7ffe, 0x7fff, 0x8000, 0x8001),
        };

        TEST_ALL_COMB_HELPER(tc, int16x8, add, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, adds, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, sub, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, subs, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, mul_lo, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, mul_hi, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, min, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, max, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, avg, s, 2);
        TEST_ALL_COMB_HELPER(tc, int16x8, avg_trunc, s, 2);

        TEST_ALL_COMB_HELPER(tc, uint16x8, add, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, adds, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, sub, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, subs, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, mul_lo, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, mul_hi, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, min, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, max, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, avg, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint16x8, avg_trunc, s, 2);

        TEST_ALL_COMB_HELPER_T(tc, int32x4, int16x8, mull_lo, s, 2);
        TEST_ALL_COMB_HELPER_T(tc, int32x4, int16x8, mull_hi, s, 2);
        TEST_ALL_COMB_HELPER_T(tc, uint32x4, uint16x8, mull_lo, s, 2);
        TEST_ALL_COMB_HELPER_T(tc, uint32x4, uint16x8, mull_hi, s, 2);

        TEST_ARRAY_HELPER1(tc, int16x8, neg, s);
        TEST_ARRAY_HELPER1(tc, int16x8, abs, s);

        // this one can't contain zros
        uint16x8 s2[] = {
            uint16x8::make_const(0x1111, 0x2222, 0x3333, 0x4444),
            uint16x8::make_const(0xcccc, 0xdddd, 0xeeee, 0xffff),
            uint16x8::make_const(0x0510, 0x0001, 0x0002, 0x0003),
            uint16x8::make_const(0xfffc, 0xfffd, 0xfffe, 0xffff),
            uint16x8::make_const(0x7ffe, 0x7fff, 0x8000, 0x8001),

            uint16x8::make_const(0x1111, 0x2222, 0x3333, 0x4444),
            uint16x8::make_const(0xcccc, 0xdddd, 0xeeee, 0xffff),
            uint16x8::make_const(0x0230, 0x0001, 0x0002, 0x0003),
            uint16x8::make_const(0xfffc, 0xfffd, 0xfffe, 0xffff),
            uint16x8::make_const(0x7ffe, 0x7fff, 0x8000, 0x8001),
        };

        TEST_ALL_COMB_HELPER(tc, uint16x8, div_p<16>, s2, 2);

        uint16x8 s3[] = {
            uint16x8::make_const(0x01, 0x02, 0x03, 0x04),
            uint16x8::make_const(0x07, 0x0a, 0x0d, 0x12),
            uint16x8::make_const(0x13, 0x15, 0x1d, 0x22),
            uint16x8::make_const(0x27, 0x34, 0x46, 0x68),
            uint16x8::make_const(0x7e, 0x7f, 0x80, 0x81),

            uint16x8::make_const(0x91, 0x9a, 0xa1, 0xa4),
            uint16x8::make_const(0xa6, 0xaa, 0xb2, 0xb7),
            uint16x8::make_const(0xb8, 0xbf, 0xc1, 0xc3),
            uint16x8::make_const(0xc6, 0xce, 0xd2, 0xd5),
            uint16x8::make_const(0xda, 0xf2, 0xfa, 0xff),
        };
        TEST_ALL_COMB_HELPER(tc, uint16x8, div_p<8>, s3, 2);

        uint16x8 s4[] = {
            uint16x8::make_const(0x01, 0x02, 0x03, 0x04),
            uint16x8::make_const(0x05, 0x06, 0x07, 0x08),
            uint16x8::make_const(0x09, 0x0a, 0x0b, 0x0c),
            uint16x8::make_const(0x0d, 0x0e, 0x0f, 0x0f),
        };
        TEST_ALL_COMB_HELPER(tc, uint16x8, div_p<8>, s4, 2);
    }

    //int32x4
    {
        uint32x4 s[] = {
            uint32x4::make_const(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            uint32x4::make_const(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            uint32x4::make_const(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            uint32x4::make_const(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            uint32x4::make_const(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),

            uint32x4::make_const(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            uint32x4::make_const(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            uint32x4::make_const(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            uint32x4::make_const(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            uint32x4::make_const(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),
        };

        TEST_ALL_COMB_HELPER(tc, int32x4, add, s, 4);
        TEST_ALL_COMB_HELPER(tc, int32x4, sub, s, 4);
        TEST_ALL_COMB_HELPER(tc, int32x4, min, s, 4);
        TEST_ALL_COMB_HELPER(tc, int32x4, max, s, 4);
        TEST_ALL_COMB_HELPER(tc, int32x4, avg, s, 4);
        TEST_ALL_COMB_HELPER(tc, int32x4, avg_trunc, s, 4);

        TEST_ALL_COMB_HELPER(tc, uint32x4, add, s, 4);
        TEST_ALL_COMB_HELPER(tc, uint32x4, sub, s, 4);
        TEST_ALL_COMB_HELPER(tc, uint32x4, min, s, 4);
        TEST_ALL_COMB_HELPER(tc, uint32x4, max, s, 4);
        TEST_ALL_COMB_HELPER(tc, uint32x4, avg, s, 4);
        TEST_ALL_COMB_HELPER(tc, uint32x4, avg_trunc, s, 4);

        TEST_ALL_COMB_HELPER_T(tc, uint64x2, uint32x4, mull_lo, s, 4);
        TEST_ALL_COMB_HELPER_T(tc, uint64x2, uint32x4, mull_hi, s, 4);
        TEST_ALL_COMB_HELPER_T(tc, uint64x2, uint32x4, mul_lo, s, 4);

        TEST_ARRAY_HELPER1(tc, int32x4, neg, s);
        TEST_ARRAY_HELPER1(tc, int32x4, abs, s);
    }

    //int64x2
    {
        uint64x2 s[] = {
            uint64x2::make_const(0x1111111111111111, 0x2222222222222222),
            uint64x2::make_const(0x3333333333333333, 0x4444444444444444),
            uint64x2::make_const(0xcccccccccccccccc, 0xdddddddddddddddd),
            uint64x2::make_const(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            uint64x2::make_const(0x0000000000000000, 0x0000000000000001),

            uint64x2::make_const(0x0000000000000002, 0x0000000000000003),
            uint64x2::make_const(0xfffffffffffffffc, 0xfffffffffffffffd),
            uint64x2::make_const(0xfffffffffffffffe, 0xffffffffffffffff),
            uint64x2::make_const(0x7ffffffffffffffe, 0x7fffffffffffffff),
            uint64x2::make_const(0x8000000000000000, 0x8000000000000001),

            uint64x2::make_const(0x1111111111111111, 0x2222222222222222),
            uint64x2::make_const(0x3333333333333333, 0x4444444444444444),
            uint64x2::make_const(0xcccccccccccccccc, 0xdddddddddddddddd),
            uint64x2::make_const(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            uint64x2::make_const(0x0000000000000000, 0x0000000000000001),

            uint64x2::make_const(0x0000000000000002, 0x0000000000000003),
            uint64x2::make_const(0xfffffffffffffffc, 0xfffffffffffffffd),
            uint64x2::make_const(0xfffffffffffffffe, 0xffffffffffffffff),
            uint64x2::make_const(0x7ffffffffffffffe, 0x7fffffffffffffff),
            uint64x2::make_const(0x8000000000000000, 0x8000000000000001),
        };

        TEST_ALL_COMB_HELPER(tc, int64x2, add, s, 2);
        TEST_ALL_COMB_HELPER(tc, int64x2, sub, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint64x2, add, s, 2);
        TEST_ALL_COMB_HELPER(tc, uint64x2, sub, s, 2);

        TEST_ARRAY_HELPER1(tc, int64x2, neg, s);
        TEST_ARRAY_HELPER1(tc, int64x2, abs, s);
    }

    // TODO implement tests for 256-bit types
}

} // namespace SIMDPP_ARCH_NAMESPACE
