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
//algorithm
#include <simdpp/algorithm/copy_n.h>

namespace SIMDPP_ARCH_NAMESPACE {


template<typename T>
void test_copy_n_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect = { (T)42,(T)42 };
        vector_t ovect = { (T)0,(T)0 };

        copy_n(ivect.data(),2, ovect.data());
        TEST_EQUAL_COLLECTIONS(tr, ivect, ovect);
    }
    { //test negative don't change ovect
        vector_t ivect = { (T)42,(T)42 };
        vector_t ovect = { (T)0,(T)0 };

        copy_n(ivect.data(), -2, ovect.data());

        TEST_EQUAL(tr, (T)0, ovect[0]);
        TEST_EQUAL(tr, (T)0, ovect[1]);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(150, (T)42);
        vector_t ovect(150, (T)0);

        copy_n(ivect.data(),100, ovect.data());
        for (auto i = 0; i < 100; ++i)
        {
            TEST_EQUAL(tr, ovect[i], ivect[i]);
        }
        for (auto i = 100; i <ovect.size(); ++i)
        {
            TEST_EQUAL(tr, ovect[i], (T)0);
        }
    }
    //CopyNFuzzingTest ? see CopyFuzzingTest    
}

void test_copy_n(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("copy_n");
    test_copy_n_type<double>(ts, tr);
    test_copy_n_type<float>(ts, tr);
    test_copy_n_type<uint64_t>(ts, tr);
    test_copy_n_type<int64_t>(ts, tr);
    test_copy_n_type<uint32_t>(ts, tr);
    test_copy_n_type<int32_t>(ts, tr);
    test_copy_n_type<uint16_t>(ts, tr);
    test_copy_n_type<int16_t>(ts, tr);
    test_copy_n_type<uint8_t>(ts, tr);
    test_copy_n_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE