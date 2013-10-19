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

#ifndef LIBSIMDPP_SIMD_INT8X32_H
#define LIBSIMDPP_SIMD_INT8X32_H

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

/** Generic class representing 16x 8-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
class basic_int8x32 : public int256 {
public:

    using element_type = uint8_t;
    using uint_element_type = uint8_t;
    using int_vector_type = basic_int8x32;
    using uint_vector_type = uint8x32;
    using half_vector_type = basic_int8x16;
    using mask_type = mask_int8x32;

    static constexpr unsigned length = 32;
    static constexpr unsigned num_bits = 8;
    static constexpr uint_element_type all_bits = 0xff;

    basic_int8x32() = default;
    basic_int8x32(const basic_int8x32 &) = default;
    basic_int8x32 &operator=(const basic_int8x32 &) = default;

    /// @{
    /// Construct from base type
    basic_int8x32(const int256& d) : int256(d) {}
    basic_int8x32& operator=(const int256& d) { int256::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    basic_int8x32(__m256i d) : int256(d) {}
    basic_int8x32& operator=(__m256i d) { int256::operator=(d); return *this; }
#endif
    /// @}

#if SIMDPP_USE_AVX2
#else
    basic_int8x32(basic_int8x16 d0, basic_int8x16 d1) : int256(d0, d1) {}

    const basic_int8x16& operator[](unsigned i) const { return u8(i); }
          basic_int8x16& operator[](unsigned i)       { return u8(i); }
#endif
};

/** @ingroup simd_vec_int
    Class representing 16x 8-bit signed integer vector
*/
class int8x32 : public basic_int8x32 {
public:

    using element_type = int8_t;
    using half_vector_type = int8x16;

    int8x32() = default;
    int8x32(const int8x32 &) = default;
    int8x32 &operator=(const int8x32 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    int8x32(__m256i d) : basic_int8x32(d) {}
    int8x32& operator=( __m256i d) { basic_int8x32::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    int8x32(const int256& d) : basic_int8x32(d) {}
    int8x32(const basic_int8x32& d) : basic_int8x32(d) {}
    int8x32& operator=(int256 d) { basic_int8x32::operator=(d); return *this; }
    int8x32& operator=(basic_int8x32 d) { basic_int8x32::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    int8x32(int8x16 d0, int8x16 d1) : basic_int8x32(d0, d1) {}

    const int8x16& operator[](unsigned i) const { return i8(i); }
          int8x16& operator[](unsigned i)       { return i8(i); }
#endif

    /** Creates a signed int8x32 vector with the contents set to zero

        @code
        r0 = 0
        ...
        r15 = 0
        @endcode
    */
    static int8x32 zero();

    /** Creates a signed int8x32 vector from a value loaded from memory.

        @code
            | 0  1  ... 31 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-AVX, 4}
        @icost{NEON, 1}
    */
    static int8x32 load_broadcast(const int8_t* v0);

    /** Creates a signed int8x32 vector from a value stored in a core register.

        @code
            | 0  1  ... 31 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-AVX, NEON, 3}
    */
    static int8x32 set_broadcast(int8_t v0);

    /** Creates a signed int8x32 vector from a value known at compile-time

        @code
            | 0  1  ... 31 |
        r = [ v0 v0 ... v0 ]
        @endcode
    */
    static int8x32 make_const(int8_t v0);

    /** Creates a signed int8x32 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 31 |
        r = [ v0 v1 v0 v1 ... v1 ]
        @endcode
    */
    static int8x32 make_const(int8_t v0, int8_t v1);

    /** Creates a signed int8x32 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  ... 31 |
        r = [ v0 v1 v2 v3 v0 v1 ... v3 ]
        @endcode
    */
    static int8x32 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3);

    /** Creates a signed int8x32 vector from eight values known at compile-time

        @code
            | 0  ... 7   8  ... 15  16 ... 23  24 ... 31 |
        r = [ v0 ... v7, v0 ... v7, v0 ... v7, v0 ... v7 ]
        @endcode
    */
    static int8x32 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                              int8_t v4, int8_t v5, int8_t v6, int8_t v7);

    /** Creates a signed int8x32 vector from sixteen values known at
        compile-time

        @code
            | 0  ... 15   16 ... 31  |
        r = [ v0 ... v15, v0 ... v15 ]
        @endcode
    */
    static int8x32 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                              int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                              int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                              int8_t v12, int8_t v13, int8_t v14, int8_t v15);

    /** Creates a signed int8x32 vector from thirty two values known at
        compile-time

        @code
            | 0  ... 31  ]
        r = [ v0 ... v31 ]
        @endcode
    */
    static int8x32 make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                              int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                              int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                              int8_t v12, int8_t v13, int8_t v14, int8_t v15,
                              int8_t v16, int8_t v17, int8_t v18, int8_t v19,
                              int8_t v20, int8_t v21, int8_t v22, int8_t v23,
                              int8_t v24, int8_t v25, int8_t v26, int8_t v27,
                              int8_t v28, int8_t v29, int8_t v30, int8_t v31);
};

