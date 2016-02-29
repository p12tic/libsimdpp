/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FWD_H
#define LIBSIMDPP_SIMDPP_TYPES_FWD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>
#include <simdpp/types/tag.h>

/*  This is an internal helper file that contains forward declarations of the
    vector templates and typedefs of specific vector types urcoah
*/
namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

namespace detail {
//template<int> void construct_eval();
} // namespace detail

// types
template<unsigned N, class E = void> class float32;
template<unsigned N, class E = void> class mask_float32;

typedef float32<4> float32x4;
typedef float32<8> float32x8;
typedef mask_float32<4> mask_float32x4;
typedef mask_float32<8> mask_float32x8;

template<unsigned N, class E = void> class float64;
template<unsigned N, class E = void> class mask_float64;

typedef float64<2> float64x2;
typedef float64<4> float64x4;
typedef mask_float64<2> mask_float64x2;
typedef mask_float64<4> mask_float64x4;

template<unsigned N, class E = void> class int8;
template<unsigned N, class E = void> class uint8;
template<unsigned N, class E = void> class mask_int8;

typedef int8<16> int8x16;
typedef int8<32> int8x32;
typedef uint8<16> uint8x16;
typedef uint8<32> uint8x32;
typedef mask_int8<16> mask_int8x16;
typedef mask_int8<32> mask_int8x32;

template<unsigned N, class E = void> class int16;
template<unsigned N, class E = void> class uint16;
template<unsigned N, class E = void> class mask_int16;

typedef int16<8> int16x8;
typedef int16<16> int16x16;
typedef uint16<8> uint16x8;
typedef uint16<16> uint16x16;
typedef mask_int16<8> mask_int16x8;
typedef mask_int16<16> mask_int16x16;

template<unsigned N, class E = void> class int32;
template<unsigned N, class E = void> class uint32;
template<unsigned N, class E = void> class mask_int32;

typedef int32<4> int32x4;
typedef int32<8> int32x8;
typedef uint32<4> uint32x4;
typedef uint32<8> uint32x8;
typedef mask_int32<4> mask_int32x4;
typedef mask_int32<8> mask_int32x8;

template<unsigned N, class E = void> class int64;
template<unsigned N, class E = void> class uint64;
template<unsigned N, class E = void> class mask_int64;

typedef int64<2> int64x2;
typedef int64<4> int64x4;
typedef uint64<2> uint64x2;
typedef uint64<4> uint64x4;
typedef mask_int64<2> mask_int64x2;
typedef mask_int64<4> mask_int64x4;

#if SIMDPP_USE_AVX512F
#define SIMDPP_FAST_FLOAT32_SIZE 16
#define SIMDPP_FAST_FLOAT64_SIZE 8
#elif SIMDPP_USE_AVX
#define SIMDPP_FAST_FLOAT32_SIZE 8
#define SIMDPP_FAST_FLOAT64_SIZE 4
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NULL
#define SIMDPP_FAST_FLOAT32_SIZE 4
#define SIMDPP_FAST_FLOAT64_SIZE 2
#endif

#if SIMDPP_USE_AVX512F
#define SIMDPP_FAST_INT8_SIZE 32
#define SIMDPP_FAST_INT16_SIZE 16
#define SIMDPP_FAST_INT32_SIZE 16
#define SIMDPP_FAST_INT64_SIZE 8
#elif SIMDPP_USE_AVX2
#define SIMDPP_FAST_INT8_SIZE 32
#define SIMDPP_FAST_INT16_SIZE 16
#define SIMDPP_FAST_INT32_SIZE 8
#define SIMDPP_FAST_INT64_SIZE 4
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NULL
#define SIMDPP_FAST_INT8_SIZE 16
#define SIMDPP_FAST_INT16_SIZE 8
#define SIMDPP_FAST_INT32_SIZE 4
#define SIMDPP_FAST_INT64_SIZE 2
#endif

typedef           float32<SIMDPP_FAST_FLOAT32_SIZE> float32v;
typedef mask_float32<SIMDPP_FAST_FLOAT32_SIZE> mask_float32v;
typedef           float64<SIMDPP_FAST_FLOAT64_SIZE> float64v;
typedef mask_float64<SIMDPP_FAST_FLOAT64_SIZE> mask_float64v;

