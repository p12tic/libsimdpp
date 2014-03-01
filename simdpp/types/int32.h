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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32_H
#define LIBSIMDPP_SIMDPP_TYPES_INT32_H

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

/** Class representing a @a gint32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class gint32<N, void> {
public:

    using element_type = int32_t;
    using uint_element_type = uint32_t;
    using int_vector_type = gint32<N>;
    using uint_vector_type = uint32<N>;
    using mask_type = mask_int32<N>;
    using maskdata_type = maskdata_int32<N>;
    using base_vector_type = gint32v;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT32_SIZE - 1) / SIMDPP_FAST_INT32_SIZE;

    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    gint32<N>() = default;
    gint32<N>(const gint32<N>&) = default;
    gint32<N>& operator=(const gint32<N>&) = default;

    template<class E> explicit gint32<N>(const  gint8<N*4,E>& d);
    template<class E> explicit gint32<N>(const gint16<N*2,E>& d);
    template<class E>          gint32<N>(const gint32<N,E>& d);
    template<class E> explicit gint32<N>(const gint64<N/2,E>& d);
    template<class E> gint32<N>& operator=(const  gint8<N*4,E>& d);
    template<class E> gint32<N>& operator=(const gint16<N*2,E>& d);
    template<class E> gint32<N>& operator=(const gint32<N,E>& d);
    template<class E> gint32<N>& operator=(const gint64<N/2,E>& d);

    /// @{
    /// Construct from compatible float32x8 floating-point vector type
    explicit gint32<N>(const float32<N>& d)
    {
        for (unsigned i = 0; i < vec_length; ++i) {
            (*this)[i] = d[i];
        }
    }
    gint32<N>& operator=(const float32<N>& d) { operator=(gint32<N>(d)); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const gint32v& operator[](unsigned i) const { return *(du_+i); }
    gint32v& operator[](unsigned i)             { return *(du_+i); }

    gint32<N> eval() const { return *this; }

    /// Creates a int32 vector with the contents set to zero
    static gint32<N> zero()
    {
        return set_vec(gint32v::zero());
    }

    /// Creates a int32 vector with the contents set to ones
    static gint32<N> ones()
    {
        return set_vec(gint32v::ones());
    }

private:
    /// Creates a int32 vector with the contents set to copy of native register
    static gint32<N> set_vec(gint32v a)
    {
        gint32<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }

protected:
    union {
        uint32v du_[vec_length];
        int32v di_[vec_length];
    };
};


/** Class representing an signed @a int32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int32<N, void> : public gint32<N, void> {
public:

    using element_type = int32_t;
    using gint32<N>::vec_length;
    using base_vector_type = int32v;

    int32<N>() = default;
    int32<N>(const int32<N>&) = default;
    int32<N>& operator=(const int32<N>&) = default;

    template<class E> explicit int32<N>(const  gint8<N*4,E>& d);
    template<class E> explicit int32<N>(const gint16<N*2,E>& d);
    template<class E>          int32<N>(const gint32<N,E>& d);
    template<class E> explicit int32<N>(const gint64<N/2,E>& d);
    template<class E> int32<N>& operator=(const  gint8<N*4,E>& d);
    template<class E> int32<N>& operator=(const gint16<N*2,E>& d);
    template<class E> int32<N>& operator=(const gint32<N,E>& d);
    template<class E> int32<N>& operator=(const gint64<N/2,E>& d);

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit int32<N>(const float32<N>& d) : gint32<N>(d) {}
    int32<N>& operator=(const float32<N>& d) { gint32<N>::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int32v& operator[](unsigned i) const { return *(gint32<N>::di_+i); }
    int32v& operator[](unsigned i)             { return *(gint32<N>::di_+i); }

    int32<N> eval() const { return *this; }

    static int32<N> zero() { return gint32<N>::zero(); }
    static int32<N> ones() { return gint32<N>::ones(); }

    /** Creates a signed int32 vector from a value known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v0 v0 v0   ... ]
        @endcode
    */
    static int32<N> make_const(int32_t v0)
    {
        return set_vec(int32v::make_const(v0));
    }

    /** Creates a signed int32 vector from two values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v0 v1   ... ]
        @endcode
    */
    static int32<N> make_const(int32_t v0, int32_t v1)
    {
        return set_vec(int32v::make_const(v0, v1));
    }

    /** Creates a signed int32 vector from four values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v2 v3   ... ]
        @endcode
    */
    static int32<N> make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
    {
        return set_vec(int32v::make_const(v0, v1, v2, v3));
    }