/** @ingroup simd_vec_int
    Class representing 16x 8-bit unsigned integer vector
*/
class uint8x32 : public basic_int8x32 {
public:
    using half_vector_type = uint8x16;

    uint8x32() = default;
    uint8x32(const uint8x32 &) = default;
    uint8x32 &operator=(const uint8x32 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    uint8x32(__m256i d) : basic_int8x32(d) {}
    uint8x32& operator=(__m256i d) { basic_int8x32::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from the base type
    uint8x32(const int256& d) : basic_int8x32(d) {}
    uint8x32(const basic_int8x32& d) : basic_int8x32(d) {}
    uint8x32& operator=(int256 d) { basic_int8x32::operator=(d); return *this; }
    uint8x32& operator=(basic_int8x32 d) { basic_int8x32::operator=(d); return *this; }
    /// @}

#if SIMDPP_USE_AVX2
#else
    uint8x32(uint8x16 d0, uint8x16 d1) : basic_int8x32(d0, d1) {}

    const uint8x16& operator[](unsigned i) const { return u8(i); }
          uint8x16& operator[](unsigned i)       { return u8(i); }
#endif

    /** Creates a unsigned int8x32 vector with the contents set to zero

        @code
        r0 = 0
        ...
        r15 = 0
        @endcode
    */
    static uint8x32 zero();

    /** Creates a unsigned int8x32 vector from a value loaded from memory.

        @code
            | 0  1  ... 31 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-AVX, 4}
        @icost{NEON, 1}
    */
    static uint8x32 load_broadcast(const uint8_t* v0);

    /** Creates a unsigned int8x32 vector from a value stored in a core register.

        @code
            | 0  1  ... 31 |
        r = [ v0 v0 ... v0 ]
        @endcode
        @icost{SSE2-AVX, NEON, 3}
    */
    static uint8x32 set_broadcast(uint8_t v0);

    /** Creates a unsigned int8x32 vector from a value known at compile-time

        @code
            | 0  1  ... 31 |
        r = [ v0 v0 ... v0 ]
        @endcode
    */
    static uint8x32 make_const(uint8_t v0);

    /** Creates a unsigned int8x32 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 31 |
        r = [ v0 v1 v0 v1 ... v1 ]
        @endcode
    */
    static uint8x32 make_const(uint8_t v0, uint8_t v1);

    /** Creates a unsigned int8x32 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  5  ... 31 |
        r = [ v0 v1 v2 v3 v0 v1 ... v3 ]
        @endcode
    */
    static uint8x32 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

    /** Creates a unsigned int8x32 vector from eight values known at compile-time

        @code
            | 0  ... 7   8  ... 15  16 ... 23  24 ... 31 |
        r = [ v0 ... v7, v0 ... v7, v0 ... v7, v0 ... v7 ]
        @endcode
    */
    static uint8x32 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

    /** Creates a unsigned int8x32 vector from sixteen values known at
        compile-time

        @code
            | 0  ... 15   16 ... 31  |
        r = [ v0 ... v15, v0 ... v15 ]
        @endcode
    */
    static uint8x32 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                               uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                               uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

    /** Creates a unsigned int8x32 vector from thirty two values known at
        compile-time

        @code
            | 0  ... 31  |
        r = [ v0 ... v31 ]
        @endcode
    */
    static uint8x32 make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                               uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                               uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15,
                               uint8_t v16, uint8_t v17, uint8_t v18, uint8_t v19,
                               uint8_t v20, uint8_t v21, uint8_t v22, uint8_t v23,
                               uint8_t v24, uint8_t v25, uint8_t v26, uint8_t v27,
                               uint8_t v28, uint8_t v29, uint8_t v30, uint8_t v31);
};

/// Class representing a mask for 32x 8-bit integer vector
class mask_int8x32 {
public:
    static constexpr unsigned length = 32;

    mask_int8x32() = default;
    mask_int8x32(const mask_int8x32 &) = default;
    mask_int8x32 &operator=(const mask_int8x32 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
    mask_int8x32(__m256i d) : d_(d) {}
    mask_int8x32(basic_int8x32 d) : d_(d) {}
    mask_int8x32(int8x32 d) : d_(d) {}
    mask_int8x32(uint8x32 d) : d_(d) {}
#else
    mask_int8x32(mask_int8x16 m0, mask_int8x16 m1) { m_[0] = m0; m_[1] = m1; }
#endif
#endif

    /// Access the underlying type
    operator basic_int8x32() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
#else
    mask_int8x16& operator[](unsigned id) { return m_[id]; }
    const mask_int8x16& operator[](unsigned id) const { return m_[id]; }
#endif
#endif

private:
#if SIMDPP_USE_AVX2
    basic_int8x32 d_;
#else
    mask_int8x16 m_[2];
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
