/*  Copyright (C) 2011-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

static const uint64_t c_2_pow_24 = 16777216;
static const uint64_t c_2_pow_23 = c_2_pow_24 / 2;
static const uint64_t c_2_pow_25 = c_2_pow_24 * 2;
static const uint64_t c_2_pow_53 = 9007199254740992;
static const uint64_t c_2_pow_52 = c_2_pow_53 / 2;
static const uint64_t c_2_pow_54 = c_2_pow_53 * 2;

template<unsigned B>
void test_convert_int8_n(TestResultsSet& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
    using uint32_4n = uint32<B>;
    using  int32_4n = int32<B>;
    using uint64_8n = uint64<B>;
    using  int64_8n = int64<B>;
    using float32_4n = float32<B>;
    using float64_8n = float64<B>;

    TestData<int8_n> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0x11, 0x22, 0x33, 0x44));
    s.add(make_uint(0xbb, 0xcc, 0xdd, 0xee));
    s.add(make_uint(0xfc, 0xfd, 0xfe, 0xff));

    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,     int8_n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,    uint8_n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,     int8_n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,    uint8_n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,   int8_n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,  uint8_n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,   int8_n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,  uint8_n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,   int8_n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,  uint8_n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,   int8_n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,  uint8_n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n,  int8_n, to_float32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n, uint8_n, to_float32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,   int8_n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,  uint8_n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,   int8_n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,  uint8_n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n,  int8_n, to_float64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n, uint8_n, to_float64, s);
}

template<unsigned B>
void test_convert_int16_n(TestResultsSet& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
    using uint32_4n = uint32<B>;
    using  int32_4n = int32<B>;
    using uint64_8n = uint64<B>;
    using  int64_8n = int64<B>;
    using float32_4n = float32<B>;
    using float64_8n = float64<B>;

    TestData<int16_2n> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0x1111, 0x2222, 0x3333, 0x4444));
    s.add(make_uint(0xbbbb, 0xcccc, 0xdddd, 0xeeee));
    s.add(make_uint(0xfffc, 0xfffd, 0xfffe, 0xffff));

    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,     int16_2n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,    uint16_2n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,     int16_2n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,    uint16_2n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,   int16_2n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,  uint16_2n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,   int16_2n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,  uint16_2n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,   int16_2n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,  uint16_2n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,   int16_2n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,  uint16_2n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n,  int16_2n, to_float32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n, uint16_2n, to_float32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,   int16_2n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,  uint16_2n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,   int16_2n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,  uint16_2n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n,  int16_2n, to_float64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n, uint16_2n, to_float64, s);
}

template<unsigned B>
void test_convert_int32_n(TestResultsSet& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
    using uint32_4n = uint32<B>;
    using  int32_4n = int32<B>;
    using uint64_8n = uint64<B>;
    using  int64_8n = int64<B>;
    using float32_4n = float32<B>;
    using float64_8n = float64<B>;

    TestData<int32_4n> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0x11111111, 0x22222222, 0x33333333, 0x44444444));
    s.add(make_uint(0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee));
    s.add(make_uint(0xfffffffc, 0xfffffffd, 0xfffffffe, 0xffffffff));

    s.add(make_uint(1, 100));
    s.add(make_uint(-1, -100));
    s.add(make_uint(0, -15));
    s.add(make_uint(c_2_pow_23 - 1, c_2_pow_23));
    s.add(make_uint(c_2_pow_23 + 1, c_2_pow_23 + 2));
    s.add(make_uint(c_2_pow_24 - 1, c_2_pow_24));
    s.add(make_uint(c_2_pow_24 + 1, c_2_pow_24 + 2));
    s.add(make_uint(c_2_pow_25 - 1, c_2_pow_25));
    s.add(make_uint(c_2_pow_25 + 1, c_2_pow_25 + 2));
    s.add(make_int(-c_2_pow_23 + 1, -c_2_pow_23));
    s.add(make_int(-c_2_pow_23 - 1, -c_2_pow_23 - 2));
    s.add(make_int(-c_2_pow_24 + 1, -c_2_pow_24));
    s.add(make_int(-c_2_pow_24 - 1, -c_2_pow_24 - 2));
    s.add(make_int(-c_2_pow_25 + 1, -c_2_pow_25));
    s.add(make_int(-c_2_pow_25 - 1, -c_2_pow_25 - 2));

    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,     int32_4n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,    uint32_4n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,     int32_4n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,    uint32_4n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,   int32_4n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,  uint32_4n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,   int32_4n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,  uint32_4n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,   int32_4n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,  uint32_4n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,   int32_4n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,  uint32_4n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n,  int32_4n, to_float32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n, uint32_4n, to_float32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,   int32_4n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,  uint32_4n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,   int32_4n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,  uint32_4n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n,  int32_4n, to_float64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n, uint32_4n, to_float64, s);
}

template<unsigned B>
void test_convert_int64_n(TestResultsSet& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
    using uint32_4n = uint32<B>;
    using  int32_4n = int32<B>;
    using uint64_8n = uint64<B>;
    using  int64_8n = int64<B>;
#if SIMDPP_HAS_INT64_TO_FLOAT32_CONVERSION || SIMDPP_HAS_UINT64_TO_FLOAT32_CONVERSION
    using float32_4n = float32<B>;
#endif
#if SIMDPP_HAS_INT64_TO_FLOAT64_CONVERSION || SIMDPP_HAS_UINT64_TO_FLOAT64_CONVERSION
    using float64_8n = float64<B>;
#endif
    TestData<int64_8n> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0x1111111111111111, 0x2222222222222222,
                    0x3333333333333333, 0x4444444444444444));
    s.add(make_uint(0xbbbbbbbbbbbbbbbb, 0xcccccccccccccccc,
                    0xdddddddddddddddd, 0xeeeeeeeeeeeeeeee));
    s.add(make_uint(0xfffffffffffffffc, 0xfffffffffffffffd,
                    0xfffffffffffffffe, 0xffffffffffffffff));

    s.add(make_uint(1, 100));
    s.add(make_uint(-1, -100));
    s.add(make_uint(0, -15));
    s.add(make_uint(63100000, 63100001));
    s.add(make_uint(63100002, 63100003));
    s.add(make_uint(-63100000, -63100001));
    s.add(make_uint(-63100002, -63100003));

    s.add(make_uint(c_2_pow_24 - 1, c_2_pow_24));
    s.add(make_uint(c_2_pow_24 + 1, c_2_pow_24 + 2));
    s.add(make_uint(c_2_pow_52 - 1, c_2_pow_52));
    s.add(make_uint(c_2_pow_52 + 1, c_2_pow_52 + 2));
    s.add(make_uint(c_2_pow_53 - 1, c_2_pow_53));
    s.add(make_uint(c_2_pow_53 + 1, c_2_pow_53 + 2));
    s.add(make_uint(c_2_pow_54 - 1, c_2_pow_54));
    s.add(make_uint(c_2_pow_54 + 1, c_2_pow_54 + 2));
    s.add(make_int(-c_2_pow_24 + 1, -c_2_pow_24));
    s.add(make_int(-c_2_pow_24 - 1, -c_2_pow_24 - 2));
    s.add(make_int(-c_2_pow_52 + 1, -c_2_pow_52));
    s.add(make_int(-c_2_pow_52 - 1, -c_2_pow_52 - 2));
    s.add(make_int(-c_2_pow_53 + 1, -c_2_pow_53));
    s.add(make_int(-c_2_pow_53 - 1, -c_2_pow_53 - 2));
    s.add(make_int(-c_2_pow_54 + 1, -c_2_pow_54));
    s.add(make_int(-c_2_pow_54 - 1, -c_2_pow_54 - 2));

#if SIMDPP_X86
    // TODO: figure out how to handle rounding differences.
    ts.set_precision(1);
#endif

    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,     int64_8n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,    uint64_8n, to_int8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,     int64_8n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,    uint64_8n, to_uint8, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,   int64_8n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,  uint64_8n, to_int16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,   int64_8n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,  uint64_8n, to_uint16, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,   int64_8n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,  uint64_8n, to_int32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,   int64_8n, to_uint32, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,  uint64_8n, to_uint32, s);
#if SIMDPP_HAS_INT64_TO_FLOAT32_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n,  int64_8n, to_float32, s);
#endif
#if SIMDPP_HAS_UINT64_TO_FLOAT32_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n, uint64_8n, to_float32, s);
#endif
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,   int64_8n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,  uint64_8n, to_int64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,   int64_8n, to_uint64, s);
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,  uint64_8n, to_uint64, s);
#if SIMDPP_HAS_INT64_TO_FLOAT64_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n,  int64_8n, to_float64, s);
#endif
#if SIMDPP_HAS_UINT64_TO_FLOAT64_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n, uint64_8n, to_float64, s);
#endif

#if SIMDPP_X86
    ts.unset_precision();
#endif
}

template<unsigned B>
void test_convert_float32_n(TestResultsSet& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
    using uint32_4n = uint32<B>;
    using  int32_4n = int32<B>;
#if SIMDPP_HAS_FLOAT32_TO_INT64_CONVERSION
    using uint64_8n = uint64<B>;
#endif
#if SIMDPP_HAS_FLOAT32_TO_INT64_CONVERSION
    using  int64_8n = int64<B>;
#endif
    using float32_4n = float32<B>;
    using float64_8n = float64<B>;

    TestData<float32_4n> sp;
    sp.add(make_uint(0, 1, 2, 3));
    sp.add(make_float(1.0, 100.0));
    sp.add(make_float(0.0, 15.0));
    sp.add(make_float(1.0, 1.1));
    sp.add(make_uint(c_2_pow_23 - 1, c_2_pow_23));
    sp.add(make_uint(c_2_pow_23 + 1, c_2_pow_23 + 2));
    sp.add(make_uint(c_2_pow_24 - 1, c_2_pow_24));
    sp.add(make_uint(c_2_pow_24 + 1, c_2_pow_24 + 2));
    sp.add(make_uint(c_2_pow_25 - 1, c_2_pow_25));
    sp.add(make_uint(c_2_pow_25 + 1, c_2_pow_25 + 2));

    TestData<float32_4n> sn = sp;
    sn.add(make_float(-1.0, -100.0));
    sn.add(make_float(-0.0, -15.0));
    sn.add(make_float(-1.0, -1.1));
    sn.add(make_int(-c_2_pow_23 + 1, -c_2_pow_23));
    sn.add(make_int(-c_2_pow_23 - 1, -c_2_pow_23 - 2));
    sn.add(make_int(-c_2_pow_24 + 1, -c_2_pow_24));
    sn.add(make_int(-c_2_pow_24 - 1, -c_2_pow_24 - 2));
    sn.add(make_int(-c_2_pow_25 + 1, -c_2_pow_25));
    sn.add(make_int(-c_2_pow_25 - 1, -c_2_pow_25 - 2));
    // float -> integer overflows are undefined, we're not testing them

#if SIMDPP_X86
    // TODO: figure out how to handle rounding differences.
    ts.set_precision(1);
#endif

    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,     float32_4n, to_int8, sn);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,     float32_4n, to_uint8, sp);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,   float32_4n, to_int16, sn);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,   float32_4n, to_uint16, sp);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,   float32_4n, to_int32, sn);
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,   float32_4n, to_uint32, sp);
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n,  float32_4n, to_float32, sn);
#if SIMDPP_HAS_FLOAT32_TO_INT64_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,   float32_4n, to_int64, sn);
#endif
#if SIMDPP_HAS_FLOAT32_TO_UINT64_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,   float32_4n, to_uint64, sp);
#endif
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n,  float32_4n, to_float64, sp);

#if SIMDPP_X86
    ts.unset_precision();
#endif
}

template<unsigned B>
void test_convert_float64_n(TestResultsSet& ts)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using  int8_n = int8<B>;
    using uint16_2n = uint16<B>;
    using  int16_2n = int16<B>;
#if SIMDPP_HAS_FLOAT64_TO_UINT32_CONVERSION
    using uint32_4n = uint32<B>;
#endif
    using  int32_4n = int32<B>;
#if SIMDPP_HAS_FLOAT64_TO_UINT64_CONVERSION
    using uint64_8n = uint64<B>;
#endif
#if SIMDPP_HAS_FLOAT64_TO_INT64_CONVERSION
    using  int64_8n = int64<B>;
#endif
    using float32_4n = float32<B>;
    using float64_8n = float64<B>;

    TestData<float64_8n> sp;
    sp.add(make_uint(0, 1, 2, 3));
    sp.add(make_float(1.0, 100.0));
    sp.add(make_float(0.0, 15.0));
    sp.add(make_float(1.0, 1.1));
    sp.add(make_uint(c_2_pow_24 - 1, c_2_pow_24));
    sp.add(make_uint(c_2_pow_24 + 1, c_2_pow_24 + 2));

    TestData<float64_8n> sp64 = sp;
    sp64.add(make_uint(c_2_pow_52 - 1, c_2_pow_52));
    sp64.add(make_uint(c_2_pow_52 + 1, c_2_pow_52 + 2));
    sp64.add(make_uint(c_2_pow_53 - 1, c_2_pow_53));
    sp64.add(make_uint(c_2_pow_53 + 1, c_2_pow_53 + 2));
    sp64.add(make_uint(c_2_pow_54 - 1, c_2_pow_54));
    sp64.add(make_uint(c_2_pow_54 + 1, c_2_pow_54 + 2));

    TestData<float64_8n> sn = sp;
    sn.add(make_float(-1.0, -100.0));
    sn.add(make_float(-0.0, -15.0));
    sn.add(make_float(-1.0, -1.1));
    sn.add(make_int(-c_2_pow_24 + 1, -c_2_pow_24));
    sn.add(make_int(-c_2_pow_24 - 1, -c_2_pow_24 - 2));

    TestData<float64_8n> sn64 = sp;
    sn64.add(sn);
    sn64.add(make_int(-c_2_pow_52 + 1, -c_2_pow_52));
    sn64.add(make_int(-c_2_pow_52 - 1, -c_2_pow_52 - 2));
    sn64.add(make_int(-c_2_pow_53 + 1, -c_2_pow_53));
    sn64.add(make_int(-c_2_pow_53 - 1, -c_2_pow_53 - 2));
    sn64.add(make_int(-c_2_pow_54 + 1, -c_2_pow_54));
    sn64.add(make_int(-c_2_pow_54 - 1, -c_2_pow_54 - 2));
    // float -> integer overflows are undefined, we're not testing them

#if SIMDPP_X86
    ts.set_precision(1);
#endif

    TEST_PUSH_ARRAY_OP1_T(ts,  int8_n,     float64_8n, to_int8, sn);
    TEST_PUSH_ARRAY_OP1_T(ts, uint8_n,     float64_8n, to_uint8, sp);
    TEST_PUSH_ARRAY_OP1_T(ts,  int16_2n,   float64_8n, to_int16, sn);
    TEST_PUSH_ARRAY_OP1_T(ts, uint16_2n,   float64_8n, to_uint16, sp);
    TEST_PUSH_ARRAY_OP1_T(ts,  int32_4n,   float64_8n, to_int32, sn);
#if SIMDPP_HAS_FLOAT64_TO_UINT32_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, uint32_4n,   float64_8n, to_uint32, sp);
#endif
    TEST_PUSH_ARRAY_OP1_T(ts, float32_4n,  float64_8n, to_float32, sn);
#if SIMDPP_HAS_FLOAT64_TO_INT64_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts,  int64_8n,   float64_8n, to_int64, sn64);
#endif
#if SIMDPP_HAS_FLOAT64_TO_UINT64_CONVERSION
    TEST_PUSH_ARRAY_OP1_T(ts, uint64_8n,   float64_8n, to_uint64, sp64);
#endif
    TEST_PUSH_ARRAY_OP1_T(ts, float64_8n,  float64_8n, to_float64, sp);

#if SIMDPP_X86
    ts.unset_precision();
#endif
}

void test_convert(TestResults& res)
{
    TestResultsSet& ts = res.new_results_set("convert");
    test_convert_int8_n<16>(ts);
    test_convert_int16_n<16>(ts);
    test_convert_int32_n<16>(ts);
    test_convert_int64_n<16>(ts);
    test_convert_float32_n<16>(ts);
    test_convert_float64_n<16>(ts);
    test_convert_int8_n<32>(ts);
    test_convert_int16_n<32>(ts);
    test_convert_int32_n<32>(ts);
    test_convert_int64_n<32>(ts);
    test_convert_float32_n<32>(ts);
    test_convert_float64_n<32>(ts);
    test_convert_int8_n<64>(ts);
    test_convert_int16_n<64>(ts);
    test_convert_int32_n<64>(ts);
    test_convert_int64_n<64>(ts);
    test_convert_float32_n<64>(ts);
    test_convert_float64_n<64>(ts);
}

} // namespace SIMDPP_ARCH_NAMESPACE
