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
    using E = typename V::element_type;

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack.
    // NOTE: MSVC 2013 does not support constant expressions within
    // SIMDPP_ALIGN, thus we're aligning to the alignment of the largest V
    // is going to be instantiated with
    SIMDPP_ALIGN(64) E rdata[V::length];

    tc.reset_seq();
    TestData<V> mask_data;
    mask_data.add(make_int(0, 0, 0, 0));
    mask_data.add(make_int(1, 0, 0, 0));
    mask_data.add(make_int(0, 1, 0, 0));
    mask_data.add(make_int(0, 0, 1, 0));
    mask_data.add(make_int(0, 0, 0, 1));

    for (unsigned j = 0; j < mask_data.size(); ++j) {
        typename V::mask_vector_type mask;
        mask = bit_not(cmp_eq(mask_data[j], 0));

        std::memset(rdata, 0, V::length_bytes);

        store_masked(rdata, sv[0], mask);
        TEST_PUSH_STORED(tc, V, rdata, 1);

        V rv = load(rdata);
        TEST_EQUAL(tr, bit_and(sv[0], mask), rv);
    }

}

template<class V, unsigned vnum>
void test_store_helper(TestResultsSet& tc, TestReporter& tr, const V* sv)
{
    using namespace simdpp;
    using E = typename V::element_type;

    const unsigned element_count = vnum * V::length;
    const unsigned byte_count = vnum * V::length_bytes;

    // On certain architectures, e.g. armv7 NEON, 128 bit vectors are not
    // necessarily aligned to 16 bytes on the stack.
    // NOTE: MSVC 2013 does not support constant expressions within
    // SIMDPP_ALIGN, thus we're aligning to the alignment of the largest V
    // is going to be instantiated with
#if SIMDPP_USE_ALTIVEC
    // Force-aligning to 64 bytes exposes a bug in GCC on Altivec
    SIMDPP_ALIGN(16) E rdata[element_count];
    SIMDPP_ALIGN(16) E sdata0[V::length];
#else
    SIMDPP_ALIGN(64) E rdata[element_count];
    SIMDPP_ALIGN(64) E sdata0[V::length];
#endif
    E data_zero[element_count];
    std::memset(data_zero, 0, byte_count);

    store(sdata0, sv[0]); // store single aligned element for comparisons
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, sdata0, V::length);

    for (unsigned i = 0; i < vnum; i++) {
        std::memset(rdata, 0, byte_count);

        store(rdata + i * V::length, sv[0]);

        TEST_PUSH_STORED(tc, V, rdata, vnum);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata, i * V::length);
        TEST_EQUAL_MEMORY(tr, sdata0, rdata + i * V::length, V::length);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata + (i + 1) * V::length,
                          (vnum - i - 1) * V::length);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        std::memset(rdata, 0, byte_count);

        store_u(rdata + i, sv[0]);

        TEST_PUSH_STORED(tc, V, rdata, vnum);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata, i);
        TEST_EQUAL_MEMORY(tr, sdata0, rdata + i, V::length);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata + i + V::length,
                          (vnum - 1) * V::length - i);
    }

    for (unsigned i = 0; i < vnum; i++) {
        std::memset(rdata, 0, byte_count);

        stream(rdata + i * V::length, sv[0]);

        TEST_PUSH_STORED(tc, V, rdata, vnum);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata, i * V::length);
        TEST_EQUAL_MEMORY(tr, sdata0, rdata + i * V::length, V::length);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata + (i + 1) * V::length,
                          (vnum - i - 1) * V::length);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        std::memset(rdata, 0, byte_count);

        store_first(rdata, sv[0], i);

        TEST_PUSH_STORED(tc, V, rdata, 1);
        TEST_EQUAL_MEMORY(tr, sdata0, rdata, i);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata + i + 1,
                          vnum * V::length - i - 1);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        std::memset(rdata, 0, byte_count);

        store_last(rdata, sv[0], i);

        TEST_PUSH_STORED(tc, V, rdata, 1);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata, V::length - i);
        TEST_EQUAL_MEMORY(tr, sdata0 + V::length - i, rdata + V::length - i, i);
        TEST_EQUAL_MEMORY(tr, data_zero, rdata + V::length,
                          (vnum - 1) * V::length);
    }

    std::memset(rdata, 0, byte_count);
    store_packed2(rdata, sv[0], sv[1]);
    TEST_PUSH_STORED(tc, V, rdata, 2);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 0 * V::length, V::length);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 1 * V::length, V::length);

    std::memset(rdata, 0, byte_count);
    store_packed3(rdata, sv[0], sv[1], sv[2]);
    TEST_PUSH_STORED(tc, V, rdata, 3);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 0 * V::length, V::length);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 1 * V::length, V::length);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 2 * V::length, V::length);

    std::memset(rdata, 0, byte_count);
    store_packed4(rdata, sv[0], sv[1], sv[2], sv[3]);
    TEST_PUSH_STORED(tc, V, rdata, 3);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 0 * V::length, V::length);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 1 * V::length, V::length);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 2 * V::length, V::length);
    TEST_NOT_EQUAL_MEMORY(tr, data_zero, rdata + 3 * V::length, V::length);
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
