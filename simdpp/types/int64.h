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
class gint64 {
public:

    using element_type = int64_t;
    using uint_element_type = uint64_t;
    using int_vector_type = gint64<N>;
    using uint_vector_type = uint64<N>;
    using mask_type = mask_int64<N>;
    using base_vector_type = gint64v;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT64_SIZE - 1) / SIMDPP_FAST_INT64_SIZE;

    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    gint64<N>() = default;
    gint64<N>(const gint64<N>&) = default;
    gint64<N>& operator=(const gint64<N>&) = default;

    gint64<N>(const gint8<N*8>& d);
    gint64<N>(const gint16<N*4>& d);
    gint64<N>(const gint32<N*2>& d);
    gint64<N>& operator=(const gint8<N*8>& d);
    gint64<N>& operator=(const gint16<N*4>& d);
    gint64<N>& operator=(const gint32<N*2>& d);

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

    const gint64v* begin() const   { return du_; }
    gint64v* begin()               { return du_; }
    const gint64v* end() const     { return du_+vec_length; }
    gint64v* end()                 { return du_+vec_length; }
    const gint64v& operator[](unsigned i) const { return *(du_+i); }
    gint64v& operator[](unsigned i)             { return *(du_+i); }

    /// Creates a int64 vector with the contents set to zero
    static gint64<N> zero()
    {
        return set_broadcast(gint64v::zero());
    }

    /// Creates a int64 vector with the contents set to ones
    static gint64<N> ones()
    {
        return set_broadcast(gint64v::ones());
    }

    /// Creates a int64 vector with the contents set to copy of native register
    static gint64<N> set_broadcast(gint64v a)
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
class int64 : public gint64<N> {
public:

    using element_type = int64_t;
    using gint64<N>::vec_length;
    using base_vector_type = int64v;

    int64<N>() = default;
    int64<N>(const int64<N>&) = default;
    int64<N>& operator=(const int64<N>&) = default;

    int64<N>(const gint8<N*8>& d);
    int64<N>(const gint16<N*4>& d);
    int64<N>(const gint32<N*2>& d);
    int64<N>(const gint64<N>& d);
    int64<N>& operator=(const gint8<N*8>& d);
    int64<N>& operator=(const gint16<N*4>& d);
    int64<N>& operator=(const gint32<N*2>& d);
    int64<N>& operator=(const gint64<N>& d);

    /// @{
    /// Construct from compatible float64 vector type
    explicit int64<N>(const float64<N>& d) : gint64<N>(d) {}
    int64<N>& operator=(const float64<N>& d) { gint64<N>::operator=(d); return *this; }
    /// @}

    const int64v* begin() const { return gint64<N>::di_; }
    int64v* begin()             { return gint64<N>::di_; }
    const int64v* end() const   { return gint64<N>::di_+vec_length; }
    int64v* end()               { return gint64<N>::di_+vec_length; }
    const int64v& operator[](unsigned i) const { return *(gint64<N>::di_+i); }
    int64v& operator[](unsigned i)             { return *(gint64<N>::di_+i); }

    /** Creates a signed int64 vector from a value loaded from memory.

        @code
            | 0  1  | ... |
        r = [ v0 v0   ... ]
        @endcode
    */
    static int64<N> load_broadcast(const int64_t* v0)
    {
        return set_broadcast(int64v::load_broadcast(v0));
    }

    /** Creates a signed int64 vector from a value stored in a core register.

        @code
            | 0  1  | ... |
        r = [ v0 v0   ... ]
        @endcode
    */
    static int64<N> set_broadcast(int64_t v0)
    {
        return set_broadcast(int64v::set_broadcast(v0));
    }

    /** Creates a signed int64 vector from a value known at compile-time

        @code
            | 0  1  | ... |
        r = [ v0 v0   ... ]
        @endcode
    */
    static int64<N> make_const(int64_t v0)
    {
        return set_broadcast(int64v::make_const(v0));
    }

    /** Creates a signed int64 vector from two values known at compile-time

        @code
            | 0  1  | ... |
        r = [ v0 v1   ... ]
        @endcode
    */
    static int64<N> make_const(int64_t v0, int64_t v1)
    {
        return set_broadcast(int64v::make_const(v0, v1));
    }

