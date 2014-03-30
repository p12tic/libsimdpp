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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X16_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_int
/// @{

/** Generic class representing 16x 16-bit integer vector.
    To be used where the signedness of the underlying element type is not important
*/
template<>
class uint16<16, void> {
public:

    using element_type = uint16_t;
    using uint_element_type = uint16_t;
    using int_vector_type = uint16x16;
    using uint_vector_type = uint16x16;
    using mask_vector_type = mask_int16x16;
    using base_vector_type = uint16x16;

    static constexpr unsigned length = 16;
    static constexpr unsigned vec_length = 1;
    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;

    uint16<16>() = default;
    uint16<16>(const uint16x16 &) = default;
    uint16<16> &operator=(const uint16x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
    uint16<16>(__m256i d) : d_(d) {}
    uint16<16>& operator=(__m256i d) { d_ = d; return *this; }
    /// @}

    template<class E> explicit uint16<16>(const  uint8<32,E>& d);
    template<class E>          uint16<16>(const uint16<16,E>& d);
    template<class E> explicit uint16<16>(const uint32<8,E>& d);
    template<class E> explicit uint16<16>(const uint64<4,E>& d);
    template<class E> uint16<16>& operator=(const  uint8<32,E>& d);
    template<class E> uint16<16>& operator=(const uint16<16,E>& d);
    template<class E> uint16<16>& operator=(const uint32<8,E>& d);
    template<class E> uint16<16>& operator=(const uint64<4,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint16x16& operator[](unsigned) const   { return *this; }
          uint16x16& operator[](unsigned)         { return *this; }
    /// @}

    uint16<16> eval() const { return *this; }

    /// Creates a int16x16 vector with the contents set to zero
    static uint16x16 zero();

    /// Creates a int16x16 vector with the contents set to ones
    static uint16x16 ones();

private:
    __m256i d_;
};

/** Class representing 16x 16-bit signed integer vector
*/
template<>
class int16<16, void> : public uint16x16 {
public:
    using base_vector_type = int16x16;
    using element_type = int16_t;

    int16<16>() = default;
    int16<16>(const int16x16 &) = default;
    int16<16> &operator=(const int16x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
    int16<16>(__m256i d) : uint16x16(d) {}
    int16<16>& operator=(__m256i d) { uint16x16::operator=(d); return *this; }
    /// @}

    template<class E> explicit int16<16>(const  uint8<32,E>& d);
    template<class E>          int16<16>(const uint16<16,E>& d);
    template<class E> explicit int16<16>(const uint32<8,E>& d);
    template<class E> explicit int16<16>(const uint64<4,E>& d);
    template<class E> int16<16>& operator=(const  uint8<32,E>& d);
    template<class E> int16<16>& operator=(const uint16<16,E>& d);
    template<class E> int16<16>& operator=(const uint32<8,E>& d);
    template<class E> int16<16>& operator=(const uint64<4,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int16x16& operator[](unsigned) const   { return *this; }
          int16x16& operator[](unsigned)         { return *this; }
    /// @}

    int16<16> eval() const { return *this; }
};

/** Class representing 8x 16-bit unsigned integer vector
*/
template<>
class uint16<16, void> : public uint16x16 {
public:
    using base_vector_type = uint16x16;

    uint16<16>() = default;
    uint16<16>(const uint16x16 &) = default;
    uint16<16> &operator=(const uint16x16 &) = default;

    /// @{
    /// Construct from the underlying vector type
    uint16<16>(__m256i d) : uint16x16(d) {}
    uint16<16>& operator=(__m256i d) { uint16x16::operator=(d); return *this; }
    /// @}

    template<class E> explicit uint16<16>(const  uint8<32,E>& d);
    template<class E>          uint16<16>(const uint16<16,E>& d);
    template<class E> explicit uint16<16>(const uint32<8,E>& d);
    template<class E> explicit uint16<16>(const uint64<4,E>& d);
    template<class E> uint16<16>& operator=(const  uint8<32,E>& d);
    template<class E> uint16<16>& operator=(const uint16<16,E>& d);
    template<class E> uint16<16>& operator=(const uint32<8,E>& d);
    template<class E> uint16<16>& operator=(const uint64<4,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint16x16& operator[](unsigned) const   { return *this; }
          uint16x16& operator[](unsigned)         { return *this; }
    /// @}

    uint16<16> eval() const { return *this; }
};

/// Class representing possibly optimized mask data for 16x 16-bit integer vector
template<>
class maskdata_int16<16> {
public:
    using base_vector_type = maskdata_int16<16>;
    static constexpr unsigned length = 16;
    static constexpr unsigned vec_length = 1;

    maskdata_int16<16>() = default;
    maskdata_int16<16>(const maskdata_int16<16> &) = default;
    maskdata_int16<16> &operator=(const maskdata_int16<16> &) = default;

    maskdata_int16<16>(int16<16> d) : d_(d) {}

    /// Convert to bitmask
    operator uint16<16>() const;

    /// @{
    /// Access base vectors
    const maskdata_int16<16>& operator[](unsigned) const { return *this; }
          maskdata_int16<16>& operator[](unsigned)       { return *this; }
    /// @}

private:
    uint16<16> d_;
};


/// Class representing a mask for 16x 16-bit integer vector
template<>
class mask_int16<16, void> : public uint16<16, void> {
public:
    mask_int16<16>() = default;
    mask_int16<16>(const mask_int16<16> &) = default;
    mask_int16<16> &operator=(const mask_int16<16> &) = default;
    mask_int16<16>(const maskdata_int16<16>& d);

    /// @{
    /// Construct from the underlying vector type
    mask_int16<16>(__m256i d);
    mask_int16<16>(uint16<16> d);
    /// @}

    mask_int16<16> eval() const { return *this; }

    const maskdata_int16<16>& mask() const { return mask_; }

private:
    maskdata_int16<16> mask_;
};
/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
