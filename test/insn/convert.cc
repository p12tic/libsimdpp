/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned B>
void test_convert_n(TestSuite& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_n = uint16<B/2>;
    using  int16_n = int16<B/2>;
    //using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
    using uint32_n = uint32<B/4>;
    using  int32_n = int32<B/4>;
    //using uint32_2n = uint32<B/2>;
    using  int32_2n = int32<B/2>;
    //using uint64_n = uint64<B/8>;
    //using  int64_n = int64<B/8>;
    //using uint64_2n = uint64<B/4>;
    using  int64_2n = int64<B/4>;
    using float32_n =  float32<B/4>;
    //using float32_2n = float32<B/2>;
    //using float64_n =  float64<B/8>;
    using float64_2n = float64<B/4>;

    //int8
    {
    int8_n s[] = {
        (uint8_n) make_uint(0x00, 0x11, 0x22, 0x33),
        (uint8_n) make_uint(0xcc, 0xdd, 0xee, 0xff),
    };
    TEST_ARRAY_HELPER1_T(ts, int16_2n,  int8_n, to_int16, s);
    TEST_ARRAY_HELPER1_T(ts, int16_2n, uint8_n, to_int16, s);
    }

    //int16
    {
    int16_n s[] = {
        (uint16_n) make_uint(0x0000, 0x1111, 0x2222, 0x3333),
        (uint16_n) make_uint(0xcccc, 0xdddd, 0xeeee, 0xffff),
    };
    TEST_ARRAY_HELPER1_T(ts, int32_2n,  int16_n, to_int32, s);
    TEST_ARRAY_HELPER1_T(ts, int32_2n, uint16_n, to_int32, s);
    }

    //int32
    {
    int32_n s[] = {
        (int32_n) make_uint(0x00000000, 0x11111111),
        (int32_n) make_uint(0x22222222, 0x33333333),
        (int32_n) make_uint(0xcccccccc, 0xeeeeeeee),
        (int32_n) make_uint(0xdddddddd, 0xffffffff),
    };
    TEST_ARRAY_HELPER1_T(ts, int64_2n,  int32_n, to_int64, s);
    TEST_ARRAY_HELPER1_T(ts, int64_2n, uint32_n, to_int64, s);

    int32_n sf[] = {
        (int32_n) make_uint(1, 100),
        (int32_n) make_uint(-1, -100),
        (int32_n) make_uint(0, -15),
        (int32_n) make_uint(63100000, 63100001),
        (int32_n) make_uint(63100002, 63100003),
        (int32_n) make_uint(-63100000, -63100001),
        (int32_n) make_uint(-63100002, -63100003),
    };

    ts.set_precision(1);
    set_round_to_zero(); // set consistent mode on SSE2
    TEST_ARRAY_HELPER1_T(ts, float32_n,  int32_n, to_float32, sf);
    TEST_ARRAY_HELPER1_T(ts, float64_2n, int32_n, to_float64, sf);
    set_round_to_nearest();
    ts.unset_precision();
    }

    //float32
    {
    float32_n sf[] = {
        (float32_n) make_float(1.0, 100.0),
        (float32_n) make_float(-1.0, -100.0),
        (float32_n) make_float(0.0, -15.0),
        (float32_n) make_float(1.0, 1.1),
        (float32_n) make_float(-1.0, -1.1),
        (float32_n) make_float(63100000.0, 63100000.0),
        (float32_n) make_float(63100002.0, 63100003.0),
        (float32_n) make_float(-63100000.0, -63100001.0),
        (float32_n) make_float(-63100002.0, -63100003.0),
    };

    TEST_ARRAY_HELPER1_T(ts, int32_n, float32_n, to_int32, sf);
    }

    //float64
    {
    float64_2n sf[] = {
        (float64_2n) make_float(1.0, 100.0),
        (float64_2n) make_float(-1.0, -100.0),
        (float64_2n) make_float(0.0, -15.0),
        (float64_2n) make_float(1.0, 1.1),
        (float64_2n) make_float(-1.0, -1.1),
        (float64_2n) make_float(63100000.0, 63100000.0),
        (float64_2n) make_float(63100002.0, 63100003.0),
        (float64_2n) make_float(-63100000.0, -63100001.0),
        (float64_2n) make_float(-63100002.0, -63100003.0),
    };

    TEST_ARRAY_HELPER1_T(ts, int32_n, float64_2n, to_int32, sf);
    }
}

void test_convert(TestResults& res)
{
    TestSuite& ts = NEW_TEST_SUITE(res, "convert");
    test_convert_n<16>(ts);
    test_convert_n<32>(ts);
    test_convert_n<64>(ts);
}

} // namespace SIMDPP_ARCH_NAMESPACE
