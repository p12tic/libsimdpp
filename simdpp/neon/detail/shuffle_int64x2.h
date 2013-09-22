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

#ifndef LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT64x2_H
#define LIBSIMDPP_NEON_DETAIL_SHUFFLE_INT64x2_H

#include <type_traits>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
using T = basic_int64x2;    // full vector
using H = uint64x1_t;       // half vector


/// Returns the lower/higher part of a vector. Cost: 0
inline H lo(T a)   { return vget_low_u64(a); }
inline H hi(T a)   { return vget_high_u64(a); }

/// Combines two half vectors. Cost: 0
inline T co(H lo, H hi) { return vcombine_u64(lo, hi); }

// 2-element permutation
template<unsigned s0, unsigned s1>
T permute2(T a)
{
    constexpr unsigned sel = s0*2 + s1;
    switch (sel) {
    case 0:  /*00*/ return co(lo(a), lo(a));
    case 1:  /*01*/ return a;
    case 2:  /*10*/ return co(hi(a), lo(a));
    case 3:  /*11*/ return co(hi(a), hi(a));
    }
}

// 2-element shuffle: the first element must come from a, the second - from b
template<unsigned s0, unsigned s1>
T shuffle1(T a, T b)
{
    constexpr unsigned sel = s0*2 + s1;
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

