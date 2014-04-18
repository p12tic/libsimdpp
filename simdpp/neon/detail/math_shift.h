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

template<unsigned count>
int8x16 shift_r(int8x16 a)      { return vshrq_n_s8(a, count); }
template<unsigned count>
uint8x16 shift_r(uint8x16 a)    { return vshrq_n_u8(a, count); }
template<unsigned count>
int16x8 shift_r(int16x8 a)      { return vshrq_n_s16(a, count); }
template<unsigned count>
uint16x8 shift_r(uint16x8 a)    { return vshrq_n_u16(a, count); }
template<unsigned count>
int32x4 shift_r(int32x4 a)      { return vshrq_n_s32(a, count); }
template<unsigned count>
uint32x4 shift_r(uint32x4 a)    { return vshrq_n_u32(a, count); }
template<unsigned count>
int64x2 shift_r(int64x2 a)      { return vshrq_n_s64(a, count); }
template<unsigned count>
uint64x2 shift_r(uint64x2 a)    { return vshrq_n_u64(a, count); }
template<unsigned count>
uint8x16 shift_l(uint8x16 a)  { return vshlq_n_u8(a, count); }
template<unsigned count>
uint16x8 shift_l(uint16x8 a)  { return vshlq_n_u16(a, count); }
template<unsigned count>
uint32x4 shift_l(uint32x4 a)  { return vshlq_n_u32(a, count); }
template<unsigned count>
uint64x2 shift_l(uint64x2 a)  { return vshlq_n_u64(a, count); }

template<>
inline int8x16 shift_r<0>(int8x16 a)      { return a; }
template<>
inline uint8x16 shift_r<0>(uint8x16 a)    { return a; }
template<>
inline int16x8 shift_r<0>(int16x8 a)      { return a; }
template<>
inline uint16x8 shift_r<0>(uint16x8 a)    { return a; }
template<>
inline int32x4 shift_r<0>(int32x4 a)      { return a; }
template<>
inline uint32x4 shift_r<0>(uint32x4 a)    { return a; }
template<>
inline int64x2 shift_r<0>(int64x2 a)      { return a; }
template<>
inline uint64x2 shift_r<0>(uint64x2 a)    { return a; }
template<>
inline uint8x16 shift_l<0>(uint8x16 a)  { return a; }
template<>
inline uint16x8 shift_l<0>(uint16x8 a)  { return a; }
template<>
inline uint32x4 shift_l<0>(uint32x4 a)  { return a; }
template<>
inline uint64x2 shift_l<0>(uint64x2 a)  { return a; }

} // namespace detail
} // namespace neon
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif

