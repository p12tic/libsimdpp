/*  libsimdpp
    Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** Extracts the @a id-th element from int8x16 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 1-2}
    @icost{SSE4.1-AVX, 1}
*/
template<unsigned id>
inline uint8_t extract(basic_int8x16 a)
{
    static_assert(id < 16, "index out of bounds");
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

/** Extracts the @a id-th element from int16x8 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.
*/
template<unsigned id>
inline uint16_t extract(basic_int16x8 a)
{
    static_assert(id < 8, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE2
    return _mm_extract_epi16(a, id);
#elif SIMDPP_USE_NEON
    return vgetq_lane_u16(a, id);
#endif
}

/** Extracts the @a id-th element from int32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
*/
template<unsigned id>
inline uint32_t extract(basic_int32x4 a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE4_1
    return _mm_extract_epi32(a, id);
#elif SIMDPP_USE_SSE2
    int32x4 t = a;
    if (id != 0) {
        t = move_l<id>(t);
    }
    return _mm_cvtsi128_si32(t);
#elif SIMDPP_USE_NEON
    return vgetq_lane_u32(a, id);
#endif
}

/** Extracts an element from int64x2 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
*/
template<unsigned id>
inline uint64_t extract(basic_int64x2 a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE4_1
    return _mm_extract_epi64(a, id);
#elif SIMDPP_USE_SSE2
    uint64x2 t = a;
    if (id != 0) {
        t = move_l<id>(t);
    }
    return _mm_cvtsi128_si64(t);
#elif SIMDPP_USE_NEON
    return vgetq_lane_u64(a, id);
#endif
}

/** Extracts an element from float32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
*/
template<unsigned id>
inline float extract(float32x4 a)
{
    static_assert(id < 4, "index out of bounds");
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
inline double extract(float64x2 a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    return bit_cast<double>(extract<id>(int64x2(a)));
#endif
}

namespace detail {
/* Implementation of extract_bits */
template<unsigned id>
struct extract_bits_impl {

    uint16_t operator()(uint8x16 a)
    {
#if SIMDPP_USE_NULL
        uint16_t r = 0;
        null::foreach<uint8x16>(a, [&r](uint8_t x){
            x = (x >> id) & 1;
            r = (r >> 1) | (uint16_t(x) << 15);
            return 0; // dummy
        });
        return r;
#elif SIMDPP_USE_SSE2
        a = shift_l<7-id>((uint16x8) a);
        return _mm_movemask_epi8(a);
#elif SIMDPP_USE_NEON
        uint8x16 mask = uint8x16::make_const(0x80);
        int8x16 shift_mask = int8x16::make_const(-7,-6,-5,-4,-3,-2,-1,0);

        a = bit_and(a, mask);
        a = vshlq_u8(a, shift_mask);
        a = vpaddlq_u8(a);
        a = vpaddlq_u16(a);
        a = vpaddlq_u32(a);
        a = zip_lo(a, a);
        return extract<0>((uint16x8)a);
#endif
    }
};

// Optimized implementation
template<>
struct extract_bits_impl<777> {

    uint16_t operator()(uint8x16 a)
    {
#if SIMDPP_USE_NULL
        uint16_t r = 0;
        null::foreach<uint8x16>(a, [&r](uint8_t x){
            x = x & 1;
            r = (r >> 1) | (uint16_t(x) << 15);
            return 0; // dummy
        });
        return r;
#elif SIMDPP_USE_SSE2
        return _mm_movemask_epi8(a);
#elif SIMDPP_USE_NEON
        uint8x16 mask = uint8x16::make_const(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

        a = bit_and(a, mask);
        a = vpaddlq_u8(a);
        a = vpaddlq_u16(a);
        a = vpaddlq_u32(a);
        a = zip_lo(a, a);
        return extract<0>((uint16x8)a);
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
    static_assert(id < 8 || id == 777, "index out of bounds");
    return detail::extract_bits_impl<id>()(a);
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif


