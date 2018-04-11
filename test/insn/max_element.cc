/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <simdpp/simd.h>
#include <simdpp/algorithm/max_element.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
struct binary_cmp_greater
{
public:
    binary_cmp_greater() = default;
    using simd_mask_T = typename simdpp::simd_traits<T>::simd_mask_type;
    using simd_type_T = typename simdpp::simd_traits<T>::simd_type;

    SIMDPP_INL bool operator()(T a, T b) const SIMDPP_NOEXCEPT { return a < b; }

    SIMDPP_INL simd_mask_T operator()(const simd_type_T& a, const simd_type_T& b) const SIMDPP_NOEXCEPT { return simdpp::cmp_lt(a, b); }
};

template<typename T>
struct MaxElementFuzzingTest
{
    MaxElementFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        auto cmpOPGreater = binary_cmp_greater<T>();

        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::max_element(input.cbegin(), input.cend());
                auto res_simd = simdpp::max_element(input.data(), input.data() + input.size());
                TEST_EQUAL(tr, *res_std,*res_simd);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::max_element(input.cbegin(), input.cend());
                auto res_simd = simdpp::max_element(input.data(), input.data() + input.size());
                TEST_EQUAL(tr, *res_std, *res_simd);

            }
            {//aligned input/ouput + predicate 
                auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::max_element(input.cbegin(), input.cend(), cmpOPGreater);
                auto res_simd = simdpp::max_element(input.data(), input.data() + input.size(), cmpOPGreater);
                TEST_EQUAL(tr, *res_std, *res_simd);
            }
            {//unaligned input/ouput + predicate 
                auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::max_element(input.cbegin(), input.cend(), cmpOPGreater);
                auto res_simd = simdpp::max_element(input.data(), input.data() + input.size(), cmpOPGreater);
                TEST_EQUAL(tr, *res_std, *res_simd);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
void test_max_element_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    auto cmpOPGreater = binary_cmp_greater<T>();
    {//test classical max
        { //test prologue
            vector_aligned_t ivect(5);
            std::iota(begin(ivect), end(ivect), (T)1);
            ivect[0] = { (T)127 };
            TEST_EQUAL(tr, (T)127, *max_element(ivect.data(), ivect.data() + ivect.size()));
        }
        { //test epilogue
            vector_aligned_t ivect(100);
            std::iota(begin(ivect), end(ivect), (T)1);
            ivect[99] = { (T)127 };
            TEST_EQUAL(tr, (T)127, *max_element(ivect.data(), ivect.data() + ivect.size()));
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(100);
            std::iota(begin(ivect), end(ivect), (T)1);
            ivect[50] = { (T)127 };
            TEST_EQUAL(tr, (T)127, *max_element(ivect.data(), ivect.data() + ivect.size()));
        }
    }
    {//test max with comp op
        { //test prologue
            vector_aligned_t ivect(5);
            std::iota(begin(ivect), end(ivect), (T)1);
            ivect[0] = { (T)127 };
            TEST_EQUAL(tr, (T)127, *max_element(ivect.data(), ivect.data() + ivect.size(), cmpOPGreater));
        }
        { //test epilogue
            vector_aligned_t ivect(100);
            std::iota(begin(ivect), end(ivect), (T)1);
            ivect[99] = { (T)127 };
            TEST_EQUAL(tr, (T)127, *max_element(ivect.data(), ivect.data() + ivect.size(), cmpOPGreater));
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(100);
            std::iota(begin(ivect), end(ivect), (T)1);
            ivect[50] = { (T)127 };
            TEST_EQUAL(tr, (T)127, *max_element(ivect.data(), ivect.data() + ivect.size(), cmpOPGreater));
        }
    }
    MaxElementFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144});//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_max_element(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("max_element");
    test_max_element_type<double>(ts, tr);
    test_max_element_type<float>(ts, tr);
    //test_max_type<uint64_t>(ts, tr); //FIXME
    //test_max_type<int64_t>(ts, tr); //FIXME
    test_max_element_type<uint32_t>(ts, tr);
    test_max_element_type<int32_t>(ts, tr);    
    test_max_element_type<uint16_t>(ts, tr);
    test_max_element_type<int16_t>(ts, tr);
    test_max_element_type<uint8_t>(ts, tr);
    test_max_element_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
