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
#include <simdpp/simd.h>
#include <simdpp/algorithm/none_of.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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
struct NoneOffFuzzingTest
{
    NoneOffFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator(5) {}
    void operator()(TestReporter& tr)
    {
        const auto predEqualTen = UnaryPredicateEqualValue<T>((T)10);
        srand((unsigned int)time(nullptr));
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generator));
                input[(size_t)(rand() % input.size())] = 10;
                auto res_std = std::none_of(input.cbegin(), input.cend(), predEqualTen);
                auto res_simd = simdpp::none_of(input.data(), input.data() + input.size(), predEqualTen);
                TEST_EQUAL(tr, res_std, res_simd);
            }
            {//non aligned input/ouput
                auto input(DataGenerator<T, GeneratorConstant<T>>(size, m_generator));
                input[(size_t)(rand() % input.size())] = 10;
                auto res_std = std::none_of(input.cbegin(), input.cend(), predEqualTen);
                auto res_simd = simdpp::none_of(input.data(), input.data() + input.size(), predEqualTen);
                TEST_EQUAL(tr, res_std, res_simd);
            }

            {//aligned input/ouput
                auto input(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generator));
                auto res_std = std::none_of(input.cbegin(), input.cend(), predEqualTen);
                auto res_simd = simdpp::none_of(input.data(), input.data() + input.size(), predEqualTen);
                TEST_EQUAL(tr, res_std, res_simd);
            }
            {//non aligned input/ouput
                auto input(DataGenerator<T, GeneratorConstant<T>>(size, m_generator));
                auto res_std = std::none_of(input.cbegin(), input.cend(), predEqualTen);
                auto res_simd = simdpp::none_of(input.data(), input.data() + input.size(), predEqualTen);
                TEST_EQUAL(tr, res_std, res_simd);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorConstant<T> m_generator;
};

template<typename T>
    void test_none_of_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
      
    {//test with predicate
        const auto predEqualTen = UnaryPredicateEqualValue<T>((T)10);
        { //test prologue
        vector_t ivect = { (T)1,(T)2};
        auto res = none_of(ivect.data(), ivect.data() + ivect.size(), predEqualTen);
        auto resstd = std::none_of(begin(ivect), end(ivect), predEqualTen);
        TEST_EQUAL(tr, res, resstd);
        }
        { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(50, (T)5);
        ivect[49]=(T)10;
        auto res = none_of(ivect.data(), ivect.data() + ivect.size(), predEqualTen);
        auto resstd = std::none_of(begin(ivect), end(ivect), predEqualTen);
        TEST_EQUAL(tr, res, resstd);
        }
    }
    NoneOffFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_none_of(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("none_of");
    //test_none_of_type<double>(ts, tr); //FIXME
    //test_none_of_type<float>(ts, tr); //FIXME
    test_none_of_type<uint64_t>(ts, tr);
    test_none_of_type<int64_t>(ts, tr);
    test_none_of_type<uint32_t>(ts, tr);
    test_none_of_type<int32_t>(ts, tr);
    test_none_of_type<uint16_t>(ts, tr);
    test_none_of_type<int16_t>(ts, tr);
    test_none_of_type<uint8_t>(ts, tr);
    test_none_of_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE  
