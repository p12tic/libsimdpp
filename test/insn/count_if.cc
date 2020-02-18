/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <simdpp/simd.h>
//algorithm
#include <simdpp/algorithm/count_if.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
struct UnaryPredicateEqualValue
{
public:
    UnaryPredicateEqualValue(T val) :m_val(val), m_val_simd(simdpp::splat(val)) {}
    using simd_mask_T = typename simdpp::simd_traits<T>::simd_mask_type;
    using simd_type_T = typename simdpp::simd_traits<T>::simd_type;

    SIMDPP_INL bool                  operator()(T a)           const SIMDPP_NOEXCEPT { return a == m_val; }
    SIMDPP_INL simd_mask_T operator()(const simd_type_T& a) const SIMDPP_NOEXCEPT { return cmp_eq(a, m_val_simd); }

    T m_val;
    simd_type_T m_val_simd;
};

template<typename T>
struct CountIfFuzzingTest
{
    CountIfFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator(42) {}
    void operator()(TestReporter& tr)
    {
        const auto pred = UnaryPredicateEqualValue<T>((T)42);
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generator));
                input[(input.size() - 1) % 2] = (T)0;
                auto res_std = std::count_if(input.cbegin(), input.cend(),pred);
                auto res_simd = simdpp::count_if(input.data(), input.data() + input.size(), pred);
                TEST_EQUAL(tr, res_std, res_simd);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorConstant<T>>(size, m_generator));
                input[(input.size() - 1) % 2] = (T)0;
                auto res_std = std::count_if(input.cbegin(), input.cend(), pred);
                auto res_simd = simdpp::count_if(input.data(), input.data() + input.size(), pred);
                TEST_EQUAL(tr, res_std, res_simd);

            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorConstant<T> m_generator;
};

template<typename T>
void test_count_if_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    const auto pred = UnaryPredicateEqualValue<T>((T)42);
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect = { (T)42,(T)42 };
        auto res = count_if(ivect.data(), ivect.data() + ivect.size(), pred);
        auto resstd = std::count_if(begin(ivect), end(ivect), pred);
        TEST_EQUAL(tr, res, resstd);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(50, (T)42);
        ivect[25] = (T)0;
        ivect[49] = (T)0;
        auto res = count_if(ivect.data(), ivect.data() + ivect.size(), pred);
        auto resstd = std::count_if(begin(ivect), end(ivect), pred);
        TEST_EQUAL(tr, res, resstd);
    }
    CountIfFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_count_if(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("count_if");
    test_count_if_type<double>(ts, tr);
    test_count_if_type<float>(ts, tr);
    test_count_if_type<uint64_t>(ts, tr);
    test_count_if_type<int64_t>(ts, tr);
    test_count_if_type<uint32_t>(ts, tr);
    test_count_if_type<int32_t>(ts, tr);
    test_count_if_type<uint16_t>(ts, tr);
    test_count_if_type<int16_t>(ts, tr);
    test_count_if_type<uint8_t>(ts, tr);
    test_count_if_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE  
