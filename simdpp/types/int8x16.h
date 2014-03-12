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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X16_H
#define LIBSIMDPP_SIMDPP_TYPES_INT8X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <cstdint>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 16x 8-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint8<16, void> {
public:

    using element_type = uint8_t;
    using uint_element_type = uint8_t;
    using int_vector_type = gint8x16;
    using uint_vector_type = uint8x16;
    using base_vector_type = gint8x16;
    using mask_type = mask_int8x16;
    using maskdata_type = maskdata_int8<16>;

    static constexpr unsigned length = 16;
    static constexpr unsigned vec_length = 1;
    static constexpr unsigned num_bits = 8;
    static constexpr uint_element_type all_bits = 0xff;

    gint8<16>() = default;
    gint8<16>(const gint8x16 &) = default;
    gint8<16> &operator=(const gint8x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    gint8<16>(__m128i d) : d_(d) {}
    gint8<16>& operator=(__m128i d) { d_ = d; return *this; }
#elif SIMDPP_USE_NEON
    gint8<16>(uint8x16_t d) : d_(d) {}
    gint8<16>( int8x16_t d) : d_(d) {}
    gint8<16>& operator=(uint8x16_t d) { d_ = d; return *this; }
    gint8<16>& operator=( int8x16_t d) { d_ = d; return *this; }
#elif SIMDPP_USE_ALTIVEC
    gint8<16>(__vector uint8_t d) : d_(d) {}
    gint8<16>(__vector  int8_t d) : d_(d) {}
    gint8<16>& operator=(__vector uint8_t d) { d_ = d;; return *this; }
    gint8<16>& operator=(__vector  int8_t d) { d_ = d;; return *this; }
#endif
    /// @}

    /// @{
    /// Convert to underlying vector type
#if SIMDPP_USE_SSE2
    operator __m128i() const        { return d_; }
#elif SIMDPP_USE_NEON
    operator int8x16_t() const      { return vreinterpretq_s8_u8(d_); }
    operator uint8x16_t() const     { return d_; }
#elif SIMDPP_USE_ALTIVEC
    operator __vector uint8_t() const       { return (__vector uint8_t)d_; }
    operator __vector  int8_t() const       { return (__vector int8_t)d_; }
#endif
    /// @}

    /// @{
    /// Construct from compatible integer type
    template<class E>          gint8<16>(const gint8<16,E>& d);
    template<class E> explicit gint8<16>(const gint16<8,E>& d);
    template<class E> explicit gint8<16>(const gint32<4,E>& d);
    template<class E> explicit gint8<16>(const gint64<2,E>& d);
    template<class E> gint8<16>& operator=(const gint8<16,E>& d);
    template<class E> gint8<16>& operator=(const gint16<8,E>& d);
    template<class E> gint8<16>& operator=(const gint32<4,E>& d);
    template<class E> gint8<16>& operator=(const gint64<2,E>& d);
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint8<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint8<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const gint8x16& operator[](unsigned) const { return *this; }
          gint8x16& operator[](unsigned)       { return *this; }
    /// @}

    gint8<16> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint8_t& el(unsigned i) const  { return u8(i); }
          uint8_t& el(unsigned i)        { return u8(i); }
#endif
#endif

    /// Creates a int8x32 vector with the contents set to zero
    static gint8x16 zero();

    /// Creates a int8x32 vector with the contents set to ones
    static gint8x16 ones();

protected:
#if SIMDPP_USE_NULL
    const uint8_t& u8(unsigned i) const   { return du_[i]; }
          uint8_t& u8(unsigned i)         { return du_[i]; }
    const int8_t& i8(unsigned i) const   { return di_[i]; }
          int8_t& i8(unsigned i)         { return di_[i]; }
#endif

private:
#if SIMDPP_USE_SSE2
     __m128i d_;
#elif SIMDPP_USE_NEON
    uint8x16_t d_;
#elif SIMDPP_USE_ALTIVEC
    __vector uint8_t d_;
#elif SIMDPP_USE_NULL
    union {
        uint8_t du_[16];
        int8_t di_[16];
    };
#endif
};

/** Class representing 16x 8-bit signed integer vector
*/
template<>
class int8<16, void> : public gint8x16 {
public:
    using element_type = int8_t;
    using base_vector_type = int8x16;

