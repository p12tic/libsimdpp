#   libsimdpp
#   Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#
#   * Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#   POSSIBILITY OF SUCH DAMAGE.

include_directories(${libsimdpp_SOURCE_DIR})

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

set(TEST1_SOURCES
    arch_registration.cc
    test_case.cc
    test_main.cc
)

set(TEST1_HEADERS
    arch_registration.h
    test_case.h
    test_helpers.h
    test_results.h
    tests.h
    traits.h
)

set(TEST1_ARCH_SOURCES
    tests/bitwise.cc
    tests/compare.cc
    tests/construct.cc
    tests/convert.cc
    tests/main.cc
    tests/math_fp.cc
    tests/math_int.cc
    tests/math_shift.cc
    tests/memory_load.cc
    tests/memory_store.cc
    tests/shuffle.cc
    tests/shuffle_bytes.cc
    tests/shuffle_generic.cc
    tests/transpose.cc
)

set(TEST1_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST1_ARCH_SOURCES})
    simdpp_multiversion(TEST1_ARCH_GEN_SOURCES ${SRC} ${NATIVE_ARCHS})
endforeach()

add_executable(test1 EXCLUDE_FROM_ALL
    ${TEST1_SOURCES}
    ${TEST1_ARCH_GEN_SOURCES}
)

set_target_properties(test1 PROPERTIES COMPILE_FLAGS "-std=c++11")

add_test(test_simdpp test1)
add_dependencies(check test1)

