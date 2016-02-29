/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_MEMORY_LOAD_H
#define LIBSIMDPP_SSE_MEMORY_LOAD_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {


/// @{
/** Loads the first @a N elements of a 128-bit vector from memory.

    @a N must be a power of 2 and at least @a M/4 where @a M is the number of
    elements within vector. @a P must be 0 or @a M/2 if @a N == M/2.

    If @a N is @a M/2, then the values of non-loaded elements are preserved,
    otherwise, they are set to zero.
*/
template<unsigned P, unsigned N> SIMDPP_INL
void load_lane(uint8x16& a, const void* p)
{
    SIMDPP_STATIC_ASSERT(N==4 || N==8, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==8 && P==8), "Position not supported");
    switch (N) {
    case 4:
        a = _mm_castps_si128(_mm_load_ss(reinterpret_cast<const float*>(p)));
        break;
    case 8:
        if (P == 0) {
            a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
        } else {
            a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
        }
        break;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void load_lane(uint16x8& a, const void* p)
{
    SIMDPP_STATIC_ASSERT(N==2 || N==4, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==4 && P==4), "Position not supported");
    switch (N) {
    case 2:
        a = _mm_castps_si128(_mm_load_ss(reinterpret_cast<const float*>(p)));
        break;
    case 4:
        if (P == 0) {
            a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
        } else {
            a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
        }
        break;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void load_lane(uint32x4& a, const void* p)
{
    SIMDPP_STATIC_ASSERT(N==1 || N==2, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==2 && P==2), "Position not supported");
    switch (N) {
    case 1:
        a = _mm_castps_si128(_mm_load_ss(reinterpret_cast<const float*>(p)));
        break;
    case 2:
        if (P == 0) {
            a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
        } else {
            a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
        }
        break;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void load_lane(uint64x2& a, const void* p)
{
    SIMDPP_STATIC_ASSERT(N==1, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || P==1, "Position not supported");
    if (P == 0) {
        a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
    } else {
        a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<const __m64*>(p)));
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void load_lane(float32x4& a, const void* p)
{
    SIMDPP_STATIC_ASSERT(N==1 || N==2, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==2 && P==2), "Position not supported");
    switch (N) {
    case 1:
        a = _mm_load_ss(reinterpret_cast<const float*>(p));
    case 2:
        if (P == 0) {
            a = _mm_loadl_pi(a, reinterpret_cast<const __m64*>(p));
        } else {
            a = _mm_loadh_pi(a, reinterpret_cast<const __m64*>(p));
        }
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void load_lane(float64x2& a, const void* p)
{
    SIMDPP_STATIC_ASSERT(N==1, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || P==1, "Position not supported");

    const double* q = reinterpret_cast<const double*>(p);
    if (P == 0) {
        a = _mm_loadl_pd(a, q);
    } else {
        a = _mm_loadh_pd(a, q);
    }
}
/// @}

} // namespace sse
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif

