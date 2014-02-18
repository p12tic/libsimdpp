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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FWD_H
#define LIBSIMDPP_SIMDPP_TYPES_FWD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>

/*  This is an internal helper file that contains forward declarations of the
    vector templates and typedefs of specific vector types urcoah
*/
namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// types
template<unsigned N> class float32;
template<unsigned N> class mask_float32;
using float32x4 = float32<4>;
using float32x8 = float32<8>;
using mask_float32x4 = mask_float32<4>;
using mask_float32x8 = mask_float32<8>;

template<unsigned N> class float64;
template<unsigned N> class mask_float64;
using float64x2 = float64<2>;
using float64x4 = float64<4>;
using mask_float64x2 = mask_float64<2>;
using mask_float64x4 = mask_float64<4>;

template<unsigned B> class int_bits;
using int128 = int_bits<16>;
using int256 = int_bits<32>;

template<unsigned N> class gint8;
template<unsigned N> class int8;
template<unsigned N> class uint8;
template<unsigned N> class mask_int8;
using basic_int8x16 = gint8<16>;
using basic_int8x32 = gint8<32>;
using int8x16 = int8<16>;
using int8x32 = int8<32>;
using uint8x16 = uint8<16>;
using uint8x32 = uint8<32>;
using mask_int8x16 = mask_int8<16>;
using mask_int8x32 = mask_int8<32>;

template<unsigned N> class gint16;
template<unsigned N> class int16;
template<unsigned N> class uint16;
template<unsigned N> class mask_int16;
using basic_int16x8 = gint16<8>;
using basic_int16x16 = gint16<16>;
using int16x8 = int16<8>;
using int16x16 = int16<16>;
using uint16x8 = uint16<8>;
using uint16x16 = uint16<16>;
using mask_int16x8 = mask_int16<8>;
using mask_int16x16 = mask_int16<16>;

template<unsigned N> class gint32;
template<unsigned N> class int32;
template<unsigned N> class uint32;
template<unsigned N> class mask_int32;
using basic_int32x4 = gint32<4>;
using basic_int32x8 = gint32<8>;
using int32x4 = int32<4>;
using int32x8 = int32<8>;
using uint32x4 = uint32<4>;
using uint32x8 = uint32<8>;
using mask_int32x4 = mask_int32<4>;
using mask_int32x8 = mask_int32<8>;

template<unsigned N> class gint64;
template<unsigned N> class int64;
template<unsigned N> class uint64;
template<unsigned N> class mask_int64;
using basic_int64x2 = gint64<2>;
using basic_int64x4 = gint64<4>;
using int64x2 = int64<2>;
using int64x4 = int64<4>;
using uint64x2 = uint64<2>;
using uint64x4 = uint64<4>;
using mask_int64x2 = mask_int64<2>;
using mask_int64x4 = mask_int64<4>;

// math_shift.h
inline int16x8 shift_r(int16x8, unsigned);
inline uint16x8 shift_r(uint16x8, unsigned);
inline basic_int16x8 shift_l(basic_int16x8, unsigned);
inline int64x2 shift_r(int64x2, unsigned);
inline uint64x2 shift_r(uint64x2, unsigned);
inline basic_int64x2 shift_l(basic_int64x2, unsigned);
template<unsigned count> int16x8 shift_r(int16x8);
template<unsigned count> uint16x8 shift_r(uint16x8);
template<unsigned count> basic_int16x8 shift_l(basic_int16x8);
template<unsigned count> int32x4 shift_r(int32x4);

inline int16x16 shift_r(int16x16, unsigned);
inline uint16x16 shift_r(uint16x16, unsigned);
inline basic_int16x16 shift_l(basic_int16x16, unsigned);
inline int64x4 shift_r(int64x4, unsigned);
inline uint64x4 shift_r(uint64x4, unsigned);
inline basic_int64x4 shift_l(basic_int64x4, unsigned);
template<unsigned count> int16x16 shift_r(int16x16);
template<unsigned count> uint16x16 shift_r(uint16x16);
template<unsigned count> basic_int16x16 shift_l(basic_int16x16);
template<unsigned count> int32x8 shift_r(int32x8);

#endif // DOXYGEN_SHOULD_SKIP_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
