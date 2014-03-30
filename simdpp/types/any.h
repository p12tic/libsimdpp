/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_ANY_H
#define LIBSIMDPP_SIMDPP_TYPES_ANY_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/fwd.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_any
/// @{

/** Represents any vector that has @a B bytes of data
*/
template<unsigned B, class V>
struct any_vec {
    static const unsigned length_bytes = B;
    using type = V;

    /// @{
    /// Returns the wrapped vector
    V& vec() { return static_cast<V&>(*this); }
    const V& vec() const { return static_cast<const V&>(*this); }
    /// @}
};

template<unsigned N, class V> struct any_vec8 : any_vec<N, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE8;
};
template<unsigned N, class V> struct any_vec16 : any_vec<N*2, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE16;
};
template<unsigned N, class V> struct any_vec32 : any_vec<N*4, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE32;
};
template<unsigned N, class V> struct any_vec64 : any_vec<N*8, V>
{
    static const unsigned size_tag = SIMDPP_TAG_SIZE64;
};

template<unsigned N, class V>
struct any_float32 : any_vec32<N, V>
{
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_FLOAT32_SIZE - 1) / SIMDPP_FAST_FLOAT32_SIZE;
    using element_type = float;
    using uint_element_type = uint32_t;
    using int_vector_type = int32<N>;
    using uint_vector_type = uint32<N>;
    using mask_vector_type = mask_float32<N>;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;
};

template<unsigned N, class V>
struct any_float64 : any_vec64<N, V>
{
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_FLOAT64_SIZE - 1) / SIMDPP_FAST_FLOAT64_SIZE;
    using element_type = double;
    using uint_element_type = uint64_t;
    using int_vector_type = int64<N>;
    using uint_vector_type = uint64<N>;
    using mask_vector_type = mask_float64<N>;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;
};

template<unsigned N, class V>
struct any_int8 : any_vec8<N, V>
{
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT8_SIZE - 1) / SIMDPP_FAST_INT8_SIZE;
    using uint_element_type = uint8_t;
    using int_vector_type = int8<N>;
    using uint_vector_type = uint8<N>;
    using mask_vector_type = mask_int8<N>;

    static constexpr unsigned num_bits = 8;
    static constexpr uint_element_type all_bits = 0xff;
};

template<unsigned N, class V>
struct any_int16 : any_vec16<N, V>
{
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT16_SIZE - 1) / SIMDPP_FAST_INT16_SIZE;
    using uint_element_type = uint16_t;
    using int_vector_type = int16<N>;
    using uint_vector_type = uint16<N>;
    using mask_vector_type = mask_int16<N>;

    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;
};

template<unsigned N, class V>
struct any_int32 : any_vec32<N, V>
{
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT32_SIZE - 1) / SIMDPP_FAST_INT32_SIZE;
    using uint_element_type = uint32_t;
    using int_vector_type = int32<N>;
    using uint_vector_type = uint32<N>;
    using mask_vector_type = mask_int32<N>;

    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;
};

template<unsigned N, class V>
struct any_int64 : any_vec64<N, V>
{
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT64_SIZE - 1) / SIMDPP_FAST_INT64_SIZE;
    using uint_element_type = uint64_t;
    using int_vector_type = int64<N>;
    using uint_vector_type = uint64<N>;
    using mask_vector_type = mask_int64<N>;

    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
