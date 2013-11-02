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

#ifndef LIBSIMDPP_NEON_MEMORY_STORE_H
#define LIBSIMDPP_NEON_MEMORY_STORE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace neon {

/// @{
/** Stores @a n elements of a 128-bit vector starting from the @a pos-th one.
    @a p must be aligned to 16 bytes.

    @a n must be a power of 2. @a pos must be a multiple of @a n. The behavior is
    undefined if @a pos+n exceeds the number of elements in the specified vector.
*/
template<unsigned pos, unsigned n>
void store_lane(void* p, basic_int8x16 a)
{
    static_assert(n == 1 || n == 2 || n == 4 || n == 8, "Size not supported");
    static_assert(pos%n == 0, "pos must be a multiple of n");
    static_assert(pos+n <= 16, "Index out of bounds");
    switch (n) {
    case 1:
        vst1q_lane_u8(reinterpret_cast<uint8_t*>(p), a, pos);
        return;
    case 2:
        vst1q_lane_u16(reinterpret_cast<uint16_t*>(p), vreinterpretq_u16_u8(a), pos/2);
        return;
    case 4:
        vst1q_lane_u32(reinterpret_cast<uint32_t*>(p), vreinterpretq_u32_u8(a), pos/4);
        return;
    case 8:
        vst1q_lane_u64(reinterpret_cast<uint64_t*>(p), vreinterpretq_u64_u8(a), pos/8);
        return;
    }
}

template<unsigned pos, unsigned n>
void store_lane(void* p, basic_int16x8 a)
{
    static_assert(n == 1 || n == 2 || n == 4, "Size not supported");
    static_assert(pos%n == 0, "pos must be a multiple of n");
    static_assert(pos+n <= 8, "Index out of bounds");
    switch (n) {
    case 1:
        vst1q_lane_u16(reinterpret_cast<uint16_t*>(p), a, pos);
        return;
    case 2:
        vst1q_lane_u32(reinterpret_cast<uint32_t*>(p), vreinterpretq_u32_u16(a), pos/2);
        return;
    case 4:
        vst1q_lane_u64(reinterpret_cast<uint64_t*>(p), vreinterpretq_u64_u16(a), pos/4);
        return;
    }
}

template<unsigned pos, unsigned n>
void store_lane(void* p, basic_int32x4 a)
{
    static_assert(n == 1 || n == 2, "Size not supported");
    static_assert(pos%n == 0, "pos must be a multiple of n");
    static_assert(pos+n <= 4, "Index out of bounds");
    switch (n) {
    case 1:
        vst1q_lane_u32(reinterpret_cast<uint32_t*>(p), a, pos);
        return;
    case 2:
        vst1q_lane_u64(reinterpret_cast<uint64_t*>(p), vreinterpretq_u64_u32(a), pos/2);
        return;
    }
}

template<unsigned pos, unsigned n>
void store_lane(void* p, basic_int64x2 a)
{
    static_assert(n == 1, "Size not supported");
    static_assert(pos%n == 0, "pos must be a multiple of n");
    static_assert(pos+n <= 2, "Index out of bounds");
    vst1q_lane_u64(reinterpret_cast<uint64_t*>(p), a, pos);
}

template<unsigned pos, unsigned n>
void store_lane(float* p, float32x4 a)
{
    store_lane<pos,n>(p, basic_int32x4(a));
}
/// @}

} // namespace neon
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
