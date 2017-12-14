/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>
#include <simdpp/detail/align_v128.h>
#include <vector>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned S, unsigned N> simdpp::uint8<N> move_v128_l(const simdpp::uint8<N>& a) { return simdpp::move16_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint16<N> move_v128_l(const simdpp::uint16<N>& a) { return simdpp::move8_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint32<N> move_v128_l(const simdpp::uint32<N>& a) { return simdpp::move4_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint64<N> move_v128_l(const simdpp::uint64<N>& a) { return simdpp::move2_l<S>(a); }
template<unsigned S, unsigned N> simdpp::float32<N> move_v128_l(const simdpp::float32<N>& a) { return simdpp::move4_l<S>(a); }
template<unsigned S, unsigned N> simdpp::float64<N> move_v128_l(const simdpp::float64<N>& a) { return simdpp::move2_l<S>(a); }
template<unsigned S, unsigned N> simdpp::uint8<N> move_v128_r(const simdpp::uint8<N>& a) { return simdpp::move16_r<S>(a); }
template<unsigned S, unsigned N> simdpp::uint16<N> move_v128_r(const simdpp::uint16<N>& a) { return simdpp::move8_r<S>(a); }
template<unsigned S, unsigned N> simdpp::uint32<N> move_v128_r(const simdpp::uint32<N>& a) { return simdpp::move4_r<S>(a); }
template<unsigned S, unsigned N> simdpp::uint64<N> move_v128_r(const simdpp::uint64<N>& a) { return simdpp::move2_r<S>(a); }
template<unsigned S, unsigned N> simdpp::float32<N> move_v128_r(const simdpp::float32<N>& a) { return simdpp::move4_r<S>(a); }
template<unsigned S, unsigned N> simdpp::float64<N> move_v128_r(const simdpp::float64<N>& a) { return simdpp::move2_r<S>(a); }

// shuffles within 256-bit vectors are limited to 128-bit halves
template<class V>
struct Shuffle_width {
    static const unsigned div = V::length * V::num_bits / 128;
    static const unsigned value = V::length / div;
};

template<class V, unsigned i>
struct Test_move_r {
    static const unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = move_v128_r<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_move_l {
    static const unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = move_v128_l<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_splat2 {
    static const unsigned limit = Shuffle_width<V>::value;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = simdpp::splat2<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_splat4 {
    static const unsigned limit = Shuffle_width<V>::value;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = simdpp::splat4<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_splat8 {
    static const unsigned limit = Shuffle_width<V>::value;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = simdpp::splat8<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_splat16 {
    static const unsigned limit = Shuffle_width<V>::value;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = simdpp::splat16<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_splat {
    static const unsigned limit = V::length;
    static void test(TestResultsSet& tc, const V& a)
    {
        V r = simdpp::splat<i>(a);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_align {
    static const unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        V r = simdpp::detail::align_v128<i>(a, b);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_insert_extract {
    static const unsigned limit = V::length;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        V r = simdpp::insert<i>(a, simdpp::extract<i>(b));
        TEST_PUSH(tc, V, r);
    }
};

template<class V>
void test_shuffle_type(TestResultsSet &tc, const V& v1, const V& v2)
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

template<unsigned B>
void test_shuffle_n(TestResultsSet& tc)
{
    using namespace simdpp;

    Vectors<B,4> v;

    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    test_shuffle_type<uint8_n>(tc, v.u8[0], v.u8[1]);
    test_shuffle_type<uint16_n>(tc, v.u16[0], v.u16[1]);
    test_shuffle_type<uint32_n>(tc, v.u32[0], v.u32[1]);
    test_shuffle_type<uint64_n>(tc, v.u64[0], v.u64[1]);
    test_shuffle_type<float32_n>(tc, v.f32[0], v.f32[1]);
    test_shuffle_type<float64_n>(tc, v.f64[0], v.f64[1]);

    TemplateTestHelper<Test_splat16,uint8_n>::run(tc, v.u8[0]);
    TemplateTestHelper<Test_splat8, uint16_n>::run(tc, v.u16[0]);
    TemplateTestHelper<Test_splat4, uint32_n>::run(tc, v.u32[0]);
    TemplateTestHelper<Test_splat2, uint64_n>::run(tc, v.u64[0]);
    TemplateTestHelper<Test_splat4, float32_n>::run(tc, v.f32[0]);
    TemplateTestHelper<Test_splat2, float64_n>::run(tc, v.f64[0]);
}

template<class E, class V>
void test_extract_bits(TestResultsSet& tc)
{
    using namespace simdpp;

    for (unsigned el = 0; el < V::length; el++) {
        simdpp::SIMDPP_ARCH_NAMESPACE::detail::mem_block<V> mu;
        mu = make_zero();
        mu[el] = 0xff;
        TEST_PUSH(tc, E, extract_bits_any(V(mu)));
        mu[el] = 1 << 0;
        TEST_PUSH(tc, E, extract_bits<0>(V(mu)));
        mu[el] = 1 << 1;
        TEST_PUSH(tc, E, extract_bits<1>(V(mu)));
        mu[el] = 1 << 2;
        TEST_PUSH(tc, E, extract_bits<2>(V(mu)));
        mu[el] = 1 << 3;
        TEST_PUSH(tc, E, extract_bits<3>(V(mu)));
        mu[el] = 1 << 4;
        TEST_PUSH(tc, E, extract_bits<4>(V(mu)));
        mu[el] = 1 << 5;
        TEST_PUSH(tc, E, extract_bits<5>(V(mu)));
        mu[el] = 1 << 6;
        TEST_PUSH(tc, E, extract_bits<6>(V(mu)));
        mu[el] = 1 << 7;
        TEST_PUSH(tc, E, extract_bits<7>(V(mu)));
    }
}

void test_shuffle(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("shuffle");

    test_shuffle_n<16>(tc);
    test_shuffle_n<32>(tc);
    test_shuffle_n<64>(tc);

    using namespace simdpp;

    // extract bits
    test_extract_bits<uint16_t, uint8<16>>(tc);
    test_extract_bits<uint32_t, uint8<32>>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
