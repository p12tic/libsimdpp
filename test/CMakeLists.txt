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

# ------------------------------------------------------------------------------
# check available architectures

list_contains(HAS_SSE2 X86_SSE2 ${NATIVE_ARCHS})
list_contains(HAS_SSE3 X86_SSE3 ${NATIVE_ARCHS})
list_contains(HAS_SSSE3 X86_SSSE3 ${NATIVE_ARCHS})
list_contains(HAS_SSE4_1 X86_SSE4_1 ${NATIVE_ARCHS})
list_contains(HAS_AVX X86_AVX ${NATIVE_ARCHS})
list_contains(HAS_AVX2 X86_AVX2 ${NATIVE_ARCHS})
list_contains(HAS_AVX512F X86_AVX512F ${NATIVE_ARCHS})
list_contains(HAS_AVX512BW X86_AVX512BW ${NATIVE_ARCHS})
list_contains(HAS_AVX512DQ X86_AVX512DQ ${NATIVE_ARCHS})
list_contains(HAS_AVX512VL X86_AVX512VL ${NATIVE_ARCHS})
list_contains(HAS_NEON X86_NEON ${NATIVE_ARCHS})

# ------------------------------------------------------------------------------

# We need to specify test configuration to be able to test compilation failure
# tests on MSVC.
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C Debug --verbose)

set(TEST_INSN_SOURCES
    utils/test_results_set.cc
    main_insn.cc
)

set(TEST_INSN_HEADERS
    utils/test_helpers.h
    utils/test_results.h
    utils/test_results_set.h
    insn/tests.h
    common/masks.h
    common/vectors.h
    common/aligned_allocator.h
)

set(TEST_INSN_ARCH_SOURCES
    insn/bitwise.cc
    insn/blend.cc
    insn/compare.cc
    insn/construct.cc
    insn/convert.cc
    insn/for_each.cc
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

set(TEST_INSN_ARCH_GEN_SOURCES "")

foreach(SRC ${TEST_INSN_ARCH_SOURCES})
    simdpp_multiarch(TEST_INSN_ARCH_GEN_SOURCES ${SRC} ${COMPILABLE_ARCHS})
endforeach()

# print compiler detection information
message(STATUS "Checking detected compiler for tests...")
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

    foreach(GENSRC ${TEST_INSN_ARCH_GEN_SOURCES})
        get_property(CURRENT_COMPILE_FLAGS
                     SOURCE "${GENSRC}" PROPERTY COMPILE_FLAGS)
        set_property(SOURCE "${GENSRC}" PROPERTY COMPILE_FLAGS
                     "${DEFAULT_FLAGS} ${CURRENT_COMPILE_FLAGS}")
    endforeach()
endif()

add_executable(test_insn EXCLUDE_FROM_ALL
    ${TEST_INSN_SOURCES}
    ${TEST_INSN_ARCH_GEN_SOURCES}
)

if(SIMDPP_MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # enable _vectorcall on i386 builds (only works on MSVC 2013)
        set_target_properties(test_insn PROPERTIES COMPILE_FLAGS "/Gv")
    endif()
elseif(SIMDPP_MSVC_INTEL)
    set_target_properties(test_insn PROPERTIES COMPILE_FLAGS "/Qstd=c++11")
else()
    # Xcode clang linker spends very long time in deduplication pass when
    # linking the test executable unless -fvisibility-inlines-hidden is passed.
    set_target_properties(test_insn PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wextra -fvisibility-inlines-hidden")
endif()

if("${CMAKE_VERSION}" VERSION_GREATER 2.8.12)
    # We don't want to break testing on old environments where newer cmake
    # versions are not easily available.
    target_compile_definitions(test_insn PUBLIC "-DSIMDPP_DISABLE_DEPRECATED_IN_2_1_AND_OLDER=1")
endif()

add_test(s_test_insn test_insn)
add_dependencies(check test_insn)

# ------------------------------------------------------------------------------
# Dispatcher test

set(TEST_DISPATCHER_SOURCES
    main_dispatcher.cc
    utils/test_results_set.cc
)

set(TEST_DISPATCHER_ARCH_SOURCES
    dispatcher/dispatcher.cc
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
    set_target_properties(test_dispatcher PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall -fvisibility-inlines-hidden")
endif()
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.12)
    target_compile_definitions(test_dispatcher PUBLIC "-DSIMDPP_DISABLE_DEPRECATED_IN_2_1_AND_OLDER=1")
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
if(HAS_AVX512BW)
    add_test(s_test_dispatcher9 test_dispatcher "X86_AVX512BW")
endif()
if(HAS_AVX512DQ)
    add_test(s_test_dispatcher10 test_dispatcher "X86_AVX512DQ")
endif()
if(HAS_AVX512VL)
    add_test(s_test_dispatcher11 test_dispatcher "X86_AVX512VL")
endif()
if(HAS_NEON)
    add_test(s_test_dispatcher12 test_dispatcher "ARM_NEON")
    add_test(s_test_dispatcher13 test_dispatcher "ARM_NEON_FLT_SP")
endif()

add_dependencies(check test_dispatcher)

# ------------------------------------------------------------------------------
# Expression test

set(TEST_EXPR_SOURCES
    main_expr.cc
    expr/tests.cc
    expr/bitwise.cc
    expr/compare.cc
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
    set_target_properties(test_expr PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -Wall -fvisibility-inlines-hidden")
endif()
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.12)
    target_compile_definitions(test_expr PUBLIC "-DSIMDPP_DISABLE_DEPRECATED_IN_2_1_AND_OLDER=1")
endif()

add_test(s_test_expr1 test_expr)
add_dependencies(check test_expr)

add_custom_target(create_dir_for_compile_fail
                  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/compile_fail")
add_dependencies(check create_dir_for_compile_fail)

add_test(NAME test_compile_fail
         COMMAND ${CMAKE_COMMAND} ${libsimdpp_SOURCE_DIR}/test/compile_fail
            -G "${CMAKE_GENERATOR}"
            -T "${CMAKE_GENERATOR_TOOLSET}"
            "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
            "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
            "-Dlibsimdpp_SOURCE_DIR=${libsimdpp_SOURCE_DIR}"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/compile_fail)
