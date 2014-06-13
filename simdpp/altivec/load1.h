/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_ALTIVEC_LOAD1_H
#define LIBSIMDPP_ALTIVEC_LOAD1_H
#if SIMDPP_USE_ALTIVEC || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace altivec {

/** Loads a single element from unaligned memory location and places it to the
    first position in the vector. The contents of the rest of the vector are
    undefined.

    @code
    a.vec(0) = *p
    @endcode

    @icost{ALTIVEC, 2}
*/
/// @{
inline uint8x16 load1_u(uint8x16& a, const uint8_t* p)
{
    a = vec_lde(0, p);
    // The format of vec_lvs{l,r} is compatible with the one accepted by
    // shuffle_bytes16
    uint8x16 perm = vec_lvsl(0, p);
    a = shuffle_bytes16(a, a, perm);
    return a;
}

inline uint16x8 load1_u(uint16x8& a, const uint16_t* p)
{
    a = vec_lde(0, p);
    uint8x16 perm = vec_lvsl(0, p);
    a = shuffle_bytes16(a, a, perm);
    return a;
}

inline uint32x4 load1_u(uint32x4& a, const uint32_t* p)
{
    a = vec_lde(0, p);
    uint8x16 perm = vec_lvsl(0, p);
    a = shuffle_bytes16(a, a, perm);
    return a;
}

inline float32x4 load1_u(float32x4& a, const float* p)
{
    a = vec_lde(0, p);
    uint8x16 perm = vec_lvsl(0, p);
    a = shuffle_bytes16(a, a, perm);
    return a;
}
/// @}

/** Loads a single element from a memory location and places it to the vector.
    The position of the element is determined by the last 4 address @a p bits.
    The contents of the rest of the vector are undefined.

    @code
    i = (p % 15) / sizeof(element)
    a[i] = *p
    @endcode
*/
/// @{
inline uint8x16 load1(uint8x16& a, const uint8_t* p)
{
    a = vec_lde(0, p);
    return a;
}

inline uint16x8 load1(uint16x8& a, const uint16_t* p)
{
    a = vec_lde(0, p);
    return a;
}

inline uint32x4 load1(uint32x4& a, const uint32_t* p)
{
    a = vec_lde(0, p);
    return a;
}

inline float32x4 load1(float32x4& a, const float* p)
{
    a = vec_lde(0, p);
    return a;
}
/// @}

} // namespace altivec
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
