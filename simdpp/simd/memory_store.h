/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_MEMORY_STORE_H
#define LIBSIMDPP_SIMD_MEMORY_STORE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

#if SIMDPP_USE_SSE2
    #include <simdpp/sse/extract_half.h>
    #include <simdpp/sse/memory_store.h>
    #include <simdpp/sse/detail/store_packed.h>
#elif SIMDPP_USE_NEON
    #include <simdpp/neon/memory_store.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/// @defgroup simd_store
/// @{

/// @{
/** Stores a 128-bit or 256-bit integer vector to an aligned memory location.

    @par 128-bit version:

    @code
    *(p) = a[0..127]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 128-bit version:

    @code
    *(p) = a[0..255]
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, 2}
    @icost{AVX (integer vectors), 2}
*/
inline void store(void* p, int128 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_store_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u32(reinterpret_cast<uint32_t*>(p), a);
#endif
}

inline void store(void* p, int256 a)
{
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
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_store_ps(p, a);
#elif SIMDPP_USE_NEON
    vst1q_f32(p, a);
#endif
}

inline void store(float* p, float32x8 a)
{
#if SIMDPP_USE_AVX
    _mm256_store_ps(p, a);
#else
    store(p, a[0]);
    store(p+4, a[1]);
#endif
}

inline void store(double *p, float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_store_pd(p, a);
#elif SIMDPP_USE_NEON
    store(p, int64x2(a));
#endif
}

inline void store(double* p, float64x4 a)
{
#if SIMDPP_USE_AVX
    _mm256_store_pd(p, a);
#else
    store(p, a[0]);
    store(p+2, a[1]);
#endif
}
/// @{
/** Stores a 128-bit or 256-bit integer, 32-bit or 64-bit float vector to an
    unaligned memory location.

    @par 128-bit version:

    @code
    *(p) = a[0..127]
    @endcode

    @a p must be aligned to the element size. If @a p is aligned to 16 bytes
    only the referenced 16 byte block is accessed. Otherwise, memory within the
    smallest 16-byte aligned 32-byte block may be accessed.

    @par 128-bit version:

    @code
    *(p) = a[0..255]
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, 2}
    @icost{AVX (integer vectors), 2}

    @a p must be aligned to the element size. If @a p is aligned to 32 bytes
    only the referenced 16 byte block is accessed. Otherwise, memory within the
    smallest 32-byte aligned 64-byte block may be accessed.
*/
inline void store_u(void* p, basic_int8x16 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u8(reinterpret_cast<uint8_t*>(p), a);
#endif
}

inline void store_u(void* p, basic_int8x32 a)
{
#if SIMDPP_USE_AVX2
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    store_u(q, a[0]);
    store_u(q+16, a[1]);
#endif
}

inline void store_u(void* p, basic_int16x8 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u16(reinterpret_cast<uint16_t*>(p), a);
#endif
}

inline void store_u(void* p, basic_int16x16 a)
{
#if SIMDPP_USE_AVX2
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    store_u(q, a[0]);
    store_u(q+16, a[1]);
#endif
}

inline void store_u(void* p, basic_int32x4 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u32(reinterpret_cast<uint32_t*>(p), a);
#endif
}

inline void store_u(void* p, basic_int32x8 a)
{
#if SIMDPP_USE_AVX2
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    store_u(q, a[0]);
    store_u(q+16, a[1]);
#endif
}

inline void store_u(void* p, basic_int64x2 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    vst1q_u64(reinterpret_cast<uint64_t*>(p), a);
#endif
}

inline void store_u(void* p, basic_int64x4 a)
{
#if SIMDPP_USE_AVX2
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), a);
#else
    char* q = reinterpret_cast<char*>(p);
    store_u(q, a[0]);
    store_u(q+16, a[1]);
#endif
}

inline void store_u(float* p, float32x4 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_ps(p, a);
#elif SIMDPP_USE_NEON
    vst1q_f32(p, a);
#endif
}

inline void store_u(float* p, float32x8 a)
{
#if SIMDPP_USE_AVX
    _mm256_storeu_ps(p, a);
#else
    store_u(p, a[0]);
    store_u(p+4, a[1]);
#endif
}

inline void store_u(double* p, float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_storeu_pd(p, a);
#elif SIMDPP_USE_NEON
    store_u(p, int64x2(a));
#endif
}

inline void store_u(double* p, float64x4 a)
{
#if SIMDPP_USE_AVX
    _mm256_storeu_pd(p, a);
#else
    store_u(p, a[0]);
    store_u(p+2, a[1]);
#endif
}
/// @}

