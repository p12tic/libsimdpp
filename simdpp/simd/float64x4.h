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

#ifndef LIBSIMDPP_SIMD_FLOAT64X4_H
#define LIBSIMDPP_SIMD_FLOAT64X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int64x4.h>
#include <simdpp/simd/float64x2.h>
#include <simdpp/simd/cast.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

class basic_int64x4;

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x4 vector
class float64x4 {
public:

    using element_type = double;
    using uint_element_type = uint64_t;
    using int_vector_type = basic_int64x4;
    using uint_vector_type = uint64x4;
    using half_vector_type = float64x2;
    using mask_type = mask_float64x4;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    float64x4() = default;
    float64x4(const float64x4&) = default;
    float64x4& operator=(const float64x4&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    float64x4(__m256d d) : d_(d) {}
    float64x4& operator=(__m256d d) { d_ = d; return *this; }
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_AVX
    operator __m256d() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int64x4 integer vector type
#if SIMDPP_USE_AVX2
    explicit float64x4(basic_int64x4 d) : d_(_mm256_castsi256_pd(d)) {}
#elif SIMDPP_USE_AVX
    explicit float64x4(basic_int64x4 d);
#else
    explicit float64x4(basic_int64x4 d)
    {
        d_[0] = float64x2(d[0]);
        d_[1] = float64x2(d[1]);
    }
#endif
    float64x4& operator=(basic_int64x4 d) { operator=(float64x4(d)); return *this; }

    /// @}

#if SIMDPP_USE_AVX
    float64x4(float64x2 d0, float64x2 d1)
    {
        d_ = _mm256_insertf128_pd(_mm256_castpd128_pd256(d0), d1, 1);
    }
#else
    float64x4(float64x2 d0, float64x2 d1) { d_[0] = d0; d_[1] = d1; }

    const float64x2& operator[](unsigned i) const { return d_[i]; }
          float64x2& operator[](unsigned i)       { return d_[i]; }
#endif


    /** Creates a float64x4 vector with the contens set to zero

        @code
        r0 = 0.0
        ...
        r7 = 0.0
        @endcode
    */
    static float64x4 zero();

    /** Creates a float64x4 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float64x4 load_broadcast(const double* v0);

    /** Creates a float64x4 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float64x4 set_broadcast(double v0);

    /** Creates a float64x4 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static float64x4 make_const(double v0);

    /** Creates a float64x4 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static float64x4 make_const(double v0, double v1);

    /** Creates a float64x4 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static float64x4 make_const(double v0, double v1, double v2, double v3);

private:
#if SIMDPP_USE_AVX
    __m256d d_;
#else
    float64x2 d_[2];
#endif
};

/// Class representing a mask for 4x 64-bit floating-point vector
class mask_float64x4 {
public:
    static constexpr unsigned length = 4;

    mask_float64x4() = default;
    mask_float64x4(const mask_float64x4 &) = default;
    mask_float64x4 &operator=(const mask_float64x4 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX
    mask_float64x4(__m256d d) : d_(d) {}
    mask_float64x4(float64x4 d) : d_(d) {}
#else
    mask_float64x4(mask_float64x2 m0, mask_float64x2 m1) { m_[0] = m0; m_[1] = m1; }
#endif
#endif

    /// Access the underlying type
    operator float64x4() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX
#else
    mask_float64x2& operator[](unsigned id) { return m_[id]; }
    const mask_float64x2& operator[](unsigned id) const { return m_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_AVX
    float64x4 d_;
#else
    mask_float64x2 m_[2];
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