typedef           int8<SIMDPP_FAST_INT8_SIZE> int8v;
typedef         uint8<SIMDPP_FAST_INT8_SIZE> uint8v;
typedef mask_int8<SIMDPP_FAST_INT8_SIZE> mask_int8v;

typedef           int16<SIMDPP_FAST_INT16_SIZE> int16v;
typedef         uint16<SIMDPP_FAST_INT16_SIZE> uint16v;
typedef mask_int16<SIMDPP_FAST_INT16_SIZE> mask_int16v;

typedef           int32<SIMDPP_FAST_INT32_SIZE> int32v;
typedef         uint32<SIMDPP_FAST_INT32_SIZE> uint32v;
typedef mask_int32<SIMDPP_FAST_INT32_SIZE> mask_int32v;

typedef           int64<SIMDPP_FAST_INT64_SIZE> int64v;
typedef         uint64<SIMDPP_FAST_INT64_SIZE> uint64v;
typedef mask_int64<SIMDPP_FAST_INT64_SIZE> mask_int64v;

typedef mask_float32<SIMDPP_FAST_FLOAT32_SIZE*2> mask_float32v2;
typedef           float64<SIMDPP_FAST_FLOAT64_SIZE*2> float64v2;
typedef mask_float64<SIMDPP_FAST_FLOAT64_SIZE*2> mask_float64v2;

typedef           int8<SIMDPP_FAST_INT8_SIZE*2> int8v2;
typedef         uint8<SIMDPP_FAST_INT8_SIZE*2> uint8v2;
typedef mask_int8<SIMDPP_FAST_INT8_SIZE*2> mask_int8v2;

typedef           int16<SIMDPP_FAST_INT16_SIZE*2> int16v2;
typedef         uint16<SIMDPP_FAST_INT16_SIZE*2> uint16v2;
typedef mask_int16<SIMDPP_FAST_INT16_SIZE*2> mask_int16v2;

typedef           int32<SIMDPP_FAST_INT32_SIZE*2> int32v2;
typedef         uint32<SIMDPP_FAST_INT32_SIZE*2> uint32v2;
typedef mask_int32<SIMDPP_FAST_INT32_SIZE*2> mask_int32v2;

typedef           int64<SIMDPP_FAST_INT64_SIZE*2> int64v2;
typedef         uint64<SIMDPP_FAST_INT64_SIZE*2> uint64v2;
typedef mask_int64<SIMDPP_FAST_INT64_SIZE*2> mask_int64v2;


typedef           float32<SIMDPP_FAST_FLOAT32_SIZE*4> float32v4;
typedef mask_float32<SIMDPP_FAST_FLOAT32_SIZE*4> mask_float32v4;
typedef           float64<SIMDPP_FAST_FLOAT64_SIZE*4> float64v4;
typedef mask_float64<SIMDPP_FAST_FLOAT64_SIZE*4> mask_float64v4;

typedef           int8<SIMDPP_FAST_INT8_SIZE*4> int8v4;
typedef         uint8<SIMDPP_FAST_INT8_SIZE*4> uint8v4;
typedef mask_int8<SIMDPP_FAST_INT8_SIZE*4> mask_int8v4;

typedef           int16<SIMDPP_FAST_INT16_SIZE*4> int16v4;
typedef         uint16<SIMDPP_FAST_INT16_SIZE*4> uint16v4;
typedef mask_int16<SIMDPP_FAST_INT16_SIZE*4> mask_int16v4;

typedef           int32<SIMDPP_FAST_INT32_SIZE*4> int32v4;
typedef         uint32<SIMDPP_FAST_INT32_SIZE*4> uint32v4;
typedef mask_int32<SIMDPP_FAST_INT32_SIZE*4> mask_int32v4;

typedef           int64<SIMDPP_FAST_INT64_SIZE*4> int64v4;
typedef         uint64<SIMDPP_FAST_INT64_SIZE*4> uint64v4;
typedef mask_int64<SIMDPP_FAST_INT64_SIZE*4> mask_int64v4;

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
