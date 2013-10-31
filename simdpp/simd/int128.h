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

#ifndef LIBSIMDPP_SIMD_INT128_H
#define LIBSIMDPP_SIMD_INT128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cstdint>
#include <simdpp/simd/fwd.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_vec_int Types: integral vectors
/// @{

/// Base class for all 128-bit integer objects
class int128 {
public:
    using element_type = uint64_t;
    using uint_element_type = uint64_t;
    using int_vector_type = int128;

    static constexpr unsigned length = 2;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    int128() = default;
    int128(const int128 &) = default;
    int128 &operator=(const int128 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int128(__m128i d) : d_(d) {}
#elif SIMDPP_USE_NEON
    int128(uint32x4_t d)  : d_(d) {}
    int128( int32x4_t d) : d_(vreinterpretq_u32_s32(d)) {}
    int128( int64x2_t d) : d_(vreinterpretq_u32_s64(d)) {}
    int128(uint64x2_t d) : d_(vreinterpretq_u32_u64(d)) {}
    int128( int16x8_t d) : d_(vreinterpretq_u32_s16(d)) {}
    int128(uint16x8_t d) : d_(vreinterpretq_u32_u16(d)) {}
    int128( int8x16_t d) : d_(vreinterpretq_u32_s8(d)) {}
    int128(uint8x16_t d) : d_(vreinterpretq_u32_u8(d)) {}
#elif SIMDPP_USE_ALTIVEC
    int128(__vector uint8_t d)          : d_(d) {}
    int128(__vector  int8_t d)          : d_((__vector uint8_t)d) {}
    int128(__vector   __bool char d)    : d_((__vector uint8_t)d) {}
    int128(__vector uint16_t d)         : d_((__vector uint8_t)d) {}
    int128(__vector  int16_t d)         : d_((__vector uint8_t)d) {}
    int128(__vector   __bool short d)   : d_((__vector uint8_t)d) {}
    int128(__vector uint32_t d)         : d_((__vector uint8_t)d) {}
    int128(__vector  int32_t d)         : d_((__vector uint8_t)d) {}
    int128(__vector   __bool int d)     : d_((__vector uint8_t)d) {}
#endif
    /// @}

    /// @{
    /// Convert to underlying vector type
#if SIMDPP_USE_SSE2
    operator __m128i() const        { return d_; }
#elif SIMDPP_USE_NEON
    operator uint32x4_t() const     { return d_; }
    operator int32x4_t() const      { return vreinterpretq_s32_u32(d_); }
    operator int64x2_t() const      { return vreinterpretq_s64_u32(d_); }
    operator uint64x2_t() const     { return vreinterpretq_u64_u32(d_); }
    operator int16x8_t() const      { return vreinterpretq_s16_u32(d_); }
    operator uint16x8_t() const     { return vreinterpretq_u16_u32(d_); }
    operator int8x16_t() const      { return vreinterpretq_s8_u32(d_); }
    operator uint8x16_t() const     { return vreinterpretq_u8_u32(d_); }
#elif SIMDPP_USE_ALTIVEC
    operator __vector uint8_t() const       { return (__vector uint8_t)d_; }
    operator __vector  int8_t() const       { return (__vector int8_t)d_; }
    operator __vector __bool int8_t() const   { return (__vector __bool int8_t)d_; }
    operator __vector uint16_t() const      { return (__vector uint16_t)d_; }
    operator __vector  int16_t() const      { return (__vector int16_t)d_; }
    operator __vector __bool int16_t() const  { return (__vector __bool int16_t)d_; }
    operator __vector uint32_t() const      { return (__vector uint32_t)d_; }
    operator __vector  int32_t() const      { return (__vector int32_t)d_; }
    operator __vector __bool int32_t() const    { return (__vector __bool int32_t)d_; }
#endif
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint64_t& operator[](unsigned i) const { return u64(i); }
          uint64_t& operator[](unsigned i)       { return u64(i); }
#endif
#endif

    /** Creates a 128-bit integer vector with the contents set to zero

        @code
        a[0..127] = 0
        @endcode
    */
    static int128 zero();

    /** Creates a 128-bit integer vector with contents set to ones

        @code
        a[0..127] = 0
        @endcode
    */
    static int128 ones();

protected:
#if SIMDPP_USE_NULL
    // For internal use only
    const uint64_t& u64(unsigned i) const   { return u64_[i]; }
          uint64_t& u64(unsigned i)         { return u64_[i]; }
    const uint32_t& u32(unsigned i) const   { return u32_[i]; }
          uint32_t& u32(unsigned i)         { return u32_[i]; }
    const uint16_t& u16(unsigned i) const   { return u16_[i]; }
          uint16_t& u16(unsigned i)         { return u16_[i]; }
    const uint8_t& u8(unsigned i) const     { return u8_[i]; }
          uint8_t& u8(unsigned i)           { return u8_[i]; }
    const int64_t& i64(unsigned i) const   { return i64_[i]; }
          int64_t& i64(unsigned i)         { return i64_[i]; }
    const int32_t& i32(unsigned i) const   { return i32_[i]; }
          int32_t& i32(unsigned i)         { return i32_[i]; }
    const int16_t& i16(unsigned i) const   { return i16_[i]; }
          int16_t& i16(unsigned i)         { return i16_[i]; }
    const int8_t& i8(unsigned i) const     { return i8_[i]; }
          int8_t& i8(unsigned i)           { return i8_[i]; }
    const float& f32(unsigned i) const     { return f32_[i]; }
          float& f32(unsigned i)           { return f32_[i]; }
    const double& f64(unsigned i) const     { return f64_[i]; }
          double& f64(unsigned i)           { return f64_[i]; }
#endif

private:
#if SIMDPP_USE_SSE2
     __m128i d_;
#elif SIMDPP_USE_NEON
    uint32x4_t d_;
#elif SIMDPP_USE_ALTIVEC
    __vector uint8_t d_;
#elif SIMDPP_USE_NULL
    union {
        uint64_t u64_[2];
        uint32_t u32_[4];
        uint16_t u16_[8];
        uint8_t u8_[16];
        int64_t i64_[2];
        int32_t i32_[4];
        int16_t i16_[8];
        int8_t i8_[16];
        double f64_[2];
        float f32_[4];
    };
#endif
};

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
