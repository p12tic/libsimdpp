/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef LIBSIMDPP_SSE_MEMORY_STORE_H
#define LIBSIMDPP_SSE_MEMORY_STORE_H
#if SIMDPP_USE_SSE2 || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace sse {

/// @{
/** Stores the first @a N elements of a 128-bit vector to memory.

    @a N must be a power of 2 and at least @a M/4 where @a M is the number of
    elements within vector. @a P must be 0 or @a M/2 if @a N == M/2.
*/
template<unsigned P, unsigned N> SIMDPP_INL
void store_lane(void* p, const uint8x16& a)
{
    SIMDPP_STATIC_ASSERT(N==4 || N==8, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==8 && P==8), "Position not supported");
    switch (N) {
    case 4:
        _mm_store_ss(reinterpret_cast<float*>(p), _mm_castsi128_ps(a));
        return;
    case 8:
        if (P == 0) {
            _mm_storel_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
        } else {
            _mm_storeh_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
        }
        return;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void store_lane(void* p, const uint16x8& a)
{
    SIMDPP_STATIC_ASSERT(N==2 || N==4, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==4 && P==4), "Position not supported");
    switch (N) {
    case 2:
        _mm_store_ss(reinterpret_cast<float*>(p), _mm_castsi128_ps(a));
        return;
    case 4:
        if (P == 0) {
            _mm_storel_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
        } else {
            _mm_storeh_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
        }
        return;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void store_lane(void* p, const uint32x4& a)
{
    SIMDPP_STATIC_ASSERT(N==1 || N==2, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==2 && P==2), "Position not supported");
    switch (N) {
    case 1:
        _mm_store_ss(reinterpret_cast<float*>(p), _mm_castsi128_ps(a));
        return;
    case 2:
        if (P == 0) {
            _mm_storel_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
        } else {
            _mm_storeh_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
        }
        return;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void store_lane(void* p, const uint64x2& a)
{
    SIMDPP_STATIC_ASSERT(N==1, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || P==1, "Position not supported");
    if (P == 0) {
        _mm_storel_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
    } else {
        _mm_storeh_pi(reinterpret_cast<__m64*>(p), _mm_castsi128_ps(a));
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void store_lane(void* p, const float32x4& a)
{
    SIMDPP_STATIC_ASSERT(N==1 || N==2, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || (N==2 && P==2), "Position not supported");
    switch (N) {
    case 1:
        _mm_store_ss(reinterpret_cast<float*>(p), a);
        return;
    case 2:
        if (P == 0) {
            _mm_storel_pi(reinterpret_cast<__m64*>(p), a);
        } else {
            _mm_storeh_pi(reinterpret_cast<__m64*>(p), a);
        }
        return;
    }
}

template<unsigned P, unsigned N> SIMDPP_INL
void store_lane(void* p, const float64x2& a)
{
    SIMDPP_STATIC_ASSERT(N==1, "Size not supported");
    SIMDPP_STATIC_ASSERT(P==0 || P==1, "Position not supported");
    if (P == 0) {
        _mm_storel_pi(reinterpret_cast<__m64*>(p), _mm_castpd_ps(a));
    } else {
        _mm_storeh_pi(reinterpret_cast<__m64*>(p), _mm_castpd_ps(a));
    }
}
/// @}

/** Stores bytes in an 128-bit integer vector according to a mask. The highest
    bit in the corresponding byte in the mask defines whether the byte will
    be saved. @a p does not need to be aligned to 16 bytes.
*/
SIMDPP_INL void store_masked(void* p, const uint8x16& a, const uint8x16& mask)
{
    _mm_maskmoveu_si128(a, mask, reinterpret_cast<char*>(p));
}

SIMDPP_INL void store_masked(void* p, const uint16x8& a, const uint16x8& mask) { store_masked(p, uint8x16(a), uint8x16(mask)); }
SIMDPP_INL void store_masked(void* p, const uint32x4& a, const uint32x4& mask) { store_masked(p, uint8x16(a), uint8x16(mask)); }
SIMDPP_INL void store_masked(void* p, const uint64x2& a, const uint64x2& mask) { store_masked(p, uint8x16(a), uint8x16(mask)); }


} // namespace sse
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
