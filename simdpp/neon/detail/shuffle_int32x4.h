/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT32x4_H
#define LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT32x4_H

#include <type_traits>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
using T = basic_int32x4;    // full vector
using H = uint32x2_t;       // half vector


/// Returns the lower/higher part of a vector. Cost: 0
inline H lo(T a)   { return vget_low_u32(a); }
inline H hi(T a)   { return vget_high_u32(a); }

/// Cost: 1
template<unsigned N>
T bcast(T a)
{
    H h = (N < 2) ? lo(a) : hi(a);
    return (uint32x4_t) vdupq_lane_u32(h, N % 2);
}

/// Combines two half vectors. Cost: 0
inline T co(H lo, H hi){ return vcombine_u32(lo, hi); }

/// Reverses the elements in half-vector or half-vectors in a vector. Cost: 1
inline H rev(H a)      { return vrev64_u32(a); }
inline T rev(T a)      { return vrev64q_u32(a); }

/// Duplicates the lower/higher element in the half-vector. Cost: 1
inline H dup_lo(H a)   { return vdup_lane_u32(a, 0); }
inline H dup_hi(H a)   { return vdup_lane_u32(a, 1); }

/** Shuffles two half-vectors or one vector
    Cost: If s0,s1 == 0,3 or 2,1 then 2, otherwise 0-1.
*/
template<unsigned s0, unsigned s1>
H shf(H a, H b)
{
    constexpr unsigned sel = s0*4 + s1;
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

template<unsigned s0, unsigned s1>
H shf(T a)
{
    return shf<s0,s1>(lo(a), hi(a));
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
T shf(T a)
{
    return co(shf<s0,s1>(lo(a), hi(a)), shf<s2,s3>(lo(a), hi(a)));
}

// 4-element permutations
inline T perm4(_0,_0,_0,_0, T a) { return bcast<0>(a); }
inline T perm4(_1,_1,_1,_1, T a) { return bcast<1>(a); }
inline T perm4(_2,_2,_2,_2, T a) { return bcast<2>(a); }
inline T perm4(_3,_3,_3,_3, T a) { return bcast<3>(a); }
inline T perm4(_1,_0,_3,_2, T a) { return rev(a); }

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
T perm4(std::integral_constant<unsigned, s0>,
        std::integral_constant<unsigned, s1>,
        std::integral_constant<unsigned, s2>,
        std::integral_constant<unsigned, s3>, T a)
{
    return shf<s0,s1,s2,s3>(a);
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
T permute4(T a)
{
    return perm4(std::integral_constant<unsigned, s0>{},
                 std::integral_constant<unsigned, s1>{},
                 std::integral_constant<unsigned, s2>{},
                 std::integral_constant<unsigned, s3>{}, a);
}

// 2-element shuffle: the first two elements must come from a, the last two -
// from b
template<unsigned s0, unsigned s1>
T shuffle2(T a, T b)
{
    return co(shf<s0,s1>(a), shf<s0,s1>(b));
}
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
T shuffle2(T a, T b)
{
    return co(shf<s0,s1>(a), shf<s2,s3>(b));
}

} // namespace shuffle_int32x4
} // namespace detail
} // namespace neon
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

