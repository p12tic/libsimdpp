/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_CORE_PERMUTE_ZBYTES16_H
#define LIBSIMDPP_SIMDPP_CORE_PERMUTE_ZBYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/permute_bytes16.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


// FIXME: move to insn
/// @{
/** Selects bytes from a vector according to a mask, optionally selecting zero.
    Each byte within the mask defines which element to select:
     * Bit 7 results in the result byte being zeroed, if set.
     * Bits 6-4 must be zero or the behavior is undefined
     * Bits 3-0 define the element within the given vector.

    @par 128-bit version:
    @unimp{SSE2-SSE3}
    @icost{NEON, 2}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.

    @unimp{SSE2-SSE3}
    @icost{SSSE3-AVX, 2}
    @icost{AVX2, 1}
    @icost{NEON, 4}
    @icost{ALTIVEC, 2-3}

*/
inline uint8x16 permute_zbytes16(uint8x16 a, uint8x16 mask)
{
#if SIMDPP_USE_NULL
    uint8x16 ai = a;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi.el(i) & 0x0f;
        bool zero = mi.el(i) & 0x80;
        r.el(i) = zero ? 0 : ai.el(j);
    }
    return r;
#elif SIMDPP_USE_SSSE3 || SIMDPP_USE_NEON
    return permute_bytes16(a, mask);
#elif SIMDPP_USE_ALTIVEC
    int8x16 a0 = a;
    int8x16 zero_mask = mask;
    zero_mask = shift_r<7>(zero_mask); // shift in the sign bit
    a0 = permute_bytes16(a0, mask);
    a0 = bit_andnot(a0, zero_mask);
    return a0;
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, mask);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 permute_zbytes16(uint8x32 a, uint8x32 mask)
{
    return _mm256_shuffle_epi8(a, mask);
}
#endif

template<unsigned N>
uint8<N> permute_zbytes16(uint8<N> a, uint8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, permute_zbytes16, a, mask);
}
template<unsigned N>
uint16<N> permute_zbytes16(uint16<N> a, uint16<N> mask)
{
    return (uint16<N>) permute_zbytes16(uint8<N*2>(a), uint8<N*2>(mask));
}
template<unsigned N>
uint32<N> permute_zbytes16(uint32<N> a, uint32<N> mask)
{
    return (uint32<N>) permute_zbytes16(uint8<N*4>(a), uint8<N*4>(mask));
}
template<unsigned N>
uint64<N> permute_zbytes16(uint64<N> a, uint64<N> mask)
{
    return (uint64<N>) permute_zbytes16(uint8<N*8>(a), uint8<N*8>(mask));
}
template<unsigned N>
float32<N> permute_zbytes16(float32<N> a, uint32<N> mask)
{
    return float32<N>(permute_zbytes16(uint32<N>(a), mask));
}
template<unsigned N>
float64<N> permute_zbytes16(float64<N> a, uint64<N> mask)
{
    return float64<N>(permute_zbytes16(uint64<N>(a), mask));
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

