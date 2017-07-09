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
void test_store_masked(TestResultsSet& tc, TestReporter& tr, const V* sv)
{
    using namespace simdpp;
    SIMDPP_ALIGN(16) V rv[1];

    tc.reset_seq();
    TestData<V> mask_data(
        make_int(0, 0, 0, 0),
        make_int(1, 0, 0, 0),
        make_int(0, 1, 0, 0),
        make_int(0, 0, 1, 0),
        make_int(0, 0, 0, 1)
    );

    for (unsigned j = 0; j < mask_data.size(); ++j) {
        typename V::mask_vector_type mask;
        mask = bit_not(cmp_eq(mask_data.data()[j], 0));

        std::memset(rv, 0, sizeof(V));

        store_masked(rv, sv[0], mask);
        TEST_PUSH(tc, V, rv[0]);

        TEST_CMP_VEC(tr, bit_and(sv[0], mask), rv[0]);
    }

}

template<class V, unsigned vnum>
void test_store_helper(TestResultsSet& tc, TestReporter& tr, const V* sv)
{
    using namespace simdpp;
    V zero = make_zero();

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack
    SIMDPP_ALIGN(16) V rv[vnum];
    auto rdata = reinterpret_cast<typename V::element_type*>(rv);

    auto rzero = [](V* r)
    {
        std::memset(r, 0, sizeof(V) * vnum);
    };

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        store(rv+i, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
        TEST_CMP_VEC(tr, sv[0], rv[i]);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        store_u(rv+i, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
        TEST_CMPNE_VEC(tr, zero, rv[i]);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        rzero(rv);
        store_u(rdata+i, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        stream(rv+i, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
        TEST_CMP_VEC(tr, sv[0], rv[i]);

    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv);
        store_first(rv, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
        if (i > 1) { // the first element may be zero
            TEST_CMPNE_VEC(tr, zero, rv[0]);
        }
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv);
        store_last(rv, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
        if (i > 0) {
            TEST_CMPNE_VEC(tr, zero, rv[0]);
        }
    }

    rzero(rv);
    store_packed2(rv, sv[0], sv[1]);
    TEST_ARRAY_PUSH(tc, V, rv);
    TEST_CMPNE_VEC(tr, zero, rv[0]);
    TEST_CMPNE_VEC(tr, zero, rv[1]);

    rzero(rv);
    store_packed3(rv, sv[0], sv[1], sv[2]);
    TEST_ARRAY_PUSH(tc, V, rv);
    TEST_CMPNE_VEC(tr, zero, rv[0]);
    TEST_CMPNE_VEC(tr, zero, rv[1]);
    TEST_CMPNE_VEC(tr, zero, rv[2]);

    rzero(rv);
    store_packed4(rv, sv[0], sv[1], sv[2], sv[3]);
    TEST_ARRAY_PUSH(tc, V, rv);
    TEST_CMPNE_VEC(tr, zero, rv[0]);
    TEST_CMPNE_VEC(tr, zero, rv[1]);
    TEST_CMPNE_VEC(tr, zero, rv[2]);
    TEST_CMPNE_VEC(tr, zero, rv[3]);
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

    test_store_masked<uint32<B/4>>(tc, tr, v.u32);
    test_store_masked<uint64<B/8>>(tc, tr, v.u64);
    test_store_masked<int32<B/4>>(tc, tr, v.i32);
    test_store_masked<int64<B/8>>(tc, tr, v.i64);
    test_store_masked<float32<B/4>>(tc, tr, v.f32);
    test_store_masked<float64<B/8>>(tc, tr, v.f64);
}

void test_memory_store(TestResults& res, TestReporter& tr)
{
    TestResultsSet& tc = res.new_results_set("memory_store");

    test_memory_store_n<16>(tc, tr);
    test_memory_store_n<32>(tc, tr);
    test_memory_store_n<64>(tc, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
