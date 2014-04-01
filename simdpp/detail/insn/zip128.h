/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP128_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/zip_hi.h>
#include <simdpp/detail/insn/zip_lo.h>
#include <simdpp/detail/insn/unzip_hi.h>
#include <simdpp/detail/insn/unzip_lo.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

template<unsigned N> uint8<N> unzip128_lo(uint8<N> a, uint8<N> b) { return unzip16_lo(a, b); }
template<unsigned N> uint16<N> unzip128_lo(uint16<N> a, uint16<N> b) { return unzip8_lo(a, b); }
template<unsigned N> uint32<N> unzip128_lo(uint32<N> a, uint32<N> b) { return unzip4_lo(a, b); }
template<unsigned N> uint64<N> unzip128_lo(uint64<N> a, uint64<N> b) { return unzip2_lo(a, b); }
template<unsigned N> float32<N> unzip128_lo(float32<N> a, float32<N> b) { return unzip4_lo(a, b); }
template<unsigned N> float64<N> unzip128_lo(float64<N> a, float64<N> b) { return unzip2_lo(a, b); }

template<unsigned N> uint8<N> unzip128_hi(uint8<N> a, uint8<N> b) { return unzip16_hi(a, b); }
template<unsigned N> uint16<N> unzip128_hi(uint16<N> a, uint16<N> b) { return unzip8_hi(a, b); }
template<unsigned N> uint32<N> unzip128_hi(uint32<N> a, uint32<N> b) { return unzip4_hi(a, b); }
template<unsigned N> uint64<N> unzip128_hi(uint64<N> a, uint64<N> b) { return unzip2_hi(a, b); }
template<unsigned N> float32<N> unzip128_hi(float32<N> a, float32<N> b) { return unzip4_hi(a, b); }
template<unsigned N> float64<N> unzip128_hi(float64<N> a, float64<N> b) { return unzip2_hi(a, b); }

template<unsigned N> uint8<N> zip128_lo(uint8<N> a, uint8<N> b) { return zip16_lo(a, b); }
template<unsigned N> uint16<N> zip128_lo(uint16<N> a, uint16<N> b) { return zip8_lo(a, b); }
template<unsigned N> uint32<N> zip128_lo(uint32<N> a, uint32<N> b) { return zip4_lo(a, b); }
template<unsigned N> uint64<N> zip128_lo(uint64<N> a, uint64<N> b) { return zip2_lo(a, b); }
template<unsigned N> float32<N> zip128_lo(float32<N> a, float32<N> b) { return zip4_lo(a, b); }
template<unsigned N> float64<N> zip128_lo(float64<N> a, float64<N> b) { return zip2_lo(a, b); }

template<unsigned N> uint8<N> zip128_hi(uint8<N> a, uint8<N> b) { return zip16_hi(a, b); }
template<unsigned N> uint16<N> zip128_hi(uint16<N> a, uint16<N> b) { return zip8_hi(a, b); }
template<unsigned N> uint32<N> zip128_hi(uint32<N> a, uint32<N> b) { return zip4_hi(a, b); }
template<unsigned N> uint64<N> zip128_hi(uint64<N> a, uint64<N> b) { return zip2_hi(a, b); }
template<unsigned N> float32<N> zip128_hi(float32<N> a, float32<N> b) { return zip4_hi(a, b); }
template<unsigned N> float64<N> zip128_hi(float64<N> a, float64<N> b) { return zip2_hi(a, b); }


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


