/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/


#include "benchmark/benchmark.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <simdpp/simd.h>

namespace {

   template<typename T>
   class LoadStoreFixture : public ::benchmark::Fixture {
   public:
      void SetUp(const ::benchmark::State& st)
      {
         m_inputvect.resize((size_t)st.range(0));
         std::fill(m_inputvect.begin(), m_inputvect.end(),(T)42);
         m_outputvect.resize((size_t)st.range(0));
      }
      void TearDown(const ::benchmark::State&)
      {
         m_inputvect.clear();
         m_outputvect.clear();
      }
      using vector_aligned_t = std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>>;
      vector_aligned_t  m_inputvect;
      vector_aligned_t  m_outputvect;
   };

   BENCHMARK_TEMPLATE_DEFINE_F(LoadStoreFixture, UnaryUNINT8_SIMD_Test, uint8_t)(benchmark::State& st)
   {
      const auto size = (size_t)st.range(0);
      using simd_type_T = typename simdpp::simd_traits<uint8_t>::simd_type;
      const auto simd_size = simd_type_T::base_length;
      while (st.KeepRunning())
      {
         const auto* ptrin = m_inputvect.data();
         auto* ptrout = m_outputvect.data();
         for (size_t i = 0; i < size; i += simd_size)
         {
            simd_type_T element = simdpp::load(ptrin);
            simdpp::store(ptrout, element);
            ptrin += simd_size;
            ptrout += simd_size;
         }
      }
   }
   BENCHMARK_REGISTER_F(LoadStoreFixture, UnaryUNINT8_SIMD_Test)->Arg(64)->Arg(128)->Arg(256)->Arg(512)->Arg(1024);

  BENCHMARK_TEMPLATE_DEFINE_F(LoadStoreFixture, UnaryUNINT8_STD_Test, uint8_t)(benchmark::State& st)
   {
      const auto size = (size_t)st.range(0);
      using simd_type_T = typename simdpp::simd_traits<uint8_t>::simd_type;
      const auto simd_size = simd_type_T::base_length;      
      while (st.KeepRunning())
      {
         const auto* ptrin = m_inputvect.data();
         auto* ptrout = m_outputvect.data();
         for (size_t i = 0; i < size; ++i)
         {
            *ptrout++=*ptrin++;
         }
      }
   }
  BENCHMARK_REGISTER_F(LoadStoreFixture, UnaryUNINT8_STD_Test)->Arg(64)->Arg(128)->Arg(256)->Arg(512)->Arg(1024);
}  // namespace
