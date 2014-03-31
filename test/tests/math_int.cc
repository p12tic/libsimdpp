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

    // Vectors with 8-bit integer elements
    {
        uint8x32 s[] = {
            (uint8<32>) make_uint(0x11, 0x22, 0x33, 0x44),
            (uint8<32>) make_uint(0xcc, 0xdd, 0xee, 0xff),
            (uint8<32>) make_uint(0x00, 0x01, 0x02, 0x03),
            (uint8<32>) make_uint(0xfc, 0xfd, 0xfe, 0xff),
            (uint8<32>) make_uint(0x7e, 0x7f, 0x80, 0x81),

            (uint8<32>) make_uint(0x11, 0x22, 0x33, 0x44),
            (uint8<32>) make_uint(0xcc, 0xdd, 0xee, 0xff),
            (uint8<32>) make_uint(0x00, 0x01, 0x02, 0x03),
            (uint8<32>) make_uint(0xfc, 0xfd, 0xfe, 0xff),
            (uint8<32>) make_uint(0x7e, 0x7f, 0x80, 0x81),
        };

        TEST_ALL_COMB_HELPER2(tc, int8x32, add, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, add_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, sub, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, sub_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, min, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, max, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, avg, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8x32, avg_trunc, s, 1);

        TEST_ALL_COMB_HELPER2(tc, uint8x32, add, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, add_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, sub, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, sub_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, min, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, max, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, avg, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8x32, avg_trunc, s, 1);

        TEST_ARRAY_HELPER1(tc, int8x32, neg, s);
        TEST_ARRAY_HELPER1(tc, int8x32, abs, s);

        // this one can't contain zeros
        // NOTE: no support for 32-byte vectors yet
        uint8x16 s2[] = {
            (uint8x16) make_uint(0x01, 0x02, 0x03, 0x04),
            (uint8x16) make_uint(0x07, 0x0a, 0x0d, 0x12),
            (uint8x16) make_uint(0x13, 0x15, 0x1d, 0x22),
            (uint8x16) make_uint(0x27, 0x34, 0x46, 0x68),
            (uint8x16) make_uint(0x7e, 0x7f, 0x80, 0x81),

            (uint8x16) make_uint(0x91, 0x9a, 0xa1, 0xa4),
            (uint8x16) make_uint(0xa6, 0xaa, 0xb2, 0xb7),
            (uint8x16) make_uint(0xb8, 0xbf, 0xc1, 0xc3),
            (uint8x16) make_uint(0xc6, 0xce, 0xd2, 0xd5),
            (uint8x16) make_uint(0xda, 0xf2, 0xfa, 0xff),
        };

        TEST_ALL_COMB_HELPER1(tc, uint8x16, div_p<8>, s2, 1);

        uint8x16 s3[] = {
            (uint8x16) make_uint(0x01, 0x02, 0x03, 0x04),
            (uint8x16) make_uint(0x05, 0x06, 0x07, 0x08),
            (uint8x16) make_uint(0x09, 0x0a, 0x0b, 0x0c),
            (uint8x16) make_uint(0x0d, 0x0e, 0x0f, 0x0f),
        };
        TEST_ALL_COMB_HELPER1(tc, uint8x16, div_p<4>, s3, 1);
    }

    // Vectors with 16-bit integer elements
    {
        uint16x16 s[] = {
            (uint16x16) make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            (uint16x16) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            (uint16x16) make_uint(0x0000, 0x0001, 0x0002, 0x0003),
            (uint16x16) make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            (uint16x16) make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),

            (uint16x16) make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            (uint16x16) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            (uint16x16) make_uint(0x0000, 0x0001, 0x0002, 0x0003),
            (uint16x16) make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            (uint16x16) make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),
        };

        TEST_ALL_COMB_HELPER2(tc, int16x16, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, add_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, sub_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, mul_lo, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, mul_hi, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, min, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, max, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, avg, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16x16, avg_trunc, s, 2);

        TEST_ALL_COMB_HELPER2(tc, uint16x16, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, add_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, sub_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, mul_lo, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, mul_hi, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, min, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, max, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, avg, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16x16, avg_trunc, s, 2);

        TEST_ALL_COMB_HELPER1_T(tc, int32<16>, int16x16, mull, s, 2);
        TEST_ALL_COMB_HELPER1_T(tc, uint32<16>, uint16x16, mull, s, 2);

        TEST_ARRAY_HELPER1(tc, int16x16, neg, s);
        TEST_ARRAY_HELPER1(tc, int16x16, abs, s);

        // this one can't contain zeros
        // NOTE: no support for 32-byte vectors yet
        uint16x8 s2[] = {
            (uint16<8>) make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            (uint16<8>) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            (uint16<8>) make_uint(0x0510, 0x0001, 0x0002, 0x0003),
            (uint16<8>) make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            (uint16<8>) make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),

            (uint16<8>) make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            (uint16<8>) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            (uint16<8>) make_uint(0x0230, 0x0001, 0x0002, 0x0003),
            (uint16<8>) make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            (uint16<8>) make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),
        };

        TEST_ALL_COMB_HELPER1(tc, uint16x8, div_p<16>, s2, 2);

        uint16x8 s3[] = {
            (uint16<8>) make_uint(0x01, 0x02, 0x03, 0x04),
            (uint16<8>) make_uint(0x07, 0x0a, 0x0d, 0x12),
            (uint16<8>) make_uint(0x13, 0x15, 0x1d, 0x22),
            (uint16<8>) make_uint(0x27, 0x34, 0x46, 0x68),
            (uint16<8>) make_uint(0x7e, 0x7f, 0x80, 0x81),

            (uint16<8>) make_uint(0x91, 0x9a, 0xa1, 0xa4),
            (uint16<8>) make_uint(0xa6, 0xaa, 0xb2, 0xb7),
            (uint16<8>) make_uint(0xb8, 0xbf, 0xc1, 0xc3),
            (uint16<8>) make_uint(0xc6, 0xce, 0xd2, 0xd5),
            (uint16<8>) make_uint(0xda, 0xf2, 0xfa, 0xff),
        };
        TEST_ALL_COMB_HELPER1(tc, uint16x8, div_p<8>, s3, 2);

        uint16x8 s4[] = {
            (uint16<8>) make_uint(0x01, 0x02, 0x03, 0x04),
            (uint16<8>) make_uint(0x05, 0x06, 0x07, 0x08),
            (uint16<8>) make_uint(0x09, 0x0a, 0x0b, 0x0c),
            (uint16<8>) make_uint(0x0d, 0x0e, 0x0f, 0x0f),
        };
        TEST_ALL_COMB_HELPER1(tc, uint16x8, div_p<8>, s4, 2);
    }

    // Vectors with 32-bit integer elements
    {
        uint32x8 s[] = {
            (uint32<8>) make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            (uint32<8>) make_uint(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            (uint32<8>) make_uint(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            (uint32<8>) make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            (uint32<8>) make_uint(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),

            (uint32<8>) make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            (uint32<8>) make_uint(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            (uint32<8>) make_uint(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            (uint32<8>) make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            (uint32<8>) make_uint(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),
        };

        TEST_ALL_COMB_HELPER2(tc, int32x8, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32x8, sub, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32x8, min, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32x8, max, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32x8, avg, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32x8, avg_trunc, s, 4);

        TEST_ALL_COMB_HELPER2(tc, uint32x8, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32x8, sub, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32x8, min, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32x8, max, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32x8, avg, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32x8, avg_trunc, s, 4);

#if !(SIMDPP_USE_ALTIVEC)
        TEST_ALL_COMB_HELPER1_T(tc, uint64<8>, uint32x8, mull, s, 4);
        TEST_ALL_COMB_HELPER1_T(tc, uint32x8, uint32x8, mul_lo, s, 4);
#endif

        TEST_ARRAY_HELPER1(tc, int32x8, neg, s);
        TEST_ARRAY_HELPER1(tc, int32x8, abs, s);
    }

    // Vectors with 64-bit integer elements
    {
        uint64x4 s[] = {
            (uint64<4>) make_uint(0x1111111111111111, 0x2222222222222222),
            (uint64<4>) make_uint(0x3333333333333333, 0x4444444444444444),
            (uint64<4>) make_uint(0xcccccccccccccccc, 0xdddddddddddddddd),
            (uint64<4>) make_uint(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            (uint64<4>) make_uint(0x0000000000000000, 0x0000000000000001),

            (uint64<4>) make_uint(0x0000000000000002, 0x0000000000000003),
            (uint64<4>) make_uint(0xfffffffffffffffc, 0xfffffffffffffffd),
            (uint64<4>) make_uint(0xfffffffffffffffe, 0xffffffffffffffff),
            (uint64<4>) make_uint(0x7ffffffffffffffe, 0x7fffffffffffffff),
            (uint64<4>) make_uint(0x8000000000000000, 0x8000000000000001),

            (uint64<4>) make_uint(0x1111111111111111, 0x2222222222222222),
            (uint64<4>) make_uint(0x3333333333333333, 0x4444444444444444),
            (uint64<4>) make_uint(0xcccccccccccccccc, 0xdddddddddddddddd),
            (uint64<4>) make_uint(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            (uint64<4>) make_uint(0x0000000000000000, 0x0000000000000001),

            (uint64<4>) make_uint(0x0000000000000002, 0x0000000000000003),
            (uint64<4>) make_uint(0xfffffffffffffffc, 0xfffffffffffffffd),
            (uint64<4>) make_uint(0xfffffffffffffffe, 0xffffffffffffffff),
            (uint64<4>) make_uint(0x7ffffffffffffffe, 0x7fffffffffffffff),
            (uint64<4>) make_uint(0x8000000000000000, 0x8000000000000001),
        };

        TEST_ALL_COMB_HELPER2(tc, int64x4, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int64x4, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint64x4, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint64x4, sub, s, 2);

        TEST_ARRAY_HELPER1(tc, int64x4, neg, s);
        TEST_ARRAY_HELPER1(tc, int64x4, abs, s);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
