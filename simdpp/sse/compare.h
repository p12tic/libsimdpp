/*  Copyright (C) 2011  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_COMPARE_H
#define LIBSIMDPP_SSE_COMPARE_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/cmp_eq.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {

/** Tests no bits are set in 128-bit integer vector. Returns @c true if
    <tt>a</tt> has all bits unset, @c false otherwise

    @icost{SSE2, SSE3, SSSE3, 3}
    @icost{SSE4.1, 2}
*/
SIMDPP_INL
bool test_zero(const uint8x16& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(int8x16::zero(), a);
#elif SIMDPP_USE_SSE2
    mask_int8x16 r = cmp_eq((int8x16)a, int8x16::zero());
    return (_mm_movemask_epi8(int8x16(r)) == 0xffff);
#endif
}
SIMDPP_INL
bool test_zero(const uint16x8& a) { return test_zero(uint8x16(a)); }
SIMDPP_INL
bool test_zero(const uint32x4& a) { return test_zero(uint8x16(a)); }
SIMDPP_INL
bool test_zero(const uint64x2& a) { return test_zero(uint8x16(a)); }

/** Tests if 128-bit integer @a a consists only from zeros if a mask @a mask is
    applied. Returns @c true if <tt>a & mask</tt> has all bits unset, @c false
    otherwise

    @icost{SSE2, SSE3, SSSE3, 4}
    @icost{SSE4.1, 1}
*/
SIMDPP_INL
bool test_zero(const uint8x16& a, const uint8x16& mask)
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

SIMDPP_INL
bool test_zero(const uint16x8& a, const uint16x8& mask) { return test_zero(uint8x16(a), uint8x16(mask)); }
SIMDPP_INL
bool test_zero(const uint32x4& a, const uint32x4& mask) { return test_zero(uint8x16(a), uint8x16(mask)); }
SIMDPP_INL
bool test_zero(const uint64x2& a, const uint64x2& mask) { return test_zero(uint8x16(a), uint8x16(mask)); }

/** Tests if all bits are set in a 128-bit integer. Returns @c true if @a a has
    all bits set, @c false otherwise.

    @icost{SSE2, SSE3, SSSE3, 3}
    @icost{SSE4.1, 2}
*/
SIMDPP_INL
bool test_ones(const uint8x16& a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(a, int8x16::ones());
#elif SIMDPP_USE_SSE2
    mask_int8x16 r = cmp_eq((int8x16)a, int8x16::ones());
    return (_mm_movemask_epi8(int8x16(r)) == 0xffff);
#endif
}

SIMDPP_INL
bool test_ones(const uint16x8& a) { return test_ones(uint8x16(a)); }
SIMDPP_INL
bool test_ones(const uint32x4& a) { return test_ones(uint8x16(a)); }
SIMDPP_INL
bool test_ones(const uint64x2& a) { return test_ones(uint8x16(a)); }


/** Tests if 128-bit integer consists only from ones when a mask is applied.
    Returns @c true if <tt>a & mask</tt> has all @a mask bits set, @c false
    otherwise.

    @icost{SSE2, SSE3, SSSE3, 4}
    @icost{SSE4.1, 1}
*/
SIMDPP_INL
bool test_ones(const uint8x16& a, const uint8x16& mask)
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

SIMDPP_INL
bool test_ones(const uint16x8& a, const uint16x8& mask) { return test_ones(uint8x16(a), uint8x16(mask)); }
SIMDPP_INL
bool test_ones(const uint32x4& a, const uint32x4& mask) { return test_ones(uint8x16(a), uint8x16(mask)); }
SIMDPP_INL
bool test_ones(const uint64x2& a, const uint64x2& mask) { return test_ones(uint8x16(a), uint8x16(mask)); }

} // namespace sse
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
