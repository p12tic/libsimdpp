/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned B>
void test_construct_n(TestResultsSet& tc)
{
    using namespace simdpp;

    Vectors<B,2> v;

    using uint8_n = uint8<B>;
    using int8_n = int8<B>;
    using uint16_n = uint16<B/2>;
    using int16_n = int16<B/2>;
    using uint32_n = uint32<B/4>;
    using int32_n = int32<B/4>;
    using uint64_n = uint64<B/8>;
    using int64_n = int64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    // 16-byte vectors
    TEST_PUSH(tc,uint8_n,load_splat(v.pu8+6));
    TEST_PUSH(tc,uint8_n,splat(0x10));
    TEST_PUSH(tc,uint8_n,make_uint(0x10));
    TEST_PUSH(tc,uint8_n,make_uint(0x10, 0x11));
    TEST_PUSH(tc,uint8_n,make_uint(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,uint8_n,make_uint(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,uint8_n,make_uint(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                    0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,int8_n,load_splat(v.pi8+2));
    TEST_PUSH(tc,int8_n,splat(0x10));
    TEST_PUSH(tc,int8_n,make_int(0x10));
    TEST_PUSH(tc,int8_n,make_int(0x10, 0x11));
    TEST_PUSH(tc,int8_n,make_int(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,int8_n,make_int(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,int8_n,make_int(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                  0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,uint16_n,load_splat(v.pu16+6));
    TEST_PUSH(tc,uint16_n,splat(0x1010));
    TEST_PUSH(tc,uint16_n,make_uint(0x1010));
    TEST_PUSH(tc,uint16_n,make_uint(0x1010, 0x1111));
    TEST_PUSH(tc,uint16_n,make_uint(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,uint16_n,make_uint(0x1010, 0x1111, 0x1212, 0x1313,
                                    0x1414, 0x1515, 0x1616, 0x1717));

    TEST_PUSH(tc,int16_n,load_splat(v.pi16+2));
    TEST_PUSH(tc,int16_n,splat(0x1010));
    TEST_PUSH(tc,int16_n,make_int(0x1010));
    TEST_PUSH(tc,int16_n,make_int(0x1010, 0x1111));
    TEST_PUSH(tc,int16_n,make_int(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,int16_n,make_int(0x1010, 0x1111, 0x1212, 0x1313,
                                  0x1414, 0x1515, 0x1616, 0x1717));

    TEST_PUSH(tc,uint32_n,load_splat(v.pu32+0));
    TEST_PUSH(tc,uint32_n,splat(0x10101010));
    TEST_PUSH(tc,uint32_n,make_uint(0x10101010));
    TEST_PUSH(tc,uint32_n,make_uint(0x10101010, 0x11111111));
    TEST_PUSH(tc,uint32_n,make_uint(0x10101010, 0x11111111, 0x12121212, 0x13131313));
    TEST_PUSH(tc,uint32_n,make_uint(0x10101010, 0x11111111, 0x12121212, 0x13131313,
                                    0x14141414, 0x15151515, 0x16161616, 0x17171717));

    TEST_PUSH(tc,int32_n,load_splat(v.pi32+2));
    TEST_PUSH(tc,int32_n,splat(0x10101010));
    TEST_PUSH(tc,int32_n,make_int(0x10101010));
    TEST_PUSH(tc,int32_n,make_int(0x10101010, 0x11111111));
    TEST_PUSH(tc,int32_n,make_int(0x10101010, 0x11111111, 0x12121212, 0x13131313));
    TEST_PUSH(tc,int32_n,make_int(0x10101010, 0x11111111, 0x12121212, 0x13131313,
                                  0x14141414, 0x15151515, 0x16161616, 0x17171717));

    TEST_PUSH(tc,uint64_n,load_splat(v.pu64+0));
    TEST_PUSH(tc,uint64_n,splat(0x1010101010101010));
    TEST_PUSH(tc,uint64_n,make_uint(0x1010101010101010));
    TEST_PUSH(tc,uint64_n,make_uint(0x1010101010101010, 0x1111111111111111));
    TEST_PUSH(tc,uint64_n,make_uint(0x1010101010101010, 0x1111111111111111,
                                    0x1212121212121212, 0x1313131313131313));

    TEST_PUSH(tc,int64_n,load_splat(v.pi64+1));
    TEST_PUSH(tc,int64_n,splat(0x1010101010101010));
    TEST_PUSH(tc,int64_n,make_int(0x1010101010101010));
    TEST_PUSH(tc,int64_n,make_int(0x1010101010101010, 0x1111111111111111));
    TEST_PUSH(tc,int64_n,make_int(0x1010101010101010, 0x1111111111111111,
                                  0x1212121212121212, 0x1313131313131313));

    TEST_PUSH(tc,float32_n,load_splat(v.pf32+0));
    TEST_PUSH(tc,float32_n,splat(1.0101010f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f, 1.1111111f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f,
                                      1.4141414f, 1.5151515f, 1.6161616f, 1.7171717f));

    TEST_PUSH(tc,float64_n,load_splat(v.pf64+0));
    TEST_PUSH(tc,float64_n,splat(1.010101010101010));
    TEST_PUSH(tc,float64_n,make_float(1.010101010101010));
    TEST_PUSH(tc,float64_n,make_float(1.010101010101010, 1.111111111111111));
    TEST_PUSH(tc,float64_n,make_float(1.010101010101010, 1.111111111111111,
                                      1.212121212121212, 1.131313131313131));
}

void test_construct(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("construct");
    test_construct_n<16>(tc);
    test_construct_n<32>(tc);
    test_construct_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
