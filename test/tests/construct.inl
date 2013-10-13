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

#ifndef LIBSIMDPP_TEST_TESTS_CONSTRUCT_H
#define LIBSIMDPP_TEST_TESTS_CONSTRUCT_H

namespace SIMDPP_ARCH_NAMESPACE {

void test_construct(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "construct");

    using namespace simdpp;

    union {
        uint8_t u8[32];
        int8_t s8[32];
        uint16_t u16[16];
        int16_t s16[16];
        uint32_t u32[8];
        int32_t s32[8];
        uint64_t u64[4];
        int64_t s64[4];
        float f32[8];
        double f64[4];
    };

    u8[0] = 0x10;   u8[1] = 0x11;   u8[2] = 0x12;   u8[3] = 0x13;
    u8[4] = 0x14;   u8[5] = 0x15;   u8[6] = 0x16;   u8[7] = 0x17;
    u8[8] = 0x18;   u8[9] = 0x19;   u8[10] = 0x20;  u8[11] = 0x21;
    u8[12] = 0x22;  u8[13] = 0x23;  u8[14] = 0x24;  u8[15] = 0x25;
    u8[16] = 0x26;  u8[17] = 0x27;  u8[18] = 0x28;  u8[19] = 0x29;
    u8[20] = 0x30;  u8[21] = 0x31;  u8[22] = 0x32;  u8[23] = 0x33;
    u8[24] = 0x34;  u8[25] = 0x35;  u8[26] = 0x36;  u8[27] = 0x37;
    u8[28] = 0x38;  u8[29] = 0x39;  u8[30] = 0x40;  u8[31] = 0x41;

