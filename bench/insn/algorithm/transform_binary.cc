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
//algorithm
#include <simdpp/algorithm/transform.h>


namespace {

template< typename T>
struct BinaryOpAdd
{
public:
   BinaryOpAdd() {}
   SIMDPP_INL T operator()(T const &a0, T const &a1) const  SIMDPP_NOEXCEPT
   {
      return a0 + a1;
   }

   template<typename U>
   SIMDPP_INL U operator()(U const &a0, U const &a1) const  SIMDPP_NOEXCEPT
   {
      using namespace simdpp;
      return a0 + a1;
   }
};


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

/*********************Binary****************************/

template<typename T>
class TransformBinaryFixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State& st) 
  {
      m_inputvect = DataGenerator<T, GeneratorConstant<T>>((size_t)st.range(0), GeneratorConstant<T>(42));
      m_inputvect2 = DataGenerator<T, GeneratorConstant<T>>((size_t)st.range(0), GeneratorConstant<T>(42));
      m_outputvect.resize((size_t)st.range(0));
  }
  void TearDown(const ::benchmark::State&) 
  {
     m_inputvect.clear();
     m_inputvect2.clear();
     m_outputvect.clear();
  }
  using vector_aligned_t = std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>>;
  vector_aligned_t  m_inputvect;
  vector_aligned_t  m_inputvect2;
  vector_aligned_t  m_outputvect;
  BinaryOpAdd<T> opPlus= BinaryOpAdd<T>();
};

//UINT8_T
BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT8_SIMD_Test, uint8_t)(benchmark::State& st) 
{
  const auto size= (size_t)st.range(0);
  while (st.KeepRunning()) 
  {
    benchmark::DoNotOptimize(simdpp::transform(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(),m_inputvect2.data(),m_outputvect.data(), opPlus));
  }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT8_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT8_STD_Test, uint8_t)(benchmark::State& st)
{
  const auto size = (size_t)st.range(0);
  while (st.KeepRunning())
  {
    benchmark::DoNotOptimize(std::transform(m_inputvect.begin(), m_inputvect.end(), m_inputvect.begin(),m_outputvect.begin(), opPlus));
  }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT8_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

//UINT16_T
BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT16_SIMD_Test, uint16_t)(benchmark::State& st) 
{
  const auto size= (size_t)st.range(0);
  while (st.KeepRunning()) 
  {
     benchmark::DoNotOptimize(simdpp::transform(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), m_inputvect2.data(), m_outputvect.data(), opPlus));
  }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT16_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT16_STD_Test, uint16_t)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::transform(m_inputvect.begin(), m_inputvect.end(), m_inputvect.begin(), m_outputvect.begin(), opPlus));
   }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT16_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

//UINT32_T
BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT32_SIMD_Test, uint32_t)(benchmark::State& st) 
{
  const auto size= (size_t)st.range(0);
  while (st.KeepRunning()) 
  {
     benchmark::DoNotOptimize(simdpp::transform(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), m_inputvect2.data(), m_outputvect.data(), opPlus));
  }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT32_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT32_STD_Test, uint32_t)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::transform(m_inputvect.begin(), m_inputvect.end(), m_inputvect.begin(), m_outputvect.begin(), opPlus));
   }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT32_STD_Test)->Arg(1)->Arg(10)->Arg(31)->Arg(100)->Arg(1000)->Arg(10000);

//UINT64_T
BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT64_SIMD_Test, uint64_t)(benchmark::State& st) 
{
  const auto size= (size_t)st.range(0);
  while (st.KeepRunning()) 
  {
     benchmark::DoNotOptimize(simdpp::transform(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), m_inputvect2.data(), m_outputvect.data(), opPlus));
  }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT64_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryUNINT64_STD_Test, uint64_t)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::transform(m_inputvect.begin(), m_inputvect.end(), m_inputvect.begin(), m_outputvect.begin(), opPlus));
   }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryUNINT64_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

//FLOAT
BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryFloat_SIMD_Test, float)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(simdpp::transform(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), m_inputvect2.data(), m_outputvect.data(), opPlus));
   }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryFloat_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);


BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryFloat_STD_Test, float)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::transform(m_inputvect.begin(), m_inputvect.end(), m_inputvect.begin(), m_outputvect.begin(), opPlus));
   }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryFloat_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

//DOUBLE
BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryDouble_SIMD_Test, double)(benchmark::State& st) 
{
  const auto size= (size_t)st.range(0);
  while (st.KeepRunning()) 
  {
     benchmark::DoNotOptimize(simdpp::transform(m_inputvect.data(), m_inputvect.data() + m_inputvect.size(), m_inputvect2.data(), m_outputvect.data(), opPlus));
  }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryDouble_SIMD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

BENCHMARK_TEMPLATE_DEFINE_F(TransformBinaryFixture, BinaryDouble_STD_Test, double)(benchmark::State& st)
{
   const auto size = (size_t)st.range(0);
   while (st.KeepRunning())
   {
      benchmark::DoNotOptimize(std::transform(m_inputvect.begin(), m_inputvect.end(), m_inputvect.begin(), m_outputvect.begin(), opPlus));
   }
}
BENCHMARK_REGISTER_F(TransformBinaryFixture, BinaryDouble_STD_Test)->Arg(1)->Arg(10)->Arg(32)->Arg(100)->Arg(1000)->Arg(10000);

}  // namespace