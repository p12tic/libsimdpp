/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NEON_DETAIL_MATH_SHIFT_H
#define LIBSIMDPP_NEON_DETAIL_MATH_SHIFT_H
#if SIMDPP_USE_NEON

#include <simdpp/types.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace neon {
namespace detail {

template<unsigned count> SIMDPP_INL
int8x16 shift_r(const int8x16& a)      { return vshrq_n_s8(a, count); }
template<unsigned count> SIMDPP_INL
uint8x16 shift_r(const uint8x16& a)    { return vshrq_n_u8(a, count); }
template<unsigned count> SIMDPP_INL
int16x8 shift_r(const int16x8& a)      { return vshrq_n_s16(a, count); }
template<unsigned count> SIMDPP_INL
uint16x8 shift_r(const uint16x8& a)    { return vshrq_n_u16(a, count); }
template<unsigned count> SIMDPP_INL
int32x4 shift_r(const int32x4& a)      { return vshrq_n_s32(a, count); }
template<unsigned count> SIMDPP_INL
uint32x4 shift_r(const uint32x4& a)    { return vshrq_n_u32(a, count); }
template<unsigned count> SIMDPP_INL
int64x2 shift_r(const int64x2& a)      { return vshrq_n_s64(a, count); }
template<unsigned count> SIMDPP_INL
uint64x2 shift_r(const uint64x2& a)    { return vshrq_n_u64(a, count); }
template<unsigned count> SIMDPP_INL
uint8x16 shift_l(const uint8x16& a)  { return vshlq_n_u8(a, count); }
template<unsigned count> SIMDPP_INL
uint16x8 shift_l(const uint16x8& a)  { return vshlq_n_u16(a, count); }
template<unsigned count> SIMDPP_INL
uint32x4 shift_l(const uint32x4& a)  { return vshlq_n_u32(a, count); }
template<unsigned count> SIMDPP_INL
uint64x2 shift_l(const uint64x2& a)  { return vshlq_n_u64(a, count); }

template<>
SIMDPP_INL int8x16 shift_r<0>(const int8x16& a)      { return a; }
template<>
SIMDPP_INL uint8x16 shift_r<0>(const uint8x16& a)    { return a; }
template<>
SIMDPP_INL int16x8 shift_r<0>(const int16x8& a)      { return a; }
template<>
SIMDPP_INL uint16x8 shift_r<0>(const uint16x8& a)    { return a; }
template<>
SIMDPP_INL int32x4 shift_r<0>(const int32x4& a)      { return a; }
template<>
SIMDPP_INL uint32x4 shift_r<0>(const uint32x4& a)    { return a; }
template<>
SIMDPP_INL int64x2 shift_r<0>(const int64x2& a)      { return a; }
template<>
SIMDPP_INL uint64x2 shift_r<0>(const uint64x2& a)    { return a; }
template<>
SIMDPP_INL uint8x16 shift_l<0>(const uint8x16& a)  { return a; }
template<>
SIMDPP_INL uint16x8 shift_l<0>(const uint16x8& a)  { return a; }
template<>
SIMDPP_INL uint32x4 shift_l<0>(const uint32x4& a)  { return a; }
template<>
SIMDPP_INL uint64x2 shift_l<0>(const uint64x2& a)  { return a; }

} // namespace detail
} // namespace neon
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif

