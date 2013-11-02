/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_DETAIL_NEON_SHUFFLE_H
#define LIBSIMDPP_DETAIL_NEON_SHUFFLE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
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
    int64x1_t ah, bh, al, bl;
    al = vget_low_u64(a);
    bl = vget_low_u64(b);
    ah = vget_high_u64(a);
    bh = vget_high_u64(b);
    a = vcombine_u64(bl, ah);
    b = vcombine_u64(al, bh);
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
    int64x1_t ah, bh, al, bl;
    al = vget_low_u64(a);
    bl = vget_low_u64(b);
    ah = vget_high_u64(a);
    bh = vget_high_u64(b);
    a = vcombine_u64(al, bh);
    b = vcombine_u64(bl, ah);
}

inline void transpose2(basic_int64x2& a, basic_int64x2& b)
{
    int64x1_t ah, bh, al, bl;
    al = vget_low_u64(a);
    bl = vget_low_u64(b);
    ah = vget_high_u64(a);
    bh = vget_high_u64(b);
    a = vcombine_u64(al, bl);
    b = vcombine_u64(ah, bh);
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
