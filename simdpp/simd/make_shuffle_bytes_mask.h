/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_SHUFFLE_BYTES_MASK_H
#define LIBSIMDPP_SIMD_SHUFFLE_BYTES_MASK_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <array>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace detail {

/// s - selector, u - number of elements per group
template<int s, unsigned u>
void assert_selector_range()
{
    static_assert(-1 <= s && s < u*2, "Selector out of range");
}

template<int s0, int s1, int u>
void assert_selector_range()
{
    static_assert(-1 <= s0 && s0 < u*2, "Selector out of range");
    static_assert(-1 <= s1 && s1 < u*2, "Selector out of range");
}

template<int s0, int s1, int s2, int s3, int u>
void assert_selector_range()
{
    static_assert(-1 <= s0 && s0 < u*2, "Selector out of range");
    static_assert(-1 <= s1 && s1 < u*2, "Selector out of range");
    static_assert(-1 <= s2 && s2 < u*2, "Selector out of range");
    static_assert(-1 <= s3 && s3 < u*2, "Selector out of range");
}

/// s - selector, u - the number of elements per group
template<int s, int u>
uint8_t get_shuffle_bytex1_16()
{
    return (s == -1) ? 0x80 : (s < u ? s : (s-u)+16);
}

/// s - selector, u - the number of elements per group
template<int s, int u>
std::array<uint8_t,2> get_shuffle_bytex2_16()
{
    std::array<uint8_t,2> r;
    r[0] = (s == -1) ? 0x80 : (s < u ? s*2   : (s-u)*2+16);
    r[1] = (s == -1) ? 0x80 : r[0]+1;
    return r;
}

/// s - selector, u - the number of elements per group
template<int s, int u>
std::array<uint8_t,4> get_shuffle_bytex4_16()
{
    std::array<uint8_t,4> r;
    r[0] = (s == -1) ? 0x80 : (s < u ? s*4   : (s-u)*4+16);
    r[1] = (s == -1) ? 0x80 : r[0]+1;
    r[2] = (s == -1) ? 0x80 : r[0]+2;
    r[3] = (s == -1) ? 0x80 : r[0]+3;
    return r;
}

} // namespace detail

/// @{
/** Makes a mask to shuffle an int8x16 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    All elements within vectors are grouped into sets of two adjacent elements.
    Elements within each set of the resulting vector can be selected only from
    corresponding sets of the source vectors.

    The template arguments define which elements to select from each element
    group:
     * Values [0,1] select elements from the first vector.
     * Values [2,3] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1] : b[s1])
    r2 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0+2] : b[s0+2])
    r3 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1+2] : b[s1+2])
    ...
    r14 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0+14] : b[s0+14])
    r15 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1+14] : b[s1+14])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1>
basic_int8x16 make_shuffle_bytes16_mask(basic_int8x16 &mask)
{
    detail::assert_selector_range<s0,s1,2>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,2>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,2>();
    mask = uint8x16::make_const(b0,   b1,   b0+2, b1+2,
                                b0+4, b1+4, b0+6, b1+6,
                                b0+8, b1+8, b0+10,b1+10,
                                b0+12,b1+12,b0+14,b1+14);
    return mask;
}

template<int s0, int s1>
basic_int8x32 make_shuffle_bytes16_mask(basic_int8x32 &mask)
{
    detail::assert_selector_range<s0,s1,2>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,2>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,2>();
    mask = uint8x32::make_const(b0,   b1,   b0+2, b1+2,
                                b0+4, b1+4, b0+6, b1+6,
                                b0+8, b1+8, b0+10,b1+10,
                                b0+12,b1+12,b0+14,b1+14,
                                b0,   b1,   b0+2, b1+2,
                                b0+4, b1+4, b0+6, b1+6,
                                b0+8, b1+8, b0+10,b1+10,
                                b0+12,b1+12,b0+14,b1+14);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int8x16 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    All elements within vectors are grouped into sets of four adjacent
    elements. Elements within each set of the resulting vector can be selected
    only from corresponding sets of the source vectors.

    The template arguments define which elements to select from each element
    group:
     * Values [0,3] select elements from the first vector.
     * Values [4,7] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 4 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s1 < 4 ? a[s1] : b[s1])
    r2 = (s2 == -1) ? 0 : (s2 < 4 ? a[s2] : b[s2])
    r3 = (s3 == -1) ? 0 : (s3 < 4 ? a[s3] : b[s3])
    ...
    r12 = (s0 == -1) ? 0 : (s0 < 4 ? a[s0+12] : b[s0+12])
    r13 = (s1 == -1) ? 0 : (s1 < 4 ? a[s1+12] : b[s1+12])
    r14 = (s2 == -1) ? 0 : (s2 < 4 ? a[s2+12] : b[s2+12])
    r15 = (s3 == -1) ? 0 : (s3 < 4 ? a[s3+12] : b[s3+12])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1, int s2, int s3>
basic_int8x16 make_shuffle_bytes16_mask(basic_int8x16 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,4>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,4>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,4>();
    auto b2 = detail::get_shuffle_bytex1_16<s2,4>();
    auto b3 = detail::get_shuffle_bytex1_16<s3,4>();
    mask = uint8x16::make_const(b0,   b1,   b2,   b3,
                                b0+4, b1+4, b2+4, b3+4,
                                b0+8, b1+8, b2+8, b3+8,
                                b0+12,b1+12,b2+12,b3+12);
    return mask;
}

template<int s0, int s1, int s2, int s3>
basic_int8x32 make_shuffle_bytes16_mask(basic_int8x32 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,4>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,4>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,4>();
    auto b2 = detail::get_shuffle_bytex1_16<s2,4>();
    auto b3 = detail::get_shuffle_bytex1_16<s3,4>();
    mask = uint8x32::make_const(b0,   b1,   b2,   b3,
                                b0+4, b1+4, b2+4, b3+4,
                                b0+8, b1+8, b2+8, b3+8,
                                b0+12,b1+12,b2+12,b3+12,
                                b0,   b1,   b2,   b3,
                                b0+4, b1+4, b2+4, b3+4,
                                b0+8, b1+8, b2+8, b3+8,
                                b0+12,b1+12,b2+12,b3+12);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int8x16 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    All elements within vectors are grouped into sets of eight adjacent
    elements. Elements within each set of the resulting vector can be selected
    only from corresponding sets of the source vectors.

    The template arguments define which elements to select from each element
    group:
     * Values [0,7] select elements from the first vector.
     * Values [8,15] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 8 ? a[s0] : b[s0])
    ...
    r7 = (s7 == -1) ? 0 : (s7 < 8 ? a[s7] : b[s7])
    r8 = (s0 == -1) ? 0 : (s0 < 8 ? a[s0+8] : b[s0+8])
    ...
    r15 = (s7 == -1) ? 0 : (s7 < 8 ? a[s7+8] : b[s7+8])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7>
basic_int8x16 make_shuffle_bytes16_mask(basic_int8x16 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,8>();
    detail::assert_selector_range<s4,s5,s6,s7,8>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,8>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,8>();
    auto b2 = detail::get_shuffle_bytex1_16<s2,8>();
    auto b3 = detail::get_shuffle_bytex1_16<s3,8>();
    auto b4 = detail::get_shuffle_bytex1_16<s4,8>();
    auto b5 = detail::get_shuffle_bytex1_16<s5,8>();
    auto b6 = detail::get_shuffle_bytex1_16<s6,8>();
    auto b7 = detail::get_shuffle_bytex1_16<s7,8>();
    mask = uint8x16::make_const(b0,   b1,   b2,   b3,
                                b4,   b5,   b6,   b7,
                                b0+8, b1+8, b2+8, b3+8,
                                b4+8, b5+8, b6+8, b7+8);
    return mask;
}

template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7>
basic_int8x32 make_shuffle_bytes16_mask(basic_int8x32 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,8>();
    detail::assert_selector_range<s4,s5,s6,s7,8>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,8>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,8>();
    auto b2 = detail::get_shuffle_bytex1_16<s2,8>();
    auto b3 = detail::get_shuffle_bytex1_16<s3,8>();
    auto b4 = detail::get_shuffle_bytex1_16<s4,8>();
    auto b5 = detail::get_shuffle_bytex1_16<s5,8>();
    auto b6 = detail::get_shuffle_bytex1_16<s6,8>();
    auto b7 = detail::get_shuffle_bytex1_16<s7,8>();
    mask = uint8x32::make_const(b0,   b1,   b2,   b3,
                                b4,   b5,   b6,   b7,
                                b0+8, b1+8, b2+8, b3+8,
                                b4+8, b5+8, b6+8, b7+8,
                                b0,   b1,   b2,   b3,
                                b4,   b5,   b6,   b7,
                                b0+8, b1+8, b2+8, b3+8,
                                b4+8, b5+8, b6+8, b7+8);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int8x16 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    The template arguments define which elements to select from each element
    group:
     * Values [0,15] select elements from the first vector.
     * Values [16,32] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 16 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s0 < 16 ? a[s1] : b[s1])
    ...
    r15 = (s15 == -1) ? 0 : (s15 < 16 ? a[s15] : b[s15])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7,
         int s8, int s9, int s10, int s11, int s12, int s13, int s14, int s15>
basic_int8x16 make_shuffle_bytes16_mask(basic_int8x16 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,16>();
    detail::assert_selector_range<s4,s5,s6,s7,16>();
    detail::assert_selector_range<s8,s9,s10,s11,16>();
    detail::assert_selector_range<s12,s13,s14,s15,16>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,16>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,16>();
    auto b2 = detail::get_shuffle_bytex1_16<s2,16>();
    auto b3 = detail::get_shuffle_bytex1_16<s3,16>();
    auto b4 = detail::get_shuffle_bytex1_16<s4,16>();
    auto b5 = detail::get_shuffle_bytex1_16<s5,16>();
    auto b6 = detail::get_shuffle_bytex1_16<s6,16>();
    auto b7 = detail::get_shuffle_bytex1_16<s7,16>();
    auto b8 = detail::get_shuffle_bytex1_16<s8,16>();
    auto b9 = detail::get_shuffle_bytex1_16<s9,16>();
    auto b10 = detail::get_shuffle_bytex1_16<s10,16>();
    auto b11 = detail::get_shuffle_bytex1_16<s11,16>();
    auto b12 = detail::get_shuffle_bytex1_16<s12,16>();
    auto b13 = detail::get_shuffle_bytex1_16<s13,16>();
    auto b14 = detail::get_shuffle_bytex1_16<s14,16>();
    auto b15 = detail::get_shuffle_bytex1_16<s15,16>();
    mask = uint8x16::make_const(b0,  b1,  b2,  b3,
                                b4,  b5,  b6,  b7,
                                b8,  b9,  b10, b11,
                                b12, b13, b14, b15);
    return mask;
}

template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7,
         int s8, int s9, int s10, int s11, int s12, int s13, int s14, int s15>
basic_int8x32 make_shuffle_bytes16_mask(basic_int8x32 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,16>();
    detail::assert_selector_range<s4,s5,s6,s7,16>();
    detail::assert_selector_range<s8,s9,s10,s11,16>();
    detail::assert_selector_range<s12,s13,s14,s15,16>();
    auto b0 = detail::get_shuffle_bytex1_16<s0,16>();
    auto b1 = detail::get_shuffle_bytex1_16<s1,16>();
    auto b2 = detail::get_shuffle_bytex1_16<s2,16>();
    auto b3 = detail::get_shuffle_bytex1_16<s3,16>();
    auto b4 = detail::get_shuffle_bytex1_16<s4,16>();
    auto b5 = detail::get_shuffle_bytex1_16<s5,16>();
    auto b6 = detail::get_shuffle_bytex1_16<s6,16>();
    auto b7 = detail::get_shuffle_bytex1_16<s7,16>();
    auto b8 = detail::get_shuffle_bytex1_16<s8,16>();
    auto b9 = detail::get_shuffle_bytex1_16<s9,16>();
    auto b10 = detail::get_shuffle_bytex1_16<s10,16>();
    auto b11 = detail::get_shuffle_bytex1_16<s11,16>();
    auto b12 = detail::get_shuffle_bytex1_16<s12,16>();
    auto b13 = detail::get_shuffle_bytex1_16<s13,16>();
    auto b14 = detail::get_shuffle_bytex1_16<s14,16>();
    auto b15 = detail::get_shuffle_bytex1_16<s15,16>();
    mask = uint8x32::make_const(b0,  b1,  b2,  b3,
                                b4,  b5,  b6,  b7,
                                b8,  b9,  b10, b11,
                                b12, b13, b14, b15,
                                b0,  b1,  b2,  b3,
                                b4,  b5,  b6,  b7,
                                b8,  b9,  b10, b11,
                                b12, b13, b14, b15);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int16x8 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    All elements within vectors are grouped into sets of two adjacent elements.
    Elements within each set of the resulting vector can be selected only from
    corresponding sets of the source vectors.

    The template arguments define which elements to select from each element
    group:
     * Values [0,1] select elements from the first vector.
     * Values [2,3] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1] : b[s1])
    r2 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0+2] : b[s0+2])
    r3 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1+2] : b[s1+2])
    ...
    r6 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0+6] : b[s0+6])
    r7 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1+6] : b[s1+6])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1>
basic_int16x8 make_shuffle_bytes16_mask(basic_int16x8 &mask)
{
    detail::assert_selector_range<s0,s1,2>();
    auto b0 = detail::get_shuffle_bytex2_16<s0,2>();
    auto b1 = detail::get_shuffle_bytex2_16<s1,2>();
    mask = uint8x16::make_const(b0[0],   b0[1],   b1[0],   b1[1],
                                b0[0]+4, b0[1]+4, b1[0]+4, b1[1]+4,
                                b0[0]+8, b0[1]+8, b1[0]+8, b1[1]+8,
                                b0[0]+12,b0[1]+12,b1[0]+12,b1[1]+12);
    return mask;
}

template<int s0, int s1>
basic_int16x16 make_shuffle_bytes16_mask(basic_int16x16 &mask)
{
    detail::assert_selector_range<s0,s1,2>();
    auto b0 = detail::get_shuffle_bytex2_16<s0,2>();
    auto b1 = detail::get_shuffle_bytex2_16<s1,2>();
    mask = uint8x32::make_const(b0[0],   b0[1],   b1[0],   b1[1],
                                b0[0]+4, b0[1]+4, b1[0]+4, b1[1]+4,
                                b0[0]+8, b0[1]+8, b1[0]+8, b1[1]+8,
                                b0[0]+12,b0[1]+12,b1[0]+12,b1[1]+12,
                                b0[0],   b0[1],   b1[0],   b1[1],
                                b0[0]+4, b0[1]+4, b1[0]+4, b1[1]+4,
                                b0[0]+8, b0[1]+8, b1[0]+8, b1[1]+8,
                                b0[0]+12,b0[1]+12,b1[0]+12,b1[1]+12);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int16x8 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    All elements within vectors are grouped into sets of four adjacent
    elements. Elements within each set of the resulting vector can be selected
    only from corresponding sets of the source vectors.

    The template arguments define which elements to select from each element
    group:
     * Values [0,3] select elements from the first vector.
     * Values [4,7] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 4 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s1 < 4 ? a[s1] : b[s1])
    r2 = (s2 == -1) ? 0 : (s2 < 4 ? a[s2] : b[s2])
    r3 = (s3 == -1) ? 0 : (s3 < 4 ? a[s3] : b[s3])
    ...
    r12 = (s0 == -1) ? 0 : (s0 < 4 ? a[s0+12] : b[s0+12])
    r13 = (s1 == -1) ? 0 : (s1 < 4 ? a[s1+12] : b[s1+12])
    r14 = (s2 == -1) ? 0 : (s2 < 4 ? a[s2+12] : b[s2+12])
    r15 = (s3 == -1) ? 0 : (s3 < 4 ? a[s3+12] : b[s3+12])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1, int s2, int s3>
basic_int16x8 make_shuffle_bytes16_mask(basic_int16x8 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,4>();
    auto b0 = detail::get_shuffle_bytex2_16<s0,4>();
    auto b1 = detail::get_shuffle_bytex2_16<s1,4>();
    auto b2 = detail::get_shuffle_bytex2_16<s2,4>();
    auto b3 = detail::get_shuffle_bytex2_16<s3,4>();
    mask = uint8x16::make_const(b0[0],   b0[1],   b1[0],   b1[1],
                                b2[0],   b2[1],   b3[0],   b3[1],
                                b0[0]+8, b0[1]+8, b1[0]+8, b1[1]+8,
                                b2[0]+8, b2[1]+8, b3[0]+8, b3[1]+8);
    return mask;
}

template<int s0, int s1, int s2, int s3>
basic_int16x16 make_shuffle_bytes16_mask(basic_int16x16 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,4>();
    auto b0 = detail::get_shuffle_bytex2_16<s0,4>();
    auto b1 = detail::get_shuffle_bytex2_16<s1,4>();
    auto b2 = detail::get_shuffle_bytex2_16<s2,4>();
    auto b3 = detail::get_shuffle_bytex2_16<s3,4>();
    mask = uint8x32::make_const(b0[0],   b0[1],   b1[0],   b1[1],
                                b2[0],   b2[1],   b3[0],   b3[1],
                                b0[0]+8, b0[1]+8, b1[0]+8, b1[1]+8,
                                b2[0]+8, b2[1]+8, b3[0]+8, b3[1]+8,
                                b0[0],   b0[1],   b1[0],   b1[1],
                                b2[0],   b2[1],   b3[0],   b3[1],
                                b0[0]+8, b0[1]+8, b1[0]+8, b1[1]+8,
                                b2[0]+8, b2[1]+8, b3[0]+8, b3[1]+8);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int16x8 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    The template arguments define which elements to select from each element
    group:
     * Values [0,7] select elements from the first vector.
     * Values [8,15] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 8 ? a[s0] : b[s0])
    ...
    r7 = (s7 == -1) ? 0 : (s7 < 8 ? a[s7] : b[s7])
    r8 = (s0 == -1) ? 0 : (s0 < 8 ? a[s0+8] : b[s0+8])
    ...
    r15 = (s7 == -1) ? 0 : (s7 < 8 ? a[s7+8] : b[s7+8])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7>
basic_int16x8 make_shuffle_bytes16_mask(basic_int16x8 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,8>();
    detail::assert_selector_range<s4,s5,s6,s7,8>();

    auto b0 = detail::get_shuffle_bytex2_16<s0,8>();
    auto b1 = detail::get_shuffle_bytex2_16<s1,8>();
    auto b2 = detail::get_shuffle_bytex2_16<s2,8>();
    auto b3 = detail::get_shuffle_bytex2_16<s3,8>();
    auto b4 = detail::get_shuffle_bytex2_16<s4,8>();
    auto b5 = detail::get_shuffle_bytex2_16<s5,8>();
    auto b6 = detail::get_shuffle_bytex2_16<s6,8>();
    auto b7 = detail::get_shuffle_bytex2_16<s7,8>();
    mask = uint8x16::make_const(b0[0], b0[1], b1[0], b1[1],
                                b2[0], b2[1], b3[0], b3[1],
                                b4[0], b4[1], b5[0], b5[1],
                                b6[0], b6[1], b7[0], b7[1]);
    return mask;
}

template<int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7>
basic_int16x16 make_shuffle_bytes16_mask(basic_int16x16 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,8>();
    detail::assert_selector_range<s4,s5,s6,s7,8>();

    auto b0 = detail::get_shuffle_bytex2_16<s0,8>();
    auto b1 = detail::get_shuffle_bytex2_16<s1,8>();
    auto b2 = detail::get_shuffle_bytex2_16<s2,8>();
    auto b3 = detail::get_shuffle_bytex2_16<s3,8>();
    auto b4 = detail::get_shuffle_bytex2_16<s4,8>();
    auto b5 = detail::get_shuffle_bytex2_16<s5,8>();
    auto b6 = detail::get_shuffle_bytex2_16<s6,8>();
    auto b7 = detail::get_shuffle_bytex2_16<s7,8>();

    mask = uint8x32::make_const(b0[0], b0[1], b1[0], b1[1],
                                b2[0], b2[1], b3[0], b3[1],
                                b4[0], b4[1], b5[0], b5[1],
                                b6[0], b6[1], b7[0], b7[1],
                                b0[0], b0[1], b1[0], b1[1],
                                b2[0], b2[1], b3[0], b3[1],
                                b4[0], b4[1], b5[0], b5[1],
                                b6[0], b6[1], b7[0], b7[1]);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int32x4 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    All elements within vectors are grouped into sets of two adjacent elements.
    Elements within each set of the resulting vector can be selected only from
    corresponding sets of the source vectors.

    The template arguments define which elements to select from each element
    group:
     * Values [0,1] select elements from the first vector.
     * Values [2,3] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1] : b[s1])
    r2 = (s0 == -1) ? 0 : (s0 < 2 ? a[s0+2] : b[s0+2])
    r3 = (s1 == -1) ? 0 : (s1 < 2 ? a[s1+2] : b[s1+2])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1>
basic_int32x4 make_shuffle_bytes16_mask(basic_int32x4 &mask)
{
    detail::assert_selector_range<s0,s1,2>();
    auto b0 = detail::get_shuffle_bytex4_16<s0,2>();
    auto b1 = detail::get_shuffle_bytex4_16<s1,2>();
    mask = uint8x16::make_const(b0[0],   b0[1],   b0[2],   b0[3],
                                b1[0],   b1[1],   b1[2],   b1[3],
                                b0[0]+8, b0[1]+8, b0[2]+8, b0[3]+8,
                                b1[0]+8, b1[1]+8, b1[2]+8, b1[3]+8);
    return mask;
}

template<int s0, int s1>
basic_int32x8 make_shuffle_bytes16_mask(basic_int32x8 &mask)
{
    detail::assert_selector_range<s0,s1,2>();
    auto b0 = detail::get_shuffle_bytex4_16<s0,2>();
    auto b1 = detail::get_shuffle_bytex4_16<s1,2>();

    mask = uint8x32::make_const(b0[0],   b0[1],   b0[2],   b0[3],
                                b1[0],   b1[1],   b1[2],   b1[3],
                                b0[0]+8, b0[1]+8, b0[2]+8, b0[3]+8,
                                b1[0]+8, b1[1]+8, b1[2]+8, b1[3]+8,
                                b0[0],   b0[1],   b0[2],   b0[3],
                                b1[0],   b1[1],   b1[2],   b1[3],
                                b0[0]+8, b0[1]+8, b0[2]+8, b0[3]+8,
                                b1[0]+8, b1[1]+8, b1[2]+8, b1[3]+8);
    return mask;
}
/// @}

/// @{
/** Makes a mask to shuffle an int32x4 vector using @c permute_bytes16,
    @c shuffle_bytes16, @c permute_zbytes16 or @c shuffle_zbytes16 functions.

    The template arguments define which elements to select from each element
    group:
     * Values [0,3] select elements from the first vector.
     * Values [4,7] select elements from the second vector. The mask can only be
       used in @c shuffle_bytes16 or @c shuffle_zbytes16
     * Value [-1] sets the corresponding element to zero. The mask can only be
       used in @c permute_zbytes16 or @c shuffle_zbytes16

    @par 128-bit version:

    The created mask will cause @c shuffle_bytes16 to perform as follows:
    @code
    r0 = (s0 == -1) ? 0 : (s0 < 4 ? a[s0] : b[s0])
    r1 = (s1 == -1) ? 0 : (s1 < 4 ? a[s1] : b[s1])
    r2 = (s2 == -1) ? 0 : (s2 < 4 ? a[s2] : b[s2])
    r3 = (s3 == -1) ? 0 : (s3 < 4 ? a[s3] : b[s3])
    @endcode

    @par 256-bit version:

    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.
*/
template<int s0, int s1, int s2, int s3>
basic_int32x4 make_shuffle_bytes16_mask(basic_int32x4 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,4>();
    auto b0 = detail::get_shuffle_bytex4_16<s0,4>();
    auto b1 = detail::get_shuffle_bytex4_16<s1,4>();
    auto b2 = detail::get_shuffle_bytex4_16<s2,4>();
    auto b3 = detail::get_shuffle_bytex4_16<s3,4>();
    mask = uint8x16::make_const(b0[0], b0[1], b0[2], b0[3],
                                b1[0], b1[1], b1[2], b1[3],
                                b2[0], b2[1], b2[2], b2[3],
                                b3[0], b3[1], b3[2], b3[3]);
    return mask;
}

template<int s0, int s1, int s2, int s3>
basic_int32x8 make_shuffle_bytes16_mask(basic_int32x8 &mask)
{
    detail::assert_selector_range<s0,s1,s2,s3,4>();
    auto b0 = detail::get_shuffle_bytex4_16<s0,4>();
    auto b1 = detail::get_shuffle_bytex4_16<s1,4>();
    auto b2 = detail::get_shuffle_bytex4_16<s2,4>();
    auto b3 = detail::get_shuffle_bytex4_16<s3,4>();

    mask = uint8x32::make_const(b0[0], b0[1], b0[2], b0[3],
                                b1[0], b1[1], b1[2], b1[3],
                                b2[0], b2[1], b2[2], b2[3],
                                b3[0], b3[1], b3[2], b3[3],
                                b0[0], b0[1], b0[2], b0[3],
                                b1[0], b1[1], b1[2], b1[3],
                                b2[0], b2[1], b2[2], b2[3],
                                b3[0], b3[1], b3[2], b3[3]);
    return mask;
}
/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
