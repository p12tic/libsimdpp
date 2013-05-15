/*  libsimdpp
    Copyright (C) 2011-2013  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_EXTRACT_H
#define LIBSIMDPP_SIMD_EXTRACT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/cast.h>

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
#if SIMDPP_USE_NULL
    return a[id];
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    return bit_cast<double>(extract<id>(int64x2(a)));
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif


