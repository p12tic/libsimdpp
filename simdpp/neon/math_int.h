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

#ifndef LIBSIMDPP_DETAIL_NEON_MATH_INT_H
#define LIBSIMDPP_DETAIL_NEON_MATH_INT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace neon {

/** Multiplies the values of two int8x16 vectors and returns the low
    part of the multiplication

    @code
    r0 = low(a0 * b0)
    ...
    r15 = low(a15 * b15)
    @endcode
*/
inline int128 mul_lo(basic_int8x16 a, basic_int8x16 b)
{
    return vmulq_u8(a, b);
}

/** Multiplies the first 8 values of two signed int8x16 vectors and expands the
    results to 16 bits.

    @code
    r0 = a0 * b0
    ...
    r7 = a7 * b7
    @endcode
*/
inline int128 mull_lo(int8x16 a, int8x16 b)
{
    return vmullq_s8(vget_low_s8(a), vget_low_s8(b));
}

/** Multiplies the first 8 values of two unsigned int8x16 vectors and expands the
    results to 16 bits.

    @code
    r0 = a0 * b0
    ...
    r7 = a7 * b7
    @endcode
*/
inline int128 mull_lo(uint8x16 a, uint8x16 b)
{
    return vmullq_u8(vget_low_u8(a), vget_low_u8(b));
}

/** Multiplies the last 8 values of two signed int8x16 vectors and expands the
    results to 16 bits.

    @code
    r0 = a8 * b8
    ...
    r7 = a15 * b15
    @endcode
*/
inline int128 mull_hi(int8x16 a, int8x16 b)
{
    return vmullq_s8(vget_high_s8(a), vget_high_s8(b));
}


/** Multiplies the last 8 values of two unsigned int8x16 vectors and expands
    the results to 16 bits.

    @code
    r0 = a8 * b8
    ...
    r7 = a15 * b15
    @endcode
*/
inline int128 mull_hi(uint8x16 a, uint8x16 b)
{
    return vmullq_u8(vget_high_u8(a), vget_high_u8(b));
}

} // namespace neon
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
