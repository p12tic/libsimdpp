/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT32X4_H
#define LIBSIMDPP_SIMD_INT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/int128.h>
#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

class float32x4;

/** Generic class representing 4x 32-bit integer vector.
        To be used where the signedness of the underlying element type is not important
*/
class basic_int32x4 : public int128 {
public:

    basic_int32x4() = default;
    basic_int32x4(const basic_int32x4&) = default;
    basic_int32x4& operator=(const basic_int32x4&) = default;

    /// @{
    /// Construct from base type
    basic_int32x4(const int128& d) : int128(d) {}
    basic_int32x4& operator=(int128 d) { int128::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    basic_int32x4(__m128i d) : int128{d} {}
    basic_int32x4& operator=(__m128i d) { int128::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    basic_int32x4(uint32x4_t d) : int128{d} {}
    basic_int32x4( int32x4_t d) : int128{d} {}
    basic_int32x4& operator=(uint32x4_t d) { int128::operator=(d); return *this; }
    basic_int32x4& operator=( int32x4_t d) { int128::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit basic_int32x4(const float32x4& d);
    basic_int32x4& operator=(const float32x4& d) { operator=(basic_int32x4(d)); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint32_t& operator[](unsigned i) const  { return u32(i); }
          uint32_t& operator[](unsigned i)        { return u32(i); }
#endif
#endif
};

/** Class representing 4x 32-bit signed integer vector
*/
class int32x4 : public basic_int32x4 {
public:

    int32x4() = default;
    int32x4(const int32x4&) = default;
    int32x4& operator=(const int32x4&) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int32x4(__m128i d) : basic_int32x4{d} {}
    int32x4& operator=(__m128i d) { basic_int32x4::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int32x4(int32x4_t d) : basic_int32x4{d} {}
    int32x4& operator=(int32x4_t d) { basic_int32x4::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int32x4(const int128& d) : basic_int32x4{d} {}
    int32x4(const basic_int32x4& d) : basic_int32x4{d} {}
    int32x4& operator=(int128 d) { basic_int32x4::operator=(d); return *this; }
    int32x4& operator=(basic_int32x4 d) { basic_int32x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit int32x4(const float32x4& d) : basic_int32x4{d} {}
    int32x4& operator=(const float32x4& d) { basic_int32x4::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const int32_t& operator[](unsigned i) const  { return i32(i); }
          int32_t& operator[](unsigned i)        { return i32(i); }
#endif
#endif

    /** Creates a signed int32x4 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        r2 = 0
        r3 = 0
        @endcode

    */
    static int32x4 zero();

    /** Creates a signed int32x4 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode

        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static int32x4 load_broadcast(const int32_t* v0);

    /** Creates a signed int32x4 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode

        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static int32x4 set_broadcast(int32_t v0);

    /** Creates a signed int32x4 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode

    */
    static int32x4 make_const(int32_t v0);

    /** Creates a signed int32x4 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode

    */
    static int32x4 make_const(int32_t v0, int32_t v1);

    /** Creates a signed int32x4 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode

    */
    static int32x4 make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3);
};

/** Class representing 4x 32-bit unsigned integer vector
*/
class uint32x4 : public basic_int32x4 {
public:

    uint32x4() = default;
    uint32x4(const uint32x4&) = default;
    uint32x4& operator=(const uint32x4&) = default;

    /// @{
    /// Construct from the underlying vector type
    #if SIMDPP_USE_SSE2
    uint32x4(__m128i d) : basic_int32x4{d} {}
    uint32x4& operator=(__m128i d) { basic_int32x4::operator=(d); return *this; }
    #elif SIMDPP_USE_NEON
    uint32x4(uint32x4_t d) : basic_int32x4{d} {}
    uint32x4& operator=(uint32x4_t d) { basic_int32x4::operator=(d); return *this; }
    #endif
    /// @}

    /// @{
    /// Construct from the base type
    uint32x4(const int128& d) : basic_int32x4{d} {}
    uint32x4(const basic_int32x4& d) : basic_int32x4{d} {}
    uint32x4& operator=(int128 d) { basic_int32x4::operator=(d); return *this; }
    uint32x4& operator=(basic_int32x4 d) { basic_int32x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit uint32x4(const float32x4& d) : basic_int32x4{d} {}
    uint32x4& operator=(const float32x4& d) { basic_int32x4::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint32_t& operator[](unsigned i) const  { return u32(i); }
          uint32_t& operator[](unsigned i)        { return u32(i); }
#endif
#endif

    /** Creates an unsigned int32x4 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        r2 = 0
        r3 = 0
        @endcode

    */
    static uint32x4 zero();

    /** Creates an unsigned int32x4 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode

        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static uint32x4 load_broadcast(const uint32_t* v0);

    /** Creates an unsigned int32x4 vector from a value stored in a core
        register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode

        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static uint32x4 set_broadcast(uint32_t v0);

    /** Creates an unsigned int32x4 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode

    */
    static uint32x4 make_const(uint32_t v0);

    /** Creates an unsigned int32x4 vector from two values known at
        compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode

    */
    static uint32x4 make_const(uint32_t v0, uint32_t v1);

    /** Creates an unsigned int32x4 vector from four values known at
        compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode

    */
    static uint32x4 make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3);
};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
