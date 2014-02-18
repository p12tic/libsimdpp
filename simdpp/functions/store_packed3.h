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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_STORE_PACKED3_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_STORE_PACKED3_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/detail/mem_pack.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

namespace detail {
// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_store_i_pack3(void* p, V a, V b, V c)
{
    p = detail::assume_aligned(p, 32);
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    detail::mem_pack3(a, b, c);
    store(q, a);
    store(q + 32, b);
    store(q + 64, c);
#else
    store_packed3(q, a[0], b[0], c[0]);
    store_packed3(q + 48, a[1], b[1], c[1]);
#endif
}
} //namespace detail

/// @{
/** Interleaves 8-bit values from three vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), ... , *(p+45) ] = a
    [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ] = b
    [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ] = c
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), ... , *(p+93) ] = a
    [ *(p+1), *(p+4), *(p+7), ... , *(p+94) ] = b
    [ *(p+2), *(p+5), *(p+8), ... , *(p+95) ] = c
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed3(void* p,
                          basic_int8x16 a, basic_int8x16 b, basic_int8x16 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    uint8x16x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u8(reinterpret_cast<uint8_t*>(p), t);
#endif
}

inline void store_packed3(void* p,
                          basic_int8x32 a, basic_int8x32 b, basic_int8x32 c)
{
    detail::v256_store_i_pack3(p, a, b, c);
}
/// @}

/// @{
/** Interleaves 16-bit values from three vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), ... , *(p+21) ] = a
    [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ] = b
    [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ] = c
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), ... , *(p+45) ] = a
    [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ] = b
    [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ] = c
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed3(void* p,
                          basic_int16x8 a, basic_int16x8 b, basic_int16x8 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    uint16x8x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u16(reinterpret_cast<uint16_t*>(p), t);
#endif
}

inline void store_packed3(void* p,
                          basic_int16x16 a, basic_int16x16 b, basic_int16x16 c)
{
    detail::v256_store_i_pack3(p, a, b, c);
}
/// @}

/// @{
/** Interleaves 32-bit values from three vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), *(p+9)  ] = a
    [ *(p+1), *(p+4), *(p+7), *(p+10) ] = b
    [ *(p+2), *(p+5), *(p+8), *(p+11) ] = c
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), ... , *(p+21) ] = a
    [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ] = b
    [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ] = c
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed3(void* p,
                          basic_int32x4 a, basic_int32x4 b, basic_int32x4 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    uint32x4x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u32(reinterpret_cast<uint32_t*>(p), t);
#endif
}

inline void store_packed3(void* p,
                          basic_int32x8 a, basic_int32x8 b, basic_int32x8 c)
{
    detail::v256_store_i_pack3(p, a, b, c);
}
/// @}

/// @{
/** Interleaves 64-bit values from three vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+3) ] = a
    [ *(p+1), *(p+4) ] = b
    [ *(p+2), *(p+5) ] = c
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), *(p+9)  ] = a
    [ *(p+1), *(p+4), *(p+7), *(p+10) ] = b
    [ *(p+2), *(p+5), *(p+8), *(p+11) ] = c
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed3(void* p,
                          basic_int64x2 a, basic_int64x2 b, basic_int64x2 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    uint64_t* q = reinterpret_cast<uint64_t*>(p);
    uint64x1x2_t t1, t2, t3;
    t1.val[0] = vget_low_u64(a);  t1.val[1] = vget_low_u64(b);
    t2.val[0] = vget_low_u64(c);  t2.val[1] = vget_high_u64(a);
    t3.val[0] = vget_high_u64(b);  t3.val[1] = vget_high_u64(c);

    vst2_u64(q, t1);
    vst2_u64(q+2, t2);
    vst2_u64(q+4, t3);
#endif
}

inline void store_packed3(void* p,
                          basic_int64x4 a, basic_int64x4 b, basic_int64x4 c)
{
    detail::v256_store_i_pack3(p, a, b, c);
}
/// @}

/// @{
/** Interleaves 32-bit floating-point values from three vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), *(p+9)  ] = a
    [ *(p+1), *(p+4), *(p+7), *(p+10) ] = b
    [ *(p+2), *(p+5), *(p+8), *(p+11) ] = c
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), ... , *(p+21) ] = a
    [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ] = b
    [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ] = c
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed3(float* p, float32x4 a, float32x4 b, float32x4 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    detail::mem_pack3(a, b, c);
    store(p, a);
    store(p+4, b);
    store(p+8, c);
#elif SIMDPP_USE_NEON
    float32x4x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_f32(p, t);
#endif
}

inline void store_packed3(float* p,
                          float32x8 a, float32x8 b, float32x8 c)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack3(a, b, c);
    store(p, a);
    store(p + 8, b);
    store(p + 16, c);
#else
    store_packed3(p, a[0], b[0], c[0]);
    store_packed3(p + 12, a[1], b[1], c[1]);
#endif
}
/// @}

/// @{
/** Interleaves 64-bit floating-point values from three vectors and stores
    the result into successive locations starting from @a p.

    Loads 64-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    [ *(p),   *(p+3) ] = a
    [ *(p+1), *(p+4) ] = b
    [ *(p+2), *(p+5) ] = c
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+3), *(p+6), *(p+9)  ] = a
    [ *(p+1), *(p+4), *(p+7), *(p+10) ] = b
    [ *(p+2), *(p+5), *(p+8), *(p+11) ] = c
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed3(double* p, float64x2 a, float64x2 b, float64x2 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    detail::mem_pack3(a, b, c);
    store(p, a);
    store(p+2, b);
    store(p+4, c);
#endif
}

inline void store_packed3(double* p,
                          float64x4 a, float64x4 b, float64x4 c)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack3(a, b, c);
    store(p, a);
    store(p + 4, b);
    store(p + 8, c);
#else
    store_packed3(p, a[0], b[0], c[0]);
    store_packed3(p + 6, a[1], b[1], c[1]);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

