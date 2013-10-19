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

#ifndef LIBSIMDPP_SIMD_INT16X16_H
#define LIBSIMDPP_SIMD_INT16X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int256.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 16x 16-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
class basic_int16x16 : public int256 {
public:

    using element_type = uint16_t;
    using uint_element_type = uint16_t;
    using int_vector_type = basic_int16x16;
    using uint_vector_type = uint16x16;
    using half_vector_type = basic_int16x8;
    using mask_type = mask_int16x16;

    static constexpr unsigned length = 16;
    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;

    basic_int16x16() = default;
    basic_int16x16(const basic_int16x16 &) = default;
    basic_int16x16 &operator=(const basic_int16x16 &) = default;

    /// @{
    /// Construct from base type
    basic_int16x16(const int256& d) : int256(d) {}
    basic_int16x16& operator=(int256 d) { int256::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    basic_int16x16(__m256i d) : int256(d) {}
    basic_int16x16& operator=(__m256i d) { int256::operator=(d); return *this; }
#endif
    /// @}

#if SIMDPP_USE_AVX2
#else
    basic_int16x16(basic_int16x8 d0, basic_int16x8 d1) : int256(d0, d1) {}

    const basic_int16x8& operator[](unsigned i) const { return u16(i); }
          basic_int16x8& operator[](unsigned i)       { return u16(i); }
#endif
};

/** Class representing 16x 16-bit signed integer vector
*/
class int16x16 : public basic_int16x16 {
public:

    using element_type = int16_t;
    using half_vector_type = int16x8;

    int16x16() = default;
    int16x16(const int16x16 &) = default;
    int16x16 &operator=(const int16x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    int16x16(__m256i d) : basic_int16x16(d) {}
    int16x16& operator=(__m256i d) { basic_int16x16::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int16x16(const int256& d) : basic_int16x16(d) {}
    int16x16(basic_int16x16 d) : basic_int16x16(d) {}
    int16x16& operator=(int256 d) { basic_int16x16::operator=(d); return *this; }
    int16x16& operator=(basic_int16x16 d) { basic_int16x16::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    int16x16(int16x8 d0, int16x8 d1) : basic_int16x16(d0, d1) {}

    const int16x8& operator[](unsigned i) const { return i16(i); }
          int16x8& operator[](unsigned i)       { return i16(i); }
#endif

    /** Creates a signed int16x16 vector with the contents set to zero

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
    */
    static int16x16 zero();

    /** Creates a signed int16x16 vector from a value loaded from memory.

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 3}
        @icost{NEON, 1}
    */
    static int16x16 load_broadcast(const int16_t* v0);

    /** Creates a signed int16x16 vector from a value stored in a core register.

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static int16x16 set_broadcast(int16_t v0);

    /** Creates a signed int16x16 vector from a value known at compile-time

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
    */
    static int16x16 make_const(int16_t v0);

    /** Creates a signed int16x16 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  ... 15 |
        r = [ v0 v1 v0 v1 v0 ... v1 ]
        @endcode
    */
    static int16x16 make_const(int16_t v0, int16_t v1);

    /** Creates a signed int16x16 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  ... 15 |
        r = [ v0 v1 v2 v3 v0 v1 ... v3 ]
        @endcode
    */
    static int16x16 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3);

    /** Creates a signed int16x16 vector from eight values known at compile-time

        @code
            | 0  ... 7   8  ... 15 |
        r = [ v0 ... v7, v0 ... v7 ]
        @endcode
    */
    static int16x16 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                               int16_t v4, int16_t v5, int16_t v6, int16_t v7);

    /** Creates a signed int16x16 vector from eight values known at compile-time

        @code
            | 0  1  ... 15  |
        r = [ v0 v1 ... v15 ]
        @endcode
    */
    static int16x16 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                               int16_t v4, int16_t v5, int16_t v6, int16_t v7,
                               int16_t v8, int16_t v9, int16_t v10, int16_t v11,
                               int16_t v12, int16_t v13, int16_t v14, int16_t v15);
};

/** Class representing 8x 16-bit unsigned integer vector
*/
class uint16x16 : public basic_int16x16 {
public:

    using half_vector_type = uint16x8;

    uint16x16() = default;
    uint16x16(const uint16x16 &) = default;
    uint16x16 &operator=(const uint16x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    uint16x16(__m256i d) : basic_int16x16(d) {}
    uint16x16& operator=(__m256i d) { basic_int16x16::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint16x16(const int256& d) : basic_int16x16(d) {}
    uint16x16(basic_int16x16 d) : basic_int16x16(d) {}
    uint16x16& operator=(int256 d) { basic_int16x16::operator=(d); return *this; }
    uint16x16& operator=(basic_int16x16 d) { basic_int16x16::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    uint16x16(uint16x8 d0, uint16x8 d1) : basic_int16x16(d0, d1) {}

    const uint16x8& operator[](unsigned i) const { return u16(i); }
          uint16x8& operator[](unsigned i)       { return u16(i); }
#endif

    /** Creates a unsigned int16x16 vector with the contents set to zero

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
    */
    static uint16x16 zero();

    /** Creates a unsigned int16x16 vector from a value loaded from memory.

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 3}
        @icost{NEON, 1}
    */
    static uint16x16 load_broadcast(const uint16_t* v0);

    /** Creates a unsigned int16x16 vector from a value stored in a core register.

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static uint16x16 set_broadcast(uint16_t v0);

    /** Creates a unsigned int16x16 vector from a value known at compile-time

        @code
            | 0  1  ... 15 |
        r = [ v0 v0 ... v0 ]
        @endcode
    */
    static uint16x16 make_const(uint16_t v0);

    /** Creates a unsigned int16x16 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  ... 15 |
        r = [ v0 v1 v0 v1 v0 ... v1 ]
        @endcode
    */
    static uint16x16 make_const(uint16_t v0, uint16_t v1);

    /** Creates a unsigned int16x16 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  ... 15 |
        r = [ v0 v1 v2 v3 v0 v1 ... v3 ]
        @endcode
    */
    static uint16x16 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3);

    /** Creates a unsigned int16x16 vector from eight values known at compile-time

        @code
            | 0  ... 7   8  ... 15 |
        r = [ v0 ... v7, v0 ... v7 ]
        @endcode
    */
    static uint16x16 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7);

    /** Creates a unsigned int16x16 vector from eight values known at compile-time

        @code
            | 0  1  ... 15  |
        r = [ v0 v1 ... v15 ]
        @endcode
    */
    static uint16x16 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7,
                                uint16_t v8, uint16_t v9, uint16_t v10, uint16_t v11,
                                uint16_t v12, uint16_t v13, uint16_t v14, uint16_t v15);
};

/// Class representing a mask for 16x 16-bit integer vector
class mask_int16x16 {
public:
    static constexpr unsigned length = 16;

    mask_int16x16() = default;
    mask_int16x16(const mask_int16x16 &) = default;
    mask_int16x16 &operator=(const mask_int16x16 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
    mask_int16x16(__m256i d) : d_(d) {}
    mask_int16x16(basic_int16x16 d) : d_(d) {}
#else
    mask_int16x16(mask_int16x8 m0, mask_int16x8 m1) { m_[0] = m0; m_[1] = m1; }
#endif
#endif

    /// Access the underlying type
    operator basic_int16x16() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
#else
    mask_int16x8& operator[](unsigned id) { return m_[id]; }
    const mask_int16x8& operator[](unsigned id) const { return m_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_AVX2
    basic_int16x16 d_;
#else
    mask_int16x8 m_[2];
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
