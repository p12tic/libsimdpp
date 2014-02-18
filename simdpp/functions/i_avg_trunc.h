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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_I_AVG_TRUNC_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_I_AVG_TRUNC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Computes truncated average of the unsigned 8-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint8x16 avg_trunc(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint8x16>(a, b, [](uint8_t a, uint8_t b){
        return (uint16_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // (x & y) + ((x ^ y) >> 1)
    uint8x16 x1 = bit_and(a, b);
    uint8x16 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#elif SIMDPP_USE_NEON
    return vhaddq_u8(a, b);
#endif
}

inline uint8x32 avg_trunc(uint8x32 a, uint8x32 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1)
    uint8x32 x1 = bit_and(a, b);
    uint8x32 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of signed 8-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{NEON, ALTIVEC, 2}
*/
inline int8x16 avg_trunc(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int8x16>(a, b, [](int8_t a, int8_t b){
        return (int16_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 a2, b2, bias, r;
    bias = uint8x16::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vhaddq_s8(a, b);
#endif
}

inline int8x32 avg_trunc(int8x32 a, int8x32 b)
{
#if SIMDPP_USE_AVX2
    uint8x32 a2, b2, bias, r;
    bias = uint8x32::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of unsigned 16-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint16x8 avg_trunc(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){
        return (uint32_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // (x & y) + ((x ^ y) >> 1)
    uint16x8 x1 = bit_and(a, b);
    uint16x8 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#elif SIMDPP_USE_NEON
    return vhaddq_u16(a, b);
#endif
}

inline uint16x16 avg_trunc(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1)
    uint16x16 x1 = bit_and(a, b);
    uint16x16 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of signed 16-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{NEON, ALTIVEC, 2}
*/
inline int16x8 avg_trunc(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){
        return (int32_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint16x8 a2, b2, bias, r;
    bias = uint16x8::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vhaddq_s16(a, b);
#endif
}

inline int16x16 avg_trunc(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 a2, b2, bias, r;
    bias = uint16x16::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of unsigned 32-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint32x4 avg_trunc(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint32x4>(a, b, [](uint32_t a, uint32_t b){
        return (uint64_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // (x & y) + ((x ^ y) >> 1)
    uint32x4 x1 = bit_and(a, b);
    uint32x4 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#elif SIMDPP_USE_NEON
    return vhaddq_u32(a, b);
#endif
}

inline uint32x8 avg_trunc(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    // (x & y) + ((x ^ y) >> 1)
    uint32x8 x1 = bit_and(a, b);
    uint32x8 x2 = bit_xor(a, b);
    return add(x1, shift_r<1>(x2));
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes truncated average of signed 32-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}
    @icost{ALTIVEC, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{ALTIVEC, 8}
    @icost{NEON, 2}
*/
inline int32x4 avg_trunc(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int32x4>(a, b, [](int32_t a, int32_t b){
        return (int64_t(a) + b) >> 1;
    });
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint32x4 a2, b2, bias, r;
    bias = uint32x4::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vhaddq_s32(a, b);
#endif
}

inline int32x8 avg_trunc(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    uint32x8 a2, b2, bias, r;
    bias = uint32x8::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg_trunc(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#else
    return {avg_trunc(a[0], b[0]), avg_trunc(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

