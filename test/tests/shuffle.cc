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
#include "../common/vectors.h"
#include <simdpp/simd.h>
#include <vector>

namespace SIMDPP_ARCH_NAMESPACE {

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
        a = simdpp::move_r<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_move_l {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::move_l<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_broadcast {
    static constexpr unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::broadcast<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_broadcast_w {
    static constexpr unsigned limit = V::length;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::broadcast_w<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_align {
    static constexpr unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a, V b)
    {
        a = simdpp::align<i>(a, b);
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
    TEST_PUSH(tc, V, zip_lo(v1, v2));
    TEST_PUSH(tc, V, zip_hi(v1, v2));
    TEST_PUSH(tc, V, unzip_lo(v1, v2));
    TEST_PUSH(tc, V, unzip_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_broadcast, V>::run(tc, v1);
    TemplateTestHelper<Test_broadcast_w, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
    TemplateTestHelper<Test_insert_extract, V>::run(tc, v1, v2);
}

template<class V>
void test_shuffle_type256(TestCase &tc, V v1, V v2)
{
    TEST_PUSH(tc, V, zip_lo(v1, v2));
    TEST_PUSH(tc, V, zip_hi(v1, v2));
    TEST_PUSH(tc, V, unzip_lo(v1, v2));
    TEST_PUSH(tc, V, unzip_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_broadcast, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
}

template<class T>
using AlignedVector = std::vector<T, simdpp::aligned_allocator<T, 32>>;

template<class V>
AlignedVector<V> test_blend_make_sel_vec()
{
    using U = typename V::uint_element_type;
    using T = typename V::element_type;
    AlignedVector<V> r;

    T z = simdpp::bit_cast<T, U>(U(0));
    T o = simdpp::bit_cast<T, U>(~U(0));
    r.push_back(V::make_const(z, z));
    r.push_back(V::make_const(z, o));
    r.push_back(V::make_const(o, z));
    r.push_back(V::make_const(o, o));

    return r;
}

template<class V, class M>
AlignedVector<M> test_blend_make_sel_mask()
{
    AlignedVector<M> r;
    r.push_back(cmp_eq(V::make_const(0, 0), V::make_const(0, 0)));
    r.push_back(cmp_eq(V::make_const(0, 0), V::make_const(0, 1)));
    r.push_back(cmp_eq(V::make_const(0, 0), V::make_const(1, 0)));
    r.push_back(cmp_eq(V::make_const(0, 0), V::make_const(1, 1)));
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
