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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X32_H
#define LIBSIMDPP_SIMDPP_TYPES_INT8X32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 16x 8-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint8<32, void> {
public:

    using element_type = uint8_t;
    using uint_element_type = uint8_t;
    using int_vector_type = gint8x32;
    using uint_vector_type = uint8x32;
    using half_vector_type = gint8x16;
    using base_vector_type = gint8x32;
    using mask_type = mask_int8x32;
    using maskdata_type = maskdata_int8<16>;

    static constexpr unsigned vec_length = 1;
    static constexpr unsigned length = 32;
    static constexpr unsigned num_bits = 8;
    static constexpr uint_element_type all_bits = 0xff;

    gint8<32>() = default;
    gint8<32>(const gint8x32 &) = default;
    gint8<32> &operator=(const gint8x32 &) = default;

    /// @{
    /// Construct from the underlying vector type
    gint8<32>(__m256i d) : d_(d) {}
    gint8<32>& operator=(__m256i d) { d_ = d; return *this; }
    /// @}

    /// @{
    /// Construct from compatible integer type
    template<class E>          gint8<32>(const  gint8<32,E>& d);
    template<class E> explicit gint8<32>(const gint16<16,E>& d);
    template<class E> explicit gint8<32>(const gint32<8,E>& d);
    template<class E> explicit gint8<32>(const gint64<4,E>& d);
    template<class E> gint8<32>& operator=(const  gint8<32,E>& d);
    template<class E> gint8<32>& operator=(const gint16<16,E>& d);
    template<class E> gint8<32>& operator=(const gint32<8,E>& d);
    template<class E> gint8<32>& operator=(const gint64<4,E>& d);
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint8<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint8<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const gint8x32& operator[](unsigned) const   { return *this; }
          gint8x32& operator[](unsigned)         { return *this; }
    /// @}

    /// Creates a int8x32 vector with the contents set to zero
    static gint8x32 zero();

    /// Creates a int8x32 vector with the contents set to ones
    static gint8x32 ones();

private:

    __m256i d_;
};

/** @ingroup simd_vec_int
    Class representing 16x 8-bit signed integer vector
*/
template<>
class int8<32, void> : public gint8x32 {
public:

    using element_type = int8_t;
    using base_vector_type = int8x32;

    int8<32>() = default;
    int8<32>(const int8x32 &) = default;
    int8<32> &operator=(const int8x32 &) = default;

    /// @{
    /// Construct from the underlying vector type
    int8<32>(__m256i d) : gint8x32(d) {}
    int8<32>& operator=( __m256i d) { gint8x32::operator=(d); return *this; }
    /// @}

    template<class E>          int8<32>(const  gint8<32,E>& d);
    template<class E> explicit int8<32>(const gint16<16,E>& d);
    template<class E> explicit int8<32>(const gint32<8,E>& d);
    template<class E> explicit int8<32>(const gint64<4,E>& d);
    template<class E> int8<32>& operator=(const  gint8<32,E>& d);
    template<class E> int8<32>& operator=(const gint16<16,E>& d);
    template<class E> int8<32>& operator=(const gint32<8,E>& d);
    template<class E> int8<32>& operator=(const gint64<4,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int8<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int8<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int8x32& operator[](unsigned) const   { return *this; }
          int8x32& operator[](unsigned)         { return *this; }
    /// @}

    static int8x32 zero() { return gint8x32::zero(); }
    static int8x32 ones() { return gint8x32::ones(); }

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
template<>
class uint8<32, void> : public gint8x32 {
public:
    using base_vector_type = uint8x32;

    uint8<32>() = default;
    uint8<32>(const uint8x32 &) = default;
    uint8<32>& operator=(const uint8x32 &) = default;

    /// @{
    /// Construct from the underlying vector type
    uint8<32>(__m256i d) : gint8x32(d) {}
    uint8<32>& operator=(__m256i d) { gint8x32::operator=(d); return *this; }
    /// @}

    template<class E>          uint8<32>(const  gint8<32,E>& d);
    template<class E> explicit uint8<32>(const gint16<16,E>& d);
    template<class E> explicit uint8<32>(const gint32<8,E>& d);
    template<class E> explicit uint8<32>(const gint64<4,E>& d);
    template<class E> uint8<32>& operator=(const  gint8<32,E>& d);
    template<class E> uint8<32>& operator=(const gint16<16,E>& d);
    template<class E> uint8<32>& operator=(const gint32<8,E>& d);
    template<class E> uint8<32>& operator=(const gint64<4,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint8<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint8<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint8x32& operator[](unsigned) const   { return *this; }
          uint8x32& operator[](unsigned)         { return *this; }
    /// @}

    static uint8x32 zero() { return gint8x32::zero(); }
    static uint8x32 ones() { return gint8x32::ones(); }

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

/// Class representing possibly optimized mask data for 32x 8-bit integer vector
template<>
class maskdata_int8<32> {
public:
    using base_vector_type = maskdata_int8<32>;
    static constexpr unsigned length = 32;
    static constexpr unsigned vec_length = 1;

    maskdata_int8<32>() = default;
    maskdata_int8<32>(const maskdata_int8<32> &) = default;
    maskdata_int8<32> &operator=(const maskdata_int8<32> &) = default;

    maskdata_int8<32>(int8<32> d) : d_(d) {}

    /// Convert to bitmask
    operator uint8<32>() const;

    /// @{
    /// Access base vectors
    const maskdata_int8<32>& operator[](unsigned) const { return *this; }
          maskdata_int8<32>& operator[](unsigned)       { return *this; }
    /// @}

private:
    uint8<32> d_;
};


/// Class representing a mask for 32x 8-bit integer vector
template<>
class mask_int8<32, void> : public uint8<32, void> {
public:
    mask_int8<32>() = default;
    mask_int8<32>(const mask_int8<32> &) = default;
    mask_int8<32> &operator=(const mask_int8<32> &) = default;
    mask_int8<32>(const maskdata_int8<32>& d);

    /// @{
    /// Construct from the underlying vector type
    mask_int8<32>(__m256i d);
    mask_int8<32>(uint8<32> d);
    /// @}

    mask_int8<32> eval() const { return *this; }

    const maskdata_int8<32>& mask() const { return mask_; }

private:
    maskdata_int8<32> mask_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
