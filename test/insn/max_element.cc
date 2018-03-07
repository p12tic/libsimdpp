/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

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


namespace SIMDPP_ARCH_NAMESPACE {

    template<typename T>
    struct binary_cmp_greater
    {
    public:
        binary_cmp_greater() = default;
        using simd_mask_T = typename simdpp::typetraits<T>::simd_mask_type;
        using simd_type_T = typename simdpp::typetraits<T>::simd_type;

        bool operator()(T a, T b) { return a > b; }

        simd_mask_T operator()(const simd_type_T& a, const simd_type_T& b) { return simdpp::cmp_gt(a, b); }
    };

    template<typename T>
    void test_max_element_type(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
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
