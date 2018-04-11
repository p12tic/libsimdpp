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
#include <simdpp/algorithm/replace_if.h>

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
struct ReplaceIfFuzzingTest
{
    ReplaceIfFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generatorFive(5), m_generatorTen(10) {}
    void operator()(TestReporter& tr)
    {
        const auto pred = UnaryPredicateEqualValue<T>((T)5);
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generatorFive));
                auto expected(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generatorTen));
                simdpp::replace_if(input.data(), input.data() + input.size(), pred, (T)10);
                TEST_EQUAL_COLLECTIONS(tr, input, expected);
            }
            {//non aligned input/ouput
                auto input(DataGenerator<T, GeneratorConstant<T>>(size, m_generatorFive));
                auto expected(DataGenerator<T, GeneratorConstant<T>>(size, m_generatorTen));
                simdpp::replace_if(input.data(), input.data() + input.size(), pred, (T)10);
                TEST_EQUAL_COLLECTIONS(tr, input, expected);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorConstant<T> m_generatorFive;
    GeneratorConstant<T> m_generatorTen;
};


template<typename T>
    void test_replace_if_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
      
    { //test prologue
        vector_t ivect = { (T)42,(T)42 };
        vector_t expected = { (T)0,(T)0 };
        const auto pred = UnaryPredicateEqualValue<T>((T)42);
        replace_if(ivect.data(),ivect.data()+ivect.size(),pred,(T)0 );
        TEST_EQUAL_COLLECTIONS(tr, ivect, expected);

    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(50);
        std::iota(begin(ivect),end(ivect),(T)0);
        vector_aligned_t expected(50);
        std::copy(begin(ivect),end(ivect),begin(expected));
        expected[39]=42;
        const auto pred = UnaryPredicateEqualValue<T>((T)39);
        replace_if(ivect.data(),ivect.data()+ivect.size(),pred,(T)42 );
        TEST_EQUAL_COLLECTIONS(tr, ivect, expected);
    }
    ReplaceIfFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_replace_if(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("replace_if");
    test_replace_if_type<double>(ts, tr);
    test_replace_if_type<float>(ts, tr);
    test_replace_if_type<uint64_t>(ts, tr);
    test_replace_if_type<int64_t>(ts, tr);
    test_replace_if_type<uint32_t>(ts, tr);
    test_replace_if_type<int32_t>(ts, tr);
    test_replace_if_type<uint16_t>(ts, tr);
    test_replace_if_type<int16_t>(ts, tr);
    test_replace_if_type<uint8_t>(ts, tr);
    test_replace_if_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
