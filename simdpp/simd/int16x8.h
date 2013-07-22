/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT16X8_H
#define LIBSIMDPP_SIMD_INT16X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int128.h>
#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** Generic class representing 8x 16-bit integer vector.
        To be used where the signedness of the underlying element type is not important
*/
class basic_int16x8 : public int128 {
public:

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
    basic_int16x8(__m128i d) : int128{d} {}
    basic_int16x8& operator=(__m128i d) { int128::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    basic_int16x8(uint16x8_t d) : int128{d} {}
    basic_int16x8( int16x8_t d) : int128{d} {}
    basic_int16x8& operator=(uint16x8_t d) { int128::operator=(d); return *this; }
    basic_int16x8& operator=( int16x8_t d) { int128::operator=(d); return *this; }
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

    int16x8() = default;
    int16x8(const int16x8 &) = default;
    int16x8 &operator=(const int16x8 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int16x8(__m128i d) : basic_int16x8{d} {}
    int16x8& operator=(__m128i d) { basic_int16x8::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int16x8(int16x8_t d) : basic_int16x8{d} {}
    int16x8& operator=(int16x8_t d) { basic_int16x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int16x8(const int128& d) : basic_int16x8{d} {}
    int16x8(basic_int16x8 d) : basic_int16x8{d} {}
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
    static int128 zero();

    /** Creates a signed int16x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 3}
        @icost{NEON, 1}
    */
    static int128 load_broadcast(const int16_t* v0);

    /** Creates a signed int16x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{NEON, SSE2-SSE4.1, NEON, 2}
    */
    static int128 set_broadcast(int16_t v0);

    /** Creates a signed int16x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
    */
    static int128 make_const(int16_t v0);

    /** Creates a signed int16x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v0 v1 v0 v1 v0 v1 ]
        @endcode
    */
    static int128 make_const(int16_t v0, int16_t v1);

    /** Creates a signed int16x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v0 v1 v2 v3 ]
        @endcode
    */
    static int128 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3);

    /** Creates a signed int16x8 vector from eight values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v4 v5 v6 v7 ]
        @endcode
    */
    static int128 make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
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
    uint16x8(__m128i d) : basic_int16x8{d} {}
    uint16x8& operator=(__m128i d) { basic_int16x8::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint16x8(uint16x8_t d) : basic_int16x8{d} {}
    uint16x8& operator=(uint16x8_t d) { basic_int16x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint16x8(const int128& d) : basic_int16x8{d} {}
    uint16x8(basic_int16x8 d) : basic_int16x8{d} {}
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
    static int128 zero();

    /** Creates a unsigned int16x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 3}
        @icost{NEON, 1}
    */
    static int128 load_broadcast(const uint16_t* v0);

    /** Creates a unsigned int16x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static int128 set_broadcast(uint16_t v0);

    /** Creates a unsigned int16x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
    */
    static int128 make_const(uint16_t v0);

    /** Creates a unsigned int16x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v0 v1 v0 v1 v0 v1 ]
        @endcode
    */
    static int128 make_const(uint16_t v0, uint16_t v1);

    /** Creates a unsigned int16x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v0 v1 v2 v3 ]
        @endcode
    */
    static int128 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3);

    /** Creates a unsigned int16x8 vector from eight values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  |
        r = [ v0 v1 v2 v3 v4 v5 v6 v7 ]
        @endcode
    */
    static int128 make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                             uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7);
};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
