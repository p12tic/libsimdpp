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
void test_math_int8_n(TestResultsSet& tc)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using int8_n = int8<B>;

    TestData<uint8_n> s;
    s.add(make_uint(0x11, 0x22, 0x33, 0x44));
    s.add(make_uint(0xcc, 0xdd, 0xee, 0xff));
    s.add(make_uint(0x00, 0x01, 0x02, 0x03));
    s.add(make_uint(0xfc, 0xfd, 0xfe, 0xff));
    s.add(make_uint(0x7e, 0x7f, 0x80, 0x81));

    s.add(make_uint(0));
    s.add(make_uint(0xff));
    s.add(make_uint(0x7f));
    s.add(make_uint(0x80));
    s.add(make_uint(0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00));

    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, add_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, sub_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, avg, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int8_n, avg_trunc, s);

    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, add_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, sub_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, avg, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint8_n, avg_trunc, s);

    TEST_PUSH_ARRAY_OP1(tc, int8_n, neg, s);
    TEST_PUSH_ARRAY_OP1(tc, int8_n, abs, s);

    TEST_PUSH_ALL_COMB_OP1_T(tc, uint16_t, uint8_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int16_t, int8_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint8_t, uint8_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int8_t, int8_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint8_t, uint8_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int8_t, int8_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint8_t, uint8_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int8_t, int8_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint8_t, uint8_n, reduce_max, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int8_t, int8_n, reduce_max, s);
}

template<unsigned B>
void test_math_int16_n(TestResultsSet& tc)
{
    using namespace simdpp;

    using uint16_n = uint16<B/2>;
    using int16_n = int16<B/2>;

    TestData<uint16_n> s;
    s.add(make_uint(0x1111, 0x2222, 0x3333, 0x4444));
    s.add(make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff));
    s.add(make_uint(0x0000, 0x0001, 0x0002, 0x0003));
    s.add(make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff));
    s.add(make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001));

    s.add(make_uint(0));
    s.add(make_uint(0xffff));
    s.add(make_uint(0x7fff));
    s.add(make_uint(0x8000));
    s.add(make_uint(0x5a6b, 0, 0, 0, 0, 0, 0, 0));

    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, add_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, sub_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, mul_lo, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, mul_hi, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, avg, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int16_n, avg_trunc, s);

    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, add_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, sub_sat, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, mul_lo, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, mul_hi, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, avg, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint16_n, avg_trunc, s);

    TEST_PUSH_ALL_COMB_OP2_T(tc, int32<B/2>, int16_n, mull, s);
    TEST_PUSH_ALL_COMB_OP2_T(tc, uint32<B/2>, uint16_n, mull, s);

    TEST_PUSH_ARRAY_OP1(tc, int16_n, neg, s);
    TEST_PUSH_ARRAY_OP1(tc, int16_n, abs, s);

    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint16_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int16_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint16_n, reduce_mul, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int16_n, reduce_mul, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint16_t, uint16_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int16_t, int16_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint16_t, uint16_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int16_t, int16_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint16_t, uint16_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int16_t, int16_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint16_t, uint16_n, reduce_max, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int16_t, int16_n, reduce_max, s);
}

template<unsigned B>
void test_math_int32_n(TestResultsSet& tc)
{
    using namespace simdpp;

    using uint32_n = uint32<B/4>;
    using int32_n = int32<B/4>;

    TestData<uint32_n> s;
    s.add(make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444));
    s.add(make_uint(0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff));
    s.add(make_uint(0x00000000, 0x00000001, 0x00000002, 0x00000003));
    s.add(make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff));
    s.add(make_uint(0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001));

    s.add(make_uint(0));
    s.add(make_uint(0xffffffff));
    s.add(make_uint(0x7fffffff));
    s.add(make_uint(0x80000000));
    s.add(make_uint(0x5a6b7c8d, 0, 0, 0, 0, 0, 0, 0));

    TEST_PUSH_ALL_COMB_OP2(tc, int32_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int32_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int32_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int32_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int32_n, avg, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int32_n, avg_trunc, s);