    /// Creates a signed int64 vector with the contents set to copy of native
    /// register
    static int64<N> set_broadcast(int64v a)
    {
        int64<N> r;
        for (auto& v : r.di_) {
            v = a;
        }
        return r;
    }
};

/** Class representing an unsigned @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint64 : public gint64<N> {
public:

    using element_type = uint64_t;
    using gint64<N>::vec_length;
    using base_vector_type = uint64v;

    uint64<N>() = default;
    uint64<N>(const uint64<N>&) = default;
    uint64<N>& operator=(const uint64<N>&) = default;

    uint64<N>(const gint8<N*8>& d);
    uint64<N>(const gint16<N*4>& d);
    uint64<N>(const gint32<N*2>& d);
    uint64<N>(const gint64<N>& d);
    uint64<N>& operator=(const gint8<N*8>& d);
    uint64<N>& operator=(const gint16<N*4>& d);
    uint64<N>& operator=(const gint32<N*2>& d);
    uint64<N>& operator=(const gint64<N>& d);

    /// @{
    /// Construct from compatible float64 vector type
    explicit uint64<N>(const float64<N>& d) : gint64<N>(d) {}
    uint64<N>& operator=(const float64<N>& d) { gint64<N>::operator=(d); return *this; }
    /// @}

    const uint64v* begin() const { return gint64<N>::du_; }
    uint64v* begin()             { return gint64<N>::du_; }
    const uint64v* end() const   { return gint64<N>::du_+vec_length; }
    uint64v* end()               { return gint64<N>::du_+vec_length; }
    const uint64v& operator[](unsigned i) const { return *(gint64<N>::du_+i); }
    uint64v& operator[](unsigned i)             { return *(gint64<N>::du_+i); }

    /** Creates a unsigned int64 vector from a value loaded from memory.

        @code
            | 0  1  | ... |
        r = [ v0 v0   ... ]
        @endcode
    */
    static uint64<N> load_broadcast(const uint64_t* v0)
    {
        return set_broadcast(uint64v::load_broadcast(v0));
    }

    /** Creates a unsigned int64 vector from a value stored in a core register.

        @code
            | 0  1  | ... |
        r = [ v0 v0   ... ]
        @endcode
    */
    static uint64<N> set_broadcast(uint64_t v0)
    {
        return set_broadcast(uint64v::set_broadcast(v0));
    }

    /** Creates a unsigned int64 vector from a value known at compile-time

        @code
            | 0  1  | ... |
        r = [ v0 v0   ... ]
        @endcode
    */
    static uint64<N> make_const(uint64_t v0)
    {
        return set_broadcast(uint64v::make_const(v0));
    }

    /** Creates a unsigned int64 vector from two values known at compile-time

        @code
            | 0  1  | ... |
        r = [ v0 v1   ... ]
        @endcode
    */
    static uint64<N> make_const(uint64_t v0, uint64_t v1)
    {
        return set_broadcast(uint64v::make_const(v0, v1));
    }

    /// Creates a unsigned int64 vector with the contents set to copy of native
    /// register
    static uint64<N> set_broadcast(uint64v a)
    {
        uint64<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }
};

/// Class representing a mask for @a gint64 vector of arbitrary length. The
/// vector always contains at least one native vector.
template<unsigned N>
class mask_int64 {
public:
    using base_vector_type = mask_int64v;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT64_SIZE - 1) / SIMDPP_FAST_INT64_SIZE;

    mask_int64<N>() = default;
    mask_int64<N>(const mask_int64 &) = default;
    mask_int64<N> &operator=(const mask_int64 &) = default;

    const mask_int64v* begin() const   { return d_; }
    mask_int64v* begin()               { return d_; }
    const mask_int64v* end() const     { return d_+vec_length; }
    mask_int64v* end()                 { return d_+vec_length; }
    const mask_int64v& operator[](unsigned i) const { return *(d_+i); }
    mask_int64v& operator[](unsigned i)             { return *(d_+i); }

    /// Convert to a regular vector
    operator gint64<N>() const
    {
        gint64<N> r;
        for (unsigned i = 0; i < vec_length; ++i) {
            r[i] = d_[i];
        }
        return r;
    }

private:
    mask_int64v d_[vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
