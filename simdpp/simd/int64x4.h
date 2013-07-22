/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT64X4_H
#define LIBSIMDPP_SIMD_INT64X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/int256.h>
#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

class float64x4;

/** Generic class representing 2x 64-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
class basic_int64x4 : public int256 {
public:

    basic_int64x4() = default;
    basic_int64x4(const basic_int64x4 &) = default;
    basic_int64x4 &operator=(const basic_int64x4 &) = default;

    /// @{
    /// Construct from base type
    basic_int64x4(const int256& d) : int256(d) {}
    basic_int64x4& operator=(int256 d) { int256::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    basic_int64x4(__m256i d) : int256{d} {}
    basic_int64x4& operator=(__m256i d) { int256::operator=(d); return *this; }
#endif
    /// @}

     /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit basic_int64x4(const float64x4& d);
    basic_int64x4& operator=(const float64x4& d) { operator=(basic_int64x4(d)); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    basic_int64x4(basic_int64x2 d0, basic_int64x2 d1) : int256{d0, d1} {}

    const basic_int64x2& operator[](unsigned i) const { return u64(i); }
          basic_int64x2& operator[](unsigned i)       { return u64(i); }
#endif
};

/** Class representing 2x 64-bit signed integer vector
*/
class int64x4 : public basic_int64x4 {
public:

    int64x4() = default;
    int64x4(const int64x4 &) = default;
    int64x4 &operator=(const int64x4 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    int64x4(__m256i d) : basic_int64x4{d} {}
    int64x4& operator=(__m256i d) { basic_int64x4::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int64x4(const int256& d) : basic_int64x4{d} {}
    int64x4(basic_int64x4 d) : basic_int64x4{d} {}
    int64x4& operator=(int256 d) { basic_int64x4::operator=(d); return *this; }
    int64x4& operator=(basic_int64x4 d) { basic_int64x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float64x4 integer vector type
    explicit int64x4(const float64x4& d) : basic_int64x4{d} {}
    int64x4& operator=(const float64x4& d) { basic_int64x4::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    int64x4(int64x2 d0, int64x2 d1) : basic_int64x4{d0, d1} {}

    const int64x2& operator[](unsigned i) const { return i64(i); }
          int64x2& operator[](unsigned i)       { return i64(i); }
#endif

    /** Creates a signed int64x4 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        @endcode
    */
    static int64x4 zero();

    /** Creates a signed int64x4 vector from a value loaded from memory.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static int64x4 load_broadcast(const int64_t* v0);

    /** Creates a signed int64x4 vector from a value stored in a core register.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static int64x4 set_broadcast(int64_t v0);

    /** Creates a signed int64x4 vector from a value known at compile-time

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
    */
    static int64x4 make_const(int64_t v0);

    /** Creates a signed int64x4 vector from two values known at compile-time

        @code
            | 0  1  |
        r = [ v0 v1 ]
        @endcode
    */
    static int64x4 make_const(int64_t v0, int64_t v1);

    /** Creates an signed int64x4 vector from four values known at
        compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static int64x4 make_const(int64_t v0, int64_t v1, int64_t v2, int64_t v3);

};

/** Class representing 2x 64-bit unsigned integer vector
*/
class uint64x4 : public basic_int64x4 {
public:

    uint64x4() = default;
    uint64x4(const uint64x4 &) = default;
    uint64x4 &operator=(const uint64x4 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX2
    uint64x4(__m256i d) : basic_int64x4{d} {}
    uint64x4& operator=(__m256i d) { basic_int64x4::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint64x4(const int256& d) : basic_int64x4{d} {}
    uint64x4(basic_int64x4 d) : basic_int64x4{d} {}
    uint64x4& operator=(int256 d) { basic_int64x4::operator=(d); return *this; }
    uint64x4& operator=(basic_int64x4 d) { basic_int64x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float64x4 integer vector type
    explicit uint64x4(const float64x4& d) : basic_int64x4{d} {}
    uint64x4& operator=(const float64x4& d) { basic_int64x4::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    uint64x4(uint64x2 d0, uint64x2 d1) : basic_int64x4{d0, d1} {}

    const uint64x2& operator[](unsigned i) const { return u64(i); }
          uint64x2& operator[](unsigned i)       { return u64(i); }
#endif

    /** Creates an unsigned int64x4 vector with the contents set to zero

        @code
        r0 = 0
        r1 = 0
        @endcode
    */
    static uint64x4 zero();

    /** Creates a int64x4 vector from a value loaded from memory.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 1}
    */
    static uint64x4 load_broadcast(const uint64_t* v0);

    /** Creates an unsigned int64x4 vector from a value stored in a core
        register.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, NEON, 2}
    */
    static uint64x4 set_broadcast(uint64_t v0);

    /** Creates an unsigned int64x4 vector from a value known at compile-time

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
    */
    static uint64x4 make_const(uint64_t v0);

    /** Creates an unsigned int64x4 vector from two values known at
        compile-time

        @code
            | 0  1  |
        r = [ v0 v1 ]
        @endcode
    */
    static uint64x4 make_const(uint64_t v0, uint64_t v1);

    /** Creates an unsigned int64x4 vector from four values known at
        compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static uint64x4 make_const(uint64_t v0, uint64_t v1, uint64_t v2, uint64_t v3);

};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
