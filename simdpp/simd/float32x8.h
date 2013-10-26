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

#ifndef LIBSIMDPP_SIMD_FLOAT32X8_H
#define LIBSIMDPP_SIMD_FLOAT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int32x8.h>
#include <simdpp/simd/float32x4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

class basic_int32x8;

/// @ingroup simd_vec_fp
/// @{

/// Class representing a float32x8 vector
class float32x8 {
public:

    using element_type = float;
    using uint_element_type = uint32_t;
    using int_vector_type = basic_int32x8;
    using uint_vector_type = uint32x8;
    using half_vector_type = float32x4;
    using mask_type = mask_float32x8;

    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    float32x8() = default;
    float32x8(const float32x8&) = default;
    float32x8& operator=(const float32x8&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    float32x8(__m256 d) : d_(d) {}
    float32x8& operator=(__m256 d) { d_ = d; return *this; }
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_AVX
    operator __m256() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int32x8 integer vector type
#if SIMDPP_USE_AVX2
    explicit float32x8(basic_int32x8 d) : d_(_mm256_castsi256_ps(d)) {}
#elif SIMDPP_USE_AVX
    explicit float32x8(basic_int32x8 d)
    {
        d_ = _mm256_castsi256_ps(_mm256_insertf128_si256(_mm256_castsi128_si256(d[0]), d[1], 1));
    }
#else
    explicit float32x8(basic_int32x8 d)
    {
        d_[0] = int32x4(d[0]);
        d_[1] = int32x4(d[1]);
    }
#endif
    float32x8& operator=(basic_int32x8 d) { operator=(float32x8(d)); return *this; }
    /// @}

#if SIMDPP_USE_AVX
#else
    float32x8(float32x4 d0, float32x4 d1) { d_[0] = d0;  d_[1] = d1; }

    const float32x4& operator[](unsigned i) const { return d_[i]; }
          float32x4& operator[](unsigned i)       { return d_[i]; }
#endif

    /** Creates a float32x8 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32x8 zero();

    /** Creates a float32x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float32x8 load_broadcast(const float* v0);

    /** Creates a float32x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 2}
    */
    static float32x8 set_broadcast(float v0);

    /** Creates a float32x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static float32x8 make_const(float v0);

    /** Creates a float32x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static float32x8 make_const(float v0, float v1);

    /** Creates a float32x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static float32x8 make_const(float v0, float v1, float v2, float v3);

    /** Creates a float32x8 vector from four values known at compile-time

        @code
            | 0  1  ... 7  |
        r = [ v0 v1 ... v7 ]
        @endcode
    */
    static float32x8 make_const(float v0, float v1, float v2, float v3,
                                float v4, float v5, float v6, float v7);

private:
#if SIMDPP_USE_AVX
    __m256 d_;
#else
    float32x4 d_[2];
#endif
};

/// Class representing a mask for 8x 32-bit floating-point vector
class mask_float32x8 {
public:
    static constexpr unsigned length = 8;

    mask_float32x8() = default;
    mask_float32x8(const mask_float32x8 &) = default;
    mask_float32x8 &operator=(const mask_float32x8 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX
    mask_float32x8(__m256 d) : d_(d) {}
    mask_float32x8(float32x8 d) : d_(d) {}
#else
    mask_float32x8(mask_float32x4 m0, mask_float32x4 m1) { m_[0] = m0; m_[1] = m1; }
#endif
#endif

    /// Access the underlying type
    operator float32x8() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX
#else
    mask_float32x4& operator[](unsigned id) { return m_[id]; }
    const mask_float32x4& operator[](unsigned id) const { return m_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_AVX
    float32x8 d_;
#else
    mask_float32x4 m_[2];
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
