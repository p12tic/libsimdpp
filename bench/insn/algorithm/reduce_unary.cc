/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#include "benchmark/benchmark.h"
#include <vector>
#include <numeric>
#include <iterator>
#include <simdpp/simd.h>
//algorithm
#include <simdpp/algorithm/reduce.h>


namespace {

template <typename T>
struct GeneratorConstant
{
    GeneratorConstant(T constant) { m_constant = constant; }
    T operator()() { return m_constant; }
    T m_constant;
};

    
template<typename T, class  Generator>
std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> DataGenerator(std::size_t size, Generator gen)
{
    
    using vector_aligned_t = std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>>;
    vector_aligned_t input(size);
    std::generate(input.begin(), input.end(), gen);
    return input;
}

/*********************UNARY****************************/

template<typename T>
class ReduceUnaryFixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State& st) 
  {
      m_inputvect = DataGenerator<T, GeneratorConstant<T>>((size_t)st.range(0), GeneratorConstant<T>(1));
  }
  void TearDown(const ::benchmark::State&) 
  {
     m_inputvect.clear();
  }
  using vector_aligned_t = std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>>;
  vector_aligned_t  m_inputvect;
};

//UINT64_T
BENCHMARK_TEMPLATE_DEFINE_F(ReduceUnaryFixture, UnaryUNINT64_SIMD_Test, uint64_t)(benchmark::State& st)
{
  const auto size= (size_t)st.range(0);
  while (st.KeepRunning()) 
  {
     benchmark::DoNotOptimize(simdpp::reduce(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(),(uint64_t)0));
  }
}
BENCHMARK_REGISTER_F(ReduceUnaryFixture, UnaryUNINT64_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(ReduceUnaryFixture, UnaryUNINT64_STD_Test, uint64_t)(benchmark::State& st)
{
  const auto size = (size_t)st.range(0);
  while (st.KeepRunning())
  {
     benchmark::DoNotOptimize(std::accumulate(m_inputvect.begin(), m_inputvect.end(), (uint64_t)0));
  }
}
BENCHMARK_REGISTER_F(ReduceUnaryFixture, UnaryUNINT64_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);


//FLOAT
BENCHMARK_TEMPLATE_DEFINE_F(ReduceUnaryFixture, UnaryFLOAT_SIMD_Test, float)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(simdpp::reduce(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), (float)0));
   }
}
BENCHMARK_REGISTER_F(ReduceUnaryFixture, UnaryFLOAT_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(ReduceUnaryFixture, UnaryFLOAT_STD_Test, float)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::accumulate(m_inputvect.begin(), m_inputvect.end(), (float)0));
   }
}
BENCHMARK_REGISTER_F(ReduceUnaryFixture, UnaryFLOAT_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

//DOUBLE
BENCHMARK_TEMPLATE_DEFINE_F(ReduceUnaryFixture, UnaryDOUBLE_SIMD_Test, double)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(simdpp::reduce(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), (double)0));
   }
}
BENCHMARK_REGISTER_F(ReduceUnaryFixture, UnaryDOUBLE_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(ReduceUnaryFixture, UnaryDOUBLE_STD_Test, double)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::accumulate(m_inputvect.begin(), m_inputvect.end(), (double)0));
   }
}
BENCHMARK_REGISTER_F(ReduceUnaryFixture, UnaryDOUBLE_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);



}  // namespace