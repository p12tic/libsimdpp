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

#include <simdpp/types.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing a @a gint64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class gint64<N, void> {
public:

    using element_type = int64_t;
    using uint_element_type = uint64_t;
    using int_vector_type = gint64<N>;
    using uint_vector_type = uint64<N>;
    using base_vector_type = gint64v;
    using mask_type = mask_int64<N>;
    using maskdata_type = maskdata_int64<N>;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT64_SIZE - 1) / SIMDPP_FAST_INT64_SIZE;

    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    gint64<N>() = default;
    gint64<N>(const gint64<N>&) = default;
    gint64<N>& operator=(const gint64<N>&) = default;

    template<class E> explicit gint64<N>(const  gint8<N*8,E>& d);
    template<class E> explicit gint64<N>(const gint16<N*4,E>& d);
    template<class E> explicit gint64<N>(const gint32<N*2,E>& d);
    template<class E>          gint64<N>(const gint64<N,E>& d);
    template<class E> gint64<N>& operator=(const  gint8<N*8,E>& d);
    template<class E> gint64<N>& operator=(const gint16<N*4,E>& d);
    template<class E> gint64<N>& operator=(const gint32<N*2,E>& d);
    template<class E> gint64<N>& operator=(const gint64<N,E>& d);


    /// @{
    /// Construct from compatible float64 floating-point vector type
    explicit gint64<N>(const float64<N>& d)
    {
        for (unsigned i = 0; i < vec_length; ++i) {
            (*this)[i] = d[i];
        }
    }
    gint64<N>& operator=(const float64<N>& d) { operator=(gint64<N>(d)); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const gint64v& operator[](unsigned i) const { return *(du_+i); }
    gint64v& operator[](unsigned i)             { return *(du_+i); }

    gint64<N> eval() const { return *this; }

    /// Creates a int64 vector with the contents set to zero
    static gint64<N> zero()
    {
        return set_vec(gint64v::zero());
    }

    /// Creates a int64 vector with the contents set to ones
    static gint64<N> ones()
    {
        return set_vec(gint64v::ones());
    }

private:
    /// Creates a int64 vector with the contents set to copy of native register
    static gint64<N> set_vec(gint64v a)
    {
        gint64<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }

protected:
    union {
        uint64v du_[vec_length];
        int64v di_[vec_length];
    };
};


/** Class representing an signed @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int64<N, void> : public gint64<N, void> {
public:

    using element_type = int64_t;
    using gint64<N>::vec_length;
    using base_vector_type = int64v;

    int64<N>() = default;
    int64<N>(const int64<N>&) = default;
    int64<N>& operator=(const int64<N>&) = default;

    template<class E> explicit int64<N>(const  gint8<N*8,E>& d);
    template<class E> explicit int64<N>(const gint16<N*4,E>& d);
    template<class E> explicit int64<N>(const gint32<N*2,E>& d);
    template<class E>          int64<N>(const gint64<N,E>& d);
    template<class E> int64<N>& operator=(const  gint8<N*8,E>& d);
    template<class E> int64<N>& operator=(const gint16<N*4,E>& d);
    template<class E> int64<N>& operator=(const gint32<N*2,E>& d);
    template<class E> int64<N>& operator=(const gint64<N,E>& d);

    /// @{
    /// Construct from compatible float64 vector type
    explicit int64<N>(const float64<N>& d) : gint64<N>(d) {}
    int64<N>& operator=(const float64<N>& d) { gint64<N>::operator=(d); return *this; }
    /// @}

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

    const int64v& operator[](unsigned i) const { return *(gint64<N>::di_+i); }
    int64v& operator[](unsigned i)             { return *(gint64<N>::di_+i); }

    int64<N> eval() const { return *this; }

    static int64<N> zero() { return gint64<N>::zero(); }
    static int64<N> ones() { return gint64<N>::ones(); }
};

/** Class representing an unsigned @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint64<N, void> : public gint64<N, void> {
public:

    using element_type = uint64_t;
    using gint64<N>::vec_length;
    using base_vector_type = uint64v;

    uint64<N>() = default;
    uint64<N>(const uint64<N>&) = default;
    uint64<N>& operator=(const uint64<N>&) = default;

    template<class E> explicit uint64<N>(const  gint8<N*8,E>& d);
    template<class E> explicit uint64<N>(const gint16<N*4,E>& d);
    template<class E> explicit uint64<N>(const gint32<N*2,E>& d);
    template<class E>          uint64<N>(const gint64<N,E>& d);
    template<class E> uint64<N>& operator=(const  gint8<N*8,E>& d);
    template<class E> uint64<N>& operator=(const gint16<N*4,E>& d);
    template<class E> uint64<N>& operator=(const gint32<N*2,E>& d);
    template<class E> uint64<N>& operator=(const gint64<N,E>& d);

    /// @{
    /// Construct from compatible float64 vector type
    explicit uint64<N>(const float64<N>& d) : gint64<N>(d) {}
    uint64<N>& operator=(const float64<N>& d) { gint64<N>::operator=(d); return *this; }
    /// @}

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

    const uint64v& operator[](unsigned i) const { return *(gint64<N>::du_+i); }
    uint64v& operator[](unsigned i)             { return *(gint64<N>::du_+i); }

    uint64<N> eval() const { return *this; }

    static uint64<N> zero() { return gint64<N>::zero(); }
    static uint64<N> ones() { return gint64<N>::ones(); }
};


/// Class representing possibly optimized mask data for arbitrary length 64-bit
/// integer vector
template<unsigned N>
class maskdata_int64 {
public:
    using base_vector_type = maskdata_int64<N>;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = int64<N>::vec_length;

    maskdata_int64<N>() = default;
    maskdata_int64<N>(const maskdata_int64<N> &) = default;
    maskdata_int64<N> &operator=(const maskdata_int64<N> &) = default;

    /// Convert to bitmask
    operator uint64<N>() const;

    const maskdata_int64v& operator[](unsigned i) const { return *(d_+i); }
          maskdata_int64v& operator[](unsigned i)       { return *(d_+i); }

    mask_int64<N> eval() const { return *this; }

private:
    maskdata_int64v d_[vec_length];
};

/// Class representing a mask for 64-bit integer point vector of arbitrary
/// length.
template<unsigned N>
class mask_int64<N, void> : public uint64<N, void> {
public:
    mask_int64<N>() = default;
    mask_int64<N>(const mask_int64<N> &) = default;
    mask_int64<N> &operator=(const mask_int64<N> &) = default;
    mask_int64<N>(const maskdata_int64<N>& d);

    mask_int64<N> eval() const { return *this; }

    maskdata_int64<N> mask() const { return mask_; }

private:
    maskdata_int64<N> mask_;
};


/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
