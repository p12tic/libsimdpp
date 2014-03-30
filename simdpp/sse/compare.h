/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SSE_COMPARE_H
#define LIBSIMDPP_SSE_COMPARE_H
#if SIMDPP_USE_SSE2 || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/cmp_eq.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace sse {

/** Tests no bits are set in 128-bit integer vector. Returns @c true if
    <tt>a</tt> has all bits unset, @c false otherwise

    @icost{SSE2, SSE3, SSSE3, 3}
    @icost{SSE4.1, 2}
*/
template<class = void>
bool test_zero(uint8x16 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(int8x16::zero(), a);
#elif SIMDPP_USE_SSE2
    mask_int8x16 r = cmp_eq((int8x16)a, int8x16::zero());
    return (_mm_movemask_epi8(int8x16(r)) == 0xffff);
#endif
}
template<class = void>
bool test_zero(uint16x8 a) { return test_zero(uint8x16(a)); }
template<class = void>
bool test_zero(uint32x4 a) { return test_zero(uint8x16(a)); }
template<class = void>
bool test_zero(uint64x2 a) { return test_zero(uint8x16(a)); }

/** Tests if 128-bit integer @a a consists only from zeros if a mask @a mask is
    applied. Returns @c true if <tt>a & mask</tt> has all bits unset, @c false
    otherwise

    @icost{SSE2, SSE3, SSSE3, 4}
    @icost{SSE4.1, 1}
*/
template<class = void>
bool test_zero(uint8x16 a, uint8x16 mask)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testz_si128(a, mask);
#elif SIMDPP_USE_SSE2
    int8x16 a1, mask1;
    a1 = a;  mask1 = mask;
    a1 = bit_and(a1, mask1);
    mask_int8x16 r = cmp_eq(a1, int8x16::zero());
    return (_mm_movemask_epi8(int8x16(r)) == 0xffff);
#endif
}

template<class = void>
bool test_zero(uint16x8 a, uint16x8 mask) { return test_zero(uint8x16(a), uint8x16(mask)); }
template<class = void>
bool test_zero(uint32x4 a, uint32x4 mask) { return test_zero(uint8x16(a), uint8x16(mask)); }
template<class = void>
bool test_zero(uint64x2 a, uint64x2 mask) { return test_zero(uint8x16(a), uint8x16(mask)); }

/** Tests if all bits are set in a 128-bit integer. Returns @c true if @a a has
    all bits set, @c false otherwise.

    @icost{SSE2, SSE3, SSSE3, 3}
    @icost{SSE4.1, 2}
*/
template<class = void>
bool test_ones(uint8x16 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(a, int8x16::ones());
#elif SIMDPP_USE_SSE2
    mask_int8x16 r = cmp_eq((int8x16)a, int8x16::ones());
    return (_mm_movemask_epi8(int8x16(r)) == 0xffff);
#endif
}

template<class = void>
bool test_ones(uint16x8 a) { return test_ones(uint8x16(a)); }
template<class = void>
bool test_ones(uint32x4 a) { return test_ones(uint8x16(a)); }
template<class = void>
bool test_ones(uint64x2 a) { return test_ones(uint8x16(a)); }


/** Tests if 128-bit integer consists only from ones when a mask is applied.
    Returns @c true if <tt>a & mask</tt> has all @a mask bits set, @c false
    otherwise.

    @icost{SSE2, SSE3, SSSE3, 4}
    @icost{SSE4.1, 1}
*/
template<class = void>
bool test_ones(uint8x16 a, uint8x16 mask)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(a, mask);
#elif SIMDPP_USE_SSE2
    int8x16 a1, mask1;
    a1 = a;
    mask1 = mask;
    a1 = bit_andnot(mask1, a1);
    mask_int8x16 r = cmp_eq(a, int8x16::zero());
    return (_mm_movemask_epi8(int8x16(r)) == 0xffff);
#endif
}

template<class = void>
bool test_ones(uint16x8 a, uint16x8 mask) { return test_ones(uint8x16(a), uint8x16(mask)); }
template<class = void>
bool test_ones(uint32x4 a, uint32x4 mask) { return test_ones(uint8x16(a), uint8x16(mask)); }
template<class = void>
bool test_ones(uint64x2 a, uint64x2 mask) { return test_ones(uint8x16(a), uint8x16(mask)); }

} // namespace sse
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
