/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NEON_DETAIL_VFP_FLOAT64x2_H
#define LIBSIMDPP_NEON_DETAIL_VFP_FLOAT64x2_H

#include <simdpp/simd/types.h>
#include <cmath>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace neon {
namespace detail {

inline basic_int64x2 cmp_eq(float64x2 a, float64x2 b)
{
    union {
        basic_int64x2 rv;
        int64_t r[2];
    };
    r[0] = (a[0] == b[0]) ? 0xffffffffffffffff : 0;
    r[1] = (a[1] == b[1]) ? 0xffffffffffffffff : 0;
    return rv;
}

inline basic_int64x2 cmp_neq(float64x2 a, float64x2 b)
{
    union {
        basic_int64x2 rv;
        int64_t r[2];
    };
    r[0] = (a[0] != b[0]) ? 0xffffffffffffffff : 0;
    r[1] = (a[1] != b[1]) ? 0xffffffffffffffff : 0;
    return rv;
}

inline basic_int64x2 cmp_lt(float64x2 a, float64x2 b)
{
    union {
        basic_int64x2 rv;
        int64_t r[2];
    };
    r[0] = (a[0] < b[0]) ? 0xffffffffffffffff : 0;
    r[1] = (a[1] < b[1]) ? 0xffffffffffffffff : 0;
    return rv;
}

inline basic_int64x2 cmp_gt(float64x2 a, float64x2 b)
{
    union {
        basic_int64x2 rv;
        int64_t r[2];
    };
    r[0] = (a[0] > b[0]) ? 0xffffffffffffffff : 0;
    r[1] = (a[1] > b[1]) ? 0xffffffffffffffff : 0;
    return rv;
}

inline basic_int64x2 isnan(float64x2 a)
{
    union {
        basic_int64x2 rv;
        int64_t r[2];
    };
    r[0] = std::isnan(a[0]) ? 0xffffffffffffffff : 0;
    r[1] = std::isnan(a[1]) ? 0xffffffffffffffff : 0;
    return rv;
}

inline basic_int64x2 isnan2(float64x2 a, float64x2 b)
{
    union {
        basic_int64x2 rv;
        int64_t r[2];
    };
    r[0] = std::isnan(a[0]) || std::isnan(b[0]) ? 0xffffffffffffffff : 0;
    r[1] = std::isnan(a[1]) || std::isnan(b[1]) ? 0xffffffffffffffff : 0;
    return rv;
}

} // namespace detail
} // namespace neon
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif

