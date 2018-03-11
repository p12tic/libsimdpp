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
   using namespace simdpp;
   
   template<typename T>
      struct UnaryPredicateSquare
   {
      using simd_type_T = typename typetraits<T>::simd_type;      
      T operator()(T a) {return a*a;}
      simd_type_T operator()(const simd_type_T& a) {return a*a;}
   };

   template<typename T>
      struct BinaryPredicatePlus
   {
      using simd_type_T = typename typetraits<T>::simd_type;      
      T operator()(T a0,T a1) {return a0 + a1;}
      simd_type_T operator()(const simd_type_T& a0,const simd_type_T& a1) {return a0+a1;}
   };

   template<typename T>
      struct BinaryPredicateMul
   {
       using simd_type_T = typename typetraits<T>::simd_type;      
      T operator()(T a0,T a1) {return a0 * a1;}
      simd_type_T operator()(const simd_type_T& a0,const simd_type_T& a1) {return a0*a1;}
   };
      
   template<typename T>
      void test_transform_reduce_type_unary(TestResultsSet& ts, TestReporter& tr)
   {
      using namespace simdpp;
      using vector_t = std::vector<T>;
      using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;       
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
   }
   template<typename T, typename U>
      void test_transform_reduce_type_binary(TestResultsSet& ts, TestReporter& tr)
   {
      using namespace simdpp;
      using vector_t = std::vector<T>;
      using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
      using vector_aligned_u = std::vector<U, aligned_allocator<U, typetraits<U>::alignment>>;
      {
         vector_aligned_t ivect(50);
         std::iota(begin(ivect),end(ivect),(T)1);
         vector_aligned_u ivect2(50);
         std::iota(begin(ivect2),end(ivect2),(T)1);
         auto res  = transform_reduce( ivect.data(),ivect.data()+ivect.size(),ivect2.data(),T(0),BinaryPredicateMul<T>(),BinaryPredicatePlus<T>());
         auto expected = std::inner_product( ivect.data(), ivect.data()+ivect.size(), ivect2.data(), T(0));
         TEST_EQUAL(tr, expected,res);
      }
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
