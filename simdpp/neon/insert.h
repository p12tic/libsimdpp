/*  libsimdpp
    Copyright (C) 2011  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_NEON_INSERT_H
#define LIBSIMDPP_SIMD_NEON_INSERT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/cast.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/**
    Inserts an element into int8x16 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    ...
    r15 = (id == 15) ? x : a15
    @endcode
*/
template<unsigned id>
basic_int8x16 insert(basic_int8x16 a, uint8_t x)
{
    return vsetq_lane_u8(x, a, id);
}

/**
    Inserts an element into int16x8 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    ...
    r7 = (id == 7) ? x : a7
    @endcode
*/
template<unsigned id>
basic_int16x8 insert(basic_int16x8 a, uint16_t x)
{
    return vsetq_lane_u16(x, a, id);
}

/**
    Inserts an element into int32x4 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    r2 = (id == 2) ? x : a2
    r3 = (id == 3) ? x : a3
    @endcode
*/
template<unsigned id>
int128 insert(basic_int32x4 a, uint32_t x)
{
    return vsetq_lane_u32(x, a, id);
}

/**
    Inserts an element into int64x2 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    @endcode
*/
template<unsigned id>
int128 insert(basic_int64x2 a, uint64_t x)
{
    return vsetq_lane_u64(x, a, id);
}

/**
    Inserts an element into float32x4 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    r2 = (id == 2) ? x : a2
    r3 = (id == 3) ? x : a3
    @endcode
*/
template<unsigned id>
float32x4 insert(float32x4 a, float x)
{
    return vsetq_lane_f32(x, a, id);
}

/**
    Inserts an element into float64x2 vector at the position identified by @a id.

    @code
    r0 = (id == 0) ? x : a0
    r1 = (id == 1) ? x : a1
    @endcode
*/
template<unsigned id>
float64x2 insert(float64x2 a, double x)
{
    return float64x2(insert<id>(int64x2(a), bit_cast<int64_t>(x)));
}

/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
