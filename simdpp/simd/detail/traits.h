/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_DETAIL_TRAITS_H
#define LIBSIMDPP_SIMD_DETAIL_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

/*
    element_type -- type of each element in the vector
    unsigned_element_type -- a unsigned integer of the same size as element_type
    int_vector_type -- a generic integer vector type with elements of the same
        size as the vector in question
    half_vector_type -- if the vector is 32-byte vector, specifies 16-byte
        vector type corresponding to each of the halfs of the vector

    length -- the number of elements within vector
    num_bits -- size of element_type in bits.
    all_bits -- unsigned_element_type with the value ~0
*/
template<class T> struct traits;

// this one is needed by null
template<> struct traits<int128> {
    using element_type = uint64_t;
    using unsigned_element_type = uint64_t;
    using int_vector_type = int128;

    static constexpr unsigned length = 2;
    static constexpr unsigned num_bits = 64;
    static constexpr unsigned_element_type all_bits = 0xffffffffffffffff;
};

template<> struct traits<uint8x16> {
    using element_type = uint8_t;
    using unsigned_element_type = uint8_t;
    using int_vector_type = basic_int8x16;
    static constexpr unsigned length = 16;
    static constexpr unsigned num_bits = 8;
    static constexpr unsigned_element_type all_bits = 0xff;
};
template<> struct traits<int8x16> : public traits<uint8x16> {
    using element_type = int8_t;
};
template<> struct traits<basic_int8x16> : public traits<uint8x16> {};

template<> struct traits<uint16x8> {
    using element_type = uint16_t;
    using unsigned_element_type = uint16_t;
    using int_vector_type = basic_int16x8;
    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 16;
    static constexpr unsigned_element_type all_bits = 0xffff;
};
template<> struct traits<int16x8> : public traits<uint16x8> {
    using element_type = int16_t;
};
template<> struct traits<basic_int16x8> : public traits<uint16x8> {};

template<> struct traits<uint32x4> {
    using element_type = uint32_t;
    using unsigned_element_type = uint32_t;
    using int_vector_type = basic_int32x4;
    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 32;
    static constexpr unsigned_element_type all_bits = 0xffffffff;
};
template<> struct traits<int32x4> : public traits<uint32x4> {
    using element_type = int32_t;
};
template<> struct traits<basic_int32x4> : public traits<uint32x4> {};

template<> struct traits<uint64x2> {
    using element_type = uint64_t;
    using unsigned_element_type = uint64_t;
    using int_vector_type = basic_int64x2;
    static constexpr unsigned length = 2;
    static constexpr unsigned num_bits = 64;
    static constexpr unsigned_element_type all_bits = 0xffffffffffffffff;
};
template<> struct traits<int64x2> : public traits<uint64x2> {
    using element_type = int64_t;
};
template<> struct traits<basic_int64x2> : public traits<uint64x2> {};

template<> struct traits<float32x4> {
    using element_type = float;
    using unsigned_element_type = uint32_t;
    using int_vector_type = basic_int32x4;
    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 32;
    static constexpr unsigned_element_type all_bits = 0xffffffff;
};

template<> struct traits<float64x2> {
    using element_type = double;
    using unsigned_element_type = uint64_t;
    using int_vector_type = basic_int64x2;
    static constexpr unsigned length = 2;
    static constexpr unsigned num_bits = 64;
    static constexpr unsigned_element_type all_bits = 0xffffffffffffffff;
};

// this one needed by null
template<> struct traits<int256> {
    using element_type = uint64_t;
    using unsigned_element_type = uint64_t;
    using int_vector_type = int256;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 64;
    static constexpr unsigned_element_type all_bits = 0xffffffffffffffff;
};

template<> struct traits<uint8x32> {
    using element_type = uint8_t;
    using unsigned_element_type = uint8_t;
    using int_vector_type = basic_int8x32;
    using half_vector_type = uint8x16;

    static constexpr unsigned length = 32;
    static constexpr unsigned num_bits = 8;
    static constexpr unsigned_element_type all_bits = 0xff;
};
template<> struct traits<int8x32> : public traits<uint8x32> {
    using element_type = int8_t;
    using half_vector_type = int8x16;
};
template<> struct traits<basic_int8x32> : public traits<uint8x32> {
    using half_vector_type = basic_int8x16;
};

template<> struct traits<uint16x16> {
    using element_type = uint16_t;
    using unsigned_element_type = uint16_t;
    using int_vector_type = basic_int16x16;
    using half_vector_type = uint16x16;

    static constexpr unsigned length = 16;
    static constexpr unsigned num_bits = 16;
    static constexpr unsigned_element_type all_bits = 0xffff;
};
template<> struct traits<int16x16> : public traits<uint16x16> {
    using element_type = int16_t;
    using half_vector_type = int16x8;
};
template<> struct traits<basic_int16x16> : public traits<uint16x16> {
    using half_vector_type = basic_int16x8;
};

template<> struct traits<uint32x8> {
    using element_type = uint32_t;
    using unsigned_element_type = uint32_t;
    using int_vector_type = basic_int32x8;
    using half_vector_type = uint32x4;

    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 32;
    static constexpr unsigned_element_type all_bits = 0xffffffff;
};
template<> struct traits<int32x8> : public traits<uint32x8> {
    using element_type = int32_t;
    using half_vector_type = int32x4;
};
template<> struct traits<basic_int32x8> : public traits<uint32x8> {
    using half_vector_type = basic_int32x4;
};

template<> struct traits<uint64x4> {
    using element_type = uint64_t;
    using unsigned_element_type = uint64_t;
    using int_vector_type = basic_int64x4;
    using half_vector_type = uint64x2;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 64;
    static constexpr unsigned_element_type all_bits = 0xffffffffffffffff;
};
template<> struct traits<int64x4> : public traits<uint64x4> {
    using element_type = int64_t;
    using half_vector_type = int64x2;
};
template<> struct traits<basic_int64x4> : public traits<uint64x4> {
    using half_vector_type = basic_int64x2;
};

template<> struct traits<float32x8> {
    using element_type = float;
    using unsigned_element_type = uint32_t;
    using int_vector_type = basic_int32x8;
    using half_vector_type = float32x4;

    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 32;
    static constexpr unsigned_element_type all_bits = 0xffffffff;
};

template<> struct traits<float64x4> {
    using element_type = double;
    using unsigned_element_type = uint64_t;
    using int_vector_type = basic_int64x4;
    using half_vector_type = float64x2;

    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 64;
    static constexpr unsigned_element_type all_bits = 0xffffffffffffffff;
};

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
