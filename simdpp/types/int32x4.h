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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X4_H
#define LIBSIMDPP_SIMDPP_TYPES_INT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int128.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 4x 32-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint32<4> : public int128 {
public:

    using element_type = uint32_t;
    using uint_element_type = uint32_t;
    using int_vector_type = basic_int32x4;
    using uint_vector_type = uint32x4;
    using mask_type = mask_int32x4;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    gint32<4>() = default;
    gint32<4>(const basic_int32x4&) = default;
    gint32<4>& operator=(const basic_int32x4&) = default;

    /// @{
    /// Construct from base type
    gint32<4>(const int128& d) : int128(d) {}
    gint32<4>& operator=(int128 d) { int_bits<16>::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    gint32<4>(__m128i d) : int128(d) {}
    gint32<4>& operator=(__m128i d) { int_bits<16>::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    gint32<4>(uint32x4_t d) : int128(d) {}
    gint32<4>( int32x4_t d) : int128(d) {}
    gint32<4>& operator=(uint32x4_t d) { int_bits<16>::operator=(d); return *this; }
    gint32<4>& operator=( int32x4_t d) { int_bits<16>::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    gint32<4>(__vector uint32_t d) : int128(d) {}
    gint32<4>(__vector  int32_t d) : int128(d) {}
    gint32<4>& operator=(__vector uint32_t d) { int_bits<16>::operator=(d); return *this; }
    gint32<4>& operator=(__vector  int32_t d) { int_bits<16>::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit gint32<4>(const float32x4& d);
    gint32<4>& operator=(const float32x4& d) { operator=(basic_int32x4(d)); return *this; }
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
template<>
class int32<4> : public basic_int32x4 {
public:

    using element_type = int32_t;

    int32<4>() = default;
    int32<4>(const int32x4&) = default;
    int32<4>& operator=(const int32x4&) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int32<4>(__m128i d) : basic_int32x4(d) {}
    int32<4>& operator=(__m128i d) { basic_int32x4::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int32<4>(int32x4_t d) : basic_int32x4(d) {}
    int32<4>& operator=(int32x4_t d) { basic_int32x4::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    int32<4>(__vector  int32_t d) : basic_int32x4(d) {}
    int32<4>& operator=(__vector  int32_t d) { basic_int32x4::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int32<4>(const int128& d) : basic_int32x4(d) {}
    int32<4>(const basic_int32x4& d) : basic_int32x4(d) {}
    int32<4>& operator=(int128 d) { basic_int32x4::operator=(d); return *this; }
    int32<4>& operator=(basic_int32x4 d) { basic_int32x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit int32<4>(const float32x4& d) : basic_int32x4(d) {}
    int32<4>& operator=(const float32x4& d) { basic_int32x4::operator=(d); return *this; }
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
template<>
class uint32<4> : public basic_int32x4 {
public:

    uint32<4>() = default;
    uint32<4>(const uint32x4&) = default;
    uint32<4>& operator=(const uint32x4&) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    uint32<4>(__m128i d) : basic_int32x4(d) {}
    uint32<4>& operator=(__m128i d) { basic_int32x4::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint32<4>(uint32x4_t d) : basic_int32x4(d) {}
    uint32<4>& operator=(uint32x4_t d) { basic_int32x4::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    uint32<4>(__vector uint32_t d) : basic_int32x4(d) {}
    uint32<4>& operator=(__vector uint32_t d) { basic_int32x4::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint32<4>(const int128& d) : basic_int32x4(d) {}
    uint32<4>(const basic_int32x4& d) : basic_int32x4(d) {}
    uint32<4>& operator=(int128 d) { basic_int32x4::operator=(d); return *this; }
    uint32<4>& operator=(basic_int32x4 d) { basic_int32x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible float32x4 integer vector type
    explicit uint32<4>(const float32x4& d) : basic_int32x4(d) {}
    uint32<4>& operator=(const float32x4& d) { basic_int32x4::operator=(d); return *this; }
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

/// Class representing mask for 4x 32-bit integer vector
template<>
class mask_int32<4> {
public:
    static constexpr unsigned length = 4;

    mask_int32<4>() = default;
    mask_int32<4>(const mask_int32x4 &) = default;
    mask_int32<4> &operator=(const mask_int32x4 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if SIMDPP_USE_SSE2
    mask_int32<4>(__m128i d) : d_(d) {}
#elif SIMDPP_USE_NEON
    mask_int32<4>(uint32x4_t d) : d_(d) {}
    mask_int32<4>( int32x4_t d) : d_(d) {}
#elif SIMDPP_USE_ALTIVEC
    mask_int32<4>(__vector int32_t d) : d_(d) {}
    mask_int32<4>(__vector uint32_t d) : d_(d) {}
    mask_int32<4>(__vector __bool int d) : d_(d) {}
#endif
#if SIMDPP_USE_NULL
#else
    mask_int32<4>(basic_int32x4 d) : d_(d) {}
#endif
#endif

    /// Access the underlying type
    operator basic_int32x4() const;

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
    basic_int32x4 d_;
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
