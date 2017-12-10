#   Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>
#
#   Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 2.8.0)
project(libsimdpp_compile_fail_tests)

SET(libsimdpp_SOURCE_DIR "source_dir_not_specified" CACHE STRING "Root directory of libsimdpp")

include(CheckCXXSourceCompiles)

function(test_compile_fail DESC FLAGS CODE)
    set(CMAKE_REQUIRED_FLAGS "-std=c++11 ${FLAGS}")
    set(CMAKE_REQUIRED_DEFINITIONS "-DSIMDPP_ARCH_X86_SSE2 -DSIMDPP_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES=1")
    set(CMAKE_REQUIRED_INCLUDES "${libsimdpp_SOURCE_DIR}")
    set(CHECK_VAR "VERIFY_FAILS_TO_COMPILE_${DESC}")
    check_cxx_source_compiles("${CODE}" ${CHECK_VAR})
    if(${CHECK_VAR})
        message(FATAL_ERROR "Test ${CHECK_VAR} should have failed to compile, but it did not")
    endif()
endfunction()

set(COMPILE_FLAGS "")

test_compile_fail(when_using_unsupported_implicit_conversion_with_functions_float32x4_int32x4
                  "${COMPILE_FLAGS}" "
#include <simdpp/simd.h>

using namespace simdpp;

float32x4 test_fails(float32<4> a, int32<4> b)
{
    return add(a, b);
}

int main()
{
    float32<4> a;
    int32<4> b;
    a = test_fails(a, b);
}
")

test_compile_fail(when_using_unsupported_implicit_conversion_with_operators_float32x4_int32x4
                  "${COMPILE_FLAGS}" "
#include <simdpp/simd.h>

using namespace simdpp;

float32x4 test_fails(float32<4> a, int32<4> b)
{
    return a + b;
}

int main()
{
    float32<4> a;
    int32<4> b;
    a = test_fails(a, b);
}
")

test_compile_fail(when_using_unsupported_implicit_conversion_with_functions_int8x16_int32x4
                  "${COMPILE_FLAGS}" "
#include <simdpp/simd.h>

using namespace simdpp;

int8<16> test_fails(int8<16> a, int32<4> b)
{
    return add(a, b);
}

int main()
{
    int8<16> a;
    int32<4> b;
    a = test_fails(a, b);
}
")

test_compile_fail(when_using_unsupported_implicit_conversion_with_operators_int8x16_int32x4
                  "${COMPILE_FLAGS}" "
#include <simdpp/simd.h>

using namespace simdpp;

int8<16> test_fails(int8<16> a, int32<4> b)
{
    return a + b;
}

int main()
{
    int8<16> a;
    int32<4> b;
    a = test_fails(a, b);
}
")
