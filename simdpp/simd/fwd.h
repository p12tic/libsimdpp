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

#ifndef LIBSIMDPP_SIMD_FWD_H
#define LIBSIMDPP_SIMD_FWD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

/*
    This is an internal helper file that contains all forward declarations that
    are needed for proper compilation of other files.
*/
namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

class float32x4;
class float64x2;
class float32x8;
class float64x4;
class int128;
class int256;
class int8x16;
class int16x8;
class int32x4;
class int64x2;
class int8x32;
class int16x16;
class int32x8;
class int64x4;
class uint8x16;
class uint16x8;
class uint32x4;
class uint64x2;
class uint8x32;
class uint16x16;
class uint32x8;
class uint64x4;
class basic_int8x16;
class basic_int16x8;
class basic_int32x4;
class basic_int64x2;
class basic_int8x32;
class basic_int16x16;
class basic_int32x8;
class basic_int64x4;

template<unsigned, unsigned> basic_int64x2 permute(basic_int64x2);
template<unsigned, unsigned> basic_int64x2 shuffle1(basic_int64x2, basic_int64x2);
template<unsigned, unsigned> float64x2 permute(float64x2);
template<unsigned, unsigned> float64x2 shuffle1(float64x2, float64x2);

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
