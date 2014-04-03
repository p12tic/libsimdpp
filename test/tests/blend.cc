/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>
#include <simdpp/detail/align_v128.h>
#include <vector>

namespace SIMDPP_ARCH_NAMESPACE {

template<class T>
using AlignedVector = std::vector<T, simdpp::aligned_allocator<T, 32>>;

template<class V>
AlignedVector<V> test_blend_make_sel_vec()
{
    AlignedVector<V> r;

    using simdpp::make_uint;
    r.push_back((V) (typename V::uint_vector_type) make_uint(0, 0));
    r.push_back((V) (typename V::uint_vector_type) make_uint(0, -1));
    r.push_back((V) (typename V::uint_vector_type) make_uint(-1, 0));
    r.push_back((V) (typename V::uint_vector_type) make_uint(-1, -1));

    return r;
}

template<class V, class M>
AlignedVector<M> test_blend_make_sel_mask()
{
    AlignedVector<M> r;
    using simdpp::make_uint;
    r.push_back(cmp_eq((V) make_uint(0, 0), (V) make_uint(0, 0)));
    r.push_back(cmp_eq((V) make_uint(0, 0), (V) make_uint(0, 1)));
    r.push_back(cmp_eq((V) make_uint(0, 0), (V) make_uint(1, 0)));
    r.push_back(cmp_eq((V) make_uint(0, 0), (V) make_uint(1, 1)));
    return r;
}

template<class V, class V1, class V2, class VM>
void test_blend(TestCase &tc, V1 v1, V2 v2, const AlignedVector<VM>& masks)
{
    for (const auto& v: masks) {
        TEST_PUSH(tc, V, blend(v1, v2, v));
    }
}

template<unsigned N>
void test_blend_n(TestCase& tc)
{
    using namespace simdpp;

    Vectors<N*2> v;

    auto mu8 = test_blend_make_sel_vec<uint8<N>>();
    auto mm8 = test_blend_make_sel_mask<uint8<N>, mask_int8<N>>();

    auto mu16 = test_blend_make_sel_vec<uint16<N/2>>();
    auto mm16 = test_blend_make_sel_mask<uint16<N/2>, mask_int16<N/2>>();

    auto mu32 = test_blend_make_sel_vec<uint32<N/4>>();
    auto mm32 = test_blend_make_sel_mask<uint32<N/4>, mask_int32<N/4>>();

    auto mu64 = test_blend_make_sel_vec<uint64<N/8>>();
    auto mm64 = test_blend_make_sel_mask<uint64<N/8>, mask_int64<N/8>>();

    auto mf32 = test_blend_make_sel_vec<float32<N/4>>();
    auto mmf32 = test_blend_make_sel_mask<float32<N/4>, mask_float32<N/4>>();

    auto mf64 = test_blend_make_sel_vec<float64<N/8>>();
    auto mmf64 = test_blend_make_sel_mask<float64<N/8>, mask_float64<N/8>>();

    auto* u8 = v.template get_ptr<uint8<N>>();
    auto* i8 = v.template get_ptr<int8<N>>();

    auto* u16 = v.template get_ptr<uint16<N/2>>();
    auto* i16 = v.template get_ptr<int16<N/2>>();

    auto* u32 = v.template get_ptr<uint32<N/4>>();
    auto* i32 = v.template get_ptr<int32<N/4>>();

    auto* u64 = v.template get_ptr<uint64<N/8>>();
    auto* i64 = v.template get_ptr<int64<N/8>>();

    auto* f32 = v.template get_ptr<float32<N/4>>();
    auto* f64 = v.template get_ptr<float64<N/8>>();

    // this tests correctness, no need to test all combinations
    // see doc/expressions.txt
    test_blend<uint8<N>>(tc, mm8[0], mm8[1], mm8);
    test_blend<uint8<N>>(tc, u8[0], u8[1], mu8);
    test_blend<uint8<N>>(tc, u8[0], u8[1], mm8);
    test_blend<uint16<N/2>>(tc, mm16[0], mm16[1], mm16);
    test_blend<uint16<N/2>>(tc, u16[0], u16[1], mu16);
    test_blend<uint16<N/2>>(tc, u16[0], u16[1], mm16);
    test_blend<uint32<N/4>>(tc, mm32[0], mm32[1], mm32);
    test_blend<uint32<N/4>>(tc, u32[0], u32[1], mu32);
    test_blend<uint32<N/4>>(tc, u32[0], u32[1], mm32);
    test_blend<uint64<N/8>>(tc, mm64[0], mm64[1], mm64);
    test_blend<uint64<N/8>>(tc, u64[0], u64[1], mu64);
    test_blend<uint64<N/8>>(tc, u64[0], u64[1], mm64);
    test_blend<float32<N/4>>(tc, mmf32[0], mmf32[1], mmf32);
    test_blend<float32<N/4>>(tc, f32[0], f32[1], mf32);
    test_blend<float32<N/4>>(tc, f32[0], f32[1], mmf32);
    test_blend<float64<N/8>>(tc, mmf64[0], mmf64[1], mmf64);
    test_blend<float64<N/8>>(tc, f64[0], f64[1], mf64);
    test_blend<float64<N/8>>(tc, f64[0], f64[1], mmf64);

    // the following tests whether we can compile and run the combinations of
    // arguments we advertise to support (i.e. all combinations :-) ). There are
    // 16*16*16 = 4096 combinations in total so we only test specific patterns
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], i8[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], mm8[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], i16[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], mm16[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], i32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], mm32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], i64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], mm64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], mmf32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], f64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u8[0], u8[1], mmf64[0]));

    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], i8[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], mm8[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], i16[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], mm16[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], i32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], mm32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], i64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], mm64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], mmf32[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], f64[0]));
    TEST_PUSH(tc, uint8<N>, blend(u16[0], i32[1], mmf64[0]));

    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], i8[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], mm8[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], i16[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], mm16[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], i32[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], mm32[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], i64[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], mm64[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], mmf32[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], f64[0]));
    TEST_PUSH(tc, uint8<N>, blend(f64[0], i32[1], mmf64[0]));

    TEST_PUSH(tc, uint8<N>, blend(u64[0], u8[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], i8[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], mm8[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], u16[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], i16[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], mm16[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], u32[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], i32[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], mm32[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], u64[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], i64[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], mm64[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], f32[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], mmf32[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], f64[1], u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(u64[0], mmf64[1], u64[1]));
}

void test_blend(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "blend");
    test_blend_n<16>(tc);
    test_blend_n<32>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
