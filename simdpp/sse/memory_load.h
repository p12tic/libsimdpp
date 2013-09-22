/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SSE_MEMORY_LOAD_H
#define LIBSIMDPP_SSE_MEMORY_LOAD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace sse {


/// @{
/** Loads the first @a N elements of a 128-bit vector from memory.

    @a N must be a power of 2 and at least @a M/4 where @a M is the number of
    elements within vector. @a P must be 0 or @a M/2 if @a N == M/2.

    If @a N is @a M/2, then the values of non-loaded elements are preserved,
    otherwise, they are set to zero.
*/
template<unsigned P, unsigned N>
void load_lane(basic_int8x16& a, const void* p)
{
    static_assert(N==4 || N==8, "Size not supported");
    static_assert(P==0 || (N==8 && P==8), "Position not supported");
    switch (N) {
    case 4:
        a = _mm_castps_si128(_mm_load_ss(reinterpret_cast<float*>(p)));
        break;
    case 8:
        if (P == 0) {
            a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
        } else {
            a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
        }
        break;
    }
    return a;
}

template<unsigned P, unsigned N>
void load_lane(basic_int16x8& a, const void* p)
{
    static_assert(N==2 || N==4, "Size not supported");
    static_assert(P==0 || (N==4 && P==4), "Position not supported");
    switch (N) {
    case 2:
        a = _mm_castps_si128(_mm_load_ss(reinterpret_cast<float*>(p)));
        break;
    case 4:
        if (P == 0) {
            a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
        } else {
            a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
        }
        break;
    }
    return a;
}

template<unsigned P, unsigned N>
void load_lane(basic_int32x4& a, const void* p)
{
    static_assert(N==1 || N==2, "Size not supported");
    static_assert(P==0 || (N==2 && P==2), "Position not supported");
    switch (N) {
    case 1:
        a = _mm_castps_si128(_mm_load_ss(reinterpret_cast<float*>(p)));
        break;
    case 2:
        if (P == 0) {
            a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
        } else {
            a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
        }
        break;
    }
    return a;
}

template<unsigned P, unsigned N>
void load_lane(basic_int64x2& a, const void* p)
{
    static_assert(N==1, "Size not supported");
    static_assert(P==0 || P==1, "Position not supported");
    if (P == 0) {
        a = _mm_castps_si128(_mm_loadl_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
    } else {
        a = _mm_castps_si128(_mm_loadh_pi(_mm_castsi128_ps(a), reinterpret_cast<__m64*>(p)));
    }
    return a;
}

template<unsigned P, unsigned N>
void load_lane(float32x4& a, const float* p)
{
    static_assert(N==1 || N==2, "Size not supported");
    static_assert(P==0 || (N==2 && P==2), "Position not supported");
    switch (N) {
    case 1:
        a = _mm_load_ss(p);
        return a;
    case 2:
        if (P == 0) {
            a = _mm_loadl_pi(a, reinterpret_cast<__m64*>(p));
        } else {
            a = _mm_loadh_pi(a, reinterpret_cast<__m64*>(p));
        }
        return a;
    }
}

template<unsigned P, unsigned N>
float64x2 load_lane(float64x2& a, const double* p)
{
    static_assert(N==1, "Size not supported");
    static_assert(P==0 || P==1, "Position not supported");
    if (P == 0) {
        a = _mm_loadl_pd(a, p);
    } else {
        a = _mm_loadh_pd(a, p);
    }
    return a;
}
/// @}

} // namespace sse
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

