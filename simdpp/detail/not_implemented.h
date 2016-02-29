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
#include <type_traits>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

namespace detail {

/** A data type that can be implicitly converted to all types used in the
    library. Used to silence 'no return value' warnings
*/
class dummy_value {
public:
    operator int8x16() { return int8x16(); }
    operator int8x32() { return int8x32(); }
    operator uint8x16() { return uint8x16(); }
    operator uint8x32() { return uint8x32(); }
    operator mask_int8x16() { return mask_int8x16(); }
    operator mask_int8x32() { return mask_int8x32(); }
    operator int16x8() { return int16x8(); }
    operator int16x16() { return int16x16(); }
    operator uint16x8() { return uint16x8(); }
    operator uint16x16() { return uint16x16(); }
    operator mask_int16x8() { return mask_int16x8(); }
    operator mask_int16x16() { return mask_int16x16(); }
    operator int32x4() { return int32x4(); }
    operator int32x8() { return int32x8(); }
    operator uint32x4() { return uint32x4(); }
    operator uint32x8() { return uint32x8(); }
    operator mask_int32x4() { return mask_int32x4(); }
    operator mask_int32x8() { return mask_int32x8(); }
    operator int64x2() { return int64x2(); }
    operator int64x4() { return int64x4(); }
    operator uint64x2() { return uint64x2(); }
    operator uint64x4() { return uint64x4(); }
    operator mask_int64x2() { return mask_int64x2(); }
    operator mask_int64x4() { return mask_int64x4(); }
    operator float32x4() { return float32x4(); }
    operator float32x8() { return float32x8(); }
    operator mask_float32x4() { return mask_float32x4(); }
    operator mask_float32x8() { return mask_float32x8(); }
    operator float64x2() { return float64x2(); }
    operator float64x4() { return float64x4(); }
    operator mask_float64x2() { return mask_float64x2(); }
    operator mask_float64x4() { return mask_float64x4(); }
    operator int32_t() { return 0; }
    operator uint32_t() { return 0; }
    operator int64_t() { return 0; }
    operator uint64_t() { return 0; }
    operator float() { return 0; }
    operator double() { return 0; }
};

} // namespace detail

/** Causes compile-time error whenever unimplemented functionality is used.
    The function may only be used in templates which are not instantiated by
    default.
*/
template<class T>
void libsimdpp_instruction_not_available_template()
{
    static_assert(!std::is_same<T, T>::value, "The instruction is not available");
}

/** Causes linker error whenever unimplemented functionality is used. Compared
    to libsimdpp_instruction_not_available, this function is not limited to
    template contexts, but the errors are much harder to track down.
*/
void libsimdpp_instruction_not_available0();
void libsimdpp_instruction_not_available1();
void libsimdpp_instruction_not_available2();
void libsimdpp_instruction_not_available3();
void libsimdpp_instruction_not_available4();

#define SIMDPP_NOT_IMPLEMENTED_TEMPLATE0(T)  (                          \
    libsimdpp_instruction_not_available_template<T>(),                  \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED_TEMPLATE1(T,A)  (                        \
    (void) A,                                                           \
    libsimdpp_instruction_not_available_template<T>(),                  \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED_TEMPLATE2(T,A,B)  (                      \
    (void) A, (void) B,                                                 \
    libsimdpp_instruction_not_available_template<T>(),                  \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED_TEMPLATE3(T,A,B,C)  (                    \
    (void) A, (void) B, (void) C,                                       \
    libsimdpp_instruction_not_available_template<T>(),                  \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED_TEMPLATE4(T,A,B,C,D)  (                  \
    (void) A, (void) B, (void) C, (void) D,                             \
    libsimdpp_instruction_not_available_template<T>(),                  \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED0()  (                                    \
    libsimdpp_instruction_not_available0(),                             \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED1(A)  (                                   \
    (void) A,                                                           \
    libsimdpp_instruction_not_available1(),                             \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED2(A,B)  (                                 \
    (void) A, (void) B,                                                 \
    libsimdpp_instruction_not_available2(),                             \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED3(A,B,C)  (                               \
    (void) A, (void) B, (void) C,                                       \
    libsimdpp_instruction_not_available3(),                             \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

#define SIMDPP_NOT_IMPLEMENTED4(A,B,C,D)  (                             \
    (void) A, (void) B, (void) C, (void) D,                             \
    libsimdpp_instruction_not_available4(),                             \
    ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::dummy_value()              \
    )

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
