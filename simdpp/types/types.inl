/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INL
#define LIBSIMDPP_SIMDPP_TYPES_INL

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned N>
SIMDPP_INL int8<N>::int8(const uint8<N>& d) { *this = d.eval(); }
template<unsigned N>
SIMDPP_INL int16<N>::int16(const uint16<N>& d) { *this = d.eval(); }
template<unsigned N>
SIMDPP_INL int32<N>::int32(const uint32<N>& d) { *this = d.eval(); }
template<unsigned N>
SIMDPP_INL int64<N>::int64(const uint64<N>& d) { *this = d.eval(); }


SIMDPP_INL int8<16>::int8(const uint8<16>& d) { *this = d; }
SIMDPP_INL int16<8>::int16(const uint16<8>& d) { *this = d.eval(); }
SIMDPP_INL int32<4>::int32(const uint32<4>& d) { *this = d.eval(); }
SIMDPP_INL int64<2>::int64(const uint64<2>& d) { *this = d.eval(); }
SIMDPP_INL mask_int32<4>::mask_int32(const mask_float32<4>& d)
{
    *this = bit_cast<mask_int32<4>>(d.eval());
}
SIMDPP_INL mask_int32<4>& mask_int32<4>::operator=(const mask_float32<4>& d)
{
    *this = bit_cast<mask_int32<4>>(d.eval()); return *this;
}
SIMDPP_INL mask_int64<2>::mask_int64(const mask_float64<2>& d)
{
    *this = bit_cast<mask_int64<2>>(d.eval());
}
SIMDPP_INL mask_int64<2>& mask_int64<2>::operator=(const mask_float64<2>& d)
{
    *this = bit_cast<mask_int64<2>>(d.eval()); return *this;
}
#if SIMDPP_USE_AVX2
SIMDPP_INL int8<32>::int8(const uint8<32>& d) { *this = d; }
SIMDPP_INL int16<16>::int16(const uint16<16>& d) { *this = d.eval(); }
SIMDPP_INL int32<8>::int32(const uint32<8>& d) { *this = d.eval(); }
SIMDPP_INL int64<4>::int64(const uint64<4>& d) { *this = d.eval(); }
SIMDPP_INL mask_int32<8>::mask_int32(const mask_float32<8>& d)
{
    *this = bit_cast<mask_int32<8>>(d.eval());
}
SIMDPP_INL mask_int32<8>& mask_int32<8>::operator=(const mask_float32<8>& d)
{
    *this = bit_cast<mask_int32<8>>(d.eval()); return *this;
}
SIMDPP_INL mask_int64<4>::mask_int64(const mask_float64<4>& d)
{
    *this = bit_cast<mask_int64<4>>(d.eval());
}
SIMDPP_INL mask_int64<4>& mask_int64<4>::operator=(const mask_float64<4>& d)
{
    *this = bit_cast<mask_int64<4>>(d.eval()); return *this;
}
#endif
#if SIMDPP_USE_AVX512BW
SIMDPP_INL int8<64>::int8(const uint8<64>& d) { *this = d; }
SIMDPP_INL int16<32>::int16(const uint16<32>& d) { *this = d.eval(); }
#endif
#if SIMDPP_USE_AVX512F
SIMDPP_INL int32<16>::int32(const uint32<16>& d) { *this = d.eval(); }
SIMDPP_INL int64<8>::int64(const uint64<8>& d) { *this = d.eval(); }
SIMDPP_INL mask_int32<16>::mask_int32(const mask_float32<16>& d)
{
    *this = bit_cast<mask_int32<16>>(d.eval());
}
SIMDPP_INL mask_int32<16>& mask_int32<16>::operator=(const mask_float32<16>& d)
{
    *this = bit_cast<mask_int32<16>>(d.eval()); return *this;
}
SIMDPP_INL mask_int64<8>::mask_int64(const mask_float64<8>& d)
{
    *this = bit_cast<mask_int64<8>>(d.eval());
}
SIMDPP_INL mask_int64<8>& mask_int64<8>::operator=(const mask_float64<8>& d)
{
    *this = bit_cast<mask_int64<8>>(d.eval()); return *this;
}
#endif

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32<8>::mask_float32(const mask_int32<8>& d)
{
    *this = bit_cast<mask_float32<8>>(d.eval());
}
SIMDPP_INL mask_float32<8>& mask_float32<8>::operator=(const mask_int32<8>& d)
{
    *this = bit_cast<mask_float32<8>>(d.eval()); return *this;
}
SIMDPP_INL mask_float64<4>::mask_float64(const mask_int64<4>& d)
{
    *this = bit_cast<mask_float64<4>>(d.eval());
}
SIMDPP_INL mask_float64<4>& mask_float64<4>::operator=(const mask_int64<4>& d)
{
    *this = bit_cast<mask_float64<4>>(d.eval()); return *this;
}
#endif

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