    // 16-byte vectors
    TEST_PUSH(tc,uint8x16,uint8x16::load_broadcast(u8+6));
    TEST_PUSH(tc,uint8x16,uint8x16::set_broadcast(0x10));
    TEST_PUSH(tc,uint8x16,uint8x16::make_const(0x10));
    TEST_PUSH(tc,uint8x16,uint8x16::make_const(0x10, 0x11));
    TEST_PUSH(tc,uint8x16,uint8x16::make_const(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,uint8x16,uint8x16::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,uint8x16,uint8x16::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                               0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,int8x16,int8x16::load_broadcast(s8+2));
    TEST_PUSH(tc,int8x16,int8x16::set_broadcast(0x10));
    TEST_PUSH(tc,int8x16,int8x16::make_const(0x10));
    TEST_PUSH(tc,int8x16,int8x16::make_const(0x10, 0x11));
    TEST_PUSH(tc,int8x16,int8x16::make_const(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,int8x16,int8x16::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,int8x16,int8x16::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                             0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));

    TEST_PUSH(tc,uint16x8,uint16x8::load_broadcast(u16+6));
    TEST_PUSH(tc,uint16x8,uint16x8::set_broadcast(0x1010));
    TEST_PUSH(tc,uint16x8,uint16x8::make_const(0x1010));
    TEST_PUSH(tc,uint16x8,uint16x8::make_const(0x1010, 0x1111));
    TEST_PUSH(tc,uint16x8,uint16x8::make_const(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,uint16x8,uint16x8::make_const(0x1010, 0x1111, 0x1212, 0x1313,
                                               0x1414, 0x1515, 0x1616, 0x1717));

    TEST_PUSH(tc,int16x8,int16x8::load_broadcast(s16+2));
    TEST_PUSH(tc,int16x8,int16x8::set_broadcast(0x1010));
    TEST_PUSH(tc,int16x8,int16x8::make_const(0x1010));
    TEST_PUSH(tc,int16x8,int16x8::make_const(0x1010, 0x1111));
    TEST_PUSH(tc,int16x8,int16x8::make_const(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,int16x8,int16x8::make_const(0x1010, 0x1111, 0x1212, 0x1313,
                                             0x1414, 0x1515, 0x1616, 0x1717));

    TEST_PUSH(tc,uint32x4,uint32x4::load_broadcast(u32+0));
    TEST_PUSH(tc,uint32x4,uint32x4::set_broadcast(0x10101010));
    TEST_PUSH(tc,uint32x4,uint32x4::make_const(0x10101010));
    TEST_PUSH(tc,uint32x4,uint32x4::make_const(0x10101010, 0x11111111));
    TEST_PUSH(tc,uint32x4,uint32x4::make_const(0x10101010, 0x11111111, 0x12121212, 0x13131313));

    TEST_PUSH(tc,int32x4,int32x4::load_broadcast(s32+2));
    TEST_PUSH(tc,int32x4,int32x4::set_broadcast(0x10101010));
    TEST_PUSH(tc,int32x4,int32x4::make_const(0x10101010));
    TEST_PUSH(tc,int32x4,int32x4::make_const(0x10101010, 0x11111111));
    TEST_PUSH(tc,int32x4,int32x4::make_const(0x10101010, 0x11111111, 0x12121212, 0x13131313));

    TEST_PUSH(tc,uint64x2,uint64x2::load_broadcast(u64+0));
    TEST_PUSH(tc,uint64x2,uint64x2::set_broadcast(0x1010101010101010));
    TEST_PUSH(tc,uint64x2,uint64x2::make_const(0x1010101010101010));
    TEST_PUSH(tc,uint64x2,uint64x2::make_const(0x1010101010101010, 0x1111111111111111));

    TEST_PUSH(tc,int64x2,int64x2::load_broadcast(s64+1));
    TEST_PUSH(tc,int64x2,int64x2::set_broadcast(0x1010101010101010));
    TEST_PUSH(tc,int64x2,int64x2::make_const(0x1010101010101010));
    TEST_PUSH(tc,int64x2,int64x2::make_const(0x1010101010101010, 0x1111111111111111));

    TEST_PUSH(tc,float32x4,float32x4::load_broadcast(f32+0));
    TEST_PUSH(tc,float32x4,float32x4::set_broadcast(1.0101010f));
    TEST_PUSH(tc,float32x4,float32x4::make_const(1.0101010f));
    TEST_PUSH(tc,float32x4,float32x4::make_const(1.0101010f, 1.1111111f));
    TEST_PUSH(tc,float32x4,float32x4::make_const(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f));

    TEST_PUSH(tc,float64x2,float64x2::load_broadcast(f64+0));
    TEST_PUSH(tc,float64x2,float64x2::set_broadcast(1.010101010101010));
    TEST_PUSH(tc,float64x2,float64x2::make_const(1.010101010101010));
    TEST_PUSH(tc,float64x2,float64x2::make_const(1.010101010101010, 1.111111111111111));

    // 32-byte vectors
    TEST_PUSH(tc,uint8x32,uint8x32::load_broadcast(u8+6));
    TEST_PUSH(tc,uint8x32,uint8x32::set_broadcast(0x10));
    TEST_PUSH(tc,uint8x32,uint8x32::make_const(0x10));
    TEST_PUSH(tc,uint8x32,uint8x32::make_const(0x10, 0x11));
    TEST_PUSH(tc,uint8x32,uint8x32::make_const(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,uint8x32,uint8x32::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,uint8x32,uint8x32::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                               0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));
    TEST_PUSH(tc,uint8x32,uint8x32::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                               0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                                               0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32, 0x33,
                                               0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41));

    TEST_PUSH(tc,int8x32,int8x32::load_broadcast(s8+2));
    TEST_PUSH(tc,int8x32,int8x32::set_broadcast(0x10));
    TEST_PUSH(tc,int8x32,int8x32::make_const(0x10));
    TEST_PUSH(tc,int8x32,int8x32::make_const(0x10, 0x11));
    TEST_PUSH(tc,int8x32,int8x32::make_const(0x10, 0x11, 0x12, 0x13));
    TEST_PUSH(tc,int8x32,int8x32::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17));
    TEST_PUSH(tc,int8x32,int8x32::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                             0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25));
    TEST_PUSH(tc,int8x32,int8x32::make_const(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                             0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                                             0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32, 0x33,
                                             0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41));

