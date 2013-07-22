/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NEON_SHUFFLE_H
#define LIBSIMDPP_DETAIL_NEON_SHUFFLE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace neon {

/** @code
    a0 = b0
    a1 = a1
    b0 = a0
    b1 = b1
    @endcode
*/
inline void swap_lo(basic_int64x2& a, basic_int64x2& b)
{
// As of version 4.7, GCC does not emit vswp
#ifdef __GNUC__
    asm ( "vswp %f0, %e0 \n\t" : "+w" (a), "+w" (b) : );
#else
    int64x1_t ah, bh, al, bl;
    al = vget_low_u64(a);
    bl = vget_low_u64(b);
    ah = vget_high_u64(a);
    bh = vget_high_u64(b);
    a = vcombine_u64(bl, ah);
    b = vcombine_u64(al, bh);
#endif
}

/** @code
    a0 = a0
    a1 = b1
    b0 = b0
    b1 = a1
    @endcode
*/
inline void swap_hi(basic_int64x2& a, basic_int64x2& b)
{
// As of version 4.7, GCC does not emit vswp
#ifdef __GNUC__
    asm ( "vswp %f1, %e1 \n\t" : "+w" (a), "+w" (b) : );
#else
    int64x1_t ah, bh. al, bl;
    al = vget_low_u64(a);
    bl = vget_low_u64(b);
    ah = vget_high_u64(a);
    bh = vget_high_u64(b);
    a = vcombine_u64(al, bh);
    b = vcombine_u64(bl, ah);
#endif
}

inline void transpose2(basic_int64x2& a, basic_int64x2& b)
{
// As of version 4.7, GCC does not emit vswp
#ifdef __GNUC__
    asm ( "vswp %f0, %e1 \n\t" : "+w" (a), "+w" (b) : );
#else
    int64x1_t ah, bh. al, bl;
    al = vget_low_u64(a);
    bl = vget_low_u64(b);
    ah = vget_high_u64(a);
    bh = vget_high_u64(b);
    a = vcombine_u64(al, bl);
    b = vcombine_u64(ah, bh);
#endif
}

inline basic_int64x2 zip_lo(basic_int64x2 a, basic_int64x2 b)
{
    transpose2(a, b);
    return a;
}

inline basic_int64x2 zip_hi(basic_int64x2 a, basic_int64x2 b)
{
    transpose2(a, b);
    return b;
}

} // namespace neon
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
