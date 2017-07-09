/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned B>
void test_math_int_n(TestResultsSet& tc)
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
        TestData<uint8_n> s(
            make_uint(0x11, 0x22, 0x33, 0x44),
            make_uint(0xcc, 0xdd, 0xee, 0xff),
            make_uint(0x00, 0x01, 0x02, 0x03),
            make_uint(0xfc, 0xfd, 0xfe, 0xff),
            make_uint(0x7e, 0x7f, 0x80, 0x81),

            make_uint(0),
            make_uint(0xff),
            make_uint(0x7f),
            make_uint(0x80),
            make_uint(0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        );

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

        TEST_ALL_COMB_HELPER1_T(tc, uint16_t, uint8_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int16_t, int8_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint8_t, uint8_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int8_t, int8_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint8_t, uint8_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int8_t, int8_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint8_t, uint8_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int8_t, int8_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint8_t, uint8_n, reduce_max, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int8_t, int8_n, reduce_max, s, 1);
    }

    // Vectors with 16-bit integer elements
    {
        TestData<uint16_n> s(
            make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            make_uint(0x0000, 0x0001, 0x0002, 0x0003),
            make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001),

            make_uint(0),
            make_uint(0xffff),
            make_uint(0x7fff),
            make_uint(0x8000),
            make_uint(0x5a6b, 0, 0, 0, 0, 0, 0, 0)
        );

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

        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint16_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int16_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint16_n, reduce_mul, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int16_n, reduce_mul, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint16_t, uint16_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int16_t, int16_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint16_t, uint16_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int16_t, int16_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint16_t, uint16_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int16_t, int16_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint16_t, uint16_n, reduce_max, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int16_t, int16_n, reduce_max, s, 1);
    }

    // Vectors with 32-bit integer elements
    {
        TestData<uint32_n> s(
            make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444),
            make_uint(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff),
            make_uint(0x00000000, 0x00000001, 0x00000002, 0x00000003),
            make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff),
            make_uint(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001),

            make_uint(0),
            make_uint(0xffffffff),
            make_uint(0x7fffffff),
            make_uint(0x80000000),
            make_uint(0x5a6b7c8d, 0, 0, 0, 0, 0, 0, 0)
        );

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

        TEST_ALL_COMB_HELPER2_T(tc, uint64<B/4>, uint32_n, mull, s, 4);
        tc.sync_archs();
#if !(SIMDPP_USE_ALTIVEC)
        TEST_ALL_COMB_HELPER2_T(tc, uint32_n, uint32_n, mul_lo, s, 4);
#endif
        tc.sync_archs();

        TEST_ARRAY_HELPER1(tc, int32_n, neg, s);
        TEST_ARRAY_HELPER1(tc, int32_n, abs, s);

        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint32_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int32_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint32_n, reduce_mul, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int32_n, reduce_mul, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint32_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int32_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint32_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int32_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint32_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int32_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint32_t, uint32_n, reduce_max, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int32_t, int32_n, reduce_max, s, 1);
    }

    // Vectors with 64-bit integer elements
    {
        TestData<uint64_n> s(
            make_uint(0x1111111111111111, 0x2222222222222222),
            make_uint(0x3333333333333333, 0x4444444444444444),
            make_uint(0xcccccccccccccccc, 0xdddddddddddddddd),
            make_uint(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff),
            make_uint(0x0000000000000000, 0x0000000000000001),

            make_uint(0x0000000000000002, 0x0000000000000003),
            make_uint(0xfffffffffffffffc, 0xfffffffffffffffd),
            make_uint(0xfffffffffffffffe, 0xffffffffffffffff),
            make_uint(0x7ffffffffffffffe, 0x7fffffffffffffff),
            make_uint(0x8000000000000000, 0x8000000000000001),

            make_uint(0),
            make_uint(0xffffffffffffffff),
            make_uint(0x7fffffffffffffff),
            make_uint(0x8000000000000000),
            make_uint(0x5a6b7c8da5b6c7d8, 0, 0, 0, 0, 0, 0, 0)
        );

        TEST_ALL_COMB_HELPER2(tc, int64_n, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, int64_n, sub, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint64_n, add, s, 2);
        TEST_ALL_COMB_HELPER2(tc, uint64_n, sub, s, 2);

        tc.sync_archs();
#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64 || SIMDPP_USE_ALTIVEC
        TEST_ALL_COMB_HELPER2(tc, int64_n, min, s, 4);
        TEST_ALL_COMB_HELPER2(tc, int64_n, max, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint64_n, min, s, 4);
        TEST_ALL_COMB_HELPER2(tc, uint64_n, max, s, 4);
#endif
        tc.sync_archs();

        TEST_ARRAY_HELPER1(tc, int64_n, neg, s);
        TEST_ARRAY_HELPER1(tc, int64_n, abs, s);

        TEST_ALL_COMB_HELPER1_T(tc, uint64_t, uint64_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int64_t, int64_n, reduce_add, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint64_t, uint64_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int64_t, int64_n, reduce_or, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint64_t, uint64_n, reduce_and, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int64_t, int64_n, reduce_and, s, 1);
        tc.sync_archs();
#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64 || SIMDPP_USE_ALTIVEC
        TEST_ALL_COMB_HELPER1_T(tc, uint64_t, uint64_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int64_t, int64_n, reduce_min, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, uint64_t, uint64_n, reduce_max, s, 1);
        TEST_ALL_COMB_HELPER1_T(tc, int64_t, int64_n, reduce_max, s, 1);
#endif
        tc.sync_archs();
    }
}

