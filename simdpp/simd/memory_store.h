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

#ifndef LIBSIMDPP_SIMD_MEMORY_STORE_H
#define LIBSIMDPP_SIMD_MEMORY_STORE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/detail/mem_pack.h>

#if SIMDPP_USE_SSE2
    #include <simdpp/sse/extract_half.h>
    #include <simdpp/sse/memory_store.h>
#elif SIMDPP_USE_NEON
    #include <simdpp/neon/memory_store.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_store Operations: store a register to memory
/// @{

/// @{
/** Stores a 128-bit or 256-bit integer vector to an aligned memory location.

    @par 128-bit version:

    @code
    *(p) = a[0..127]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:

    @code
    *(p) = a[0..255]
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
    @icost{AVX (integer vectors), 2}
*/
inline void store(void* p, int128 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_store_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u64(reinterpret_cast<uint64_t*>(p), vreinterpretq_u64_u32(a));
#elif SIMDPP_USE_ALTIVEC
    vec_stl((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(p));
#endif
}

inline void store(void* p, int256 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX2
    _mm256_store_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    store(q, a[0]);
    store(q+16, a[1]);
#endif
}

inline void store(float *p, float32x4 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_store_ps(p, a);
#elif SIMDPP_USE_NEON
    vst1q_f32(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_stl((__vector float)a, 0, p);
#endif
}

inline void store(float* p, float32x8 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    _mm256_store_ps(p, a);
#else
    store(p, a[0]);
    store(p+4, a[1]);
#endif
}

inline void store(double *p, float64x2 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_store_pd(p, a);
#endif
}

inline void store(double* p, float64x4 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    _mm256_store_pd(p, a);
#else
    store(p, a[0]);
    store(p+2, a[1]);
#endif
}

/// @{
/** Stores a 128-bit or 256-bit integer, 32-bit or 64-bit floating point vector
    to memory without polluting the caches, if possible.

    @par 128-bit version:

    @code
    *(p) = a[0..127]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:

    @code
    *(p) = a[0..255]
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
    @icost{AVX (integer vectors), 2}
*/
inline void stream(void* p, int128 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    store(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(p));
#endif
}

inline void stream(void* p, int256 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX2
    _mm256_stream_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    stream(q, a[0]);
    stream(q+16, a[1]);
#endif
}

inline void stream(float* p, float32x4 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_ps(p, a);
#elif SIMDPP_USE_NEON
    store(p, a);
#elif SIMDPP_USE_ALTIVEC
    vec_st((__vector float)a, 0, p);
#endif
}

inline void stream(float* p, float32x8 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    _mm256_stream_ps(p, a);
#else
    stream(p, a[0]);
    stream(p+4, a[1]);
#endif
}

inline void stream(double* p, float64x2 a)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_pd(p, a);
#endif
}

inline void stream(double* p, float64x4 a)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    _mm256_stream_pd(p, a);
#else
    stream(p, a[0]);
    stream(p+2, a[1]);
#endif
}
/// @}

namespace detail {
// The 256-bit store_first and store_last are mostly boilerplate.

// hsz - the number of elements in the half-vector
template<unsigned hsz, class P, class V>
void v256_store_first(P* p, V a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_SSE2
    if (n >= hsz) {
        store(p, sse::extract_lo(a));
        // P may not be char*, hence sizeof
        store_first(p + 16 / sizeof(P), sse::extract_hi(a), n - hsz);
    } else {
        store_first(p, sse::extract_lo(a), n);
    }
#else
    if (n >= hsz) {
        store(p, a[0]);
        store_first(p + 16 / sizeof(P), a[1], n - hsz);
    } else {
        store_first(p, a[0], n);
    }
#endif
}

template<unsigned hsz, class P, class V>
void v256_store_last(P* p, V a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_SSE2
    if (n >= hsz) {
        store_last(p, sse::extract_lo(a), n - hsz);
        store(p + 16 / sizeof(P), sse::extract_hi(a));
    } else {
        store_last(p + 16 / sizeof(P), sse::extract_hi(a), n);
    }
#else
    if (n >= hsz) {
        store_last(p, a[0], n - hsz);
        store(p + 16 / sizeof(P), a[1]);
    } else {
        store_last(p + 16 / sizeof(P), a[1], n);
    }
#endif
}

} // namespace detail

