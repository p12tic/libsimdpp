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
    main_test1.cc
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
    simdpp_multiarch(TEST1_ARCH_GEN_SOURCES ${SRC} ${NATIVE_ARCHS})
endforeach()

add_executable(test1 EXCLUDE_FROM_ALL
    ${TEST1_SOURCES}
    ${TEST1_ARCH_GEN_SOURCES}
)

set_target_properties(test1 PROPERTIES COMPILE_FLAGS "-std=c++11")

add_test(s_test1 test1)
add_dependencies(check test1)

# ------------------------------------------------------------------------------
# Dispatcher test

set(TEST_DISPATCHER_SOURCES
    main_dispatcher.cc
)

set(TEST_DISPATCHER_ARCH_SOURCES
    tests/dispatcher.cc
)

set(TEST_DISPATCHER_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST_DISPATCHER_ARCH_SOURCES})
    simdpp_multiarch(TEST_DISPATCHER_ARCH_GEN_SOURCES ${SRC} ${NATIVE_ARCHS})
endforeach()

add_executable(test_dispatcher EXCLUDE_FROM_ALL
    ${TEST_DISPATCHER_SOURCES}
    ${TEST_DISPATCHER_ARCH_GEN_SOURCES}
)
target_link_libraries(test_dispatcher pthread)

set_target_properties(test_dispatcher PROPERTIES COMPILE_FLAGS "-std=c++11")

add_test(s_test_dispatcher1 test_dispatcher "NONE_NULL")
if(HAS_SSE2)
    add_test(s_test_dispatcher2 test_dispatcher "X86_SSE2")
endif()
if(HAS_SSE3)
    add_test(s_test_dispatcher3 test_dispatcher "X86_SSE3")
endif()
if(HAS_SSSE3)
    add_test(s_test_dispatcher4 test_dispatcher "X86_SSSE3")
endif()
if(HAS_SSE4_1)
    add_test(s_test_dispatcher5 test_dispatcher "X86_SSE4_1")
endif()
if(HAS_AVX)
    add_test(s_test_dispatcher6 test_dispatcher "X86_AVX")
endif()
if(HAS_AVX2)
    add_test(s_test_dispatcher7 test_dispatcher "X86_AVX2")
endif()
if(HAS_NEON)
    add_test(s_test_dispatcher8 test_dispatcher "ARM_NEON")
    add_test(s_test_dispatcher9 test_dispatcher "ARM_NEON_FLT_SP")
endif()

add_dependencies(check test_dispatcher)

