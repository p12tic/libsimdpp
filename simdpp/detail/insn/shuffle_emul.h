/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE_EMUL_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_SHUFFLE_EMUL_H
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/permute2.h>
#include <simdpp/core/shuffle1.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

template<class H, unsigned s0, unsigned s1, class V>
H permute_half(V a)
{
    switch (s0*4+s1) {
    case 0: /* 0 0 */ return permute2<0,0>(a[0]);
    case 1: /* 0 1 */ return a[0];
    case 2: /* 0 2 */ return shuffle1<0,0>(a[0], a[1]);
    case 3: /* 0 3 */ return shuffle1<0,1>(a[0], a[1]);
    case 4: /* 1 0 */ return permute2<1,0>(a[0]);
    case 5: /* 1 1 */ return permute2<1,1>(a[0]);
    case 6: /* 1 2 */ return shuffle1<1,0>(a[0], a[1]);
    case 7: /* 1 3 */ return shuffle1<1,1>(a[0], a[1]);
    case 8: /* 2 0 */ return shuffle1<0,0>(a[1], a[0]);
    case 9: /* 2 1 */ return shuffle1<0,1>(a[1], a[0]);
    case 10: /* 2 2 */ return permute2<0,0>(a[1]);
    case 11: /* 2 3 */ return a[1];
    case 12: /* 3 0 */ return shuffle1<1,0>(a[1], a[0]);
    case 13: /* 3 1 */ return shuffle1<1,1>(a[1], a[0]);
    case 14: /* 3 2 */ return permute2<1,0>(a[1]);
    case 15: /* 3 3 */ return permute2<1,1>(a[1]);
    }
}

/// @{
/** Permutes 4 64-bit elements within 256-bit vector using 2 element shuffling
    functions.
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
uint64x4 permute_emul(uint64x4 a)
{
    uint64x4 r;
    r[0] = permute_half<uint64x2,s0,s1>(a);
    r[1] = permute_half<uint64x2,s2,s3>(a);
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float64x4 permute_emul(float64x4 a)
{
    float64x4 r;
    r[0] = permute_half<float64x2,s0,s1>(a);
    r[1] = permute_half<float64x2,s2,s3>(a);
    return r;
}
/// @}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif // SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || defined(DOXYGEN_SHOULD_READ_THIS)
#endif
