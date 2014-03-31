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
#include <simdpp/types/any.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_int
/// @{

/** Class representing 8x 32-bit signed integer vector
*/
template<>
class int32<8, void> : public any_int32<8, int32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int32_t;
    using base_vector_type = int32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    int32<8>() = default;
    int32<8>(const int32<8> &) = default;
    int32<8> &operator=(const int32<8> &) = default;

    template<class E> int32<8>(const int32<8,E>& d) { *this = d.eval(); }
    template<class E> int32<8>(const uint32<8,E>& d) { *this = d.eval(); }
    template<class V> explicit int32<8>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int32<8>>(d.vec().eval());
    }
    template<class V> int32<8>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int32<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int32<8>(const native_type& d) : d_(d) {}
    int32<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int32<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int32<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int32<8>& operator[](unsigned) const { return *this; }
          int32<8>& operator[](unsigned)       { return *this; }
    /// @}

    int32<8> eval() const { return *this; }

    static int32<8> zero();
    static int32<8> ones();

private:
    native_type d_;
};

/** Class representing 8x 32-bit unsigned integer vector
*/
template<>
class uint32<8, void> : public any_int32<8, uint32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint32_t;
    using base_vector_type = uint32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    uint32<8>() = default;
    uint32<8>(const uint32<8> &) = default;
    uint32<8> &operator=(const uint32<8> &) = default;

    template<class E> uint32<8>(const uint32<8,E>& d) { *this = d.eval(); }
    template<class E> uint32<8>(const int32<8,E>& d) { *this = d.eval(); }
    template<class V> explicit uint32<8>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint32<8>>(d.vec().eval());
    }
    template<class V> uint32<8>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint32<8>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint32<8>(const native_type& d) : d_(d) {}
    uint32<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint32<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint32<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint32<8>& operator[](unsigned) const { return *this; }
          uint32<8>& operator[](unsigned)       { return *this; }
    /// @}

    uint32<8> eval() const { return *this; }

    static uint32<8> zero();
    static uint32<8> ones();

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 4x 32-bit integer
/// vector
template<>
class mask_int32<8, void> : public any_int32<8, mask_int32<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int32<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    mask_int32<8>() = default;
    mask_int32<8>(const mask_int32<8> &) = default;
    mask_int32<8> &operator=(const mask_int32<8> &) = default;

    mask_int32<8>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    mask_int32<8>(const uint32<8>& d) : d_(d) {}
#endif

    /// Access the underlying type
    uint32<8> unmask() const;

    const mask_int32<8>& operator[](unsigned) const { return *this; }
          mask_int32<8>& operator[](unsigned)       { return *this; }

    mask_int32<8> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
