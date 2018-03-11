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
#include <simdpp/algorithm/transform.h>

namespace SIMDPP_ARCH_NAMESPACE {

   template<typename T>
      void test_replace_type(TestResultsSet& ts, TestReporter& tr)
   {
      using namespace simdpp;
      using vector_t = std::vector<T>;
      using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
      { //test prologue
         vector_t ivect = { (T)42,(T)42 };
         vector_t expected = { (T)0,(T)0 };

         replace(ivect.data(),ivect.data()+ivect.size(),(T)42,(T)0 );
         
         for (auto i = 0; i < expected.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
         {
            TEST_EQUAL(tr, ivect[i], expected[i]);
         }
      }
      { //test main loop and epilogue on aligned vector
         vector_aligned_t ivect(50);
         std::iota(begin(ivect),end(ivect),(T)0);
         vector_aligned_t expected(50);
         std::copy(begin(ivect),end(ivect),begin(expected));
         expected[39]=42;
         replace(ivect.data(),ivect.data()+ivect.size(),(T)39,(T)42 );
         for (auto i = 0; i < expected.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
           TEST_EQUAL(tr, expected[i], ivect[i]);   
      }
   }

   void test_replace(TestResults& res, TestReporter& tr)
   {
      using namespace simdpp;
      TestResultsSet& ts = res.new_results_set("replace");
      test_replace_type<double>(ts, tr);
      test_replace_type<float>(ts, tr);
      test_replace_type<uint64_t>(ts, tr);
      test_replace_type<int64_t>(ts, tr);
      test_replace_type<uint32_t>(ts, tr);
      test_replace_type<int32_t>(ts, tr);
      test_replace_type<uint16_t>(ts, tr);
      test_replace_type<int16_t>(ts, tr);
      test_replace_type<uint8_t>(ts, tr);
      test_replace_type<int8_t>(ts, tr);
   }

} // namespace SIMDPP_ARCH_NAMESPACE
