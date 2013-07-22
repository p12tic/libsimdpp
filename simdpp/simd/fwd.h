/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
SIMDPP_ARCH_NAMESPACE_BEGIN

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

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
