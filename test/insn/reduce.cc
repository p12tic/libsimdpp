/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <numeric>
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {
    template< typename T>
    struct BinaryOpMul
    {
    public:
        BinaryOpMul() {}
        SIMDPP_INL T operator()(T const &a0, T const &a1) const  noexcept
        {
            return a0 * a1;
        }

        template<typename U>
        SIMDPP_INL U operator()(U const &a0, U const &a1) const  noexcept
        {
            return a0*a1;
        }
    };

    template<typename T>
    void test_reduce_type(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;       
        { //test prologue
            vector_t ivect = { 0,41 };
            T expected = {42};
            T init = { 1 };
            T res=reduce(ivect.data(), ivect.data() + ivect.size(),init);
            TEST_EQUAL(tr, expected,res);
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(42, 1);
            T expected = { 42 };
            T init = { 0 };
            T res = reduce(ivect.data(), ivect.data() + ivect.size(), init);
            TEST_EQUAL(tr, expected, res);
        }
        { //test main loop and epilogue on range
            vector_aligned_t ivect(150, 1);
            T expected = { 42 };
            T init = { 0 };
            T res = reduce(ivect.data()+8u, ivect.data() + ivect.size()-100u, init);
            TEST_EQUAL(tr, expected, res);
        }
    }
    
    template<typename T>
    void test_reducebinop_type(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
        auto opMul = BinaryOpMul<T>();

        { //test prologue
            vector_t ivect = { 1,42 };
            T expected = { 42 };
            T init = { 1 };
            T neutral = { 1 };
            T res = reduce(ivect.data(), ivect.data() + ivect.size(), init,neutral,opMul);
            TEST_EQUAL(tr, expected, res);
        }
        { //test main loop and epilogue on unaligned vector
            vector_t ivect(150, 1);
            T expected = { 42 };
            T init = { 42 };
            T neutral = { 1 };
            T res = reduce(ivect.data(), ivect.data() + ivect.size(), init, neutral, opMul);
            TEST_EQUAL(tr, expected, res);
        }
        { //test main loop and epilogue on aligned vector check mul
            vector_aligned_t ivect(10);
            std::iota(begin(ivect), end(ivect), (T)1.);
            T expected = { 3628800 };//aka 10!
            T init = { 1 };
            T neutral = { 1 };
            T res = reduce(ivect.data(), ivect.data() + ivect.size(), init, neutral, opMul);
            TEST_EQUAL(tr, expected, res);
        }
        { //test main loop and epilogue on aligned vector on range check mul
            vector_aligned_t ivect(10);
            std::iota(begin(ivect), end(ivect), (T)1.);
            T expected = { 840}; //4*5*6*7
            T init = { 1 };
            T neutral = { 1 };
            T res = reduce(ivect.data() + 3, ivect.data() + ivect.size() - 3, init, neutral, opMul);
            TEST_EQUAL(tr, expected, res);
        }
    }

    void test_reduce(TestResults& res, TestReporter& tr)
    {
        using namespace simdpp;
        TestResultsSet& ts = res.new_results_set("reduce");
        test_reduce_type<double>(ts, tr);
        test_reduce_type<float>(ts, tr);
        test_reduce_type<uint64_t>(ts, tr);
        test_reduce_type<int64_t>(ts, tr);
        test_reduce_type<uint32_t>(ts, tr);
        test_reduce_type<int32_t>(ts, tr);
        test_reduce_type<uint16_t>(ts, tr);
        test_reduce_type<int16_t>(ts, tr);
        test_reduce_type<uint8_t>(ts, tr);
        test_reduce_type<int8_t>(ts, tr);

        test_reducebinop_type<double>(ts, tr);
        test_reducebinop_type<float>(ts, tr);
        //TR Why no operator * for above types at least for uint64_t and int64_t
        //test_reducebinop_type<uint64_t>(ts, tr);
        //test_reducebinop_type<int64_t>(ts, tr);
        //test_reducebinop_type<uint32_t>(ts, tr);
        //test_reducebinop_type<int32_t>(ts, tr);
        //test_reducebinop_type<uint16_t>(ts, tr);
        //test_reducebinop_type<int16_t>(ts, tr);
        //test_reducebinop_type<uint8_t>(ts, tr);
        //test_reducebinop_type<int8_t>(ts, tr);

    }

} // namespace SIMDPP_ARCH_NAMESPACE
