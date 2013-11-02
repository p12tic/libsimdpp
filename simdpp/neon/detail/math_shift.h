/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_NEON_DETAIL_MATH_SHIFT_H
#define LIBSIMDPP_NEON_DETAIL_MATH_SHIFT_H

#include <simdpp/simd.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
basic_int8x16 shift_l(basic_int8x16 a)  { return vshlq_n_u8(a, count); }
template<unsigned count>
basic_int16x8 shift_l(basic_int16x8 a)  { return vshlq_n_u16(a, count); }
template<unsigned count>
basic_int32x4 shift_l(basic_int32x4 a)  { return vshlq_n_u32(a, count); }
template<unsigned count>
basic_int64x2 shift_l(basic_int64x2 a)  { return vshlq_n_u64(a, count); }

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
inline basic_int8x16 shift_l<0>(basic_int8x16 a)  { return a; }
template<>
inline basic_int16x8 shift_l<0>(basic_int16x8 a)  { return a; }
template<>
inline basic_int32x4 shift_l<0>(basic_int32x4 a)  { return a; }
template<>
inline basic_int64x2 shift_l<0>(basic_int64x2 a)  { return a; }

} // namespace detail
} // namespace neon
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

