/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT8X16_H
#define LIBSIMDPP_SIMD_INT8X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/int128.h>
#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** Generic class representing 16x 8-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
class basic_int8x16 : public int128 {
public:

    basic_int8x16() = default;
    basic_int8x16(const basic_int8x16 &) = default;
    basic_int8x16 &operator=(const basic_int8x16 &) = default;

    /// @{
    /// Construct from base type
    basic_int8x16(const int128& d) : int128(d) {}
    basic_int8x16& operator=(const int128& d) { int128::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    basic_int8x16(__m128i d) : int128{d} {}
    basic_int8x16& operator=(__m128i d) { int128::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    basic_int8x16(uint8x16_t d) : int128{d} {}
    basic_int8x16( int8x16_t d) : int128{d} {}
    basic_int8x16& operator=(uint8x16_t d) { int128::operator=(d); return *this; }
    basic_int8x16& operator=( int8x16_t d) { int128::operator=(d); return *this; }
#endif
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint8_t& operator[](unsigned i) const  { return u8(i); }
          uint8_t& operator[](unsigned i)        { return u8(i); }
#endif
#endif
};

/** Class representing 16x 8-bit signed integer vector
*/
class int8x16 : public basic_int8x16 {
public:

    int8x16() = default;
    int8x16(const int8x16 &) = default;
    int8x16 &operator=(const int8x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int8x16(__m128i d) : basic_int8x16{d} {}
    int8x16& operator=( __m128i d) { basic_int8x16::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int8x16(int8x16_t d) : basic_int8x16{d} {}
    int8x16& operator=( int8x16_t d) { basic_int8x16::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int8x16(const int128& d) : basic_int8x16{d} {}
    int8x16(const basic_int8x16& d) : basic_int8x16{d} {}
    int8x16& operator=(int128 d) { basic_int8x16::operator=(d); return *this; }
    int8x16& operator=(basic_int8x16 d) { basic_int8x16::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const int8_t& operator[](unsigned i) const  { return i8(i); }
          int8_t& operator[](unsigned i)        { return i8(i); }
#endif
#endif

    /** Creates a signed int8x16 vector with the contents set to zero

        @code
        r0 = 0
        ...
        r15 = 0
        @endcode
    */
    static int8x16 zero();

    /** Creates a signed int8x16 vector from a value loaded from memory.

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 4}
        @icost{NEON, 1}
    */
    static int8x16 load_broadcast(const int8_t* v0);

    /** Creates a signed int8x16 vector from a value stored in a core register.

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 3}
    */
    static int8x16 set_broadcast(int8_t v0);

    /** Creates a signed int8x16 vector from a value known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
    */
    static int8x16 make_const(int8_t v0);

    /** Creates a signed int8x16 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 ]
        @endcode
    */
    static int8x16 make_const(int8_t v0, int8_t v1);

    /** Creates a signed int8x16 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v1 v2 v3 v0 v1 v2 v3 v0 v1 v2 v3 v0 v1 v2 v3 ]
        @endcode
    */
    static int8x16 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3);

    /** Creates a signed int8x16 vector from eight values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v1 v2 v3 v4 v5 v6 v7 v0 v1 v2 v3 v4 v5 v6 v7 ]
        @endcode
    */
    static int8x16 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                              int8_t v4, int8_t v5, int8_t v6, int8_t v7);

    /** Creates a signed int8x16 vector from sixteen values known at
        compile-time.

        @code
            | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  |
        r = [ v0  v1  v2  v3  v4  v5  v6  v7  v8  v9  v10 v11 v12 v13 v14 v15 ]
        @endcode
    */
    static int8x16 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                              int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                              int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                              int8_t v12, int8_t v13, int8_t v14, int8_t v15);
};

/** Class representing 16x 8-bit unsigned integer vector
*/
class uint8x16 : public basic_int8x16 {
public:

    uint8x16() = default;
    uint8x16(const uint8x16 &) = default;
    uint8x16 &operator=(const uint8x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    uint8x16(__m128i d) : basic_int8x16{d} {}
    uint8x16& operator=(__m128i d) { basic_int8x16::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint8x16(uint8x16_t d) : basic_int8x16{d} {}
    uint8x16& operator=(uint8x16_t d) { basic_int8x16::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint8x16(const int128& d) : basic_int8x16{d} {}
    uint8x16(const basic_int8x16& d) : basic_int8x16{d} {}
    uint8x16& operator=(int128 d) { basic_int8x16::operator=(d); return *this; }
    uint8x16& operator=(basic_int8x16 d) { basic_int8x16::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint8_t& operator[](unsigned i) const  { return u8(i); }
          uint8_t& operator[](unsigned i)        { return u8(i); }
#endif
#endif

    /** Creates a unsigned int8x16 vector with the contents set to zero

        @code
        r0 = 0
        ...
        r15 = 0
        @endcode
    */
    static uint8x16 zero();

    /** Creates a unsigned int8x16 vector from a value loaded from memory.

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 4}
        @icost{NEON, 1}
    */
    static uint8x16 load_broadcast(const uint8_t* v0);

    /** Creates a unsigned int8x16 vector from a value stored in a core register.

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 3}
    */
    static uint8x16 set_broadcast(uint8_t v0);

    /** Creates a unsigned int8x16 vector from a value known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 v0 ]
        @endcode
    */
    static uint8x16 make_const(uint8_t v0);

    /** Creates a unsigned int8x16 vector from two values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 v0 v1 ]
        @endcode
    */
    static uint8x16 make_const(uint8_t v0, uint8_t v1);

    /** Creates a unsigned int8x16 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v1 v2 v3 v0 v1 v2 v3 v0 v1 v2 v3 v0 v1 v2 v3 ]
        @endcode
    */
    static uint8x16 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

    /** Creates a unsigned int8x16 vector from eight values known at compile-time

        @code
            | 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |
        r = [ v0 v1 v2 v3 v4 v5 v6 v7 v0 v1 v2 v3 v4 v5 v6 v7 ]
        @endcode
    */
    static uint8x16 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

    /** Creates a unsigned int8x16 vector from sixteen values known at
        compile-time.

        @code
            | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  |
        r = [ v0  v1  v2  v3  v4  v5  v6  v7  v8  v9  v10 v11 v12 v13 v14 v15 ]
        @endcode
    */
    static uint8x16 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                               uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                               uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);
};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
