/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT128_H
#define LIBSIMDPP_SIMD_INT128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** Base class for all 128-bit integer objects
*/
class int128 {
public:

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
#endif
    /// @}

    /// @{
    /// Convert to compatible 128-bit vector type
#if SIMDPP_USE_SSE2
    explicit operator __m128()      { return _mm_castsi128_ps(d_); }
    explicit operator __m128d()     { return _mm_castsi128_pd(d_); }
#elif SIMDPP_USE_NEON
    explicit operator float32x4_t() const    { return vreinterpretq_f32_u32(d_); }
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

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