#if SIMDPP_USE_NEON || SIMDPP_USE_VSX_207 || SIMDPP_USE_MSA
    TEST_PUSH_ALL_COMB_OP2_T(tc, int64<B/4>, int32_n, mull, s);
#endif

    TEST_PUSH_ALL_COMB_OP2(tc, uint32_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint32_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint32_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint32_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint32_n, avg, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint32_n, avg_trunc, s);

    TEST_PUSH_ALL_COMB_OP2_T(tc, uint64<B/4>, uint32_n, mull, s);
    TEST_PUSH_ALL_COMB_OP2_T(tc, uint32_n, uint32_n, mul_lo, s);

    TEST_PUSH_ARRAY_OP1(tc, int32_n, neg, s);
    TEST_PUSH_ARRAY_OP1(tc, int32_n, abs, s);

    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint32_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int32_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint32_n, reduce_mul, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int32_n, reduce_mul, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint32_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int32_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint32_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int32_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint32_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int32_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint32_t, uint32_n, reduce_max, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int32_t, int32_n, reduce_max, s);
}

template<unsigned B>
void test_math_int64_n(TestResultsSet& tc)
{
    using namespace simdpp;

    using uint64_n = uint64<B/8>;
    using int64_n = int64<B/8>;

    TestData<uint64_n> s;
    s.add(make_uint(0x1111111111111111, 0x2222222222222222));
    s.add(make_uint(0x3333333333333333, 0x4444444444444444));
    s.add(make_uint(0xcccccccccccccccc, 0xdddddddddddddddd));
    s.add(make_uint(0xeeeeeeeeeeeeeeee, 0xffffffffffffffff));
    s.add(make_uint(0x0000000000000000, 0x0000000000000001));

    s.add(make_uint(0x0000000000000002, 0x0000000000000003));
    s.add(make_uint(0xfffffffffffffffc, 0xfffffffffffffffd));
    s.add(make_uint(0xfffffffffffffffe, 0xffffffffffffffff));
    s.add(make_uint(0x7ffffffffffffffe, 0x7fffffffffffffff));
    s.add(make_uint(0x8000000000000000, 0x8000000000000001));

    s.add(make_uint(0));
    s.add(make_uint(0xffffffffffffffff));
    s.add(make_uint(0x7fffffffffffffff));
    s.add(make_uint(0x8000000000000000));
    s.add(make_uint(0x5a6b7c8da5b6c7d8, 0, 0, 0, 0, 0, 0, 0));

    TEST_PUSH_ALL_COMB_OP2(tc, int64_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int64_n, sub, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint64_n, add, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint64_n, sub, s);

#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64 || SIMDPP_USE_ALTIVEC
    TEST_PUSH_ALL_COMB_OP2(tc, int64_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, int64_n, max, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint64_n, min, s);
    TEST_PUSH_ALL_COMB_OP2(tc, uint64_n, max, s);
#endif

    TEST_PUSH_ARRAY_OP1(tc, int64_n, neg, s);
    TEST_PUSH_ARRAY_OP1(tc, int64_n, abs, s);

    TEST_PUSH_ALL_COMB_OP1_T(tc, uint64_t, uint64_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int64_t, int64_n, reduce_add, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint64_t, uint64_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int64_t, int64_n, reduce_or, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint64_t, uint64_n, reduce_and, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int64_t, int64_n, reduce_and, s);
#if SIMDPP_USE_NULL || SIMDPP_USE_AVX2 || SIMDPP_USE_NEON64 || SIMDPP_USE_ALTIVEC
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint64_t, uint64_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int64_t, int64_n, reduce_min, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, uint64_t, uint64_n, reduce_max, s);
    TEST_PUSH_ALL_COMB_OP1_T(tc, int64_t, int64_n, reduce_max, s);
#endif
}

