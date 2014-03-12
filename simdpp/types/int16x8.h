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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 8x 16-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class gint16<8, void> {
public:

    using element_type = uint16_t;
    using uint_element_type = uint16_t;
    using int_vector_type = gint16x8;
    using uint_vector_type = uint16x8;
    using mask_type = mask_int16x8;
    using base_vector_type = gint16x8;
    using maskdata_type = maskdata_int16<8>;

    static constexpr unsigned length = 8;
    static constexpr unsigned vec_length = 1;
    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;

    gint16<8>() = default;
    gint16<8>(const gint16x8 &) = default;
    gint16<8> &operator=(const gint16x8 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    gint16<8>(__m128i d) : d_(d) {}
    gint16<8>& operator=(__m128i d) { d_ = d; return *this; }
#elif SIMDPP_USE_NEON
    gint16<8>(uint16x8_t d) : d_(d) {}
    gint16<8>( int16x8_t d) : d_(d) {}
    gint16<8>& operator=(uint16x8_t d) { d_ = d; return *this; }
    gint16<8>& operator=( int16x8_t d) { d_ = d; return *this; }
#elif SIMDPP_USE_ALTIVEC
    gint16<8>(__vector uint16_t d) : d_(d) {}
    gint16<8>(__vector  int16_t d) : d_(d) {}
    gint16<8>& operator=(__vector uint16_t d) { d_ = d; return *this; }
    gint16<8>& operator=(__vector  int16_t d) { d_ = d; return *this; }
#endif
    /// @}

    /// @{
    /// Convert to underlying vector type
#if SIMDPP_USE_SSE2
    operator __m128i() const        { return d_; }
#elif SIMDPP_USE_NEON
    operator int16x8_t() const      { return vreinterpretq_s16_u16(d_); }
    operator uint16x8_t() const     { return d_; }
#elif SIMDPP_USE_ALTIVEC
    operator __vector uint16_t() const       { return d_; }
    operator __vector  int16_t() const       { return (__vector int16_t)d_; }
#endif
    /// @}

    template<class E> explicit gint16<8>(const gint8<16,E>& d);
    template<class E>          gint16<8>(const gint16<8,E>& d);
    template<class E> explicit gint16<8>(const gint32<4,E>& d);
    template<class E> explicit gint16<8>(const gint64<2,E>& d);
    template<class E> gint16<8>& operator=(const gint8<16,E>& d);
    template<class E> gint16<8>& operator=(const gint16<8,E>& d);
    template<class E> gint16<8>& operator=(const gint32<4,E>& d);
    template<class E> gint16<8>& operator=(const gint64<2,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const gint16x8& operator[](unsigned) const { return *this; }
          gint16x8& operator[](unsigned)       { return *this; }
    /// @}

    gint16<8> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint16_t& el(unsigned i) const  { return u16(i); }
          uint16_t& el(unsigned i)        { return u16(i); }
#endif
#endif

    /// Creates a int16x8 vector with the contents set to zero
    static gint16x8 zero();

    /// Creates a int16x8 vector with the contents set to ones
    static gint16x8 ones();

protected:
#if SIMDPP_USE_NULL
    const uint16_t& u16(unsigned i) const   { return du_[i]; }
          uint16_t& u16(unsigned i)         { return du_[i]; }
    const int16_t& i16(unsigned i) const   { return di_[i]; }
          int16_t& i16(unsigned i)         { return di_[i]; }
#endif

private:
#if SIMDPP_USE_SSE2
     __m128i d_;
#elif SIMDPP_USE_NEON
    uint16x8_t d_;
#elif SIMDPP_USE_ALTIVEC
    __vector uint16_t d_;
#elif SIMDPP_USE_NULL
    union {
        uint16_t du_[8];
        int16_t di_[8];
    };
#endif
};

/** Class representing 8x 16-bit signed integer vector
*/
template<>
class int16<8, void> : public gint16x8 {
public:
    using base_vector_type = int16x8;
    using element_type = int16_t;

    int16<8>() = default;
    int16<8>(const int16x8 &) = default;
    int16<8> &operator=(const int16x8 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    int16<8>(__m128i d) : gint16x8(d) {}
    int16<8>& operator=(__m128i d) { gint16x8::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    int16<8>(int16x8_t d) : gint16x8(d) {}
    int16<8>& operator=(int16x8_t d) { gint16x8::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    int16<8>(__vector int16_t d) : gint16x8(d) {}
    int16<8>& operator=(__vector int16_t d) { gint16x8::operator=(d); return *this; }
#endif
    /// @}

    template<class E> explicit int16<8>(const gint8<16,E>& d);
    template<class E>          int16<8>(const gint16<8,E>& d);
    template<class E> explicit int16<8>(const gint32<4,E>& d);
    template<class E> explicit int16<8>(const gint64<2,E>& d);
    template<class E> int16<8>& operator=(const gint8<16,E>& d);
    template<class E> int16<8>& operator=(const gint16<8,E>& d);
    template<class E> int16<8>& operator=(const gint32<4,E>& d);
    template<class E> int16<8>& operator=(const gint64<2,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int16x8& operator[](unsigned) const { return *this; }
          int16x8& operator[](unsigned)       { return *this; }
    /// @}

    int16<8> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const int16_t& el(unsigned i) const  { return i16(i); }
          int16_t& el(unsigned i)        { return i16(i); }
#endif
#endif

    static int16<8> zero() { return gint16<8>::zero(); }
    static int16<8> ones() { return gint16<8>::ones(); }
};

/** Class representing 8x 16-bit unsigned integer vector
*/
template<>
class uint16<8, void> : public gint16x8 {
public:
    using base_vector_type = uint16x8;

    uint16<8>() = default;
    uint16<8>(const uint16x8 &) = default;
    uint16<8> &operator=(const uint16x8 &) = default;

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    uint16<8>(__m128i d) : gint16x8(d) {}
    uint16<8>& operator=(__m128i d) { gint16x8::operator=(d); return *this; }
#elif SIMDPP_USE_NEON
    uint16<8>(uint16x8_t d) : gint16x8(d) {}
    uint16<8>& operator=(uint16x8_t d) { gint16x8::operator=(d); return *this; }
#elif SIMDPP_USE_ALTIVEC
    uint16<8>(__vector uint16_t d) : gint16x8(d) {}
    uint16<8>& operator=(__vector uint16_t d) { gint16x8::operator=(d); return *this; }
#endif
    /// @}

    template<class E> explicit uint16<8>(const gint8<16,E>& d);
    template<class E>          uint16<8>(const gint16<8,E>& d);
    template<class E> explicit uint16<8>(const gint32<4,E>& d);
    template<class E> explicit uint16<8>(const gint64<2,E>& d);
    template<class E> uint16<8>& operator=(const gint8<16,E>& d);
    template<class E> uint16<8>& operator=(const gint16<8,E>& d);
    template<class E> uint16<8>& operator=(const gint32<4,E>& d);
    template<class E> uint16<8>& operator=(const gint64<2,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint16x8& operator[](unsigned) const { return *this; }
          uint16x8& operator[](unsigned)       { return *this; }
    /// @}

    uint16<8> eval() const { return *this; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    /// For internal use only
    const uint16_t& el(unsigned i) const  { return u16(i); }
          uint16_t& el(unsigned i)        { return u16(i); }
#endif
#endif

    static uint16<8> zero() { return gint16<8>::zero(); }
    static uint16<8> ones() { return gint16<8>::ones(); }
};

/// Class representing possibly optimized mask data for 8x 16-bit integer
/// vector
template<>
class maskdata_int16<8> {
public:
    using base_vector_type = maskdata_int16<8>;
    static constexpr unsigned length = 8;
    static constexpr unsigned vec_length = 1;

    maskdata_int16<8>() = default;
    maskdata_int16<8>(const maskdata_int16<8> &) = default;
    maskdata_int16<8> &operator=(const maskdata_int16<8> &) = default;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    maskdata_int16<8>(uint16x8 d) : d_(d) {}
#endif
#endif

    /// Convert to bitmask
    operator uint16x8() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL
    bool& el(unsigned id) { return b_[id]; }
    const bool& el(unsigned id) const { return b_[id]; }
#endif
#endif

    /// @{
    /// Access base vectors
    const maskdata_int16<8>& operator[](unsigned) const { return *this; }
          maskdata_int16<8>& operator[](unsigned)       { return *this; }
    /// @}

private:
#if SIMDPP_USE_NULL
    bool b_[8];
#else
    int16x8 d_;
#endif
};

/// Class representing a mask for 8x 16-bit integer vector
template<>
class mask_int16<8, void> : public uint16<8, void> {
public:
    mask_int16<8>() = default;
    mask_int16<8>(const mask_int16<8> &) = default;
    mask_int16<8> &operator=(const mask_int16<8> &) = default;
    mask_int16<8>(const maskdata_int16<8>& d);

    /// @{
    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    mask_int16<8>(__m128i d);
    mask_int16<8>(gint16<8> d);
#elif SIMDPP_USE_NEON
    mask_int16<8>(uint16x8_t d);
    mask_int16<8>(gint16<8> d);
#elif SIMDPP_USE_ALTIVEC
    mask_int16<8>(__vector uint16_t d);
    mask_int16<8>(gint16<8> d);
#endif
    /// @}

    mask_int16<8> eval() const { return *this; }

    const maskdata_int16<8>& mask() const { return mask_; }
#if !DOXYGEN_SHOULD_SKIP_THIS && SIMDPP_USE_NULL
    maskdata_int16<8>& m_mask() { return mask_; }
#endif

private:
    maskdata_int16<8> mask_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