private:
    /// Creates a signed int32 vector with the contents set to copy of native
    /// register
    static int32<N> set_vec(int32v a)
    {
        int32<N> r;
        for (auto& v : r.di_) {
            v = a;
        }
        return r;
    }
};

/** Class representing an unsigned @a int32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint32<N, void> : public gint32<N, void> {
public:

    using element_type = uint32_t;
    using gint32<N>::vec_length;
    using base_vector_type = uint32v;

    uint32<N>() = default;
    uint32<N>(const uint32<N>&) = default;
    uint32<N>& operator=(const uint32<N>&) = default;

    template<class E> explicit uint32<N>(const  gint8<N*4,E>& d);
    template<class E> explicit uint32<N>(const gint16<N*2,E>& d);
    template<class E>          uint32<N>(const gint32<N,E>& d);
    template<class E> explicit uint32<N>(const gint64<N/2,E>& d);
    template<class E> uint32<N>& operator=(const  gint8<N*4,E>& d);
    template<class E> uint32<N>& operator=(const gint16<N*2,E>& d);
    template<class E> uint32<N>& operator=(const gint32<N,E>& d);
    template<class E> uint32<N>& operator=(const gint64<N/2,E>& d);

    /// @{
    /// Construct from compatible float32x8 integer vector type
    explicit uint32<N>(const float32<N>& d) : gint32<N>(d) {}
    uint32<N>& operator=(const float32<N>& d) { gint32<N>::operator=(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const uint32v& operator[](unsigned i) const { return *(gint32<N>::du_+i); }
    uint32v& operator[](unsigned i)             { return *(gint32<N>::du_+i); }

    uint32<N> eval() const { return *this; }

    static uint32<N> zero() { return gint32<N>::zero(); }
    static uint32<N> ones() { return gint32<N>::ones(); }

    /** Creates a unsigned int32 vector from a value known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v0 v0 v0   ... ]
        @endcode
    */
    static uint32<N> make_const(uint32_t v0)
    {
        return set_vec(uint32v::make_const(v0));
    }

    /** Creates a unsigned int32 vector from two values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v0 v1   ... ]
        @endcode
    */
    static uint32<N> make_const(uint32_t v0, uint32_t v1)
    {
        return set_vec(uint32v::make_const(v0, v1));
    }

    /** Creates a unsigned int32 vector from four values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v2 v3   ... ]
        @endcode
    */
    static uint32<N> make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
    {
        return set_vec(uint32v::make_const(v0, v1, v2, v3));
    }

private:
    /// Creates a unsigned int32 vector with the contents set to copy of native
    /// register
    static uint32<N> set_vec(uint32v a)
    {
        uint32<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }
};


/// Class representing possibly optimized mask data for arbitrary length 32-bit
/// integer vector
template<unsigned N>
class maskdata_int32 {
public:
    using base_vector_type = maskdata_int32<N>;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = int32<N>::vec_length;

    maskdata_int32<N>() = default;
    maskdata_int32<N>(const maskdata_int32<N> &) = default;
    maskdata_int32<N> &operator=(const maskdata_int32<N> &) = default;

    /// Convert to bitmask
    operator uint32<N>() const;

    const maskdata_int32v& operator[](unsigned i) const { return *(d_+i); }
          maskdata_int32v& operator[](unsigned i)       { return *(d_+i); }

    mask_int32<N> eval() const { return *this; }

private:
    maskdata_int32v d_[vec_length];
};


/// Class representing a mask for 32-bit integer point vector of arbitrary
/// length.
template<unsigned N>
class mask_int32<N, void> : public uint32<N, void> {
public:
    mask_int32<N>() = default;
    mask_int32<N>(const mask_int32<N> &) = default;
    mask_int32<N> &operator=(const mask_int32<N> &) = default;
    mask_int32<N>(const maskdata_int32<N>& d);

    mask_int32<N> eval() const { return *this; }

    mask_int32<N> mask() const { return mask_; }
private:
    maskdata_int32<N> mask_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
