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

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>
#include <cstring>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned vnum>
void test_store_helper(TestCase& tc, V* sv)
{
    using E = typename traits<V>::element_type;

    union {
        E rdata[traits<V>::length * vnum];
        V rv[vnum];
    };

    auto rzero = [&]()
    {
        for (unsigned i = 0; i < vnum; i++) {
            rv[i] = V::zero();
        }
    };

    for (unsigned i = 0; i < vnum; i++) {
        rzero();
        store(rdata+i*traits<V>::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero();
        stream(rdata+i*traits<V>::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    for (unsigned i = 0; i < (vnum-1)*traits<V>::length; i++) {
        rzero();
        store_u(rdata+i, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < traits<V>::length; i++) {
        rzero();
        store_first(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < traits<V>::length; i++) {
        rzero();
        store_last(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    rzero();
    store_packed2(rdata, sv[0], sv[1]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero();
    store_packed3(rdata, sv[0], sv[1], sv[2]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero();
    store_packed4(rdata, sv[0], sv[1], sv[2], sv[3]);
    TEST_ARRAY_PUSH(tc, V, rv);
}

void test_memory_store(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "memory_store");

    using namespace simdpp;

    const unsigned vnum = 4;
    const unsigned size = 32*vnum;

    union {
        uint8_t sdata[size];
        uint8x16 su8[vnum];
        uint16x8 su16[vnum];
        uint32x4 su32[vnum];
        uint64x2 su64[vnum];
        float32x4 sf32[vnum];
        float64x2 sf64[vnum];

        uint8x32 su8_32[vnum];
        uint16x16 su16_32[vnum];
        uint32x8 su32_32[vnum];
        uint64x4 su64_32[vnum];
        float32x8 sf32_32[vnum];
        float64x4 sf64_32[vnum];
    };

    for (unsigned i = 0; i < size; i++) {
        sdata[i] = i;
    }

    // 16-byte vectors
    test_store_helper<uint8x16, 4>(tc, su8);
    test_store_helper<uint16x8, 4>(tc, su16);
    test_store_helper<uint32x4, 4>(tc, su32);
    test_store_helper<uint64x2, 4>(tc, su64);
    test_store_helper<float32x4, 4>(tc, sf32);
    test_store_helper<float64x2, 4>(tc, sf64);

    // 32-byte vectors
    test_store_helper<uint8x32, 4>(tc, su8_32);
    test_store_helper<uint16x16, 4>(tc, su16_32);
    test_store_helper<uint32x8, 4>(tc, su32_32);
    test_store_helper<uint64x4, 4>(tc, su64_32);
    test_store_helper<float32x8, 4>(tc, sf32_32);
    test_store_helper<float64x4, 4>(tc, sf64_32);
}

} // namespace SIMDPP_ARCH_NAMESPACE