void test_math_int(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("math_int");
    test_math_int8_n<16>(tc);
    test_math_int16_n<16>(tc);
    test_math_int32_n<16>(tc);
    test_math_int64_n<16>(tc);
    test_math_int8_n<32>(tc);
    test_math_int16_n<32>(tc);
    test_math_int32_n<32>(tc);
    test_math_int64_n<32>(tc);
    test_math_int8_n<64>(tc);
    test_math_int16_n<64>(tc);
    test_math_int32_n<64>(tc);
    test_math_int64_n<64>(tc);

    using namespace simdpp;
    { // uint16
        // this one can't contain zeros
        // NOTE: no support for 32-byte vectors yet
        TestData<uint16x8> s2;
        s2.add(make_uint(0x1111, 0x2222, 0x3333, 0x4444));
        s2.add(make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff));
        s2.add(make_uint(0x0510, 0x0001, 0x0002, 0x0003));
        s2.add(make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff));
        s2.add(make_uint(0x7ffe, 0x7fff, 0x8000, 0x8001));

        TEST_PUSH_ALL_COMB_OP2(tc, uint16x8, div_p<16>, s2);

        TestData<uint16x8> s3;
        s3.add(make_uint(0x01, 0x02, 0x03, 0x04));
        s3.add(make_uint(0x07, 0x0a, 0x0d, 0x12));
        s3.add(make_uint(0x13, 0x15, 0x1d, 0x22));
        s3.add(make_uint(0x27, 0x34, 0x46, 0x68));
        s3.add(make_uint(0x7e, 0x7f, 0x80, 0x81));

        s3.add(make_uint(0x91, 0x9a, 0xa1, 0xa4));
        s3.add(make_uint(0xa6, 0xaa, 0xb2, 0xb7));
        s3.add(make_uint(0xb8, 0xbf, 0xc1, 0xc3));
        s3.add(make_uint(0xc6, 0xce, 0xd2, 0xd5));
        s3.add(make_uint(0xda, 0xf2, 0xfa, 0xff));

        TEST_PUSH_ALL_COMB_OP2(tc, uint16x8, div_p<8>, s3);

        TestData<uint16x8> s4;
        s4.add(make_uint(0x01, 0x02, 0x03, 0x04));
        s4.add(make_uint(0x05, 0x06, 0x07, 0x08));
        s4.add(make_uint(0x09, 0x0a, 0x0b, 0x0c));
        s4.add(make_uint(0x0d, 0x0e, 0x0f, 0x0f));

        TEST_PUSH_ALL_COMB_OP2(tc, uint16x8, div_p<8>, s4);
    }
    { // uint32
        // this one can't contain zeros
        // FIXME: no support for 32-byte vectors yet
        TestData<uint8x16> s2;
        s2.add(make_uint(0x01, 0x02, 0x03, 0x04));
        s2.add(make_uint(0x07, 0x0a, 0x0d, 0x12));
        s2.add(make_uint(0x13, 0x15, 0x1d, 0x22));
        s2.add(make_uint(0x27, 0x34, 0x46, 0x68));
        s2.add(make_uint(0x7e, 0x7f, 0x80, 0x81));

        s2.add(make_uint(0x91, 0x9a, 0xa1, 0xa4));
        s2.add(make_uint(0xa6, 0xaa, 0xb2, 0xb7));
        s2.add(make_uint(0xb8, 0xbf, 0xc1, 0xc3));
        s2.add(make_uint(0xc6, 0xce, 0xd2, 0xd5));
        s2.add(make_uint(0xda, 0xf2, 0xfa, 0xff));

        TEST_PUSH_ALL_COMB_OP2(tc, uint8x16, div_p<8>, s2);

        TestData<uint8x16> s3;
        s3.add(make_uint(0x01, 0x02, 0x03, 0x04));
        s3.add(make_uint(0x05, 0x06, 0x07, 0x08));
        s3.add(make_uint(0x09, 0x0a, 0x0b, 0x0c));
        s3.add(make_uint(0x0d, 0x0e, 0x0f, 0x0f));

        TEST_PUSH_ALL_COMB_OP2(tc, uint8x16, div_p<4>, s3);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
