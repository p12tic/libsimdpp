/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>
#include <cstring>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V>
void rzero(V* r, unsigned vnum)
{
    std::memset(r, 0, sizeof(V) * vnum);
}

template<class V>
void test_store_masked(TestResultsSet& tc, TestReporter& tr, const V* sv)
{
    using namespace simdpp;

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack.
    // NOTE: MSVC 2013 does not support constant expressions within
    // SIMDPP_ALIGN, thus we're aligning to the alignment of the largest V
    // is going to be instantiated with
    SIMDPP_ALIGN(64) V rv[1];

    tc.reset_seq();
    TestData<V> mask_data;
    mask_data.add(make_int(0, 0, 0, 0));
    mask_data.add(make_int(1, 0, 0, 0));
    mask_data.add(make_int(0, 1, 0, 0));
    mask_data.add(make_int(0, 0, 1, 0));
    mask_data.add(make_int(0, 0, 0, 1));

    for (unsigned j = 0; j < mask_data.size(); ++j) {
        typename V::mask_vector_type mask;
        mask = bit_not(cmp_eq(mask_data.data()[j], 0));

        std::memset(rv, 0, sizeof(V));

        store_masked(rv, sv[0], mask);
        TEST_PUSH(tc, V, rv[0]);

        TEST_EQUAL(tr, bit_and(sv[0], mask), rv[0]);
    }

}

template<class V, unsigned vnum>
void test_store_helper(TestResultsSet& tc, TestReporter& tr, const V* sv)
{
    using namespace simdpp;
    V zero = make_zero();

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack.
    // NOTE: MSVC 2013 does not support constant expressions within
    // SIMDPP_ALIGN, thus we're aligning to the alignment of the largest V
    // is going to be instantiated with
#if SIMDPP_USE_ALTIVEC
    // Force-aligning to 64 bytes exposes a bug in GCC on Altivec
    SIMDPP_ALIGN(16) V rv[vnum];
#else
    SIMDPP_ALIGN(64) V rv[vnum];
#endif

    typename V::element_type* rdata = reinterpret_cast<typename V::element_type*>(rv);

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv, vnum);
        store(rv+i, sv[0]);
        TEST_PUSH_ARRAY(tc, V, rv);
        TEST_EQUAL(tr, sv[0], rv[i]);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv, vnum);
        store_u(rv+i, sv[0]);
        TEST_PUSH_ARRAY(tc, V, rv);
        TEST_NOT_EQUAL(tr, zero, rv[i]);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        rzero(rv, vnum);
        store_u(rdata+i, sv[0]);
        TEST_PUSH_ARRAY(tc, V, rv);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv, vnum);
        stream(rv+i, sv[0]);
        TEST_PUSH_ARRAY(tc, V, rv);
        TEST_EQUAL(tr, sv[0], rv[i]);

    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv, vnum);
        store_first(rv, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
        if (i > 1) { // the first element may be zero
            TEST_NOT_EQUAL(tr, zero, rv[0]);
        }
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv, vnum);
        store_last(rv, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
        if (i > 0) {
            TEST_NOT_EQUAL(tr, zero, rv[0]);
        }
    }

    rzero(rv, vnum);
    store_packed2(rv, sv[0], sv[1]);
    TEST_PUSH_ARRAY(tc, V, rv);
    TEST_NOT_EQUAL(tr, zero, rv[0]);
    TEST_NOT_EQUAL(tr, zero, rv[1]);

    rzero(rv, vnum);
    store_packed3(rv, sv[0], sv[1], sv[2]);
    TEST_PUSH_ARRAY(tc, V, rv);
    TEST_NOT_EQUAL(tr, zero, rv[0]);
    TEST_NOT_EQUAL(tr, zero, rv[1]);
    TEST_NOT_EQUAL(tr, zero, rv[2]);

    rzero(rv, vnum);
    store_packed4(rv, sv[0], sv[1], sv[2], sv[3]);
    TEST_PUSH_ARRAY(tc, V, rv);
    TEST_NOT_EQUAL(tr, zero, rv[0]);
    TEST_NOT_EQUAL(tr, zero, rv[1]);
    TEST_NOT_EQUAL(tr, zero, rv[2]);
    TEST_NOT_EQUAL(tr, zero, rv[3]);
}

template<unsigned B>
void test_memory_store_n(TestResultsSet& tc, TestReporter& tr)
{
    using namespace simdpp;

    // vnum must be at least 4
    const unsigned vnum = 4;
    Vectors<B,vnum> v;

    test_store_helper<uint8<B>, vnum>(tc, tr, v.u8);
    test_store_helper<uint16<B/2>, vnum>(tc, tr, v.u16);
    test_store_helper<uint32<B/4>, vnum>(tc, tr, v.u32);
    test_store_helper<uint64<B/8>, vnum>(tc, tr, v.u64);

    test_store_helper<int8<B>, vnum>(tc, tr, v.i8);
    test_store_helper<int16<B/2>, vnum>(tc, tr, v.i16);
    test_store_helper<int32<B/4>, vnum>(tc, tr, v.i32);
    test_store_helper<int64<B/8>, vnum>(tc, tr, v.i64);

    test_store_helper<float32<B/4>, vnum>(tc, tr, v.f32);
    test_store_helper<float64<B/8>, vnum>(tc, tr, v.f64);

    test_store_masked<uint32<B/4> >(tc, tr, v.u32);
    test_store_masked<uint64<B/8> >(tc, tr, v.u64);
    test_store_masked<int32<B/4> >(tc, tr, v.i32);
    test_store_masked<int64<B/8> >(tc, tr, v.i64);
    test_store_masked<float32<B/4> >(tc, tr, v.f32);
    test_store_masked<float64<B/8> >(tc, tr, v.f64);
}

void test_memory_store(TestResults& res, TestReporter& tr)
{
    TestResultsSet& tc = res.new_results_set("memory_store");

    test_memory_store_n<16>(tc, tr);
    test_memory_store_n<32>(tc, tr);
    test_memory_store_n<64>(tc, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
