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

template<class V, unsigned vnum>
void test_load_helper(TestSuite& tc, void* sv_p)
{
    using E = typename V::element_type;
    auto sdata = reinterpret_cast<E*>(sv_p);

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack
    SIMDPP_ALIGN(16) V rv[vnum];

    auto rzero = [&](V* r)
    {
        std::memset(r, 0, sizeof(V) * vnum);
    };

    // calls constructor that accepts expr_construct
    for (unsigned i = 0; i < vnum; i++) {
        V r = simdpp::load(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = simdpp::load_u(sdata+i);
        TEST_PUSH(tc, V, r);
    }

    // calls operator= that accepts expr_construct
    for (unsigned i = 0; i < vnum; i++) {
        V r;
        r = simdpp::load(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r;
        r = simdpp::load_u(sdata+i);
        TEST_PUSH(tc, V, r);
    }

    // initializes the vector directly
    for (unsigned i = 0; i < vnum; i++) {
        V r = simdpp::load<V>(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = simdpp::load_u<V>(sdata+i);
        TEST_PUSH(tc, V, r);
    }

    rzero(rv);
    load_packed2(rv[0], rv[1], sdata);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero(rv);
    load_packed3(rv[0], rv[1], rv[2], sdata);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero(rv);
    load_packed4(rv[0], rv[1], rv[2], rv[3], sdata);
    TEST_ARRAY_PUSH(tc, V, rv);
}

template<unsigned B>
void test_memory_load_n(TestSuite& tc)
{
    using namespace simdpp;

    // vnum must be at least 4
    const unsigned vnum = 4;
    Vectors<B,vnum> v;

    test_load_helper<uint8<B>, vnum>(tc, v.u8);
    test_load_helper<uint16<B/2>, vnum>(tc, v.u16);
    test_load_helper<uint32<B/4>, vnum>(tc, v.u32);
    test_load_helper<uint64<B/8>, vnum>(tc, v.u64);
    test_load_helper<float32<B/4>, vnum>(tc, v.f32);
    test_load_helper<float64<B/8>, vnum>(tc, v.f64);
}

void test_memory_load(TestResults& res)
{
    TestSuite& tc = NEW_TEST_SUITE(res, "memory_load");

    test_memory_load_n<16>(tc);
    test_memory_load_n<32>(tc);
    test_memory_load_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
