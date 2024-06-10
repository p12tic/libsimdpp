/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <numeric>
#include <simdpp/simd.h>
#include <simdpp/algorithm/find_if.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
struct UnaryPredicateSupValue
{
public:
    UnaryPredicateSupValue(T val) :m_val(val), m_val_simd(simdpp::splat(val)) {}
    using simd_mask_T = typename simdpp::simd_traits<T>::simd_mask_type;
    using simd_type_T = typename simdpp::simd_traits<T>::simd_type;

    SIMDPP_INL bool                  operator()(T a)           const SIMDPP_NOEXCEPT { return a > m_val; }
    SIMDPP_INL simd_mask_T operator()(const simd_type_T& a) const SIMDPP_NOEXCEPT { return cmp_gt(a, m_val_simd); }

    T m_val;
    simd_type_T m_val_simd;
};

template<typename T>
struct FindIfFuzzingTest
{
    FindIfFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator(0) {}
    void operator()(TestReporter& tr)
    {
        
        for (auto size : m_sizes)
        {
            const auto pred = UnaryPredicateSupValue<T>((T)((size - 1) / 2));
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorIota<T>>(size, m_generator));
                auto res_std = std::find_if(input.cbegin(), input.cend(),pred);
                auto res_simd = simdpp::find_if(input.data(), input.data() + input.size(), pred);
                TEST_EQUAL(tr, *res_std, *res_simd);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorIota<T>>(size, m_generator));
                auto res_std = std::find_if(input.cbegin(), input.cend(), pred);
                auto res_simd = simdpp::find_if(input.data(), input.data() + input.size(), pred);
                TEST_EQUAL(tr, *res_std, *res_simd);

            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorIota<T> m_generator;
};

template<typename T>
void test_find_if_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    {//test prologue
        vector_aligned_t ivect(5);
        std::iota(begin(ivect), end(ivect), T(1));
        const auto SupThree = UnaryPredicateSupValue<T>((T)3);
        auto resstd = std::find_if(begin(ivect), end(ivect), [](T el) { return el > 3; });
        auto res = find_if(ivect.data(), ivect.data() + ivect.size(), SupThree);
        TEST_EQUAL(tr, *resstd, *res);
    }
    { //test main loop and epilogue 
        vector_aligned_t ivect(100);
        std::iota(begin(ivect), end(ivect), T(1));
        const auto predicate = UnaryPredicateSupValue<T>((T)98);
        auto resstd = std::find_if(begin(ivect), end(ivect), [](T el) { return el > 98; });
        auto res = find_if(ivect.data(), ivect.data() + ivect.size(), predicate);
        TEST_EQUAL(tr, *resstd, *res);
    }
    { //test main loop
        vector_aligned_t ivect(100);
        std::iota(begin(ivect), end(ivect), T(1));
        const auto predicate = UnaryPredicateSupValue<T>((T)50);
        auto resstd = std::find_if(begin(ivect), end(ivect), [](T el) { return el > 50; });
        auto res = find_if(ivect.data(), ivect.data() + ivect.size(), predicate);
        TEST_EQUAL(tr, *resstd, *res);
    }
    FindIfFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_find_if(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("find_if");
    test_find_if_type<double>(ts, tr);
    test_find_if_type<float>(ts, tr);
    //test_find_if_type<uint64_t>(ts, tr); //FIXME 
    //test_find_if_type<int64_t>(ts, tr); //FIXME
    test_find_if_type<uint32_t>(ts, tr);
    test_find_if_type<int32_t>(ts, tr);
    test_find_if_type<uint16_t>(ts, tr);
    test_find_if_type<int16_t>(ts, tr);
    test_find_if_type<uint8_t>(ts, tr);
    test_find_if_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
