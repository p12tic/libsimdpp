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
inline gint8x16 permute_zbytes16(gint8x16 a, gint8x16 mask)
{
#if SIMDPP_USE_NULL
    uint8x16 ai = a;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi[i] & 0x0f;
        bool zero = mi[i] & 0x80;
        r[i] = zero ? 0 : ai[j];
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

inline gint8x32 permute_zbytes16(gint8x32 a, gint8x32 mask)
{
#if SIMDPP_USE_AVX2
    return _mm256_shuffle_epi8(a, mask);
#else
    return {permute_zbytes16(a[0], mask[0]), permute_zbytes16(a[1], mask[1])};
#endif
}

template<unsigned N>
gint16<N> permute_zbytes16(gint16<N> a, gint16<N> mask)
{
    return permute_zbytes16(gint8<N*2>(a), gint8<N*2>(mask));
}
template<unsigned N>
gint32<N> permute_zbytes16(gint32<N> a, gint32<N> mask)
{
    return permute_zbytes16(gint8<N*4>(a), gint8<N*4>(mask));
}
template<unsigned N>
gint64<N> permute_zbytes16(gint64<N> a, gint64<N> mask)
{
    return permute_zbytes16(gint8<N*4>(a), gint8<N*4>(mask));
}
template<unsigned N>
float32<N> permute_zbytes16(float32<N> a, gint32<N> mask)
{
    return float32<N>(permute_zbytes16(gint32<N>(a), mask));
}
template<unsigned N>
float64<N> permute_zbytes16(float64<N> a, gint64<N> mask)
{
    return float64<N>(permute_zbytes16(gint64<N>(a), mask));
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