    int8<16>() = default;
    int8<16>(const int8x16 &) = default;
    int8<16> &operator=(const int8x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int8<16>(__m128i d) : gint8x16(d) {}
    int8<16>& operator=( __m128i d) { gint8x16::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int8<16>(int8x16_t d) : gint8x16(d) {}
    int8<16>& operator=( int8x16_t d) { gint8x16::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    int8<16>(__vector int8_t d) : gint8x16(d) {}
    int8<16>& operator=( __vector int8_t d) { gint8x16::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from compatible integer type
    template<class E>          int8<16>(const gint8<16,E>& d);
    template<class E> explicit int8<16>(const gint16<8,E>& d);
    template<class E> explicit int8<16>(const gint32<4,E>& d);
    template<class E> explicit int8<16>(const gint64<2,E>& d);
    template<class E> int8<16>& operator=(const gint8<16,E>& d);
    template<class E> int8<16>& operator=(const gint16<8,E>& d);
    template<class E> int8<16>& operator=(const gint32<4,E>& d);
    template<class E> int8<16>& operator=(const gint64<2,E>& d);
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int8<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int8<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int8x16& operator[](unsigned) const { return *this; }
          int8x16& operator[](unsigned)       { return *this; }
    /// @}

    int8<16> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const int8_t& el(unsigned i) const  { return i8(i); }
          int8_t& el(unsigned i)        { return i8(i); }
#endif
#endif

    static int8x16 zero() { return gint8x16::zero(); }
    static int8x16 ones() { return gint8x16::ones(); }
};

/** Class representing 16x 8-bit unsigned integer vector
*/
template<>
class uint8<16, void> : public gint8x16 {
public:

    using element_type = uint8_t;
    using base_vector_type = uint8x16;

    uint8<16>() = default;
    uint8<16>(const uint8x16 &) = default;
    uint8<16> &operator=(const uint8x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    uint8<16>(__m128i d) : gint8x16(d) {}
    uint8<16>& operator=(__m128i d) { gint8x16::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint8<16>(uint8x16_t d) : gint8x16(d) {}
    uint8<16>& operator=(uint8x16_t d) { gint8x16::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    uint8<16>(__vector uint8_t d) : gint8x16(d) {}
    uint8<16>& operator=(__vector uint8_t d) { gint8x16::operator=(d); return *this; }
#endif
    /// @}

    /// @{
    /// Construct from compatible integer type
    template<class E>          uint8<16>(const gint8<16,E>& d);
    template<class E> explicit uint8<16>(const gint16<8,E>& d);
    template<class E> explicit uint8<16>(const gint32<4,E>& d);
    template<class E> explicit uint8<16>(const gint64<2,E>& d);
    template<class E> uint8<16>& operator=(const gint8<16,E>& d);
    template<class E> uint8<16>& operator=(const gint16<8,E>& d);
    template<class E> uint8<16>& operator=(const gint32<4,E>& d);
    template<class E> uint8<16>& operator=(const gint64<2,E>& d);
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint8<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint8<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint8x16& operator[](unsigned) const { return *this; }
          uint8x16& operator[](unsigned)       { return *this; }
    /// @}

    uint8<16> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint8_t& el(unsigned i) const  { return u8(i); }
          uint8_t& el(unsigned i)        { return u8(i); }
#endif
#endif

    static uint8x16 zero() { return gint8x16::zero(); }
    static uint8x16 ones() { return gint8x16::ones(); }
};

/// Class representing possibly optimized mask data for 16x 8-bit integer
/// vector
template<>
class maskdata_int8<16> {
public:
    using base_vector_type = maskdata_int8<16>;
    static constexpr unsigned length = 16;
    static constexpr unsigned vec_length = 1;

    maskdata_int8<16>() = default;
    maskdata_int8<16>(const maskdata_int8<16> &) = default;
    maskdata_int8<16> &operator=(const maskdata_int8<16> &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    maskdata_int8<16>(uint8x16 d) : d_(d) {}
#endif
#endif

    /// Convert to bitmask
    operator uint8x16() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    bool& el(unsigned id) { return b_[id]; }
    const bool& el(unsigned id) const { return b_[id]; }
#endif
#endif

    /// @{
    /// Access base vectors
    const maskdata_int8<16>& operator[](unsigned) const { return *this; }
          maskdata_int8<16>& operator[](unsigned)       { return *this; }
    /// @}

private:
#if SIMDPP_USE_NULL
    bool b_[16];
#else
    uint8x16 d_;
#endif
};

/// Class representing a mask for 16x 8-bit integer vector
template<>
class mask_int8<16, void> : public uint8<16, void> {
public:
    mask_int8<16>() = default;
    mask_int8<16>(const mask_int8x16 &) = default;
    mask_int8<16> &operator=(const mask_int8x16 &) = default;
    mask_int8<16>(const maskdata_int8<16>& d);

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    mask_int8<16>(__m128i d);
    mask_int8<16>(gint8<16> d);
#elif SIMDPP_USE_NEON
    mask_int8<16>(uint8x16_t d);
    mask_int8<16>(gint8<16> d);
#elif SIMDPP_USE_ALTIVEC
    mask_int8<16>(__vector uint8_t d);
    mask_int8<16>(gint8<16> d);
#endif
    /// @}

    mask_int8<16> eval() const { return *this; }

    const maskdata_int8<16>& mask() const { return mask_; }
#if !DOXYGEN_SHOULD_SKIP_THIS && SIMDPP_USE_NULL
    maskdata_int8<16>& m_mask() { return mask_; }
#endif

private:
    maskdata_int8<16> mask_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
