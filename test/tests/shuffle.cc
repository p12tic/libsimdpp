/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

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

template<unsigned S, unsigned N> simdpp::uint8<N> move_v128_l(simdpp::uint8<N> a) { return simdpp::move16_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint16<N> move_v128_l(simdpp::uint16<N> a) { return simdpp::move8_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint32<N> move_v128_l(simdpp::uint32<N> a) { return simdpp::move4_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint64<N> move_v128_l(simdpp::uint64<N> a) { return simdpp::move2_l<S>(a); }
template<unsigned S, unsigned N> simdpp::float32<N> move_v128_l(simdpp::float32<N> a) { return simdpp::move4_l<S>(a); }
template<unsigned S, unsigned N> simdpp::float64<N> move_v128_l(simdpp::float64<N> a) { return simdpp::move2_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint8<N> move_v128_r(simdpp::uint8<N> a) { return simdpp::move16_r<S>(a); }
template<unsigned S, unsigned N> simdpp::uint16<N> move_v128_r(simdpp::uint16<N> a) { return simdpp::move8_r<S>(a); }
template<unsigned S, unsigned N> simdpp::uint32<N> move_v128_r(simdpp::uint32<N> a) { return simdpp::move4_r<S>(a); }
template<unsigned S, unsigned N> simdpp::uint64<N> move_v128_r(simdpp::uint64<N> a) { return simdpp::move2_r<S>(a); }
template<unsigned S, unsigned N> simdpp::float32<N> move_v128_r(simdpp::float32<N> a) { return simdpp::move4_r<S>(a); }
template<unsigned S, unsigned N> simdpp::float64<N> move_v128_r(simdpp::float64<N> a) { return simdpp::move2_r<S>(a); }

// shuffles within 256-bit vectors are limited to 128-bit halves
template<class V>
struct Shuffle_width {
    static constexpr bool is_256 = (V::length * V::num_bits) == 256 ? true : false;
    static constexpr unsigned value = is_256 ? V::length / 2 : V::length;
};

template<class V, unsigned i>
struct Test_move_r {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = move_v128_r<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_move_l {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = move_v128_l<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_splat2 {
    static constexpr unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::splat2<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_splat4 {
    static constexpr unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::splat4<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_splat8 {
    static constexpr unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::splat8<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_splat16 {
    static constexpr unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::splat16<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_splat {
    static constexpr unsigned limit = V::length;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::splat<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_align {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a, V b)
    {
        a = simdpp::detail::align_v128<i>(a, b);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_insert_extract {
    static constexpr unsigned limit = V::length;
    static void test(TestCase& tc, V a, V b)
    {
        a = simdpp::insert<i>(a, simdpp::extract<i>(b));
        TEST_PUSH(tc, V, a);
    }
};

template<class V>
void test_shuffle_type128(TestCase &tc, V v1, V v2)
{
    TEST_PUSH(tc, V, simdpp::detail::insn::zip128_lo(v1, v2));
    TEST_PUSH(tc, V, simdpp::detail::insn::zip128_hi(v1, v2));
    TEST_PUSH(tc, V, simdpp::detail::insn::unzip128_lo(v1, v2));
    TEST_PUSH(tc, V, simdpp::detail::insn::unzip128_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_splat, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
    TemplateTestHelper<Test_insert_extract, V>::run(tc, v1, v2);
}

template<class V>
void test_shuffle_type256(TestCase &tc, V v1, V v2)
{
    TEST_PUSH(tc, V, simdpp::detail::insn::zip128_lo(v1, v2));
    TEST_PUSH(tc, V, simdpp::detail::insn::zip128_hi(v1, v2));
    TEST_PUSH(tc, V, simdpp::detail::insn::unzip128_lo(v1, v2));
    TEST_PUSH(tc, V, simdpp::detail::insn::unzip128_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_splat, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
}

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

template<class V, class VM>
void test_blend(TestCase &tc, V v1, V v2, const AlignedVector<VM>& masks)
{
    for (const auto& v: masks) {
        TEST_PUSH(tc, V, blend(v1, v2, v));
    }
}

void test_shuffle(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "shuffle");

    using namespace simdpp;

    Vectors<16*4> v;

    test_shuffle_type128<uint8x16>(tc, v.u8[0], v.u8[1]);
    test_shuffle_type128<uint16x8>(tc, v.u16[0], v.u16[1]);
    test_shuffle_type128<uint32x4>(tc, v.u32[0], v.u32[1]);
    test_shuffle_type128<uint64x2>(tc, v.u64[0], v.u64[1]);
    test_shuffle_type128<float32x4>(tc, v.f32[0], v.f32[1]);
    test_shuffle_type128<float64x2>(tc, v.f64[0], v.f64[1]);

    test_shuffle_type256<uint8x32>(tc, v.du8[0], v.du8[1]);
    test_shuffle_type256<uint16x16>(tc, v.du16[0], v.du16[1]);
    test_shuffle_type256<uint32x8>(tc, v.du32[0], v.du32[1]);
    test_shuffle_type256<uint64x4>(tc, v.du64[0], v.du64[1]);
    test_shuffle_type256<float32x8>(tc, v.df32[0], v.df32[1]);
    test_shuffle_type256<float64x4>(tc, v.df64[0], v.df64[1]);

    TemplateTestHelper<Test_splat16, uint8x32>::run(tc, v.du8[0]);
    TemplateTestHelper<Test_splat8, uint16x16>::run(tc, v.du16[0]);
    TemplateTestHelper<Test_splat4, uint32x8>::run(tc, v.du32[0]);
    TemplateTestHelper<Test_splat2, uint64x4>::run(tc, v.du64[0]);
    TemplateTestHelper<Test_splat4, float32x8>::run(tc, v.df32[0]);
    TemplateTestHelper<Test_splat2, float64x4>::run(tc, v.df64[0]);

    // blend
    test_blend<uint8x16>(tc, v.u8[0], v.u8[1], test_blend_make_sel_vec<uint8x16>());
    test_blend<uint16x8>(tc, v.u16[0], v.u16[1], test_blend_make_sel_vec<uint16x8>());
    test_blend<uint32x4>(tc, v.u32[0], v.u32[1], test_blend_make_sel_vec<uint32x4>());
    test_blend<uint64x2>(tc, v.u64[0], v.u64[1], test_blend_make_sel_vec<uint64x2>());
    test_blend<float32x4>(tc, v.f32[0], v.f32[1], test_blend_make_sel_vec<uint32x4>());
    test_blend<float32x4>(tc, v.f32[0], v.f32[1], test_blend_make_sel_vec<float32x4>());
    test_blend<float64x2>(tc, v.f64[0], v.f64[1], test_blend_make_sel_vec<uint64x2>());
    test_blend<float64x2>(tc, v.f64[0], v.f64[1], test_blend_make_sel_vec<float64x2>());

    test_blend<uint8x32>(tc, v.du8[0], v.du8[1], test_blend_make_sel_vec<uint8x32>());
    test_blend<uint16x16>(tc, v.du16[0], v.du16[1], test_blend_make_sel_vec<uint16x16>());
    test_blend<uint32x8>(tc, v.du32[0], v.du32[1], test_blend_make_sel_vec<uint32x8>());
    test_blend<uint64x4>(tc, v.du64[0], v.du64[1], test_blend_make_sel_vec<uint64x4>());
    test_blend<float32x8>(tc, v.df32[0], v.df32[1], test_blend_make_sel_vec<uint32x8>());
    test_blend<float32x8>(tc, v.df32[0], v.df32[1], test_blend_make_sel_vec<float32x8>());
    test_blend<float64x4>(tc, v.df64[0], v.df64[1], test_blend_make_sel_vec<uint64x4>());
    test_blend<float64x4>(tc, v.df64[0], v.df64[1], test_blend_make_sel_vec<float64x4>());

    // blend
    test_blend<uint8x16>(tc, v.u8[0], v.u8[1], test_blend_make_sel_mask<uint8x16, mask_int8x16>());
    test_blend<uint16x8>(tc, v.u16[0], v.u16[1], test_blend_make_sel_mask<uint16x8, mask_int16x8>());
    test_blend<uint32x4>(tc, v.u32[0], v.u32[1], test_blend_make_sel_mask<uint32x4, mask_int32x4>());
    //test_blend<uint64x2>(tc, v.u64[0], v.u64[1], test_blend_make_sel_mask<uint64x2, mask_int64x2>());
    test_blend<float32x4>(tc, v.f32[0], v.f32[1], test_blend_make_sel_mask<float32x4, mask_float32x4>());
    test_blend<float64x2>(tc, v.f64[0], v.f64[1], test_blend_make_sel_mask<float64x2, mask_float64x2>());

    test_blend<uint8x32>(tc, v.du8[0], v.du8[1], test_blend_make_sel_mask<uint8x32, mask_int8x32>());
    test_blend<uint16x16>(tc, v.du16[0], v.du16[1], test_blend_make_sel_mask<uint16x16, mask_int16x16>());
    test_blend<uint32x8>(tc, v.du32[0], v.du32[1], test_blend_make_sel_mask<uint32x8, mask_int32x8>());
    //test_blend<uint64x4>(tc, v.du64[0], v.du64[1], test_blend_make_sel_mask<uint64x4, mask_int64x4>());
    test_blend<float32x8>(tc, v.df32[0], v.df32[1], test_blend_make_sel_mask<float32x8, mask_float32x8>());
    test_blend<float64x4>(tc, v.df64[0], v.df64[1], test_blend_make_sel_mask<float64x4, mask_float64x4>());

    // extract bits
    v.reset();

    for (unsigned el = 0; el < 16; el++) {
        simdpp::SIMDPP_ARCH_NAMESPACE::detail::mem_block<uint8x16> mu;
        mu = uint8x16::zero();
        mu[el] = 0xff;
        TEST_PUSH(tc, uint16_t, extract_bits_any(uint8x16(mu)));
        mu[el] = 1 << 0;
        TEST_PUSH(tc, uint16_t, extract_bits<0>(uint8x16(mu)));
        mu[el] = 1 << 1;
        TEST_PUSH(tc, uint16_t, extract_bits<1>(uint8x16(mu)));
        mu[el] = 1 << 2;
        TEST_PUSH(tc, uint16_t, extract_bits<2>(uint8x16(mu)));
        mu[el] = 1 << 3;
        TEST_PUSH(tc, uint16_t, extract_bits<3>(uint8x16(mu)));
        mu[el] = 1 << 4;
        TEST_PUSH(tc, uint16_t, extract_bits<4>(uint8x16(mu)));
        mu[el] = 1 << 5;
        TEST_PUSH(tc, uint16_t, extract_bits<5>(uint8x16(mu)));
        mu[el] = 1 << 6;
        TEST_PUSH(tc, uint16_t, extract_bits<6>(uint8x16(mu)));
        mu[el] = 1 << 7;
        TEST_PUSH(tc, uint16_t, extract_bits<7>(uint8x16(mu)));
    }

}

} // namespace SIMDPP_ARCH_NAMESPACE
