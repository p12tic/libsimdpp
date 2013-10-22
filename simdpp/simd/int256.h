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

#ifndef LIBSIMDPP_SIMD_INT256_H
#define LIBSIMDPP_SIMD_INT256_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int128.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @ingroup simd_vec_int
    Base class for all 128-bit integer objects
*/
class int256 {
public:

    using element_type = uint64_t;
    using uint_element_type = uint64_t;
    using int_vector_type = int256;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    int256() = default;
    int256(const int256 &) = default;
    int256 &operator=(const int256 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX2
    int256(__m256i d) : d_(d) {}
#elif SIMDPP_USE_AVX
    int256(__m256i d)
    {
        d_[0] = _mm256_castsi256_si128(d);
        d_[1] = _mm256_extractf128_si256(d, 1);
    }
#endif
    /// @}

    /// @{
    /// Convert to underlying vector type
#if SIMDPP_USE_AVX2
    operator __m256i() const        { return d_; }
#elif SIMDPP_USE_AVX
    operator __m256i() const
    {
        return _mm256_insertf128_si256(_mm256_castsi128_si256(d_[0]), d_[1], 1);
    }
#endif
    /// @}

#if SIMDPP_USE_AVX2
#else
    int256(int128 d0, int128 d1)    { d_[0] = d0;  d_[1] = d1; }

    const int128& operator[](unsigned i) const { return d_[i]; }
          int128& operator[](unsigned i)       { return d_[i]; }
#endif

    /** Creates a 128-bit integer vector with the contents set to zero

        @code
        a[0..255] = 0
        @endcode
    */
    static int256 zero();

    /** Creates a 128-bit integer vector with contents set to ones

        @code
        a[0..255] = 0
        @endcode
    */
    static int256 ones();

protected:

#if SIMDPP_USE_AVX2
#else
    // For internaliuse only
    const uint64x2& u64(unsigned i) const   { return u64_[i]; }
          uint64x2& u64(unsigned i)         { return u64_[i]; }
    const uint32x4& u32(unsigned i) const   { return u32_[i]; }
          uint32x4& u32(unsigned i)         { return u32_[i]; }
    const uint16x8& u16(unsigned i) const   { return u16_[i]; }
          uint16x8& u16(unsigned i)         { return u16_[i]; }
    const uint8x16& u8(unsigned i) const    { return u8_[i]; }
          uint8x16& u8(unsigned i)          { return u8_[i]; }
    const int64x2& i64(unsigned i) const   { return i64_[i]; }
          int64x2& i64(unsigned i)         { return i64_[i]; }
    const int32x4& i32(unsigned i) const   { return i32_[i]; }
          int32x4& i32(unsigned i)         { return i32_[i]; }
    const int16x8& i16(unsigned i) const   { return i16_[i]; }
          int16x8& i16(unsigned i)         { return i16_[i]; }
    const int8x16& i8(unsigned i) const    { return i8_[i]; }
          int8x16& i8(unsigned i)          { return i8_[i]; }
#endif

private:

#if SIMDPP_USE_AVX2
    __m256i d_;
#else
    union {
        int128 d_[2];
        uint64x2 u64_[2];
        uint32x4 u32_[2];
        uint16x8 u16_[2];
        uint8x16 u8_[2];
        int64x2 i64_[2];
        int32x4 i32_[2];
        int16x8 i16_[2];
        int8x16 i8_[2];
    };
#endif
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