/// @{
/** Stores the first @a n elements of an 128-bit or 256-bit integer, 32-bit or
    64-bit floating point vector to memory. @a n must be in range [0..N-1]
    where @a N is the number of elements in the vector. If @a n is zero, no
    store is made.

    @code
    *(p) = a0
    *(p+1) = a1
    ...
    *(p+n-1) = a{n-1}
    @endcode

    This function results in several instructions. It is best not to use it in
    inner loops.

    @par 128-bit version:
    @a p must be aligned to 16 bytes.
    @par 256-bit version:
    @a p must be aligned to 32 bytes.
*/
inline void store_first(void* p, basic_int8x16 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    basic_int8x16 mask = int128::ones();

    // let the compiler build a jump table
    switch (n) {
    case 0: return;
    case 1: mask = move_l<15>(mask); break;
    case 2: mask = move_l<14>(mask); break;
    case 3: mask = move_l<13>(mask); break;
    case 4: mask = move_l<12>(mask); break;
    case 5: mask = move_l<11>(mask); break;
    case 6: mask = move_l<10>(mask); break;
    case 7: mask = move_l<9>(mask); break;
    case 8: mask = move_l<8>(mask); break;
    case 9: mask = move_l<7>(mask); break;
    case 10: mask = move_l<6>(mask); break;
    case 11: mask = move_l<5>(mask); break;
    case 12: mask = move_l<4>(mask); break;
    case 13: mask = move_l<3>(mask); break;
    case 14: mask = move_l<2>(mask); break;
    case 15: mask = move_l<1>(mask); break;
    default: return; //UB
    }

    sse::store_masked(p, a, mask);
#elif SIMDPP_USE_NEON
    // The following will be trainslated into conditional instructions, thus
    // will incur no pipeline flushes
    char* q = reinterpret_cast<char*>(p);
    if (n >= 8) {
        neon::store_lane<0,8>(q, a);
        q += 8;
        a = move_l<8>(a);
    }
    if (n%8 >= 4) {
        neon::store_lane<0,4>(q, a);
        q += 4;
        a = move_l<4>(a);
    }
    if (n%4 >= 2) {
        neon::store_lane<0,2>(q, a);
        q += 2;
        a = move_l<2>(a);
    }
    if (n%2 == 1) {
        neon::store_lane<0,1>(q, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    if (n >= 8) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
        q += 8;
        n -= 8;
    }
    if (n >= 4) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        q += 4;
        n -= 4;
    }
    if (n >= 2) {
        vec_ste((__vector uint16_t)a, 0, reinterpret_cast<uint16_t*>(q));
        q += 2;
        n -= 2;
    }
    if (n == 1) {
        vec_ste((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(q));
    }
#endif
}

inline void store_first(void* p, basic_int8x32 a, unsigned n)
{
    detail::v256_store_first<16>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(void* p, basic_int16x8 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    basic_int16x8 mask = int128::ones();

    switch (n) {
    case 0: return;
    case 1: mask = move_l<7>(mask); break;
    case 2: mask = move_l<6>(mask); break;
    case 3: mask = move_l<5>(mask); break;
    case 4: mask = move_l<4>(mask); break;
    case 5: mask = move_l<3>(mask); break;
    case 6: mask = move_l<2>(mask); break;
    case 7: mask = move_l<1>(mask); break;
    default: return; //UB
    }

    sse::store_masked(p, a, mask);
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);
    if (n >= 4) {
        neon::store_lane<0,4>(q, a);
        q += 8;
        a = move_l<4>(a);
    }
    if (n%4 >= 2) {
        neon::store_lane<0,2>(q, a);
        q += 4;
        a = move_l<2>(a);
    }
    if (n%2 >= 1) {
        neon::store_lane<0,1>(q, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    if (n >= 4) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
        q += 8;
        n -= 4;
    }
    if (n >= 2) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        q += 4;
        n -= 2;
    }
    if (n == 1) {
        vec_ste((__vector uint16_t)a, 0, reinterpret_cast<uint16_t*>(q));
    }
#endif
}

inline void store_first(void* p, basic_int16x16 a, unsigned n)
{
    detail::v256_store_first<8>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(void* p, basic_int32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    switch (n) {
    case 3:
        sse::store_lane<0,2>(q, a);
        a = move_l<2>(a);
        sse::store_lane<0,1>(q+8, a);
        return;
    case 2:
        sse::store_lane<0,2>(q, a);
        return;
    case 1:
        sse::store_lane<0,1>(q, a);
        return;
    }
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);

    if (n >= 2) {
        neon::store_lane<0,2>(q, a);
        q += 8;
        a = move_l<2>(a);
    }
    if (n%2 == 1) {
        neon::store_lane<0,1>(q, a);
    }

#elif SIMDPP_USE_ALTIVEC
    u_int32_t* q = reinterpret_cast<uint32_t*>(p);
    if (n >= 2) {
        vec_ste((__vector uint32_t)a, 0, q);
        vec_ste((__vector uint32_t)a, 4, q);
        q += 8;
        n -= 4;
    }
    if (n == 1) {
        vec_ste((__vector uint32_t)a, 0, q);
    }
#endif
}

inline void store_first(void* p, basic_int32x8 a, unsigned n)
{
    detail::v256_store_first<4>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(void* p, basic_int64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_NEON
    if (n == 1) {
        neon::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
    }
#endif
}

inline void store_first(void* p, basic_int64x4 a, unsigned n)
{
    detail::v256_store_first<2>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(float* p, float32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2
    switch (n) {
    case 3:
        sse::store_lane<0,2>(p, a);
        a = permute<2,0,0,0>(a);
        sse::store_lane<0,1>(p+2, a);
        return;
    case 2:
        sse::store_lane<0,2>(p, a);
        return;
    case 1:
        sse::store_lane<0,1>(p, a);
        return;
    }
#else
    store_first(p, int32x4{a}, n);
#endif
}

inline void store_first(float* p, float32x8 a, unsigned n)
{
    detail::v256_store_first<4>(p, a, n);
}

inline void store_first(double* p, float64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#endif
}

inline void store_first(double* p, float64x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    switch (n) {
    case 3:
        store(p, sse::extract_lo(a));
        sse::store_lane<0,1>(p+2, sse::extract_hi(a));
        return;
    case 2:
        store(p, sse::extract_lo(a));
        return;
    case 1:
        sse::store_lane<0,1>(p, sse::extract_lo(a));
        return;
    }
#else
    detail::v256_store_first<2>(p, a, n);
#endif
}

/// @}

/// @{
/** Stores the last @a n elements of an 128-bit or 256-bit integer, 32-bit or
    64-bit floating point vector to memory. @a n must be in range [0..N-1]
    where @a N is the number of elements in the vector. If @a n is zero, no
    store is made.

    @code
    *(p+N-n) = a{N-n}
    ...
    *(p+N-2) = a{N-2}
    *(p+N-1) = a{N-1}
    @endcode

    This function results in several instructions. It is best not to use it in
    inner loops.

    @par 128-bit version:
    @a p must be aligned to 16 bytes.
    @par 256-bit version:
    @a p must be aligned to 32 bytes.
*/
inline void store_last(void* p, basic_int8x16 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    basic_int8x16 mask = int128::ones();

    // let the compiler build a jump table
    switch (n) {
    case 0: return;
    case 1: mask = move_r<15>(mask); break;
    case 2: mask = move_r<14>(mask); break;
    case 3: mask = move_r<13>(mask); break;
    case 4: mask = move_r<12>(mask); break;
    case 5: mask = move_r<11>(mask); break;
    case 6: mask = move_r<10>(mask); break;
    case 7: mask = move_r<9>(mask); break;
    case 8: mask = move_r<8>(mask); break;
    case 9: mask = move_r<7>(mask); break;
    case 10: mask = move_r<6>(mask); break;
    case 11: mask = move_r<5>(mask); break;
    case 12: mask = move_r<4>(mask); break;
    case 13: mask = move_r<3>(mask); break;
    case 14: mask = move_r<2>(mask); break;
    case 15: mask = move_r<1>(mask); break;
    default: return; //UB
    }

    sse::store_masked(p, a, mask);
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);
    q += 16;
    if (n >= 8) {
        q -= 8;
        neon::store_lane<8,8>(q, a);
        a = move_r<8>(a);
    }
    if (n%8 >= 4) {
        q -= 4;
        neon::store_lane<12,4>(q, a);
        a = move_r<4>(a);
    }
    if (n%4 >= 2) {
        q -= 2;
        neon::store_lane<14,2>(q, a);
        a = move_r<2>(a);
    }
    if (n%2 == 1) {
        q -= 1;
        neon::store_lane<15,1>(q, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    q += 16;
    if (n >= 8) {
        q -= 8;
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        n -= 8;
    }
    if (n >= 4) {
        q -= 4;
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        n -= 4;
    }
    if (n >= 2) {
        q -= 2;
        vec_ste((__vector uint16_t)a, 0, reinterpret_cast<uint16_t*>(q));
        n -= 2;
    }
    if (n == 1) {
        q -= 1;
        vec_ste((__vector uint8_t)a, 0, reinterpret_cast<uint8_t*>(q));
    }
#endif
}

inline void store_last(void* p, basic_int8x32 a, unsigned n)
{
    detail::v256_store_last<16>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, basic_int16x8 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    basic_int16x8 mask = int128::ones();

    switch (n) {
    case 0: return;
    case 1: mask = move_r<7>(mask); break;
    case 2: mask = move_r<6>(mask); break;
    case 3: mask = move_r<5>(mask); break;
    case 4: mask = move_r<4>(mask); break;
    case 5: mask = move_r<3>(mask); break;
    case 6: mask = move_r<2>(mask); break;
    case 7: mask = move_r<1>(mask); break;
    default: return; //UB
    }

    sse::store_masked(p, a, mask);
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);
    q += 16;
    if (n >= 4) {
        q -= 8;
        neon::store_lane<4,4>(q, a);
        a = move_r<4>(a);
    }
    if (n%4 >= 2) {
        q -= 4;
        neon::store_lane<6,2>(q, a);
        a = move_r<2>(a);
    }
    if (n%2 == 1) {
        q -= 2;
        neon::store_lane<7,1>(q, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    q += 16;
    if (n >= 4) {
        q -= 8;
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        n -= 4;
    }
    if (n >= 2) {
        q -= 4;
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        n -= 2;
    }
    if (n == 1) {
        q -= 2;
        vec_ste((__vector uint16_t)a, 0, reinterpret_cast<uint16_t*>(q));
    }
#endif
}

inline void store_last(void* p, basic_int16x16 a, unsigned n)
{
    detail::v256_store_last<8>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, basic_int32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    switch (n) {
    case 3: {
        basic_int32x4 b;
        b = move_l<1>(a);
        sse::store_lane<0,1>(q+4, b);
        sse::store_lane<2,2>(q+8, a);
        return;
    } case 2: {
        sse::store_lane<2,2>(q+8, a);
        return;
    } case 1: {
        a = move_l<3>(a);
        sse::store_lane<0,1>(q+12, a);
        return;
    }
    }
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);
    q += 16;
    if (n >= 2) {
        q -= 8;
        neon::store_lane<2,2>(q, a);
        a = move_r<2>(a);
    }
    if (n%2 == 1) {
        q -= 4;
        neon::store_lane<3,1>(q, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    q += 16;
    if (n >= 2) {
        q -= 8;
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        n -= 2;
    }
    if (n >= 1) {
        q -= 4;
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
    }
#endif
}

inline void store_last(void* p, basic_int32x8 a, unsigned n)
{
    detail::v256_store_last<4>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, basic_int64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        sse::store_lane<1,1>(q+8, a);
    }
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        neon::store_lane<1,1>(q+8, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        vec_ste((__vector uint32_t)a, 8, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 12, reinterpret_cast<uint32_t*>(q));
    }
#endif
}

inline void store_last(void* p, basic_int64x4 a, unsigned n)
{
    detail::v256_store_last<2>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(float* p, float32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2
    switch (n) {
    case 3: {
        float32x4 b;
        b = permute<1,0,0,0>(a);
        sse::store_lane<0,1>(p+1, b);
        sse::store_lane<2,2>(p+2, a);
        return;
    } case 2: {
        sse::store_lane<2,2>(p+2, a);
        return;
    } case 1: {
        a = permute<3,0,0,0>(a);
        sse::store_lane<0,1>(p+3, a);
        return;
    }
    }
#else
    store_last(p, int32x4{a}, n);
#endif
}

inline void store_last(float* p, float32x8 a, unsigned n)
{
    detail::v256_store_last<4>(p, a, n);
}

inline void store_last(double* p, float64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<1,1>(p+1, a);
    }
#endif
}

inline void store_last(double* p, float64x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    switch (n) {
    case 3:
        sse::store_lane<1,1>(p+1, sse::extract_lo(a));
        store(p+2, sse::extract_hi(a));
        return;
    case 2:
        store(p+2, sse::extract_hi(a));
        return;
    case 1:
        sse::store_lane<1,1>(p+3, sse::extract_hi(a));
        return;
    }
#else
    detail::v256_store_last<2>(p, a, n);
#endif
}
/// @}

namespace detail {

// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_store_i_pack2(void* p, V a, V b)
{
    p = detail::assume_aligned(p, 32);
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    detail::mem_pack2(a, b);
    store(q, a);
    store(q + 32, b);
#else
    store_packed2(q, a[0], b[0]);
    store_packed2(q + 32, a[1], b[1]);
#endif
}

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

template<class V>
void v256_store_i_pack4(void* p, V a, V b, V c, V d)
{
    p = detail::assume_aligned(p, 32);
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q + 32, b);
    store(q + 64, c);
    store(q + 96, d);
#else
    store_packed4(q, a[0], b[0], c[0], d[0]);
    store_packed4(q + 64, a[1], b[1], c[1], d[1]);
#endif
}

} // namespace detail

/// @{
/** Interleaves 8-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+30) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+62) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+63) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed2(void* p, basic_int8x16 a, basic_int8x16 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack2(a, b);
    store(q, a);
    store(q+16, b);
#elif SIMDPP_USE_NEON
    uint8x16x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_u8(reinterpret_cast<uint8_t*>(p), t);
#endif
}

inline void store_packed2(void* p, basic_int8x32 a, basic_int8x32 b)
{
    detail::v256_store_i_pack2(p, a, b);
}
/// @}

/// @{
/** Interleaves 16-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+30) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed2(void* p, basic_int16x8 a, basic_int16x8 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack2(a, b);
    store(q, a);
    store(q+16, b);
#elif SIMDPP_USE_NEON
    uint16x8x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_u16(reinterpret_cast<uint16_t*>(p), t);
#endif
}

inline void store_packed2(void* p, basic_int16x16 a, basic_int16x16 b)
{
    detail::v256_store_i_pack2(p, a, b);
}
/// @}

/// @{
/** Interleaves 32-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), *(p+6) ] = a
    [ *(p+1), *(p+3), *(p+5), *(p+7) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed2(void* p, basic_int32x4 a, basic_int32x4 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack2(a, b);
    store(q, a);
    store(q+16, b);
#elif SIMDPP_USE_NEON
    uint32x4x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_u32(reinterpret_cast<uint32_t*>(p), t);
#endif
}

inline void store_packed2(void* p, basic_int32x8 a, basic_int32x8 b)
{
    detail::v256_store_i_pack2(p, a, b);
}
/// @}

/// @{
/** Interleaves 64-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2) ] = a
    [ *(p+1), *(p+3) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed2(void* p, basic_int64x2 a, basic_int64x2 b)
{
    p = detail::assume_aligned(p, 16);
    char* q = reinterpret_cast<char*>(p);
    transpose2(a, b);
    store(q, a);
    store(q+16, b);
}

inline void store_packed2(void* p, basic_int64x4 a, basic_int64x4 b)
{
    detail::v256_store_i_pack2(p, a, b);
}
/// @}

/// @{
/** Interleaves 32-bit floating-point values from two vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+6) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+7) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed2(float* p, float32x4 a, float32x4 b)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    detail::mem_pack2(a, b);
    store(p, a);
    store(p+4, b);
#elif SIMDPP_USE_NEON
    float32x4x2_t t;
    t.val[0] = a;
    t.val[1] = b;
    vst2q_f32(p, t);
#endif
}

inline void store_packed2(float* p, float32x8 a, float32x8 b)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack2(a, b);
    store(p, a);
    store(p + 8, b);
#else
    store_packed2(p, a[0], b[0]);
    store_packed2(p + 8, a[1], b[1]);
#endif
}
/// @}

/// @{
/** Interleaves 64-bit floating-point values from two vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2) ] = a
    [ *(p+1), *(p+3) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes
*/
inline void store_packed2(double* p, float64x2 a, float64x2 b)
{
    p = detail::assume_aligned(p, 16);
    transpose2(a, b);
    store(p, a);
    store(p+2, b);
}

inline void store_packed2(double* p, float64x4 a, float64x4 b)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack2(a, b);
    store(p, a);
    store(p + 4, b);
#else
    store_packed2(p, a[0], b[0]);
    store_packed2(p + 4, a[1], b[1]);
#endif
}
/// @}

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

/// @{
/** Interleaves 8-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+124) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+125) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+126) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+127) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          basic_int8x16 a, basic_int8x16 b,
                          basic_int8x16 c, basic_int8x16 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    uint8x16x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_u8(reinterpret_cast<uint8_t*>(p), t);
#endif
}

inline void store_packed4(void* p,
                          basic_int8x32 a, basic_int8x32 b,
                          basic_int8x32 c, basic_int8x32 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 16-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          basic_int16x8 a, basic_int16x8 b,
                          basic_int16x8 c, basic_int16x8 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    uint16x8x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_u16(reinterpret_cast<uint16_t*>(p), t);
#endif
}

inline void store_packed4(void* p,
                          basic_int16x16 a, basic_int16x16 b,
                          basic_int16x16 c, basic_int16x16 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 32-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          basic_int32x4 a, basic_int32x4 b,
                          basic_int32x4 c, basic_int32x4 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);

    detail::mem_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    uint32x4x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_u32(reinterpret_cast<uint32_t*>(p), t);
#endif
}

inline void store_packed4(void* p,
                          basic_int32x8 a, basic_int32x8 b,
                          basic_int32x8 c, basic_int32x8 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 64-bit values from four vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4) ] = a
    [ *(p+1), *(p+5) ] = b
    [ *(p+2), *(p+6) ] = c
    [ *(p+3), *(p+7) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(void* p,
                          basic_int64x2 a, basic_int64x2 b,
                          basic_int64x2 c, basic_int64x2 d)
{
    p = detail::assume_aligned(p, 16);
    char* q = reinterpret_cast<char*>(p);
    transpose2(a, b);
    transpose2(c, d);
    store(q, a);
    store(q+16, c);
    store(q+32, b);
    store(q+48, d);
}

inline void store_packed4(void* p,
                          basic_int64x4 a, basic_int64x4 b,
                          basic_int64x4 c, basic_int64x4 d)
{
    detail::v256_store_i_pack4(p, a, b, c, d);
}
/// @}

/// @{
/** Interleaves 32-bit floating-point values from four vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ] = a
    [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ] = b
    [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ] = c
    [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(float* p,
                          float32x4 a, float32x4 b, float32x4 c, float32x4 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p+4, b);
    store(p+8, c);
    store(p+12, d);
#elif SIMDPP_USE_NEON
    float32x4x4_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    t.val[3] = d;
    vst4q_f32(p, t);
#endif
}

inline void store_packed4(float* p,
                          float32x8 a, float32x8 b, float32x8 c, float32x8 d)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p + 8, b);
    store(p + 16, c);
    store(p + 24, d);
#else
    store_packed4(p, a[0], b[0], c[0], d[0]);
    store_packed4(p + 16, a[1], b[1], c[1], d[1]);
#endif
}
/// @}

/// @{
/** Interleaves 64-bit floating-point values from four vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+4) ] = a
    [ *(p+1), *(p+5) ] = b
    [ *(p+2), *(p+6) ] = c
    [ *(p+3), *(p+7) ] = d
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+4), *(p+8),  *(p+12) ] = a
    [ *(p+1), *(p+5), *(p+9),  *(p+13) ] = b
    [ *(p+2), *(p+6), *(p+10), *(p+14) ] = c
    [ *(p+3), *(p+7), *(p+11), *(p+15) ] = d
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void store_packed4(double* p,
                          float64x2 a, float64x2 b, float64x2 c, float64x2 d)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p+2, b);
    store(p+4, c);
    store(p+6, d);
#endif
}

inline void store_packed4(double* p,
                          float64x4 a, float64x4 b, float64x4 c, float64x4 d)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    detail::mem_pack4(a, b, c, d);
    store(p, a);
    store(p + 4, b);
    store(p + 8, c);
    store(p + 12, d);
#else
    store_packed4(p, a[0], b[0], c[0], d[0]);
    store_packed4(p + 8, a[1], b[1], c[1], d[1]);
#endif
}
/// @}

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
