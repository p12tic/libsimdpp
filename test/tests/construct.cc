/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

void test_construct(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "construct");

    using namespace simdpp;

    Vectors<32*2> v;

    // 16-byte vectors
    TEST_PUSH(tc,uint8x16,load_splat(v.pu8+6));
    TEST_PUSH(tc,uint8x16,splat(0x10));
    TEST_PUSH(tc,uint8x16,make_uint(0x10));
    TEST_PUSH(tc,uint8x16,make_uint(0x10, 0x11));
    TEST_PUSH(tc,uint8x16,make_uint(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,uint8x16,make_uint(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,uint8x16,make_uint(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                    0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,int8x16,load_splat(v.pi8+2));
    TEST_PUSH(tc,int8x16,splat(0x10));
    TEST_PUSH(tc,int8x16,make_int(0x10));
    TEST_PUSH(tc,int8x16,make_int(0x10, 0x11));
    TEST_PUSH(tc,int8x16,make_int(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,int8x16,make_int(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,int8x16,make_int(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                  0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,uint16x8,load_splat(v.pu16+6));
    TEST_PUSH(tc,uint16x8,splat(0x1010));
    TEST_PUSH(tc,uint16x8,make_uint(0x1010));
    TEST_PUSH(tc,uint16x8,make_uint(0x1010, 0x1111));
    TEST_PUSH(tc,uint16x8,make_uint(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,uint16x8,make_uint(0x1010, 0x1111, 0x1212, 0x1313,
                                    0x1414, 0x1515, 0x1616, 0x1717));

    TEST_PUSH(tc,int16x8,load_splat(v.pi16+2));
    TEST_PUSH(tc,int16x8,splat(0x1010));
    TEST_PUSH(tc,int16x8,make_int(0x1010));
    TEST_PUSH(tc,int16x8,make_int(0x1010, 0x1111));
    TEST_PUSH(tc,int16x8,make_int(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,int16x8,make_int(0x1010, 0x1111, 0x1212, 0x1313,
                                  0x1414, 0x1515, 0x1616, 0x1717));

    TEST_PUSH(tc,uint32x4,load_splat(v.pu32+0));
    TEST_PUSH(tc,uint32x4,splat(0x10101010));
    TEST_PUSH(tc,uint32x4,make_uint(0x10101010));
    TEST_PUSH(tc,uint32x4,make_uint(0x10101010, 0x11111111));
    TEST_PUSH(tc,uint32x4,make_uint(0x10101010, 0x11111111, 0x12121212, 0x13131313));

    TEST_PUSH(tc,int32x4,load_splat(v.pi32+2));
    TEST_PUSH(tc,int32x4,splat(0x10101010));
    TEST_PUSH(tc,int32x4,make_int(0x10101010));
    TEST_PUSH(tc,int32x4,make_int(0x10101010, 0x11111111));
    TEST_PUSH(tc,int32x4,make_int(0x10101010, 0x11111111, 0x12121212, 0x13131313));

    TEST_PUSH(tc,uint64x2,load_splat(v.pu64+0));
    TEST_PUSH(tc,uint64x2,splat(0x1010101010101010));
    TEST_PUSH(tc,uint64x2,make_uint(0x1010101010101010));
    TEST_PUSH(tc,uint64x2,make_uint(0x1010101010101010, 0x1111111111111111));

    TEST_PUSH(tc,int64x2,load_splat(v.pi64+1));
    TEST_PUSH(tc,int64x2,splat(0x1010101010101010));
    TEST_PUSH(tc,int64x2,make_int(0x1010101010101010));
    TEST_PUSH(tc,int64x2,make_int(0x1010101010101010, 0x1111111111111111));

    TEST_PUSH(tc,float32x4,load_splat(v.pf32+0));
    TEST_PUSH(tc,float32x4,splat(1.0101010f));
    TEST_PUSH(tc,float32x4,make_float(1.0101010f));
    TEST_PUSH(tc,float32x4,make_float(1.0101010f, 1.1111111f));
    TEST_PUSH(tc,float32x4,make_float(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f));

    TEST_PUSH(tc,float64x2,load_splat(v.pf64+0));
    TEST_PUSH(tc,float64x2,splat(1.010101010101010));
    TEST_PUSH(tc,float64x2,make_float(1.010101010101010));
    TEST_PUSH(tc,float64x2,make_float(1.010101010101010, 1.111111111111111));

    // 32-byte vectors
    TEST_PUSH(tc,uint8x32,load_splat(v.pu8+6));
    TEST_PUSH(tc,uint8x32,splat(0x10));
    TEST_PUSH(tc,uint8x32,make_uint(0x10));
    TEST_PUSH(tc,uint8x32,make_uint(0x10, 0x11));
    TEST_PUSH(tc,uint8x32,make_uint(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,uint8x32,make_uint(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,uint8x32,make_uint(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                    0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,int8x32,load_splat(v.pi8+2));
    TEST_PUSH(tc,int8x32,splat(0x10));
    TEST_PUSH(tc,int8x32,make_int(0x10));
    TEST_PUSH(tc,int8x32,make_int(0x10, 0x11));
    TEST_PUSH(tc,int8x32,make_int(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,int8x32,make_int(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,int8x32,make_int(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                  0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,uint16x16,load_splat(v.pu16+6));
    TEST_PUSH(tc,uint16x16,splat(0x1010));
    TEST_PUSH(tc,uint16x16,make_uint(0x1010));
    TEST_PUSH(tc,uint16x16,make_uint(0x1010, 0x1111));
    TEST_PUSH(tc,uint16x16,make_uint(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,uint16x16,make_uint(0x1010, 0x1111, 0x1212, 0x1313,
                                     0x1414, 0x1515, 0x1616, 0x1717));
    TEST_PUSH(tc,uint16x16,make_uint(0x1010, 0x1111, 0x1212, 0x1313,
                                     0x1414, 0x1515, 0x1616, 0x1717,
                                     0x1818, 0x1919, 0x2020, 0x2121,
                                     0x2222, 0x2323, 0x2424, 0x2525));

    TEST_PUSH(tc,int16x16,load_splat(v.pi16+2));
    TEST_PUSH(tc,int16x16,splat(0x1010));
    TEST_PUSH(tc,int16x16,make_int(0x1010));
    TEST_PUSH(tc,int16x16,make_int(0x1010, 0x1111));
    TEST_PUSH(tc,int16x16,make_int(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,int16x16,make_int(0x1010, 0x1111, 0x1212, 0x1313,
                                   0x1414, 0x1515, 0x1616, 0x1717));
    TEST_PUSH(tc,int16x16,make_int(0x1010, 0x1111, 0x1212, 0x1313,
                                   0x1414, 0x1515, 0x1616, 0x1717,
                                   0x1818, 0x1919, 0x2020, 0x2121,
                                   0x2222, 0x2323, 0x2424, 0x2525));

    TEST_PUSH(tc,uint32x8,load_splat(v.pu32+0));
    TEST_PUSH(tc,uint32x8,splat(0x10101010));
    TEST_PUSH(tc,uint32x8,make_uint(0x10101010));
    TEST_PUSH(tc,uint32x8,make_uint(0x10101010, 0x11111111));
    TEST_PUSH(tc,uint32x8,make_uint(0x10101010, 0x11111111, 0x12121212, 0x13131313));
    TEST_PUSH(tc,uint32x8,make_uint(0x10101010, 0x11111111, 0x12121212, 0x13131313,
                                    0x14141414, 0x15151515, 0x16161616, 0x17171717));

    TEST_PUSH(tc,int32x8,load_splat(v.pi32+2));
    TEST_PUSH(tc,int32x8,splat(0x10101010));
    TEST_PUSH(tc,int32x8,make_int(0x10101010));
    TEST_PUSH(tc,int32x8,make_int(0x10101010, 0x11111111));
    TEST_PUSH(tc,int32x8,make_int(0x10101010, 0x11111111, 0x12121212, 0x13131313));
    TEST_PUSH(tc,int32x8,make_int(0x10101010, 0x11111111, 0x12121212, 0x13131313,
                                  0x14141414, 0x15151515, 0x16161616, 0x17171717));

    TEST_PUSH(tc,uint64x4,load_splat(v.pu64+0));
    TEST_PUSH(tc,uint64x4,splat(0x1010101010101010));
    TEST_PUSH(tc,uint64x4,make_uint(0x1010101010101010));
    TEST_PUSH(tc,uint64x4,make_uint(0x1010101010101010, 0x1111111111111111,
                                    0x1212121212121212, 0x1313131313131313));

    TEST_PUSH(tc,int64x4,load_splat(v.pi64+1));
    TEST_PUSH(tc,int64x4,splat(0x1010101010101010));
    TEST_PUSH(tc,int64x4,make_int(0x1010101010101010));
    TEST_PUSH(tc,int64x4,make_int(0x1010101010101010, 0x1111111111111111,
                                  0x1212121212121212, 0x1313131313131313));

    TEST_PUSH(tc,float32x8,load_splat(v.pf32+0));
    TEST_PUSH(tc,float32x8,splat(1.0101010f));
    TEST_PUSH(tc,float32x8,make_float(1.0101010f));
    TEST_PUSH(tc,float32x8,make_float(1.0101010f, 1.1111111f));
    TEST_PUSH(tc,float32x8,make_float(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f,
                                      1.1414141f, 1.1515151f, 1.1616161f, 1.1717171f));

    TEST_PUSH(tc,float64x4,load_splat(v.pf64+0));
    TEST_PUSH(tc,float64x4,splat(1.010101010101010));
    TEST_PUSH(tc,float64x4,make_float(1.010101010101010));
    TEST_PUSH(tc,float64x4,make_float(1.010101010101010, 1.111111111111111));
    TEST_PUSH(tc,float64x4,make_float(1.010101010101010, 1.111111111111111,
                                      1.121212121212121, 1.131313131313131));
}

} // namespace SIMDPP_ARCH_NAMESPACE
