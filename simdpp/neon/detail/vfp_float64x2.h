/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_NEON_DETAIL_VFP_FLOAT64x2_H
#define LIBSIMDPP_NEON_DETAIL_VFP_FLOAT64x2_H

#include <simdpp/simd/types.h>
#include <cmath>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

