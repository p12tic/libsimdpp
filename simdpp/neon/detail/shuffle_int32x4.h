/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT32x4_H
#define LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT32x4_H
#if SIMDPP_USE_NEON

#include <type_traits>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace neon {
namespace detail {
namespace shuffle_int32x4 {

/*
    The code below implements generalized permutations of elements within
    int32x4 vectors using various shuffling instructions available on NEON.
*/
using _0 = std::integral_constant<unsigned, 0>;
using _1 = std::integral_constant<unsigned, 1>;
using _2 = std::integral_constant<unsigned, 2>;
using _3 = std::integral_constant<unsigned, 3>;
using T = uint32x4;    // full vector
using H = uint32x2_t;       // half vector


/// Returns the lower/higher part of a vector. Cost: 0
SIMDPP_INL H lo(T a)   { return vget_low_u32(a); }
SIMDPP_INL H hi(T a)   { return vget_high_u32(a); }

/// Cost: 1
template<unsigned N> SIMDPP_INL
T bcast(T a)
{
    H h = (N < 2) ? lo(a) : hi(a);
    return (uint32x4_t) vdupq_lane_u32(h, N % 2);
}

/// Combines two half vectors. Cost: 0
SIMDPP_INL T co(H lo, H hi){ return vcombine_u32(lo, hi); }

/// Reverses the elements in half-vector or half-vectors in a vector. Cost: 1
SIMDPP_INL H rev(H a)      { return vrev64_u32(a); }
SIMDPP_INL T rev(T a)      { return vrev64q_u32(a); }

/// Duplicates the lower/higher element in the half-vector. Cost: 1
SIMDPP_INL H dup_lo(H a)   { return vdup_lane_u32(a, 0); }
SIMDPP_INL H dup_hi(H a)   { return vdup_lane_u32(a, 1); }

/** Shuffles two half-vectors or one vector
    Cost: If s0,s1 == 0,3 or 2,1 then 2, otherwise 0-1.
*/
template<unsigned s0, unsigned s1> SIMDPP_INL
H shf(H a, H b)
{
    const unsigned sel = s0*4 + s1;
    switch (sel) {
    case 0:  /*00*/ return dup_lo(a);
    case 1:  /*01*/ return a;
    case 2:  /*02*/ return vzip_u32(a, b).val[0];
    case 3:  /*03*/ return rev(vext_u32(b, a, 1));
    case 4:  /*10*/ return rev(a);
    case 5:  /*11*/ return dup_hi(a);
    case 6:  /*12*/ return vext_u32(a, b, 1);
    case 7:  /*13*/ return vzip_u32(a, b).val[1];
    case 8:  /*20*/ return vzip_u32(b, a).val[0];
    case 9:  /*21*/ return rev(vext_u32(a, b, 1));
    case 10: /*22*/ return dup_lo(b);
    case 11: /*23*/ return b;
    case 12: /*30*/ return vext_u32(b, a, 1);
    case 13: /*31*/ return vzip_u32(b, a).val[1];
    case 14: /*32*/ return rev(b);
    case 15: /*33*/ return dup_hi(b);
    }
}

template<unsigned s0, unsigned s1> SIMDPP_INL
H shf(T a)
{
    return shf<s0,s1>(lo(a), hi(a));
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
T shf(T a)
{
    return co(shf<s0,s1>(lo(a), hi(a)), shf<s2,s3>(lo(a), hi(a)));
}

// 4-element permutations
SIMDPP_INL T perm4(_0,_0,_0,_0, T a) { return bcast<0>(a); }
SIMDPP_INL T perm4(_1,_1,_1,_1, T a) { return bcast<1>(a); }
SIMDPP_INL T perm4(_2,_2,_2,_2, T a) { return bcast<2>(a); }
SIMDPP_INL T perm4(_3,_3,_3,_3, T a) { return bcast<3>(a); }
SIMDPP_INL T perm4(_1,_0,_3,_2, T a) { return rev(a); }

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
T perm4(std::integral_constant<unsigned, s0>,
        std::integral_constant<unsigned, s1>,
        std::integral_constant<unsigned, s2>,
        std::integral_constant<unsigned, s3>, T a)
{
    return shf<s0,s1,s2,s3>(a);
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
T permute4(T a)
{
    return perm4(std::integral_constant<unsigned, s0>{},
                 std::integral_constant<unsigned, s1>{},
                 std::integral_constant<unsigned, s2>{},
                 std::integral_constant<unsigned, s3>{}, a);
}

// 2-element shuffle: the first two elements must come from a, the last two -
// from b
template<unsigned s0, unsigned s1> SIMDPP_INL
T shuffle2(T a, T b)
{
    return co(shf<s0,s1>(a), shf<s0,s1>(b));
}
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
T shuffle2(T a, T b)
{
    return co(shf<s0,s1>(a), shf<s2,s3>(b));
}

} // namespace shuffle_int32x4
} // namespace detail
} // namespace neon
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif

