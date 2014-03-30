/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64_H
#define LIBSIMDPP_SIMDPP_TYPES_INT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing an signed @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int64<N, void> : public any_int64<N, int64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int64_t;
    using base_vector_type = int64v;
    using expr_type = void;

    int64<N>() = default;
    int64<N>(const int64<N>&) = default;
    int64<N>& operator=(const int64<N>&) = default;

    template<class E> int64<N>(const int64<N,E>& d) { *this = d.eval(); }
    template<class E> int64<N>(const uint64<N,E>& d) { *this = d.eval(); }
    template<class V> explicit int64<N>(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<int64<N>>(d.vec().eval());
    }
    template<class V> int64<N>& operator=(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<int64<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int64v& operator[](unsigned i) const { return d_[i]; }
    int64v& operator[](unsigned i)             { return d_[i]; }

    int64<N> eval() const { return *this; }

    static int64<N> zero() { return set_vec(int64v::zero()); }
    static int64<N> ones() { return set_vec(int64v::ones()); }

private:

    /// Creates a signed int64 vector with the contents set to copy of native
    /// register
    static int64<N> set_vec(int64v a)
    {
        int64<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

private:
    int64v d_[int64::vec_length];
};

/** Class representing an unsigned @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint64<N, void> : public any_int64<N, uint64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint64_t;
    using base_vector_type = uint64v;
    using expr_type = void;

    uint64<N>() = default;
    uint64<N>(const uint64<N>&) = default;
    uint64<N>& operator=(const uint64<N>&) = default;

    template<class E> uint64<N>(const uint64<N,E>& d) { *this = d.eval(); }
    template<class E> uint64<N>(const int64<N,E>& d) { *this = d.eval(); }
    template<class V> explicit uint64<N>(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<uint64<N>>(d.vec().eval());
    }
    template<class V> uint64<N>& operator=(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<uint64<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const uint64v& operator[](unsigned i) const { return d_[i]; }
    uint64v& operator[](unsigned i)             { return d_[i]; }

    uint64<N> eval() const { return *this; }

    static uint64<N> zero() { return set_vec(uint64v::zero()); }
    static uint64<N> ones() { return set_vec(uint64v::ones()); }

private:
    /// Creates a unsigned int64 vector with the contents set to copy of native
    /// register
    static uint64<N> set_vec(uint64v a)
    {
        uint64<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }
private:
    uint64v d_[uint64::vec_length];
};

/// Class representing a mask for 64-bit integer vector of arbitrary
/// length.
template<unsigned N>
class mask_int64<N, void> : public any_int64<N, mask_int64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int64v;
    using expr_type = void;

    mask_int64<N>() = default;
    mask_int64<N>(const mask_int64<N> &) = default;
    mask_int64<N> &operator=(const mask_int64<N> &) = default;

    /// Access the underlying type
    uint64<N> unmask() const
    {
        uint64<N> r;
        for (unsigned i = 0; i < mask_int64::vec_length; ++i) {
            r[i] = d_[i].unmask();
        }
        return r;
    }

    const mask_int64v& operator[](unsigned i) const { return d_[i]; }
          mask_int64v& operator[](unsigned i)       { return d_[i]; }

    mask_int64<N> eval() const { return *this; }

private:
    mask_int64v d_[mask_int64::vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
