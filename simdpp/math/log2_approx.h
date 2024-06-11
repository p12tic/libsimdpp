/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_MATH_LOG2_APPROX_H
#define LIBSIMDPP_SIMDPP_MATH_LOG2_APPROX_H

#include <simdpp/simd.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Calculates approximate log2(x). The function is optimized for maximum speed.
    The absolute error of the result is ... over entire range.

    This version of the function requires that the argument is nonzero positive number that
    is also not an infinity.
*/
template<unsigned N>
float32<N> log2_approx_positive_finite(const float32<N>& a)
{
    uint32<N> exponent_mask = make_uint(0x7f800000);
    uint32<N> exponent_for_1 = make_uint(0x3f800000);

    // IEEE-754 floating-point numbers are convenient as they store the 2-based exponent as a port
    // of their format already. The algorithm below extracts the exponent and then appliyes
    // a polynomial to map the [1..2) mantissa to approximate value.

    // extract the exponent into float value
    auto a_int = bit_cast<uint32<N>>(a);
    auto a_exponent_int = shift_r<23>(a_int) & 0xff;
    auto res = to_float32(bit_cast<int32<N>>(a_exponent_int) - 128);

    // extract the mantissa to the range [1..2)
    auto mantissa = bit_cast<float32<N>>(bit_select(exponent_for_1, a_int, exponent_mask));

    auto mantissa_res = -0.34484362f * mantissa + 2.02466192f;
    mantissa_res = mantissa_res * mantissa - 0.67487591f;
    res = res + mantissa_res;

    return res;
}

/** Calculates approximate log2(x). The function is optimized for maximum speed.
    The absolute error of the result is ... over entire range.

    This version of the function handles full range of inputs including special cases correctly.
*/
template<unsigned N>
float32<N> log2_approx(const float32<N>& a)
{
    uint32<N> exponent_mask = make_uint(0x7f800000);
    uint32<N> exponent_for_1 = make_uint(0x3f800000);
    float32<N> neg_infinity = make_float(-std::numeric_limits<float>::infinity());

    // IEEE-754 floating-point numbers are convenient as they store the 2-based exponent as a port
    // of their format already. The algorithm below extracts the exponent and then appliyes
    // a polynomial to map the [1..2) mantissa to approximate value.

    auto nan_mask = a < 0;

    auto zero_mask = a == 0;
    auto finite_mask = isfinite(a);

    // extract the exponent into float value
    auto a_int = bit_cast<uint32<N>>(a);
    auto a_exponent_int = shift_r<23>(a_int) & 0xff;
    auto res = to_float32(bit_cast<int32<N>>(a_exponent_int) - 128);

    // extract the mantissa to the range [1..2)
    auto mantissa = bit_cast<float32<N>>(bit_select(exponent_for_1, a_int, exponent_mask));

    auto mantissa_res = -0.34484362f * mantissa + 2.02466192f;
    mantissa_res = mantissa_res * mantissa - 0.67487591f;
    res = res + mantissa_res;

    // put back infinity if the argument was infinity
    res = blend(res, a, finite_mask);
    // put negative infinity if argument was zero
    res = blend(neg_infinity, res, zero_mask);
    // put NaN if argument was negative
    res = res | nan_mask; // 0xffffffff mask is convenient because it's NaN itself

    return res;
}

} // namespace simdpp
} // namespace SIMDPP_ARCH_NAMESPACE

#endif // LIBSIMDPP_SIMDPP_ALGORITHM_BITONIC_SORT