void test_math_int(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("math_int");
    test_math_int_n<16>(tc);
    test_math_int_n<32>(tc);
    test_math_int_n<64>(tc);

    using namespace simdpp;
    { // uint16
        // this one can't contain zeros
        // NOTE: no support for 32-byte vectors yet
        TestData<uint16x8> s2(
            make_uint(0x1111, 0x2222, 0x3333, 0x4444),
            make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
            make_uint(0x0510, 0x0001, 0x0002, 0x0003),
            make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff),
            make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001)
        );

        TEST_ALL_COMB_HELPER2(tc, uint16x8, div_p<16>, s2, 2);

        TestData<uint16x8> s3(
            make_uint(0x01, 0x02, 0x03, 0x04),
            make_uint(0x07, 0x0a, 0x0d, 0x12),
            make_uint(0x13, 0x15, 0x1d, 0x22),
            make_uint(0x27, 0x34, 0x46, 0x68),
            make_uint(0x7e, 0x7f, 0x80, 0x81),

            make_uint(0x91, 0x9a, 0xa1, 0xa4),
            make_uint(0xa6, 0xaa, 0xb2, 0xb7),
            make_uint(0xb8, 0xbf, 0xc1, 0xc3),
            make_uint(0xc6, 0xce, 0xd2, 0xd5),
            make_uint(0xda, 0xf2, 0xfa, 0xff)
        );
        TEST_ALL_COMB_HELPER2(tc, uint16x8, div_p<8>, s3, 2);

        TestData<uint16x8> s4(
            make_uint(0x01, 0x02, 0x03, 0x04),
            make_uint(0x05, 0x06, 0x07, 0x08),
            make_uint(0x09, 0x0a, 0x0b, 0x0c),
            make_uint(0x0d, 0x0e, 0x0f, 0x0f)
        );
        TEST_ALL_COMB_HELPER2(tc, uint16x8, div_p<8>, s4, 2);
    }
    { // uint32
        // this one can't contain zeros
        // FIXME: no support for 32-byte vectors yet
        TestData<uint8x16> s2(
            make_uint(0x01, 0x02, 0x03, 0x04),
            make_uint(0x07, 0x0a, 0x0d, 0x12),
            make_uint(0x13, 0x15, 0x1d, 0x22),
            make_uint(0x27, 0x34, 0x46, 0x68),
            make_uint(0x7e, 0x7f, 0x80, 0x81),

            make_uint(0x91, 0x9a, 0xa1, 0xa4),
            make_uint(0xa6, 0xaa, 0xb2, 0xb7),
            make_uint(0xb8, 0xbf, 0xc1, 0xc3),
            make_uint(0xc6, 0xce, 0xd2, 0xd5),
            make_uint(0xda, 0xf2, 0xfa, 0xff)
        );
        TEST_ALL_COMB_HELPER2(tc, uint8x16, div_p<8>, s2, 1);

        TestData<uint8x16> s3(
            make_uint(0x01, 0x02, 0x03, 0x04),
            make_uint(0x05, 0x06, 0x07, 0x08),
            make_uint(0x09, 0x0a, 0x0b, 0x0c),
            make_uint(0x0d, 0x0e, 0x0f, 0x0f)
        );
        TEST_ALL_COMB_HELPER2(tc, uint8x16, div_p<4>, s3, 1);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
