/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_ALTIVEC_LOAD1_H
#define LIBSIMDPP_ALTIVEC_LOAD1_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle_bytes.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace altivec {

/** Loads a single element from unaligned memory location and places it to the
    first position in the vector. The contents of the rest of the vector are
    undefined.

    @code
    a[0] = *p
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
