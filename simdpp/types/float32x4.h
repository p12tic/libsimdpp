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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/core/cast.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_vec_fp Types: floating-point vectors
/// @{

/// Class representing float32x4 vector
template<>
class float32<4, void> {
public:

    using element_type = float;
    using uint_element_type = uint32_t;
    using int_vector_type = gint32x4;
    using uint_vector_type = uint32x4;
    using base_vector_type = float32x4;
    using mask_type = mask_float32x4;
    using maskdata_type = maskdata_float32<4>;

    static constexpr unsigned length = 4;
    static constexpr unsigned vec_length = 1;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    float32<4>() = default;
    float32<4>(const float32x4&) = default;
    float32<4>& operator=(const float32x4&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    float32<4>(__m128 d) : d_(d) {}
    float32<4>& operator=(__m128 d) { d_ = d; return *this; }
#elif SIMDPP_USE_NEON
    float32<4>(float32x4_t d) : d_(d) {}
    float32<4>& operator=(float32x4_t d) { d_ = d; return *this; }
#elif SIMDPP_USE_ALTIVEC
    float32<4>(__vector float d) : d_(d) {}
    float32<4>& operator=(__vector float d) { d_ = d; return *this; }
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
    explicit float32<4>(gint32x4 d)     { *this = bit_cast<float32x4>(d); }
    float32<4>& operator=(gint32x4 d)   { *this = bit_cast<float32x4>(d); return *this; }
    /// @}

    /// @{
    /// Access base vectors
    const float32x4& operator[](unsigned) const { return *this; }
          float32x4& operator[](unsigned)       { return *this; }
    /// @}

    float32<4> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    /// For internal use only
    const float& el(unsigned i) const { return f32_[i]; }
          float& el(unsigned i)       { return f32_[i]; }
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



/// Class representing possibly optimized mask data for 4x 32-bit floating point
/// vector
template<>
class maskdata_float32<4> {
public:
    using base_vector_type = maskdata_float32<4>;
    static constexpr unsigned length = 4;
    static constexpr unsigned vec_length = 1;

    maskdata_float32<4>() = default;
    maskdata_float32<4>(const maskdata_float32<4> &) = default;
    maskdata_float32<4> &operator=(const maskdata_float32<4> &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    maskdata_float32<4>(float32x4 d) : d_(d) {}
#endif
#endif

    /// Convert to bitmask
    operator float32<4>() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    bool& el(unsigned id) { return b_[id]; }
    const bool& el(unsigned id) const { return b_[id]; }
#endif
#endif

    /// @{
    /// Access base vectors
    const maskdata_float32<4>& operator[](unsigned) const { return *this; }
          maskdata_float32<4>& operator[](unsigned)       { return *this; }
    /// @}

private:
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    bool b_[4];
#else
    float32x4 d_;
#endif
};


/// Class representing a mask for 4x 32-bit floating-point vector
template<>
class mask_float32<4, void> : public float32<4, void> {
public:
    mask_float32<4>() = default;
    mask_float32<4>(const mask_float32x4 &) = default;
    mask_float32<4> &operator=(const mask_float32x4 &) = default;
    mask_float32<4>(const maskdata_float32<4>& d);

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    mask_float32<4>(__m128 d);
    mask_float32<4>(float32<4> d);
#elif SIMDPP_USE_NEON
    mask_float32<4>(float32x4_t d);
    mask_float32<4>(float32<4> d);
#elif SIMDPP_USE_ALTIVEC
    mask_float32<4>(__vector float d);
    mask_float32<4>(float32<4> d);
#endif
    /// @}

    mask_float32<4> eval() const { return *this; }

    const maskdata_float32<4>& mask() const { return mask_; }
#if !DOXYGEN_SHOULD_SKIP_THIS && SIMDPP_USE_NULL
    maskdata_float32<4>& m_mask() { return mask_; }
#endif

private:
    maskdata_float32<4> mask_;
};


/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
