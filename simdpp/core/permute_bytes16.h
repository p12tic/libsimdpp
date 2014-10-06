/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_PERMUTE_BYTES16_H
#define LIBSIMDPP_SIMDPP_CORE_PERMUTE_BYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif


// FIXME: move to insn
/// @{
/** Selects bytes from a vector according to a mask. Each byte within the
    mask defines which element to select:
     * Bits 7-4 must be zero or the behavior is undefined
     * Bits 3-0 define the element within the given vector.

    @par 128-bit version:
    @unimp{SSE2-SSE3}
    @icost{NEON, 2}

    @par 256-bit version:
    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.

    @unimp{SSE2-SSE3}
    @icost{SSSE3-AVX, ALTIVEC, 2}
    @icost{NEON, 4}
*/
SIMDPP_INL uint8x16 permute_bytes16(uint8x16 a,
                                    uint8x16 mask)
{
#if SIMDPP_USE_NULL
    uint8x16 ai = a;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi.el(i) & 0x0f;
        r.el(i) = ai.el(j);
    }
    return r;
#elif SIMDPP_USE_SSSE3
    return _mm_shuffle_epi8(a, mask);
#elif SIMDPP_USE_NEON
    uint8x8x2_t table = {{vget_low_u8(a), vget_high_u8(a)}};
    uint8x8_t lo = vtbl2_u8(table, vget_low_u8(mask));
    uint8x8_t hi = vtbl2_u8(table, vget_high_u8(mask));
    return vcombine_u8(lo, hi);
#elif SIMDPP_USE_ALTIVEC
    return vec_perm((__vector uint8_t)a, (__vector uint8_t)a,
                    (__vector uint8_t)mask);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, mask);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 permute_bytes16(uint8x32 a, uint8x32 mask)
{
    return _mm256_shuffle_epi8(a, mask);
}
#endif

template<unsigned N> SIMDPP_INL
uint8<N> permute_bytes16(uint8<N> a, uint8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, permute_bytes16, a, mask)
}
template<unsigned N> SIMDPP_INL
uint16<N> permute_bytes16(uint16<N> a, uint16<N> mask)
{
    return (uint16<N>) permute_bytes16(uint8<N*2>(a), uint8<N*2>(mask));
}
template<unsigned N> SIMDPP_INL
uint32<N> permute_bytes16(uint32<N> a, uint32<N> mask)
{
    return (uint32<N>) permute_bytes16(uint8<N*4>(a), uint8<N*4>(mask));
}
template<unsigned N> SIMDPP_INL
uint64<N> permute_bytes16(uint64<N> a, uint64<N> mask)
{
    return (uint64<N>) permute_bytes16(uint8<N*8>(a), uint8<N*8>(mask));
}
template<unsigned N> SIMDPP_INL
float32<N> permute_bytes16(float32<N> a, uint32<N> mask)
{
    return float32<N>(permute_bytes16(uint32<N>(a), mask));
}
template<unsigned N> SIMDPP_INL
float64<N> permute_bytes16(float64<N> a, uint64<N> mask)
{
    return float64<N>(permute_bytes16(uint64<N>(a), mask));
}
/// @}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

