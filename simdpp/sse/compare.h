/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_COMPARE_H
#define LIBSIMDPP_SSE_COMPARE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace sse {

#ifdef SIMDPP_USE_SSE2
/** Compares the values of two float32x4 vectors for less-than or equal

    @code
    r0 = (a0 <= b0) ? 0xffffffff : 0x0
    r1 = (a1 <= b1) ? 0xffffffff : 0x0
    r2 = (a2 <= b2) ? 0xffffffff : 0x0
    r3 = (a3 <= b3) ? 0xffffffff : 0x0
    @endcode
*/
inline int128 cmp_le(float32x4 a, float32x4 b)
{
    return int32x4(_mm_cmple_ps(a, b));
}

/** Compares the values of two float64x2 vectors for less-than or equal

    @code
    r0 = (a0 <= b0) ? 0xffffffffffffffff : 0x0
    r1 = (a1 <= b1) ? 0xffffffffffffffff : 0x0
    @endcode
*/
inline int128 cmp_le(float64x2 a, float64x2 b)
{
    return int64x2(_mm_cmple_pd(a, b));
}


/** Compares the values of two float32x4 vectors for greater-than or equal

    @code
    r0 = (a0 >= b0) ? 0xffffffff : 0x0
    r1 = (a1 >= b1) ? 0xffffffff : 0x0
    r2 = (a2 >= b2) ? 0xffffffff : 0x0
    r3 = (a3 >= b3) ? 0xffffffff : 0x0
    @endcode
*/
inline int128 cmp_ge(float32x4 a, float32x4 b)
{
    return int32x4(_mm_cmpge_ps(a, b));
}

/** Compares the values of two float64x2 vectors for greater-than or equal

    @code
    r0 = (a0 >= b0) ? 0xffffffffffffffff : 0x0
    r1 = (a1 >= b1) ? 0xffffffffffffffff : 0x0
    @endcode
*/
inline int128 cmp_ge(float64x2 a, float64x2 b)
{
    return int64x2(_mm_cmpge_pd(a, b));
}

/** Tests no bits are set in 128-bit integer vector. Returns @c true if
    <tt>a</tt> has all bits unset, @c false otherwise

    @icost{SSE2, SSE3, SSSE3, 3}
    @icost{SSE4.1, 2}
*/
inline bool test_zero(int128 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(int8x16::zero(), a);
#elif SIMDPP_USE_SSE2
    int8x16 r = cmp_eq((int8x16)a, int8x16::zero());
    return (_mm_movemask_epi8(r) == 0xffff);
#endif
}

/** Tests if 128-bit integer @a a consists only from zeros if a mask @a mask is
    applied. Returns @c true if <tt>a & mask</tt> has all bits unset, @c false
    otherwise

    @icost{SSE2, SSE3, SSSE3, 4}
    @icost{SSE4.1, 1}
*/
inline bool test_zero(int128 a, int128 mask)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testz_si128(a, mask);
#elif SIMDPP_USE_SSE2
    a = bit_and(a, mask);
    int8x16 r = cmp_eq((int8x16)a, int8x16::zero());
    return (_mm_movemask_epi8(r) == 0xffff);
#endif
}

/** Tests if all bits are set in a 128-bit integer. Returns @c true if @a a has
    all bits set, @c false otherwise.

    @icost{SSE2, SSE3, SSSE3, 3}
    @icost{SSE4.1, 2}
*/
inline bool test_ones(int128 a)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(a, int8x16::ones());
#elif SIMDPP_USE_SSE2
    int8x16 r = cmp_eq((int8x16)a, int8x16::ones());
    return (_mm_movemask_epi8(r) == 0xffff);
#endif
}

/** Tests if 128-bit integer consists only from ones when a mask is applied.
    Returns @c true if <tt>a & mask</tt> has all @a mask bits set, @c false
    otherwise.

    @icost{SSE2, SSE3, SSSE3, 4}
    @icost{SSE4.1, 1}
*/
inline bool test_ones(int128 a, int128 mask)
{
#if SIMDPP_USE_SSE4_1
    return _mm_testc_si128(a, mask);
#elif SIMDPP_USE_SSE2
    a = bit_andnot(mask, a);
    int8x16 r = cmp_eq((int8x16)a, int8x16::zero());
    return (_mm_movemask_epi8(r) == 0xffff);
#endif
}

#endif

} // namespace sse
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
