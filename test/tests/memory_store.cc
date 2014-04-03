/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>
#include <cstring>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned vnum>
void test_store_helper(TestCase& tc, V* sv)
{
    using E = typename V::element_type;

    union {
        E rdata[V::length * vnum];
        V rv[vnum];
    };

    auto rzero = [&](V* r)
    {
        for (unsigned i = 0; i < vnum; i++) {
            r[i] = V::zero();
        }
    };

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        store(rdata+i*V::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        stream(rdata+i*V::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv);
        store_first(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv);
        store_last(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    rzero(rv);
    store_packed2(rdata, sv[0], sv[1]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero(rv);
    store_packed3(rdata, sv[0], sv[1], sv[2]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero(rv);
    store_packed4(rdata, sv[0], sv[1], sv[2], sv[3]);
    TEST_ARRAY_PUSH(tc, V, rv);
}

template<unsigned B>
void test_memory_store_n(TestCase& tc)
{
    using namespace simdpp;

    // vnum must be at least 4
    constexpr unsigned vnum = 4;
    Vectors<B,vnum> v;

    test_store_helper<uint8<B>, vnum>(tc, v.u8);
    test_store_helper<uint16<B/2>, vnum>(tc, v.u16);
    test_store_helper<uint32<B/4>, vnum>(tc, v.u32);
    test_store_helper<uint64<B/8>, vnum>(tc, v.u64);
    test_store_helper<float32<B/4>, vnum>(tc, v.f32);
    test_store_helper<float64<B/8>, vnum>(tc, v.f64);
}

void test_memory_store(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "memory_store");

    test_memory_store_n<16>(tc);
    test_memory_store_n<32>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
