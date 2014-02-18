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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 4x 32-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint32<8> {
public:

    using element_type = uint32_t;
    using uint_element_type = uint32_t;
    using int_vector_type = gint32x8;
    using uint_vector_type = uint32x8;
    using half_vector_type = gint32x4;
    using mask_type = mask_int32x8;
    using base_vector_type = gint32x8;

    static constexpr unsigned vec_length = 1;
    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    gint32<8>() = default;
    gint32<8>(const gint32x8&) = default;
    gint32<8>& operator=(const gint32x8&) = default;

    /// @{
    /// Construct from the underlying vector type
    gint32<8>(__m256i d) : d_(d) {}
    gint32<8>& operator=(__m256i d) { d_ = d; return *this; }
    /// @}

    /// @{
    /// Construct from compatible integer type
    gint32<8>(const gint8x32& d);
    gint32<8>(const gint16x16& d);
    gint32<8>(const gint64x4& d);
    gint32<8>& operator=(const gint8x32& d);
    gint32<8>& operator=(const gint16x16& d);
    gint32<8>& operator=(const gint64x4& d);
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit gint32<8>(const float32x8& d);
    gint32<8>& operator=(const float32x8& d) { operator=(gint32x8(d)); return *this; }
    /// @}

    /// @{
    /// Range access
    const gint32x8* begin() const                  { return this; }
          gint32x8* begin()                        { return this; }
    const gint32x8* end() const                    { return this+1; }
          gint32x8* end()                          { return this+1; }
    const gint32x8& operator[](unsigned i) const   { return *this; }
          gint32x8& operator[](unsigned i)         { return *this; }
    /// @}

    /// Creates a int32x8 vector with the contents set to zero
    static gint32x8 zero();

    /// Creates a int32x8 vector with the contents set to ones
    static gint32x8 ones();

protected:

#if SIMDPP_USE_AVX2
#else
    // For internal use only
    const uint32x4& u32(unsigned i) const    { return du_[i]; }
          uint32x4& u32(unsigned i)          { return du_[i]; }
    const int32x4& i32(unsigned i) const    { return di_[i]; }
          int32x4& i32(unsigned i)          { return di_[i]; }
#endif

private:

#if SIMDPP_USE_AVX2
    __m256i d_;
#else
    union {
        uint32x4 du_[2];
        int32x4 di_[2];
    };
#endif
};

/** Class representing 4x 32-bit signed integer vector
*/
template<>
class int32<8> : public gint32x8 {
public:

    using element_type = int32_t;
    using half_vector_type = int32x4;
    using base_vector_type = int32x8;

    int32<8>() = default;
    int32<8>(const int32x8&) = default;
    int32<8>& operator=(const int32x8&) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX2
    int32<8>(__m256i d) : gint32x8(d) {}
    int32<8>& operator=(__m256i d) { gint32x8::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from compatible integer type
    int32<8>(const gint8x32& d);
    int32<8>(const gint16x16& d);
    int32<8>(const gint32x8& d);
    int32<8>(const gint64x4& d);
    int32<8>& operator=(const gint8x32& d);
    int32<8>& operator=(const gint16x16& d);
    int32<8>& operator=(const gint32x8& d);
    int32<8>& operator=(const gint64x4& d);
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit int32<8>(const float32x8& d) : gint32x8(d) {}
    int32<8>& operator=(const float32x8& d) { gint32x8::operator=(d); return *this; }
    /// @}

    /// @{
    /// Range access
    const int32x8* begin() const                  { return this; }
          int32x8* begin()                        { return this; }
    const int32x8* end() const                    { return this+1; }
          int32x8* end()                          { return this+1; }
    const int32x8& operator[](unsigned i) const   { return *this; }
          int32x8& operator[](unsigned i)         { return *this; }
    /// @}

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
template<>
class uint32<8> : public gint32x8 {
public:

    using half_vector_type = uint32x4;
    using base_vector_type = uint32x8;

    uint32<8>() = default;
    uint32<8>(const uint32x8&) = default;
    uint32<8>& operator=(const uint32x8&) = default;

    /// @{
    /// Construct from the underlying vector type
    uint32<8>(__m256i d) : gint32x8(d) {}
    uint32<8>& operator=(__m256i d) { gint32x8::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible integer type
    uint32<8>(const gint8x32& d);
    uint32<8>(const gint16x16& d);
    uint32<8>(const gint32x8& d);
    uint32<8>(const gint64x4& d);
    uint32<8>& operator=(const gint8x32& d);
    uint32<8>& operator=(const gint16x16& d);
    uint32<8>& operator=(const gint32x8& d);
    uint32<8>& operator=(const gint64x4& d);
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit uint32<8>(const float32x8& d) : gint32x8(d) {}
    uint32<8>& operator=(const float32x8& d) { gint32x8::operator=(d); return *this; }
    /// @}

    /// @{
    /// Range access
    const uint32x8* begin() const                  { return this; }
          uint32x8* begin()                        { return this; }
    const uint32x8* end() const                    { return this+1; }
          uint32x8* end()                          { return this+1; }
    const uint32x8& operator[](unsigned i) const   { return *this; }
          uint32x8& operator[](unsigned i)         { return *this; }
    /// @}

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
template<>
class mask_int32<8> {
public:
    static constexpr unsigned length = 8;
    using base_vector_type = mask_int32x8;

    mask_int32<8>() = default;
    mask_int32<8>(const mask_int32x8 &) = default;
    mask_int32<8> &operator=(const mask_int32x8 &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_AVX2
    mask_int32<8>(__m256i d) : d_(d) {}
    mask_int32<8>(gint32x8 d) : d_(d) {}
#else
    mask_int32<8>(mask_int32x4 m0, mask_int32x4 m1) { m_[0] = m0; m_[1] = m1; }
#endif
#endif

    /// Access the underlying type
    operator gint32x8() const;

    /// @{
    /// Range access
    const mask_int32x8* begin() const                  { return this; }
          mask_int32x8* begin()                        { return this; }
    const mask_int32x8* end() const                    { return this+1; }
          mask_int32x8* end()                          { return this+1; }
    const mask_int32x8& operator[](unsigned i) const   { return *this; }
          mask_int32x8& operator[](unsigned i)         { return *this; }
    /// @}

private:
    gint32x8 d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
