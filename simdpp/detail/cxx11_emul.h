/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_CXX11_EMUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_CXX11_EMUL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/detail/workarounds.h>
#include <cmath>
#include <math.h>
#include <float.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace cxx11 {

#define SIMDPP_STATIC_ASSERT3(line) simdpp_assert_ ## line
#define SIMDPP_STATIC_ASSERT2(line) SIMDPP_STATIC_ASSERT3(line)
#define SIMDPP_STATIC_ASSERT(v, msg) typedef int SIMDPP_STATIC_ASSERT2(__LINE__) [(v) ? 1 : -1] SIMDPP_ATTRIBUTE_UNUSED

SIMDPP_INL float isnan(float x)
{
#if _MSC_VER
    return _isnan(x);
#else
    return ::isnan(x);
#endif
}

SIMDPP_INL double isnan(double x)
{
#if _MSC_VER
    return _isnan(x);
#else
    return ::isnan(x);
#endif
}

SIMDPP_INL float trunc(float x)
{
    return (x > 0) ? std::floor(x) : std::ceil(x);
}
SIMDPP_INL double trunc(double x)
{
    return (x > 0) ? std::floor(x) : std::ceil(x);
}

#if !defined(_MSC_VER) || _MSC_VER >= 1800
// fma only available since MSVC 2013
SIMDPP_INL float fma(float a, float b, float c)
{
    return ::fmaf(a, b, c);
}

SIMDPP_INL double fma(double a, double b, double c)
{
    return ::fma(a, b, c);
}
#endif

} // namespace cxx11
} // SIMDPP_ARCH_NAMESPACE
} // namespace detail
} // namespace simdpp

#endif

