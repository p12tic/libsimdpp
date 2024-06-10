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
#include <simdpp/algorithm/transform_reduce.h>

namespace SIMDPP_ARCH_NAMESPACE {
using namespace simdpp;
   
template<typename T>
    struct UnaryPredicateSquare
{
    using simd_type_T = typename simd_traits<T>::simd_type;      
    SIMDPP_INL T operator()(T a) const SIMDPP_NOEXCEPT {return a*a;}
    SIMDPP_INL simd_type_T operator()(const simd_type_T& a) const SIMDPP_NOEXCEPT {return a*a;}
};

template<typename T>
    struct BinaryPredicatePlus
{
    using simd_type_T = typename simd_traits<T>::simd_type;      
    SIMDPP_INL T operator()(T a0,T a1) const SIMDPP_NOEXCEPT {return a0 + a1;}
    SIMDPP_INL simd_type_T operator()(const simd_type_T& a0,const simd_type_T& a1) const SIMDPP_NOEXCEPT {return a0+a1;}
};

template<typename T>
    struct BinaryPredicateMul
{
    using simd_type_T = typename simd_traits<T>::simd_type;      
    SIMDPP_INL T operator()(T a0,T a1) const SIMDPP_NOEXCEPT {return a0 * a1;}
    SIMDPP_INL simd_type_T operator()(const simd_type_T& a0,const simd_type_T& a1) const SIMDPP_NOEXCEPT {return a0*a1;}
};

//from https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
template<typename T>
bool approximatelyEqual(T a, T b, T epsilon)
{
    return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

template<typename T>
struct TransformReduceUnaryFuzzingTest
{
    TransformReduceUnaryFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        T init = (T)0;

        for (auto size : m_sizes)
        {
            {//aligned input/ouput
                const auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::inner_product(input.data(), input.data() + input.size(), input.data(),init);
                auto res_simd = simdpp::transform_reduce(input.data(), input.data() + input.size(),init, BinaryPredicatePlus<T>(), UnaryPredicateSquare<T>());
                TEST_EQUAL(tr, approximatelyEqual(res_std,res_simd, 10 * std::numeric_limits<T>::epsilon()),true);
            }
            {//non aligned input/ouput
                const auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::inner_product(input.data(), input.data() + input.size(), input.data(), init);
                auto res_simd = simdpp::transform_reduce(input.data(), input.data() + input.size(), init, BinaryPredicatePlus<T>(), UnaryPredicateSquare<T>());
                TEST_EQUAL(tr, approximatelyEqual(res_std,res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
struct TransformReduceBinaryFuzzingTest
{
    TransformReduceBinaryFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        T init = (T)1;

        for (auto size : m_sizes)
        {
            {//aligned input/ouput
                const auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                const auto input2(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::inner_product(input.data(), input.data() + input.size(), input2.data(), init);
                auto res_simd = simdpp::transform_reduce(input.data(), input.data() + input.size(), input2.data(), init, BinaryPredicatePlus<T>(), BinaryPredicateMul<T>());
                TEST_EQUAL(tr, approximatelyEqual(res_std, res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
            {//non aligned input/ouput
                const auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                const auto input2(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::inner_product(input.data(), input.data() + input.size(), input2.data(), init);
                auto res_simd = simdpp::transform_reduce(input.data(), input.data() + input.size(), input2.data(), init, BinaryPredicatePlus<T>(), BinaryPredicateMul<T>());
                TEST_EQUAL(tr, approximatelyEqual(res_std, res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
    void test_transform_reduce_type_unary(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;       
    {//
        vector_aligned_t ivect={(T)0,T(1)};
        auto res=transform_reduce(ivect.data(),ivect.data()+ivect.size(),(T)0,BinaryPredicatePlus<T>(),UnaryPredicateSquare<T>());
        auto expected=std::inner_product( ivect.data(),ivect.data()+ivect.size(), ivect.data(), T(0));
        TEST_EQUAL(tr, expected,res);
    }
    {//
        vector_aligned_t ivect(50);
        std::iota(begin(ivect),end(ivect),(T)1);         
        auto res=transform_reduce(ivect.data(),ivect.data()+ivect.size(),(T)0,BinaryPredicatePlus<T>(),UnaryPredicateSquare<T>());
        auto expected=std::inner_product( ivect.data(),ivect.data()+ivect.size(), ivect.data(), T(0));
        TEST_EQUAL(tr, expected,res);
    }
    TransformReduceUnaryFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}
template<typename T, typename U>
    void test_transform_reduce_type_binary(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    using vector_aligned_u = std::vector<U, aligned_allocator<U, simd_traits<U>::alignment>>;
    {
        vector_aligned_t ivect(50);
        std::iota(begin(ivect),end(ivect),(T)1);
        vector_aligned_u ivect2(50);
        std::iota(begin(ivect2),end(ivect2),(T)1);
        auto res  = transform_reduce( ivect.data(),ivect.data()+ivect.size(),ivect2.data(),T(1), BinaryPredicatePlus<T>(), BinaryPredicateMul<T>());
        auto expected = std::inner_product( ivect.data(), ivect.data()+ivect.size(), ivect2.data(), T(1));
        TEST_EQUAL(tr, expected,res);
    }
    TransformReduceBinaryFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_transform_reduce(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("transform_reduce");
    test_transform_reduce_type_unary<double>(ts, tr);
    test_transform_reduce_type_unary<float>(ts, tr);
    // test_transform_reduce_type_unary<uint64_t>(ts, tr);   //FIXME 
    // test_transform_reduce_type_unary<int64_t>(ts, tr);    //FIXME 
    // test_transform_reduce_type_unary<uint32_t>(ts, tr);   //FIXME 
    // test_transform_reduce_type_unary<int32_t>(ts, tr);    //FIXME 
    // test_transform_reduce_type_unary<uint16_t>(ts, tr);   //FIXME 
    // test_transform_reduce_type_unary<int16_t>(ts, tr);    //FIXME 
    // test_transform_reduce_type_unary<uint8_t>(ts, tr);    //FIXME 
    // test_transform_reduce_type_unary<int8_t>(ts, tr);     //FIXME 

    test_transform_reduce_type_binary<double, double>(ts, tr);
    test_transform_reduce_type_binary<float, float>(ts, tr);
    // test_transform_reduce_type_binary<uint64_t, uint64_t>(ts,tr);     //FIXME 
    // test_transform_reduce_type_binary<int64_t, int64_t>(ts, tr);      //FIXME 
    // test_transform_reduce_type_binary<uint32_t, uint32_t>(ts, tr);    //FIXME 
    // test_transform_reduce_type_binary<int32_t, int32_t>(ts, tr);      //FIXME 
    // test_transform_reduce_type_binary<uint16_t, uint16_t>(ts, tr);    //FIXME 
    // test_transform_reduce_type_binary<int16_t, int16_t>(ts, tr);      //FIXME 
    // test_transform_reduce_type_binary<uint8_t, uint8_t>(ts, tr);      //FIXME 
    // test_transform_reduce_type_binary<int8_t, int8_t>(ts, tr);        //FIXME 

}

} // namespace SIMDPP_ARCH_NAMESPACE
