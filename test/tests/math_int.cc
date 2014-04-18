/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned B>
void test_math_int_n(TestSuite& tc)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using int8_n = int8<B>;
    using uint16_n = uint16<B/2>;
    using int16_n = int16<B/2>;
    using uint32_n = uint32<B/4>;
    using int32_n = int32<B/4>;
    using uint64_n = uint64<B/8>;
    using int64_n = int64<B/8>;

    // Vectors with 8-bit integer elements
    {
        uint8_n s[] = {
            (uint8_n) make_uint(0x11, 0x22, 0x33, 0x44),
            (uint8_n) make_uint(0xcc, 0xdd, 0xee, 0xff),
            (uint8_n) make_uint(0x00, 0x01, 0x02, 0x03),
            (uint8_n) make_uint(0xfc, 0xfd, 0xfe, 0xff),
            (uint8_n) make_uint(0x7e, 0x7f, 0x80, 0x81),

            (uint8_n) make_uint(0x11, 0x22, 0x33, 0x44),
            (uint8_n) make_uint(0xcc, 0xdd, 0xee, 0xff),
            (uint8_n) make_uint(0x00, 0x01, 0x02, 0x03),
            (uint8_n) make_uint(0xfc, 0xfd, 0xfe, 0xff),
            (uint8_n) make_uint(0x7e, 0x7f, 0x80, 0x81),
        };

        TEST_ALL_COMB_HELPER2(tc, int8_n, add, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, add_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, sub, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, sub_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, min, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, max, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, avg, s, 1);
        TEST_ALL_COMB_HELPER2(tc, int8_n, avg_trunc, s, 1);

        TEST_ALL_COMB_HELPER2(tc, uint8_n, add, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, add_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, sub, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, sub_sat, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, min, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, max, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, avg, s, 1);
        TEST_ALL_COMB_HELPER2(tc, uint8_n, avg_trunc, s, 1);

        TEST_ARRAY_HELPER1(tc, int8_n, neg, s);
        TEST_ARRAY_HELPER1(tc, int8_n, abs, s);
    }

    // Vectors with 16-bit integer elements
    {
        uint16_n s[] = {
            (uint16_n) make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            (uint16_n) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            (uint16_n) make_uint(0x0000, 0x0001, 0x0002, 0x0003),
            (uint16_n) make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            (uint16_n) make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),

            (uint16_n) make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            (uint16_n) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            (uint16_n) make_uint(0x0000, 0x0001, 0x0002, 0x0003),
            (uint16_n) make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            (uint16_n) make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),
        };

        TEST_ALL_COMB_HELPER2(tc, int16_n, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, add_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, sub_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, mul_lo, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, mul_hi, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, min, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, max, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, avg, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int16_n, avg_trunc, s, 2);

        TEST_ALL_COMB_HELPER2(tc, uint16_n, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, add_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, sub_sat, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, mul_lo, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, mul_hi, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, min, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, max, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, avg, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint16_n, avg_trunc, s, 2);

        TEST_ALL_COMB_HELPER2_T(tc, int32<B/2>, int16_n, mull, s, 2);
        TEST_ALL_COMB_HELPER2_T(tc, uint32<B/2>, uint16_n, mull, s, 2);

        TEST_ARRAY_HELPER1(tc, int16_n, neg, s);
        TEST_ARRAY_HELPER1(tc, int16_n, abs, s);
    }

    // Vectors with 32-bit integer elements
    {
        uint32_n s[] = {
            (uint32_n) make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            (uint32_n) make_uint(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            (uint32_n) make_uint(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            (uint32_n) make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            (uint32_n) make_uint(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),

            (uint32_n) make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            (uint32_n) make_uint(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            (uint32_n) make_uint(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            (uint32_n) make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            (uint32_n) make_uint(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),
        };

        TEST_ALL_COMB_HELPER2(tc, int32_n, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32_n, sub, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32_n, min, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32_n, max, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32_n, avg, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int32_n, avg_trunc, s, 4);

        TEST_ALL_COMB_HELPER2(tc, uint32_n, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32_n, sub, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32_n, min, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32_n, max, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32_n, avg, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint32_n, avg_trunc, s, 4);

#if !(SIMDPP_USE_ALTIVEC)
        TEST_ALL_COMB_HELPER2_T(tc, uint64<B/4>, uint32_n, mull, s, 4);
        TEST_ALL_COMB_HELPER2_T(tc, uint32_n, uint32_n, mul_lo, s, 4);
#endif

        TEST_ARRAY_HELPER1(tc, int32_n, neg, s);
        TEST_ARRAY_HELPER1(tc, int32_n, abs, s);
    }

    // Vectors with 64-bit integer elements
    {
        uint64_n s[] = {
            (uint64_n) make_uint(0x1111111111111111, 0x2222222222222222),
            (uint64_n) make_uint(0x3333333333333333, 0x4444444444444444),
            (uint64_n) make_uint(0xcccccccccccccccc, 0xdddddddddddddddd),
            (uint64_n) make_uint(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            (uint64_n) make_uint(0x0000000000000000, 0x0000000000000001),

            (uint64_n) make_uint(0x0000000000000002, 0x0000000000000003),
            (uint64_n) make_uint(0xfffffffffffffffc, 0xfffffffffffffffd),
            (uint64_n) make_uint(0xfffffffffffffffe, 0xffffffffffffffff),
            (uint64_n) make_uint(0x7ffffffffffffffe, 0x7fffffffffffffff),
            (uint64_n) make_uint(0x8000000000000000, 0x8000000000000001),

            (uint64_n) make_uint(0x1111111111111111, 0x2222222222222222),
            (uint64_n) make_uint(0x3333333333333333, 0x4444444444444444),
            (uint64_n) make_uint(0xcccccccccccccccc, 0xdddddddddddddddd),
            (uint64_n) make_uint(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            (uint64_n) make_uint(0x0000000000000000, 0x0000000000000001),

            (uint64_n) make_uint(0x0000000000000002, 0x0000000000000003),
            (uint64_n) make_uint(0xfffffffffffffffc, 0xfffffffffffffffd),
            (uint64_n) make_uint(0xfffffffffffffffe, 0xffffffffffffffff),
            (uint64_n) make_uint(0x7ffffffffffffffe, 0x7fffffffffffffff),
            (uint64_n) make_uint(0x8000000000000000, 0x8000000000000001),
        };

        TEST_ALL_COMB_HELPER2(tc, int64_n, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int64_n, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint64_n, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint64_n, sub, s, 2);

        TEST_ARRAY_HELPER1(tc, int64_n, neg, s);
        TEST_ARRAY_HELPER1(tc, int64_n, abs, s);
    }
}

void test_math_int(TestResults& res)
{
    TestSuite& tc = NEW_TEST_SUITE(res, "math_int");
    test_math_int_n<16>(tc);
    test_math_int_n<32>(tc);

    using namespace simdpp;
    { // uint16
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

        TEST_ALL_COMB_HELPER2(tc, uint16x8, div_p<16>, s2, 2);

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
        TEST_ALL_COMB_HELPER2(tc, uint16x8, div_p<8>, s3, 2);

        uint16x8 s4[] = {
            (uint16<8>) make_uint(0x01, 0x02, 0x03, 0x04),
            (uint16<8>) make_uint(0x05, 0x06, 0x07, 0x08),
            (uint16<8>) make_uint(0x09, 0x0a, 0x0b, 0x0c),
            (uint16<8>) make_uint(0x0d, 0x0e, 0x0f, 0x0f),
        };
        TEST_ALL_COMB_HELPER2(tc, uint16x8, div_p<8>, s4, 2);
    }
    { // uint32
        // this one can't contain zeros
        // FIXME: no support for 32-byte vectors yet
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
        TEST_ALL_COMB_HELPER2(tc, uint8x16, div_p<8>, s2, 1);

        uint8x16 s3[] = {
            (uint8x16) make_uint(0x01, 0x02, 0x03, 0x04),
            (uint8x16) make_uint(0x05, 0x06, 0x07, 0x08),
            (uint8x16) make_uint(0x09, 0x0a, 0x0b, 0x0c),
            (uint8x16) make_uint(0x0d, 0x0e, 0x0f, 0x0f),
        };
        TEST_ALL_COMB_HELPER2(tc, uint8x16, div_p<4>, s3, 1);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
