/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing an signed @a int8 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int8<N, void> : public any_int8<N, int8<N, void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int8_t;
    using base_vector_type = int8v;
    using expr_type = void;

    int8<N>() = default;
    int8<N>(const int8<N>&) = default;
    int8<N>& operator=(const int8<N>&) = default;

    template<class E> SIMDPP_INL int8<N>(const int8<N,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int8<N>(const uint8<N,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int8<N>(const any_vec<N,V>& d)
    {
        *this = bit_cast<int8<N>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int8<N>& operator=(const any_vec<N,V>& d)
    {
        *this = bit_cast<int8<N>>(d.wrapped().eval()); return *this;
    }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL int8<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int8<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int8v& vec(unsigned i) const { return d_[i]; }
    int8v& vec(unsigned i)             { return d_[i]; }

    int8<N> eval() const { return *this; }

    static int8<N> zero() { return set_vec(int8v::zero()); }
    static int8<N> ones() { return set_vec(int8v::ones()); }

private:
    /// Creates a signed int8 vector with the contents set to copy of native
    /// register
    static int8<N> set_vec(int8v a)
    {
        int8<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

private:
    int8v d_[int8::vec_length];
};

/** Class representing an unsigned @a int8 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint8<N, void> : public any_int8<N, uint8<N, void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint8_t;
    using base_vector_type = uint8v;
    using expr_type = void;

    uint8<N>() = default;
    uint8<N>(const uint8<N>&) = default;
    uint8<N>& operator=(const uint8<N>&) = default;

    template<class E> SIMDPP_INL uint8<N>(const uint8<N,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint8<N>(const int8<N,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint8<N>(const any_vec<N,V>& d)
    {
        *this = bit_cast<uint8<N>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint8<N>& operator=(const any_vec<N,V>& d)
    {
        *this = bit_cast<uint8<N>>(d.wrapped().eval()); return *this;
    }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL uint8<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint8<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const uint8v& vec(unsigned i) const { return d_[i]; }
    uint8v& vec(unsigned i)             { return d_[i]; }

    uint8<N> eval() const { return *this; }

    static uint8<N> zero() { return set_vec(uint8v::zero()); }
    static uint8<N> ones() { return set_vec(uint8v::ones()); }

private:
    /// Creates a unsigned int8 vector with the contents set to copy of native
    /// register
    static uint8<N> set_vec(uint8v a)
    {
        uint8<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

private:
    uint8v d_[uint8::vec_length];
};

/// Class representing a mask for 8-bit integer vector of arbitrary
/// length.
template<unsigned N>
class mask_int8<N, void> : public any_int8<N, mask_int8<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int8v;
    using expr_type = void;

    mask_int8<N>() = default;
    mask_int8<N>(const mask_int8<N> &) = default;
    mask_int8<N> &operator=(const mask_int8<N> &) = default;

    /// Access the underlying type
    uint8<N> unmask() const
    {
        uint8<N> r;
        for (unsigned i = 0; i < mask_int8::vec_length; ++i) {
            r.vec(i) = d_[i].unmask();
        }
        return r;
    }

    const mask_int8v& vec(unsigned i) const { return d_[i]; }
          mask_int8v& vec(unsigned i)       { return d_[i]; }

    mask_int8<N> eval() const { return *this; }

private:
    mask_int8v d_[mask_int8::vec_length];
};

/// @} -- end ingroup

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
