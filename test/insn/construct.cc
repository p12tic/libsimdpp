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
void test_construct_n(TestSuite& tc)
{
    using namespace simdpp;

    Vectors<B,2> v;

    typedef uint8<B> uint8_n;
    typedef int8<B> int8_n;
    typedef uint16<B/2> uint16_n;
    typedef int16<B/2> int16_n;
    typedef uint32<B/4> uint32_n;
    typedef int32<B/4> int32_n;
    typedef uint64<B/8> uint64_n;
    typedef int64<B/8> int64_n;
    typedef float32<B/4> float32_n;
    typedef float64<B/8> float64_n;

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

    TEST_PUSH(tc,int32_n,load_splat(v.pi32+2));
    TEST_PUSH(tc,int32_n,splat(0x10101010));
    TEST_PUSH(tc,int32_n,make_int(0x10101010));
    TEST_PUSH(tc,int32_n,make_int(0x10101010, 0x11111111));
    TEST_PUSH(tc,int32_n,make_int(0x10101010, 0x11111111, 0x12121212, 0x13131313));

    TEST_PUSH(tc,uint64_n,load_splat(v.pu64+0));
    TEST_PUSH(tc,uint64_n,splat(0x1010101010101010));
    TEST_PUSH(tc,uint64_n,make_uint(0x1010101010101010));
    TEST_PUSH(tc,uint64_n,make_uint(0x1010101010101010, 0x1111111111111111));

    TEST_PUSH(tc,int64_n,load_splat(v.pi64+1));
    TEST_PUSH(tc,int64_n,splat(0x1010101010101010));
    TEST_PUSH(tc,int64_n,make_int(0x1010101010101010));
    TEST_PUSH(tc,int64_n,make_int(0x1010101010101010, 0x1111111111111111));

    TEST_PUSH(tc,float32_n,load_splat(v.pf32+0));
    TEST_PUSH(tc,float32_n,splat(1.0101010f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f, 1.1111111f));
    TEST_PUSH(tc,float32_n,make_float(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f));

    TEST_PUSH(tc,float64_n,load_splat(v.pf64+0));
    TEST_PUSH(tc,float64_n,splat(1.010101010101010));
    TEST_PUSH(tc,float64_n,make_float(1.010101010101010));
    TEST_PUSH(tc,float64_n,make_float(1.010101010101010, 1.111111111111111));
}

void test_construct(TestResults& res)
{
    TestSuite& tc = NEW_TEST_SUITE(res, "construct");
    test_construct_n<16>(tc);
    test_construct_n<32>(tc);
    test_construct_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
