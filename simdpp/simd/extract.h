/*  libsimdpp
    Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_EXTRACT_H
#define LIBSIMDPP_SIMD_EXTRACT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/fwd.h>
#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/cast.h>
#include <simdpp/simd/detail/word_size.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_insert_extract
/// @{

/// @{
/** Extracts the @a id-th element from int8x16 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 1-2}
    @icost{SSE4.1-AVX, 1}
*/
template<unsigned id>
uint8_t extract(basic_int8x16 a)
{
    SIMDPP_STATIC_ASSERT(id < 16, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE4_1
    return _mm_extract_epi8(a, id);
#elif SIMDPP_USE_SSE2
    unsigned shift = (id % 2 == 1) ? 8 : 0;
    return _mm_extract_epi16(a, id/2) >> shift;
#elif SIMDPP_USE_NEON
    return vgetq_lane_u8(a, id);
#endif
}

template<unsigned id>
int8_t extract(int8x16 a)
{
    return extract<id>(basic_int8x16(a));
}
/// @}

/// @{
/** Extracts the @a id-th element from int16x8 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.
*/
template<unsigned id>
uint16_t extract(basic_int16x8 a)
{
    SIMDPP_STATIC_ASSERT(id < 8, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE2
    return _mm_extract_epi16(a, id);
#elif SIMDPP_USE_NEON
    return vgetq_lane_u16(a, id);
#endif
}

template<unsigned id>
int16_t extract(int16x8 a)
{
    return extract<id>(basic_int16x8(a));
}
/// @}

/// @{
/** Extracts the @a id-th element from int32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
*/
template<unsigned id>
uint32_t extract(basic_int32x4 a)
{
    SIMDPP_STATIC_ASSERT(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE4_1
    return _mm_extract_epi32(a, id);
#elif SIMDPP_USE_SSE2
    return _mm_cvtsi128_si32(move_l<id>(a)); // when id==0, move_l is template-specialized and does nothing
#elif SIMDPP_USE_NEON
    return vgetq_lane_u32(a, id);
#endif
}

template<unsigned id>
int32_t extract(int32x4 a)
{
    return extract<id>(basic_int32x4(a));
}
/// @}

/// @{
/** Extracts an element from int64x2 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
    @icost{SSE4_1, 1}
    @icost{SSE2_32bit, SSE3_32bit, SSSE3_32bit, 3-4}
    @icost{SSE4_1_32bit, 2}
*/
template<unsigned id>
uint64_t extract(basic_int64x2 a)
{
    SIMDPP_STATIC_ASSERT(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE4_1
#if SIMDPP_SSE_32_BITS
    basic_int32x4 t = a;
    uint64_t r = extract<id*2>(t);
    r |= uint64_t(extract<id*2+1>(t)) << 32;
    return r;
#else
    return _mm_extract_epi64(a, id);
#endif
#elif SIMDPP_USE_SSE2
#if SIMDPP_SSE_32_BITS
    basic_int32x4 t = a;
    uint64_t r = 0;
    t = move_l<id*2>(t); // when id==0, move_l is template-specialized and does nothing
    r = extract<0>(t);
    t = move_l<1>(t);
    r |= uint64_t(extract<0>(t)) << 32;
    return r;
#else
    uint64x2 t = a;
    if (id != 0) {
        t = move_l<id>(t);
    }
    return _mm_cvtsi128_si64(t);
#endif
#elif SIMDPP_USE_NEON
    return vgetq_lane_u64(a, id);
#endif
}

template<unsigned id>
int64_t extract(int64x2 a)
{
    return extract<id>(basic_int64x2(a));
}
/// @}

/** Extracts an element from float32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
*/
template<unsigned id>
float extract(float32x4 a)
{
    SIMDPP_STATIC_ASSERT(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE2
    return bit_cast<float>(extract<id>(int32x4(a)));
#elif SIMDPP_USE_NEON
    return vgetq_lane_f32(a, id);
#endif
}

/** Extracts an element from float64x2 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.
*/
template<unsigned id>
double extract(float64x2 a)
{
    SIMDPP_STATIC_ASSERT(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    return bit_cast<double>(extract<id>(int64x2(a)));
#endif
}

namespace {
template<unsigned id>
struct null_extract_bits_impl {
    null_extract_bits_impl(uint16_t* r) : r_(r) {}

    uint16_t* r_;

    uint8_t operator()(uint8_t x) {
        x = (x >> id) & 1;
        *r_ = (*r_ >> 1) | (uint16_t(x) << 15);
        return 0; // dummy
    }
};
}  // namespace

namespace detail {
/* Implementation of extract_bits */
template<unsigned id>
struct extract_bits_impl {

    uint16_t operator()(uint8x16 a)
    {
#if SIMDPP_USE_NULL
        uint16_t r = 0;
        null::foreach<uint8x16>(a, null_extract_bits_impl<id>(&r));
        return r;
#elif SIMDPP_USE_SSE2
        a = shift_l<7-id>((uint16x8) a);
        return _mm_movemask_epi8(a);
#elif SIMDPP_USE_NEON
        uint8x16 mask = uint8x16::make_const(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);
        int8x16 shift_mask = int8x16::make_const(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                                                 4-int(id), 5-int(id), 6-int(id), 7-int(id));

        a = vshlq_u8(a, shift_mask);
        a = bit_and(a, mask);
        a = vpaddlq_u8(a);
        a = vpaddlq_u16(a);
        a = vpaddlq_u32(a);
        uint8x8_t r = vzip_u8(vget_low_u8(a), vget_high_u8(a)).val[0];
        return vget_lane_u16(vreinterpret_u16_u8(r), 0);
#endif
    }
};

// Optimized implementation
namespace {
struct null_extract_bits_impl_777 {
    null_extract_bits_impl_777(uint16_t* r) : r_(r) {}

    uint16_t* r_;

    uint8_t operator()(uint8_t x) {
        x = x & 1;
        *r_ = (*r_ >> 1) | (uint16_t(x) << 15);
        return 0; // dummy
    }
};
}  // namespace

template<>
struct extract_bits_impl<777> {

    uint16_t operator()(uint8x16 a)
    {
#if SIMDPP_USE_NULL
        uint16_t r = 0;
        null::foreach<uint8x16>(a, null_extract_bits_impl_777(&r));
        return r;
#elif SIMDPP_USE_SSE2
        return _mm_movemask_epi8(a);
#elif SIMDPP_USE_NEON
        uint8x16 mask = uint8x16::make_const(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

        a = bit_and(a, mask);
        a = vpaddlq_u8(a);
        a = vpaddlq_u16(a);
        a = vpaddlq_u32(a);
        uint8x8_t r = vzip_u8(vget_low_u8(a), vget_high_u8(a)).val[0];
        return vget_lane_u16(vreinterpret_u16_u8(r), 0);
#endif
    }
};

} // namespace detail
/** Extracts specific bit from each byte of each element of a int8x16 vector.

    The default template argument selects the bits from each byte in most
    efficient way.

    @code
    r = (a[0] & 0x80 >> 7) | (a[1] & 0x80 >> 6) | ...  | (a[15] & 0x80 << 8)
    @endcode
*/
template<unsigned id = 777>
uint16_t extract_bits(uint8x16 a)
{
    SIMDPP_STATIC_ASSERT(id < 8 || id == 777, "index out of bounds");
    return detail::extract_bits_impl<id>()(a);
}

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


