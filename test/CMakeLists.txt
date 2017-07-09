#   Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>
#
#   Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include_directories(${libsimdpp_SOURCE_DIR})

# LIST_CONTAINS(<var> ENTRY [LIST...])
#
# Helper macro that checks whether a list contains a specific entry. It sets
# ${VAR} to TRUE if VALUE is within LIST.
#
macro(list_contains VAR VALUE)
    set(${VAR})
    foreach(IV ${ARGN})
        if(${VALUE} STREQUAL ${IV})
            SET(${VAR} TRUE)
        endif()
    endforeach()
endmacro()

# ---------------
# check available architectures

list_contains(HAS_SSE2 X86_SSE2 ${NATIVE_ARCHS})
list_contains(HAS_SSE3 X86_SSE3 ${NATIVE_ARCHS})
list_contains(HAS_SSSE3 X86_SSSE3 ${NATIVE_ARCHS})
list_contains(HAS_SSE4_1 X86_SSE4_1 ${NATIVE_ARCHS})
list_contains(HAS_AVX X86_AVX ${NATIVE_ARCHS})
list_contains(HAS_AVX2 X86_AVX2 ${NATIVE_ARCHS})
list_contains(HAS_AVX512F X86_AVX512F ${NATIVE_ARCHS})
list_contains(HAS_NEON X86_NEON ${NATIVE_ARCHS})

# ---------------

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

set(TEST1_SOURCES
    utils/test_results_set.cc
    main_test1.cc
)

set(TEST1_HEADERS
    utils/test_helpers.h
    utils/test_results.h
    utils/test_results_set.h
    insn/tests.h
    common/masks.h
    common/vectors.h
    common/aligned_allocator.h
)

set(TEST1_ARCH_SOURCES
    insn/bitwise.cc
    insn/blend.cc
    insn/compare.cc
    insn/construct.cc
    insn/convert.cc
    insn/math_fp.cc
    insn/math_int.cc
    insn/math_shift.cc
    insn/memory_load.cc
    insn/memory_store.cc
    insn/shuffle.cc
    insn/shuffle_bytes.cc
    insn/permute_generic.cc
    insn/shuffle_generic.cc
    insn/test_utils.cc
    insn/tests.cc
    insn/transpose.cc
)

set(TEST1_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST1_ARCH_SOURCES})
    simdpp_multiarch(TEST1_ARCH_GEN_SOURCES ${SRC} ${COMPILABLE_ARCHS})
endforeach()

# print compiler detection information
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "MSVC: ${MSVC}")
message(STATUS "Detected compiler:")
message(STATUS "SIMDPP_CLANG: ${SIMDPP_CLANG}")
message(STATUS "SIMDPP_GCC: ${SIMDPP_GCC}")
message(STATUS "SIMDPP_MSVC: ${SIMDPP_MSVC}")
message(STATUS "SIMDPP_INTEL: ${SIMDPP_INTEL}")
message(STATUS "SIMDPP_MSVC_INTEL: ${SIMDPP_MSVC_INTEL}")

# don't use x87 in any of the tests because it performs calculations with
# different precision
if(HAS_SSE2)
    set(DEFAULT_FLAGS "")
    if(SIMDPP_CLANG)
        set(DEFAULT_FLAGS " -msse2")
    elseif(SIMDPP_GCC)
        set(DEFAULT_FLAGS " -mfpmath=sse -msse2")
    elseif(SIMDPP_INTEL)
        set(DEFAULT_FLAGS " -msse2")
    elseif(SIMDPP_MSVC OR SIMDPP_MSVC_INTEL)
        set(DEFAULT_FLAGS " /arch:SSE2")
    endif()

    foreach(GENSRC ${TEST1_ARCH_GEN_SOURCES})
        set_property(SOURCE "${GENSRC}" APPEND_STRING PROPERTY COMPILE_FLAGS
                     "${DEFAULT_FLAGS}")
    endforeach()
endif()

add_executable(test1 EXCLUDE_FROM_ALL
    ${TEST1_SOURCES}
    ${TEST1_ARCH_GEN_SOURCES}
)

if(SIMDPP_MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # enable _vectorcall on i386 builds (only works on MSVC 2013)
        set_target_properties(test1 PROPERTIES COMPILE_FLAGS "/Gv")
    endif()
elseif(SIMDPP_MSVC_INTEL)
    set_target_properties(test1 PROPERTIES COMPILE_FLAGS "/Qstd=c++11")
else()
    set_target_properties(test1 PROPERTIES COMPILE_FLAGS "-std=c++11 -O1 -g1 -Wall -Wextra")
endif()

add_test(s_test1 test1)
add_dependencies(check test1)

# ------------------------------------------------------------------------------
# Dispatcher test

set(TEST_DISPATCHER_SOURCES
    main_dispatcher.cc
)

set(TEST_DISPATCHER_ARCH_SOURCES
    insn/dispatcher.cc
)

set(TEST_DISPATCHER_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST_DISPATCHER_ARCH_SOURCES})
    simdpp_multiarch(TEST_DISPATCHER_ARCH_GEN_SOURCES ${SRC} ${NATIVE_ARCHS})
endforeach()

add_executable(test_dispatcher EXCLUDE_FROM_ALL
    ${TEST_DISPATCHER_SOURCES}
    ${TEST_DISPATCHER_ARCH_GEN_SOURCES}
)

if(SIMDPP_MSVC)
elseif(SIMDPP_MSVC_INTEL)
    set_target_properties(test_dispatcher PROPERTIES COMPILE_FLAGS "/Qstd=c++11")
else()
    set_target_properties(test_dispatcher PROPERTIES COMPILE_FLAGS "-std=c++11 -g2 -Wall")
endif()

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
if(HAS_AVX512F)
    add_test(s_test_dispatcher8 test_dispatcher "X86_AVX512F")
endif()
if(HAS_NEON)
    add_test(s_test_dispatcher9 test_dispatcher "ARM_NEON")
    add_test(s_test_dispatcher10 test_dispatcher "ARM_NEON_FLT_SP")
endif()

add_dependencies(check test_dispatcher)

# ------------------------------------------------------------------------------
# Expression test

set(TEST_EXPR_SOURCES
    main_expr.cc
    expr/tests.cc
    expr/bitwise.cc
    expr/math_float.cc
    expr/math_int.cc
    utils/test_results_set.cc
)

add_executable(test_expr EXCLUDE_FROM_ALL
    ${TEST_EXPR_SOURCES}
)

if(SIMDPP_MSVC)
elseif(SIMDPP_MSVC_INTEL)
    set_target_properties(test_expr PROPERTIES COMPILE_FLAGS "/Qstd=c++11")
else()
    set_target_properties(test_expr PROPERTIES COMPILE_FLAGS "-std=c++11 -g2 -Wall")
endif()

add_test(s_test_expr1 test_expr)
add_dependencies(check test_expr)
