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

#ifndef LIBSIMDPP_SIMD_FLOAT32X4_H
#define LIBSIMDPP_SIMD_FLOAT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int32x4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

class basic_int32x4;

/// @defgroup simd_vec_fp Types: floating-point vectors
/// @{

/// Class representing float32x4 vector
class float32x4 {
public:

    using element_type = float;
    using uint_element_type = uint32_t;
    using int_vector_type = basic_int32x4;
    using uint_vector_type = uint32x4;
    using mask_type = mask_float32x4;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    float32x4() = default;
    float32x4(const float32x4&) = default;
    float32x4& operator=(const float32x4&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    float32x4(__m128 d) : d_(d) {}
    float32x4& operator=(__m128 d) { d_ = d; return *this; }
#elif SIMDPP_USE_NEON
    float32x4(float32x4_t d) : d_(d) {}
    float32x4& operator=(float32x4_t d) { d_ = d; return *this; }
#elif SIMDPP_USE_ALTIVEC
    float32x4(__vector float d) : d_(d) {}
    float32x4& operator=(__vector float d) { d_ = d; return *this; }
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_SSE2
    operator __m128() const { return d_; }
#elif SIMDPP_USE_NEON
    operator float32x4_t() const { return d_; }
#elif SIMDPP_USE_ALTIVEC
    operator __vector float() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int32x4 integer vector type
#if SIMDPP_USE_SSE2
    explicit float32x4(basic_int32x4 d) : d_(_mm_castsi128_ps(d)) {}
    float32x4& operator=(basic_int32x4 d) { d_ = _mm_castsi128_ps(d); return *this; }
#elif SIMDPP_USE_NEON
    explicit float32x4(basic_int32x4 d)  : d_(vreinterpretq_f32_s32(d)) {}
    float32x4& operator=(basic_int32x4 d) { d_ = vreinterpretq_f32_s32(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    explicit float32x4(basic_int32x4 d)  : d_((__vector float)d) {}
    float32x4& operator=(basic_int32x4 d) { d_ = (__vector float)d; return *this; }
#elif SIMDPP_USE_NULL
    explicit float32x4(basic_int32x4 d)
    {
        f32_[0] = bit_cast<float>(d[0]);
        f32_[1] = bit_cast<float>(d[1]);
        f32_[2] = bit_cast<float>(d[2]);
        f32_[3] = bit_cast<float>(d[3]);
    }
    float32x4& operator=(basic_int32x4 d) { operator=(float32x4(d)); return *this; }
#endif
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    /// For internal use only
    const float& operator[](unsigned i) const { return f32_[i]; }
          float& operator[](unsigned i)       { return f32_[i]; }
#endif
#endif

    /** Creates a float32x4 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32x4 zero();

    /** Creates a float32x4 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float32x4 load_broadcast(const float* v0);

    /** Creates a float32x4 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 2}
    */
    static float32x4 set_broadcast(float v0);

    /** Creates a float32x4 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static float32x4 make_const(float v0);

    /** Creates a float32x4 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static float32x4 make_const(float v0, float v1);

    /** Creates a float32x4 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static float32x4 make_const(float v0, float v1, float v2, float v3);

private:
#if SIMDPP_USE_SSE2
    __m128 d_;
#elif SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP
    union {
        float f32_[4];
        float32x4_t d_;
    };
#elif SIMDPP_USE_NEON
    float32x4_t d_;
#elif SIMDPP_USE_ALTIVEC
    __vector float d_;
#elif SIMDPP_USE_NULL
    float f32_[4];
#endif
};

/// Class representing a mask for 4x 32-bit floating-point vector
class mask_float32x4 {
public:
    static constexpr unsigned length = 4;

    mask_float32x4() = default;
    mask_float32x4(const mask_float32x4 &) = default;
    mask_float32x4 &operator=(const mask_float32x4 &) = default;


#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if SIMDPP_USE_SSE2
    mask_float32x4(__m128 d) : d_(d) {}
#elif SIMDPP_USE_NEON
    mask_float32x4(float32x4_t d) : d_(d) {}
    mask_float32x4(uint32x4_t d) : d_(d) {}
#elif SIMDPP_USE_ALTIVEC
    mask_float32x4(__vector float d) : d_(d) {}
    mask_float32x4(__vector __bool int d) : d_((__vector float)d) {}
#endif

#if SIMDPP_USE_NULL
#else
    mask_float32x4(float32x4 d) : d_(d) {}
#endif
#endif

    /// Access the underlying type
    operator float32x4() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    bool& operator[](unsigned id) { return b_[id]; }
    const bool& operator[](unsigned id) const { return b_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_NULL
    bool b_[4];
#else
    float32x4 d_;
#endif
};

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