    TEST_PUSH(tc,uint16x16,uint16x16::load_broadcast(u16+6));
    TEST_PUSH(tc,uint16x16,uint16x16::set_broadcast(0x1010));
    TEST_PUSH(tc,uint16x16,uint16x16::make_const(0x1010));
    TEST_PUSH(tc,uint16x16,uint16x16::make_const(0x1010, 0x1111));
    TEST_PUSH(tc,uint16x16,uint16x16::make_const(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,uint16x16,uint16x16::make_const(0x1010, 0x1111, 0x1212, 0x1313,
                                                 0x1414, 0x1515, 0x1616, 0x1717));
    TEST_PUSH(tc,uint16x16,uint16x16::make_const(0x1010, 0x1111, 0x1212, 0x1313,
                                                 0x1414, 0x1515, 0x1616, 0x1717,
                                                 0x1818, 0x1919, 0x2020, 0x2121,
                                                 0x2222, 0x2323, 0x2424, 0x2525));

    TEST_PUSH(tc,int16x16,int16x16::load_broadcast(s16+2));
    TEST_PUSH(tc,int16x16,int16x16::set_broadcast(0x1010));
    TEST_PUSH(tc,int16x16,int16x16::make_const(0x1010));
    TEST_PUSH(tc,int16x16,int16x16::make_const(0x1010, 0x1111));
    TEST_PUSH(tc,int16x16,int16x16::make_const(0x1010, 0x1111, 0x1212, 0x1313));
    TEST_PUSH(tc,int16x16,int16x16::make_const(0x1010, 0x1111, 0x1212, 0x1313,
                                               0x1414, 0x1515, 0x1616, 0x1717));
    TEST_PUSH(tc,int16x16,int16x16::make_const(0x1010, 0x1111, 0x1212, 0x1313,
                                               0x1414, 0x1515, 0x1616, 0x1717,
                                               0x1818, 0x1919, 0x2020, 0x2121,
                                               0x2222, 0x2323, 0x2424, 0x2525));

    TEST_PUSH(tc,uint32x8,uint32x8::load_broadcast(u32+0));
    TEST_PUSH(tc,uint32x8,uint32x8::set_broadcast(0x10101010));
    TEST_PUSH(tc,uint32x8,uint32x8::make_const(0x10101010));
    TEST_PUSH(tc,uint32x8,uint32x8::make_const(0x10101010, 0x11111111));
    TEST_PUSH(tc,uint32x8,uint32x8::make_const(0x10101010, 0x11111111, 0x12121212, 0x13131313));
    TEST_PUSH(tc,uint32x8,uint32x8::make_const(0x10101010, 0x11111111, 0x12121212, 0x13131313,
                                               0x14141414, 0x15151515, 0x16161616, 0x17171717));

    TEST_PUSH(tc,int32x8,int32x8::load_broadcast(s32+2));
    TEST_PUSH(tc,int32x8,int32x8::set_broadcast(0x10101010));
    TEST_PUSH(tc,int32x8,int32x8::make_const(0x10101010));
    TEST_PUSH(tc,int32x8,int32x8::make_const(0x10101010, 0x11111111));
    TEST_PUSH(tc,int32x8,int32x8::make_const(0x10101010, 0x11111111, 0x12121212, 0x13131313));
    TEST_PUSH(tc,int32x8,int32x8::make_const(0x10101010, 0x11111111, 0x12121212, 0x13131313,
                                             0x14141414, 0x15151515, 0x16161616, 0x17171717));

    TEST_PUSH(tc,uint64x4,uint64x4::load_broadcast(u64+0));
    TEST_PUSH(tc,uint64x4,uint64x4::set_broadcast(0x1010101010101010));
    TEST_PUSH(tc,uint64x4,uint64x4::make_const(0x1010101010101010));
    TEST_PUSH(tc,uint64x4,uint64x4::make_const(0x1010101010101010, 0x1111111111111111,
                                               0x1212121212121212, 0x1313131313131313));

    TEST_PUSH(tc,int64x4,int64x4::load_broadcast(s64+1));
    TEST_PUSH(tc,int64x4,int64x4::set_broadcast(0x1010101010101010));
    TEST_PUSH(tc,int64x4,int64x4::make_const(0x1010101010101010));
    TEST_PUSH(tc,int64x4,int64x4::make_const(0x1010101010101010, 0x1111111111111111,
                                             0x1212121212121212, 0x1313131313131313));

    TEST_PUSH(tc,float32x8,float32x8::load_broadcast(f32+0));
    TEST_PUSH(tc,float32x8,float32x8::set_broadcast(1.0101010f));
    TEST_PUSH(tc,float32x8,float32x8::make_const(1.0101010f));
    TEST_PUSH(tc,float32x8,float32x8::make_const(1.0101010f, 1.1111111f));
    TEST_PUSH(tc,float32x8,float32x8::make_const(1.0101010f, 1.1111111f, 1.2121212f, 1.3131313f,
                                                 1.1414141f, 1.1515151f, 1.1616161f, 1.1717171f));

    TEST_PUSH(tc,float64x4,float64x4::load_broadcast(f64+0));
    TEST_PUSH(tc,float64x4,float64x4::set_broadcast(1.010101010101010));
    TEST_PUSH(tc,float64x4,float64x4::make_const(1.010101010101010));
    TEST_PUSH(tc,float64x4,float64x4::make_const(1.010101010101010, 1.111111111111111));
    TEST_PUSH(tc,float64x4,float64x4::make_const(1.010101010101010, 1.111111111111111,
                                                   1.121212121212121, 1.131313131313131));
}

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
