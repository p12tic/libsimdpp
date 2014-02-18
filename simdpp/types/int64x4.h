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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X4_H
#define LIBSIMDPP_SIMDPP_TYPES_INT64X4_H

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

/** Generic class representing 4x 64-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint64<4, void> {
public:

    using element_type = uint64_t;
    using uint_element_type = uint64_t;
    using int_vector_type = gint64x4;
    using uint_vector_type = uint64x4;
    using half_vector_type = gint64x2;
    using mask_type = mask_int64x4;
    using base_vector_type = gint64x4;

    static constexpr unsigned length = 4;
    static constexpr unsigned vec_length = 1;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    gint64<4>() = default;
    gint64<4>(const gint64x4 &) = default;
    gint64<4> &operator=(const gint64x4 &) = default;

    /// @{
    /// Construct from the underlying vector type
    gint64<4>(__m256i d) : d_(d) {}
    gint64<4>& operator=(__m256i d) { d_ = d; return *this; }
    /// @}

    /// @{
    /// Construct from compatible integer type
    gint64<4>(const gint8x32& d);
    gint64<4>(const gint16x16& d);
    gint64<4>(const gint32x8& d);
    gint64<4>& operator=(const gint8x32& d);
    gint64<4>& operator=(const gint16x16& d);
    gint64<4>& operator=(const gint32x8& d);
    /// @}

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit gint64<4>(const float64x4& d);
    gint64<4>& operator=(const float64x4& d) { operator=(gint64x4(d)); return *this; }
    /// @}

    /// @{
    /// Access base vectors
    const gint64x4& operator[](unsigned) const   { return *this; }
          gint64x4& operator[](unsigned)         { return *this; }
    /// @}

    gint64<4> eval() const { return *this; }

    /// Creates a int64x4 vector with the contents set to zero
    static gint64x4 zero();

    /// Creates a int64x4 vector with the contents set to ones
    static gint64x4 ones();

private:

    __m256i d_;
};

/** Class representing 2x 64-bit signed integer vector
*/
template<>
class int64<4, void> : public gint64x4 {
public:

    using element_type = int64_t;
    using half_vector_type = int64x2;
    using base_vector_type = int64x4;

    int64<4>() = default;
    int64<4>(const int64x4 &) = default;
    int64<4> &operator=(const int64x4 &) = default;

    /// @{
    /// Construct from the underlying vector type
    int64<4>(__m256i d) : gint64x4(d) {}
    int64<4>& operator=(__m256i d) { gint64x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible integer type
    int64<4>(const gint8x32& d);
    int64<4>(const gint16x16& d);
    int64<4>(const gint32x8& d);
    int64<4>(const gint64x4& d);
    int64<4>& operator=(const gint8x32& d);
    int64<4>& operator=(const gint16x16& d);
    int64<4>& operator=(const gint32x8& d);
    int64<4>& operator=(const gint64x4& d);
    /// @}

    /// @{
    /// Construct from compatible float64x4 integer vector type
    explicit int64<4>(const float64x4& d) : gint64x4(d) {}
    int64<4>& operator=(const float64x4& d) { gint64x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Access base vectors
    const int64x4& operator[](unsigned) const   { return *this; }
          int64x4& operator[](unsigned)         { return *this; }
    /// @}

    int64<4> eval() const { return *this; }

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
template<>
class uint64<4, void> : public gint64x4 {
public:

    using half_vector_type = uint64x2;
    using base_vector_type = uint64x4;

    uint64<4>() = default;
    uint64<4>(const uint64x4 &) = default;
    uint64<4> &operator=(const uint64x4 &) = default;

    /// @{
    /// Construct from the underlying vector type
    uint64<4>(__m256i d) : gint64x4(d) {}
    uint64<4>& operator=(__m256i d) { gint64x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Construct from compatible integer type
    uint64<4>(const gint8x32& d);
    uint64<4>(const gint16x16& d);
    uint64<4>(const gint32x8& d);
    uint64<4>(const gint64x4& d);
    uint64<4>& operator=(const gint8x32& d);
    uint64<4>& operator=(const gint16x16& d);
    uint64<4>& operator=(const gint32x8& d);
    uint64<4>& operator=(const gint64x4& d);
    /// @}

    /// @{
    /// Construct from compatible float64x4 integer vector type
    explicit uint64<4>(const float64x4& d) : gint64x4(d) {}
    uint64<4>& operator=(const float64x4& d) { gint64x4::operator=(d); return *this; }
    /// @}

    /// @{
    /// Access base vectors
    const uint64x4& operator[](unsigned) const   { return *this; }
          uint64x4& operator[](unsigned)         { return *this; }
    /// @}

    uint64<4> eval() const { return *this; }

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

/// Class representing possibly optimized mask data for 4x 64-bit integer vector
template<>
class maskdata_int64<4> {
public:
    using base_vector_type = maskdata_int64<4>;
    static constexpr unsigned length = 4;
    static constexpr unsigned vec_length = 1;

    maskdata_int64<4>() = default;
    maskdata_int64<4>(const maskdata_int64<4> &) = default;
    maskdata_int64<4> &operator=(const maskdata_int64<4> &) = default;

    maskdata_int64<4>(int64<4> d) : d_(d) {}

    /// Convert to bitmask
    operator uint64<4>() const;

    /// @{
    /// Access base vectors
    const maskdata_int64<4>& operator[](unsigned) const { return *this; }
          maskdata_int64<4>& operator[](unsigned)       { return *this; }
    /// @}

private:
    uint64<4> d_;
};


/// Class representing a mask for 4x 64-bit integer vector
template<>
class mask_int64<4, void> : public uint64<4, void> {
public:
    mask_int64<4>() = default;
    mask_int64<4>(const mask_int64<4> &) = default;
    mask_int64<4> &operator=(const mask_int64<4> &) = default;
    mask_int64<4>(const maskdata_int64<4>& d);

    /// @{
    /// Construct from the underlying vector type
    mask_int64<4>(__m256i d);
    mask_int64<4>(uint64<4> d);
    /// @}

    mask_int64<4> eval() const { return *this; }

    const maskdata_int64<4>& mask() const { return mask_; }

private:
    maskdata_int64<4> mask_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
