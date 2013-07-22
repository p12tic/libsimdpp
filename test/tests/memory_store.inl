/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_MEMORY_STORE_H
#define LIBSIMDPP_TEST_TESTS_MEMORY_STORE_H

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

    constexpr unsigned vnum = 4;
    constexpr unsigned size = 16*vnum;

    union {
        uint8_t sdata[size];
        uint8x16 su8[vnum];
        uint16x8 su16[vnum];
        uint32x4 su32[vnum];
        uint64x2 su64[vnum];
        float32x4 sf32[vnum];
        float64x2 sf64[vnum];
    };

    for (unsigned i = 0; i < size; i++) {
        sdata[i] = i;
    }

    test_store_helper<uint8x16, 4>(tc, su8);
    test_store_helper<uint16x8, 4>(tc, su16);
    test_store_helper<uint32x4, 4>(tc, su32);
    test_store_helper<uint64x2, 4>(tc, su64);
    test_store_helper<float32x4, 4>(tc, sf32);
    test_store_helper<float64x2, 4>(tc, sf64);
}

SIMDPP_ARCH_NAMESPACE_END

#endif
