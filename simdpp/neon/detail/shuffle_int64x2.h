/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT64x2_H
#define LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT64x2_H
#if SIMDPP_USE_NEON

#include <type_traits>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace neon {
namespace detail {
namespace shuffle_int64x2 {

/*
    The code below implements generalized permutations of elements within
    int64x2 vectors using half-vector move instructions available on NEON.
*/
using _0 = std::integral_constant<unsigned, 0>;
using _1 = std::integral_constant<unsigned, 1>;
using _2 = std::integral_constant<unsigned, 2>;
using _3 = std::integral_constant<unsigned, 3>;
using T = uint64x2;    // full vector
using H = uint64x1_t;       // half vector


/// Returns the lower/higher part of a vector. Cost: 0
SIMDPP_INL H lo(T a)   { return vget_low_u64(a); }
SIMDPP_INL H hi(T a)   { return vget_high_u64(a); }

/// Combines two half vectors. Cost: 0
SIMDPP_INL T co(H lo, H hi) { return vcombine_u64(lo, hi); }

// 2-element permutation
template<unsigned s0, unsigned s1> SIMDPP_INL
T permute2(T a)
{
    const unsigned sel = s0*2 + s1;
    switch (sel) {
    case 0:  /*00*/ return co(lo(a), lo(a));
    case 1:  /*01*/ return a;
    case 2:  /*10*/ return co(hi(a), lo(a));
    case 3:  /*11*/ return co(hi(a), hi(a));
    }
}

// 2-element shuffle: the first element must come from a, the second - from b
template<unsigned s0, unsigned s1> SIMDPP_INL
T shuffle1(T a, T b)
{
    const unsigned sel = s0*2 + s1;
    switch (sel) {
    case 0:  /*00*/ return co(lo(a), lo(b));
    case 1:  /*01*/ return co(lo(a), hi(b));
    case 2:  /*10*/ return co(hi(a), lo(b));
    case 3:  /*11*/ return co(hi(a), hi(b));
    }
}

} // namespace shuffle_int64x2
} // namespace detail
} // namespace neon
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif

