/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_NOT_IMPLEMENTED_H
#define LIBSIMDPP_SIMDPP_DETAIL_NOT_IMPLEMENTED_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

namespace detail {

/** A data type that can be implicitly converted to all types used in the
    library. Used to silence 'no return value' warnings
*/
class not_implemented_proxy {
public:
    operator int8x16() { return int8x16::zero(); }
    operator int8x32() { return int8x32::zero(); }
    operator uint8x16() { return uint8x16::zero(); }
    operator uint8x32() { return uint8x32::zero(); }
    operator int16x8() { return int16x8::zero(); }
    operator int16x16() { return int16x16::zero(); }
    operator uint16x8() { return uint16x8::zero(); }
    operator uint16x16() { return uint16x16::zero(); }
    operator int32x4() { return int32x4::zero(); }
    operator int32x8() { return int32x8::zero(); }
    operator uint32x4() { return uint32x4::zero(); }
    operator uint32x8() { return uint32x8::zero(); }
    operator int64x2() { return int64x2::zero(); }
    operator int64x4() { return int64x4::zero(); }
    operator uint64x2() { return uint64x2::zero(); }
    operator uint64x4() { return uint64x4::zero(); }
    operator float32x4() { return float32x4::zero(); }
    operator float32x8() { return float32x8::zero(); }
    operator float64x2() { return float64x2::zero(); }
    operator float64x4() { return float64x4::zero(); }
};

} // namespace detail

#ifndef SIMDPP_DOXYGEN
/** Causes linker error whenever unimplemented functionality is used.
*/
void libsimdpp_instruction_not_available();
#endif

#define SIMDPP_NOT_IMPLEMENTED0()  (                                    \
    libsimdpp_instruction_not_available(),                              \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::not_implemented_proxy()    \
    )
#define SIMDPP_NOT_IMPLEMENTED1(A)  (                                   \
    (void) A,                                                           \
    libsimdpp_instruction_not_available(),                              \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::not_implemented_proxy()    \
    )
#define SIMDPP_NOT_IMPLEMENTED2(A,B)  (                                 \
    (void) A, (void) B,                                                 \
    libsimdpp_instruction_not_available(),                              \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::not_implemented_proxy()    \
    )

#define SIMDPP_NOT_IMPLEMENTED3(A,B,C)  (                               \
    (void) A, (void) B, (void) C,                                       \
    libsimdpp_instruction_not_available(),                              \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::not_implemented_proxy()    \
    )

#define SIMDPP_NOT_IMPLEMENTED4(A,B,C,D)  (                             \
    (void) A, (void) B, (void) C, (void) D,                             \
    libsimdpp_instruction_not_available(),                              \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::not_implemented_proxy()    \
    )

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
