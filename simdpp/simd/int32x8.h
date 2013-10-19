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

#ifndef LIBSIMDPP_SIMD_INT32X8_H
#define LIBSIMDPP_SIMD_INT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/int256.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

class float32x8;

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 4x 32-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
class basic_int32x8 : public int256 {
public:

    using element_type = uint32_t;
    using uint_element_type = uint32_t;
    using int_vector_type = basic_int32x8;
    using uint_vector_type = uint32x8;
    using half_vector_type = basic_int32x4;
    using mask_type = mask_int32x8;

    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    basic_int32x8() = default;
    basic_int32x8(const basic_int32x8&) = default;
    basic_int32x8& operator=(const basic_int32x8&) = default;

    /// @{
    /// Construct from base type
    basic_int32x8(const int256& d) : int256(d) {}
    basic_int32x8& operator=(int256 d) { int256::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    basic_int32x8(__m256i d) : int256(d) {}
    basic_int32x8& operator=(__m256i d) { int256::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit basic_int32x8(const float32x8& d);
    basic_int32x8& operator=(const float32x8& d) { operator=(basic_int32x8(d)); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    basic_int32x8(basic_int32x4 d0, basic_int32x4 d1) : int256(d0, d1) {}

    const basic_int32x4& operator[](unsigned i) const { return u32(i); }
          basic_int32x4& operator[](unsigned i)       { return u32(i); }
#endif
};

/** Class representing 4x 32-bit signed integer vector
*/
class int32x8 : public basic_int32x8 {
public:

    using element_type = int32_t;
    using half_vector_type = int32x4;

    int32x8() = default;
    int32x8(const int32x8&) = default;
    int32x8& operator=(const int32x8&) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX2
    int32x8(__m256i d) : basic_int32x8(d) {}
    int32x8& operator=(__m256i d) { basic_int32x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int32x8(const int256& d) : basic_int32x8(d) {}
    int32x8(const basic_int32x8& d) : basic_int32x8(d) {}
    int32x8& operator=(int256 d) { basic_int32x8::operator=(d); return *this; }
    int32x8& operator=(basic_int32x8 d) { basic_int32x8::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit int32x8(const float32x8& d) : basic_int32x8(d) {}
    int32x8& operator=(const float32x8& d) { basic_int32x8::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    int32x8(int32x4 d0, int32x4 d1) : basic_int32x8(d0, d1) {}

    const int32x4& operator[](unsigned i) const { return i32(i); }
          int32x4& operator[](unsigned i)       { return i32(i); }
#endif

    /** Creates a signed int32x8 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        r2 = 0
        r3 = 0
        @endcode
    */
    static int32x8 zero();

    /** Creates a signed int32x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static int32x8 load_broadcast(const int32_t* v0);

    /** Creates a signed int32x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static int32x8 set_broadcast(int32_t v0);

    /** Creates a signed int32x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static int32x8 make_const(int32_t v0);

    /** Creates a signed int32x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static int32x8 make_const(int32_t v0, int32_t v1);

    /** Creates a signed int32x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static int32x8 make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3);

    /** Creates an signed int32x8 vector from eight values known at
        compile-time

        @code
            | 0  1  ... 7  |
        r = [ v0 v1 ... v7 ]
        @endcode
    */
    static int32x8 make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3,
                              int32_t v4, int32_t v5, int32_t v6, int32_t v7);
};

/** Class representing 4x 32-bit unsigned integer vector
*/
class uint32x8 : public basic_int32x8 {
public:

    using half_vector_type = uint32x4;

    uint32x8() = default;
    uint32x8(const uint32x8&) = default;
    uint32x8& operator=(const uint32x8&) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX2
    uint32x8(__m256i d) : basic_int32x8(d) {}
    uint32x8& operator=(__m256i d) { basic_int32x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint32x8(const int256& d) : basic_int32x8(d) {}
    uint32x8(const basic_int32x8& d) : basic_int32x8(d) {}
    uint32x8& operator=(int256 d) { basic_int32x8::operator=(d); return *this; }
    uint32x8& operator=(basic_int32x8 d) { basic_int32x8::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit uint32x8(const float32x8& d) : basic_int32x8(d) {}
    uint32x8& operator=(const float32x8& d) { basic_int32x8::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    uint32x8(uint32x4 d0, uint32x4 d1) : basic_int32x8(d0, d1) {}

    const uint32x4& operator[](unsigned i) const { return u32(i); }
          uint32x4& operator[](unsigned i)       { return u32(i); }
#endif

    /** Creates an unsigned int32x8 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        r2 = 0
        r3 = 0
        @endcode
    */
    static uint32x8 zero();

    /** Creates an unsigned int32x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static uint32x8 load_broadcast(const uint32_t* v0);

    /** Creates an unsigned int32x8 vector from a value stored in a core
        register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static uint32x8 set_broadcast(uint32_t v0);

    /** Creates an unsigned int32x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static uint32x8 make_const(uint32_t v0);

    /** Creates an unsigned int32x8 vector from two values known at
        compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static uint32x8 make_const(uint32_t v0, uint32_t v1);

    /** Creates an unsigned int32x8 vector from four values known at
        compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static uint32x8 make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3);

    /** Creates an unsigned int32x8 vector from eight values known at
        compile-time

        @code
            | 0  1  ... 7  |
        r = [ v0 v1 ... v7 ]
        @endcode
    */
    static uint32x8 make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3,
                               uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7);
};

/// Class representing a mask for 8x 32-bit integer vector
class mask_int32x8 {
public:
    static constexpr unsigned length = 8;

    mask_int32x8() = default;
    mask_int32x8(const mask_int32x8 &) = default;
    mask_int32x8 &operator=(const mask_int32x8 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
    mask_int32x8(__m256i d) : d_(d) {}
    mask_int32x8(basic_int32x8 d) : d_(d) {}
#else
    mask_int32x8(mask_int32x4 m0, mask_int32x4 m1) { m_[0] = m0; m_[1] = m1; }
#endif
#endif

    /// Access the underlying type
    operator basic_int32x8() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
#else
    mask_int32x4& operator[](unsigned id) { return m_[id]; }
    const mask_int32x4& operator[](unsigned id) const { return m_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_AVX2
    basic_int32x8 d_;
#else
    mask_int32x4 m_[2];
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
