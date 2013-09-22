/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef SIMDPP_TEST_MAIN_TEST_FUNCTION_INL
#define SIMDPP_TEST_MAIN_TEST_FUNCTION_INL

#include "tests.h"
#include "tests/compare.inl"
#include "tests/convert.inl"
#include "tests/construct.inl"
#include "tests/bitwise.inl"
#include "tests/math_fp.inl"
#include "tests/math_int.inl"
#include "tests/math_shift.inl"
#include "tests/memory_load.inl"
#include "tests/memory_store.inl"
#include "tests/transpose.inl"

namespace SIMDPP_ARCH_NAMESPACE {

void main_test_function(TestResults& res)
{
    test_construct(res);
    test_convert(res);
    test_bitwise(res);
    test_math_fp(res);
    test_math_int(res);
    test_compare(res);
    test_math_shift(res);
    test_shuffle_generic(res);
    test_shuffle(res);
    test_shuffle_bytes(res);
    test_memory_load(res);
    test_memory_store(res);
    test_transpose(res);
}

} // namespace SIMDPP_ARCH_NAMESPACE

#if 0

    //--------------------------------------------------------------------------
    //blend

    a1 = uint8x16::make_const(0x11, 0x22);
    a2 = uint16x8::make_const(0x1111, 0x2222);
    a3 = uint32x4::make_const(0x11111111, 0x22222222);
    a4 = uint64x2::make_const(0x1111111111111111, 0x2222222222222222);
    a5 = float32x4::make_const(100.0f, 101.1f);
    a6 = float64x2::make_const(100.0, 101.1);

    b1 = uint8x16::make_const(0x88, 0x99);
    b2 = uint16x8::make_const(0x8888, 0x9999);
    b3 = uint32x4::make_const(0x88888888, 0x99999999);
    b4 = uint64x2::make_const(0x8888888888888888, 0x9999999999999999);
    b5 = float32x4::make_const(200.0f, 201.1f);
    b6 = float64x2::make_const(200.0, 201.1);

    uint8x16 m1 = uint8x16::make_const(0xff, 0x00);
    uint16x8 m2 = uint16x8::make_const(0xffff, 0x0000);
    uint32x4 m3 = uint32x4::make_const(0xffffffff, 0x00000000);
    uint64x2 m4 = uint64x2::make_const(0xffffffffffffffff, 0x0000000000000000);

    ar1 = uint8x16::make_const(0x11, 0x99);
    ar2 = uint16x8::make_const(0x1111, 0x9999);
    ar3 = uint32x4::make_const(0x11111111, 0x99999999);
    ar4 = uint64x2::make_const(0x1111111111111111, 0x9999999999999999);
    ar5 = float32x4::make_const(100.0f, 201.1f);
    ar6 = float64x2::make_const(100.0, 201.1);

    r1 = blend(a1, b1, m1);
    r2 = blend(a2, b2, m2);
    r3 = blend(a3, b3, m3);
    r4 = blend(a4, b4, m4);
    r5 = blend(a5, b5, m3);
    r6 = blend(a6, b6, m4);

    BOOST_CHECK(SSE_CHECK_EQUAL16(r1, ar1));
    BOOST_CHECK(SSE_CHECK_EQUAL16(r2, ar2));
    BOOST_CHECK(SSE_CHECK_EQUAL16(r3, ar3));
    BOOST_CHECK(SSE_CHECK_EQUAL16(r4, ar4));
    BOOST_CHECK(SSE_CHECK_EQUAL16(r5, ar5));
    BOOST_CHECK(SSE_CHECK_EQUAL16(r6, ar6));


#endif

#endif
