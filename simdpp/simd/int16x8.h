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

#ifndef LIBSIMDPP_SIMD_INT16X8_H
#define LIBSIMDPP_SIMD_INT16X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int128.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 8x 16-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
class basic_int16x8 : public int128 {
public:

    using element_type = uint16_t;
    using uint_element_type = uint16_t;
    using int_vector_type = basic_int16x8;
    using uint_vector_type = uint16x8;
    using mask_type = mask_int16x8;

    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;

    basic_int16x8() = default;
    basic_int16x8(const basic_int16x8 &) = default;
    basic_int16x8 &operator=(const basic_int16x8 &) = default;

    /// @{
    /// Construct from base type
    basic_int16x8(const int128& d) : int128(d) {}
    basic_int16x8& operator=(int128 d) { int128::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    basic_int16x8(__m128i d) : int128(d) {}
    basic_int16x8& operator=(__m128i d) { int128::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    basic_int16x8(uint16x8_t d) : int128(d) {}
    basic_int16x8( int16x8_t d) : int128(d) {}
    basic_int16x8& operator=(uint16x8_t d) { int128::operator=(d); return *this; }
    basic_int16x8& operator=( int16x8_t d) { int128::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    basic_int16x8(__vector uint16_t d) : int128(d) {}
    basic_int16x8(__vector  int16_t d) : int128(d) {}
    basic_int16x8& operator=(__vector uint16_t d) { int128::operator=(d); return *this; }
    basic_int16x8& operator=(__vector  int16_t d) { int128::operator=(d); return *this; }
#endif
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint16_t& operator[](unsigned i) const  { return u16(i); }
          uint16_t& operator[](unsigned i)        { return u16(i); }
#endif
#endif
};

/** Class representing 8x 16-bit signed integer vector
*/
class int16x8 : public basic_int16x8 {
public:

    using element_type = int16_t;

    int16x8() = default;
    int16x8(const int16x8 &) = default;
    int16x8 &operator=(const int16x8 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int16x8(__m128i d) : basic_int16x8(d) {}
    int16x8& operator=(__m128i d) { basic_int16x8::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int16x8(int16x8_t d) : basic_int16x8(d) {}
    int16x8& operator=(int16x8_t d) { basic_int16x8::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    int16x8(__vector int16_t d) : basic_int16x8(d) {}
    int16x8& operator=(__vector int16_t d) { basic_int16x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int16x8(const int128& d) : basic_int16x8(d) {}
    int16x8(basic_int16x8 d) : basic_int16x8(d) {}
    int16x8& operator=(int128 d) { basic_int16x8::operator=(d); return *this; }
    int16x8& operator=(basic_int16x8 d) { basic_int16x8::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const int16_t& operator[](unsigned i) const  { return i16(i); }
          int16_t& operator[](unsigned i)        { return i16(i); }
#endif
#endif

    /** Creates a signed int16x8 vector with the contents set to zero

        @code
        r0 = 0
        ...
        r7 = 0
        @endcode
    */
    static int16x8 zero();

    /** Creates a signed int16x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 3}
        @icost{NEON, 1}
    */
    static int16x8 load_broadcast(const int16_t* v0);

    /** Creates a signed int16x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{NEON, SSE2-SSE4.1, NEON, 2}
    */
    static int16x8 set_broadcast(int16_t v0);

    /** Creates a signed int16x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
    */
    static int16x8 make_const(int16_t v0);

    /** Creates a signed int16x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v0 v1 v0 v1 v0 v1 ]
        @endcode
    */
    static int16x8 make_const(int16_t v0, int16_t v1);

    /** Creates a signed int16x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v0 v1 v2 v3 ]
        @endcode
    */
    static int16x8 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3);

    /** Creates a signed int16x8 vector from eight values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v4 v5 v6 v7 ]
        @endcode
    */
    static int16x8 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                              int16_t v4, int16_t v5, int16_t v6, int16_t v7);
};

/** Class representing 8x 16-bit unsigned integer vector
*/
class uint16x8 : public basic_int16x8 {
public:

    uint16x8() = default;
    uint16x8(const uint16x8 &) = default;
    uint16x8 &operator=(const uint16x8 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    uint16x8(__m128i d) : basic_int16x8(d) {}
    uint16x8& operator=(__m128i d) { basic_int16x8::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint16x8(uint16x8_t d) : basic_int16x8(d) {}
    uint16x8& operator=(uint16x8_t d) { basic_int16x8::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    uint16x8(__vector uint16_t d) : basic_int16x8(d) {}
    uint16x8& operator=(__vector uint16_t d) { basic_int16x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint16x8(const int128& d) : basic_int16x8(d) {}
    uint16x8(basic_int16x8 d) : basic_int16x8(d) {}
    uint16x8& operator=(int128 d) { basic_int16x8::operator=(d); return *this; }
    uint16x8& operator=(basic_int16x8 d) { basic_int16x8::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint16_t& operator[](unsigned i) const  { return u16(i); }
          uint16_t& operator[](unsigned i)        { return u16(i); }
#endif
#endif

    /** Creates a unsigned int16x8 vector with the contents set to zero

        @code
        r0 = 0
        ...
        r7 = 0
        @endcode
    */
    static uint16x8 zero();

    /** Creates a unsigned int16x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 3}
        @icost{NEON, 1}
    */
    static uint16x8 load_broadcast(const uint16_t* v0);

    /** Creates a unsigned int16x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static uint16x8 set_broadcast(uint16_t v0);

    /** Creates a unsigned int16x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
    */
    static uint16x8 make_const(uint16_t v0);

    /** Creates a unsigned int16x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v0 v1 v0 v1 v0 v1 ]
        @endcode
    */
    static uint16x8 make_const(uint16_t v0, uint16_t v1);

    /** Creates a unsigned int16x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v0 v1 v2 v3 ]
        @endcode
    */
    static uint16x8 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3);

    /** Creates a unsigned int16x8 vector from eight values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v4 v5 v6 v7 ]
        @endcode
    */
    static uint16x8 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                               uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7);
};

/// Class representing mask for 8x 16-bit integer vector
class mask_int16x8 {
public:
    static constexpr unsigned length = 8;

    mask_int16x8() = default;
    mask_int16x8(const mask_int16x8 &) = default;
    mask_int16x8 &operator=(const mask_int16x8 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_SSE2
    mask_int16x8(__m128i d) : d_(d) {}
#elif SIMDPP_USE_NEON
    mask_int16x8(uint16x8_t d) : d_(d) {}
    mask_int16x8( int16x8_t d) : d_(d) {}
#elif SIMDPP_USE_ALTIVEC
    mask_int16x8(__vector int16_t d) : d_(d) {}
    mask_int16x8(__vector uint16_t d) : d_(d) {}
    mask_int16x8(__vector __bool short d) : d_(d) {}
#endif
#if SIMDPP_USE_NULL
#else
    mask_int16x8(basic_int16x8 d) : d_(d) {}
#endif
#endif

    /// Access the underlying type
    operator basic_int16x8() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    bool& operator[](unsigned id) { return b_[id]; }
    const bool& operator[](unsigned id) const { return b_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_NULL
    bool b_[8];
#else
    basic_int16x8 d_;
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
