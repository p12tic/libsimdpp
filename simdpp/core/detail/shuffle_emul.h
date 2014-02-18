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

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_SHUFFLE_EMUL_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_SHUFFLE_EMUL_H
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
// #include <simdpp/core/permute2.h> break include cycle
#include <simdpp/core/shuffle1.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// forward-declarations
template<unsigned s0, unsigned s1>
gint64x2 permute2(gint64x2 a);
template<unsigned s0, unsigned s1>
float64x2 permute2(float64x2 a);

namespace detail {

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
gint64x4 permute_emul(gint64x4 a)
{
    gint64x4 r;
    r[0] = permute_half<gint64x2,s0,s1>(a);
    r[1] = permute_half<gint64x2,s2,s3>(a);
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

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif // SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || defined(DOXYGEN_SHOULD_READ_THIS)
#endif
