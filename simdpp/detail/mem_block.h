/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_MEM_BLOCK_H
#define LIBSIMDPP_SIMDPP_DETAIL_MEM_BLOCK_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <cstring>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

/** A block of memory that stores a vector and allows access to its elements.
    Data transfer is not explicit -- the compiler is allowed to optimize it
    however it wants, failing back to storing and loading from memory, if
    necessary.
*/
template<class V>
class mem_block {
public:
    typedef typename V::element_type element_type;
    static const unsigned length = V::length;

    SIMDPP_INL mem_block() {}
    SIMDPP_INL mem_block(const mem_block& other) { std::memcpy(this, &other, sizeof(other)); }
    SIMDPP_INL mem_block(const V& v) { std::memcpy(d_, &v, sizeof(v)); }

    SIMDPP_INL mem_block& operator=(const V& v) { std::memcpy(d_, &v, sizeof(v)); return *this; }

    SIMDPP_INL operator V() const { V r; std::memcpy(&r, d_, sizeof(r)); return r; }

    SIMDPP_INL const element_type& operator[](unsigned id) const { return d_[id]; }
    SIMDPP_INL element_type& operator[](unsigned id) { return d_[id]; }

    SIMDPP_INL const element_type* operator&() const { return d_; }
private:
    union {
        element_type d_[length];
        typename V::native_type align_;
    };
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

