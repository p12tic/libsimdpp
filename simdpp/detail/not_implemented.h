/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_NOT_IMPLEMENTED_H
#define LIBSIMDPP_SIMDPP_DETAIL_NOT_IMPLEMENTED_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

namespace detail {

/** A data type that can be implicitly converted to all types used in the
    library. Used to silence 'no return value' warnings
*/
class not_implemented_proxy {
public:
    operator gint8x16() { return uint8x16::zero(); }
    operator gint8x32() { return uint8x32::zero(); }
    operator int8x16() { return int8x16::zero(); }
    operator int8x32() { return int8x32::zero(); }
    operator uint8x16() { return uint8x16::zero(); }
    operator uint8x32() { return uint8x32::zero(); }
    operator gint16x8() { return uint16x8::zero(); }
    operator gint16x16() { return uint16x16::zero(); }
    operator int16x8() { return int16x8::zero(); }
    operator int16x16() { return int16x16::zero(); }
    operator uint16x8() { return uint16x8::zero(); }
    operator uint16x16() { return uint16x16::zero(); }
    operator gint32x4() { return uint32x4::zero(); }
    operator gint32x8() { return uint32x8::zero(); }
    operator int32x4() { return int32x4::zero(); }
    operator int32x8() { return int32x8::zero(); }
    operator uint32x4() { return uint32x4::zero(); }
    operator uint32x8() { return uint32x8::zero(); }
    operator gint64x2() { return uint64x2::zero(); }
    operator gint64x4() { return uint64x4::zero(); }
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