/// @{
/** Stores a 128-bit or 256-bit integer, 32-bit or 64-bit floating point vector
    to memory without polluting the caches, if possible.

    @par 128-bit version:

    @code
    *(p) = a[0..127]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 128-bit version:

    @code
    *(p) = a[0..255]
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, 2}
    @icost{AVX (integer vectors), 2}
*/
inline void stream(void* p, int128 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_si128(reinterpret_cast<__m128i*>(p), a);
#elif SIMDPP_USE_NEON
    store(p, a);
#endif
}

inline void stream(void* p, int256 a)
{
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
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_ps(p, a);
#elif SIMDPP_USE_NEON
    store(p, a);
#endif
}

inline void stream(float* p, float32x8 a)
{
#if SIMDPP_USE_AVX
    _mm256_stream_ps(p, a);
#else
    stream(p, a[0]);
    stream(p+4, a[1]);
#endif
}

inline void stream(double* p, float64x2 a)
{
#if SIMDPP_USE_NULL
    null::store(p, a);
#elif SIMDPP_USE_SSE2
    _mm_stream_pd(p, a);
#elif SIMDPP_USE_NEON
    store(p, a);
#endif
}

inline void stream(double* p, float64x4 a)
{
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
#endif
}

inline void store_first(void* p, basic_int8x32 a, unsigned n)
{
    detail::v256_store_first<16>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(void* p, basic_int16x8 a, unsigned n)
{
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
#endif
}

inline void store_first(void* p, basic_int16x16 a, unsigned n)
{
    detail::v256_store_first<8>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(void* p, basic_int32x4 a, unsigned n)
{
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
#endif
}

inline void store_first(void* p, basic_int32x8 a, unsigned n)
{
    detail::v256_store_first<4>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(void* p, basic_int64x2 a, unsigned n)
{
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
#endif
}

inline void store_first(void* p, basic_int64x4 a, unsigned n)
{
    detail::v256_store_first<2>(reinterpret_cast<char*>(p), a, n);
}

inline void store_first(float* p, float32x4 a, unsigned n)
{
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_NEON
    store_first(p, int64x2(a), n);
#endif
}

inline void store_first(double* p, float64x4 a, unsigned n)
{
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
#endif
}

inline void store_last(void* p, basic_int8x32 a, unsigned n)
{
    detail::v256_store_last<16>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, basic_int16x8 a, unsigned n)
{
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
#endif
}

inline void store_last(void* p, basic_int16x16 a, unsigned n)
{
    detail::v256_store_last<8>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, basic_int32x4 a, unsigned n)
{
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    switch (n) {
    case 3: {
        basic_int32x4 b, c;
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
#endif
}

inline void store_last(void* p, basic_int32x8 a, unsigned n)
{
    detail::v256_store_last<4>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, basic_int64x2 a, unsigned n)
{
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
#endif
}

inline void store_last(void* p, basic_int64x4 a, unsigned n)
{
    detail::v256_store_last<2>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(float* p, float32x4 a, unsigned n)
{
#if SIMDPP_USE_SSE2
    switch (n) {
    case 3: {
        float32x4 b, c;
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<1,1>(p+1, a);
    }
#else
    store_last(p, int64x2(a), n);
#endif
}

inline void store_last(double* p, float64x4 a, unsigned n)
{
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
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    sse::detail::st_pack2(a, b);
    store(q, a);
    store(q + 32, b);
#else
    store_packed2(q, a[0], b[0]);
    store_packed2(q + 64, a[1], b[1]);
#endif
}

template<class V>
void v256_store_i_pack3(void* p, V a, V b, V c)
{
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    sse::detail::st_pack3(a, b, c);
    store(q, a);
    store(q + 32, b);
    store(q + 64, c);
#else
    store_packed3(q, a[0], b[0], c[0]);
    store_packed3(q + 96, a[1], b[1], c[1]);
#endif
}

template<class V>
void v256_store_i_pack4(void* p, V a, V b, V c, V d)
{
    char* q = reinterpret_cast<char*>(p);
#if SIMDPP_USE_AVX2
    sse::detail::st_pack4(a, b, c, d);
    store(q, a);
    store(q + 32, b);
    store(q + 64, c);
    store(q + 96, d);
#else
    store_packed4(q, a[0], b[0], c[0], d[0]);
    store_packed4(q + 128, a[1], b[1], c[1], d[1]);
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
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack2(a, b);
    store(q, a);
    store(q+16, b);
#elif SIMDPP_USE_NEON
    vst2q_u8(reinterpret_cast<uint8_t*>(p), {{a, b}});
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
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack2(a, b);
    store(q, a);
    store(q+16, b);
#elif SIMDPP_USE_NEON
    vst2q_u16(reinterpret_cast<uint16_t*>(p), {{a, b}});
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
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack2(a, b);
    store(q, a);
    store(q+16, b);
#elif SIMDPP_USE_NEON
    vst2q_u32(reinterpret_cast<uint32_t*>(p), {{a, b}});
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
#if SIMDPP_USE_NULL
    null::store_packed2(p, a, b);
#elif SIMDPP_USE_SSE2
    sse::detail::st_pack2(a, b);
    store(p, a);
    store(p+4, b);
#elif SIMDPP_USE_NEON
    vst2q_f32(p, {{a, b}});
#endif
}

inline void store_packed2(float* p, float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    sse::detail::st_pack2(a, b);
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
    transpose2(a, b);
    store(p, a);
    store(p+2, b);
}

inline void store_packed2(double* p, float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    sse::detail::st_pack2(a, b);
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
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    vst3q_u8(reinterpret_cast<uint8_t*>(p), {{a, b, c}});
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
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    vst3q_u16(reinterpret_cast<uint16_t*>(p), {{a, b, c}});
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
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    vst3q_u32(reinterpret_cast<uint32_t*>(p), {{a, b, c}});
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
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack3(a, b, c);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
#elif SIMDPP_USE_NEON
    uint64_t* q = reinterpret_cast<uint64_t*>(p);
    vst2_u64(q,   {{vget_low_u64(a), vget_low_u64(b)}} );
    vst2_u64(q+2, {{vget_low_u64(c), vget_high_u64(a)}} );
    vst2_u64(q+4, {{vget_high_u64(b), vget_high_u64(c)}} );
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
#if SIMDPP_USE_NULL
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    sse::detail::st_pack3(a, b, c);
    store(p, a);
    store(p+4, b);
    store(p+8, c);
#elif SIMDPP_USE_NEON
    vst3q_f32(p, {{a, b, c}});
#endif
}

inline void store_packed3(float* p,
                          float32x8 a, float32x8 b, float32x8 c)
{
#if SIMDPP_USE_AVX
    sse::detail::st_pack3(a, b, c);
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    sse::detail::st_pack3(a, b, c);
    store(p, a);
    store(p+2, b);
    store(p+4, c);
#elif SIMDPP_USE_NEON
    int64x2 a1, b1, c1;
    a1 = a; b1 = b; c1 = c;
    store_packed3(p, a1, b1, c1);
#endif
}

inline void store_packed3(double* p,
                          float64x4 a, float64x4 b, float64x4 c)
{
#if SIMDPP_USE_AVX
    sse::detail::st_pack3(a, b, c);
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
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    vst4q_u8(reinterpret_cast<uint8_t*>(p), {{a, b, c, d}});
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
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    vst4q_u16(reinterpret_cast<uint16_t*>(p), {{a, b, c, d}});
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
    @endcode
*/
inline void store_packed4(void* p,
                          basic_int32x4 a, basic_int32x4 b,
                          basic_int32x4 c, basic_int32x4 d)
{
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);

    sse::detail::st_pack4(a, b, c, d);
    store(q, a);
    store(q+16, b);
    store(q+32, c);
    store(q+48, d);
#elif SIMDPP_USE_NEON
    vst4q_u32(reinterpret_cast<uint32_t*>(p), {{a, b, c, d}});
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
    @endcode
*/
inline void store_packed4(void* p,
                          basic_int64x2 a, basic_int64x2 b,
                          basic_int64x2 c, basic_int64x2 d)
{
    char* q = reinterpret_cast<char*>(p);
    basic_int64x2 t0, t1, t2, t3;

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
    @endcode
*/
inline void store_packed4(float* p,
                          float32x4 a, float32x4 b, float32x4 c, float32x4 d)
{
#if SIMDPP_USE_NULL
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    sse::detail::st_pack4(a, b, c, d);
    store(p, a);
    store(p+4, b);
    store(p+8, c);
    store(p+12, d);
#elif SIMDPP_USE_NEON
    vst4q_f32(p, {{a, b, c, d}});
#endif
}

inline void store_packed4(float* p,
                          float32x8 a, float32x8 b, float32x8 c, float32x8 d)
{
#if SIMDPP_USE_AVX
    sse::detail::st_pack4(a, b, c, d);
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
    @endcode
*/
inline void store_packed4(double* p,
                          float64x2 a, float64x2 b, float64x2 c, float64x2 d)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    null::store_packed4(p, a, b, c, d);
#elif SIMDPP_USE_SSE2
    sse::detail::st_pack4(a, b, c, d);
    store(p, a);
    store(p+2, b);
    store(p+4, c);
    store(p+6, d);
#elif SIMDPP_USE_NEON
    int64x2 a1, b1, c1, d1;
    a1 = a; b1 = b; c1 = c; d1 = d;
    store_packed4(p, a1, b1, c1, d1);
#endif
}

inline void store_packed4(double* p,
                          float64x4 a, float64x4 b, float64x4 c, float64x4 d)
{
#if SIMDPP_USE_AVX
    sse::detail::st_pack4(a, b, c, d);
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

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
