#   Copyright (C) 2012-2013  Povilas Kanapickas <povilas@radix.lt>
#
#   Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(CheckCXXSourceRuns)
include(CheckCXXSourceCompiles)

# ------------------------------------------------------------------------------
# Architecture descriptions (internal)
#
# Each architecture has the following information specific to it:
#  - SIMDPP_${ARCH}_TEST_CODE: source code snippet that uses functionality
#       from that arch. Used for @c check_cxx_source_runs macro.
#  - SIMDPP_${ARCH}_CXX_FLAGS: compiler flags that are needed for compilation.
#       The flags predefine the SIMDPP_ARCH_* macro too.
#  - SIMDPP_${ARCH}_SUFFIX: defines a suffix to append to the filename of the
#       source file specific to this architecture.
#
# Three lists are created:
#
#  - SIMDPP_ARCHS_PRI - primary architectures.
#  - SIMDPP_ARCHS_SEC - secondary architectures. Effectively equivalent to one
#       of the primary architectures, just different instructions are generated
#       in specific scenarios.
#  - SIMDPP_ARCHS - all architectures
#

list(APPEND SIMDPP_ARCHS_PRI "X86_SSE2")
if(NOT MSVC)
    set(SIMDPP_X86_SSE2_CXX_FLAGS "-msse2 -DSIMDPP_ARCH_X86_SSE2")
else()
    set(SIMDPP_X86_SSE2_CXX_FLAGS "/arch:SSE2 -DSIMDPP_ARCH_X86_SSE2")
endif()
set(SIMDPP_X86_SSE2_SUFFIX "-x86_sse2")
set(SIMDPP_X86_SSE2_TEST_CODE
    "#include <emmintrin.h>
    int main()
    {
        union {
            volatile char a[16];
            __m128i align;
        };
        __m128i one = _mm_load_si128((__m128i*)(a));
        one = _mm_or_si128(one, one);
        _mm_store_si128((__m128i*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_SSE3")
if(NOT MSVC)
    set(SIMDPP_X86_SSE3_CXX_FLAGS "-msse3 -DSIMDPP_ARCH_X86_SSE3")
else()
    set(SIMDPP_X86_SSE3_CXX_FLAGS "/arch:SSE2 -DSIMDPP_ARCH_X86_SSE3")
endif()
set(SIMDPP_X86_SSE3_SUFFIX "-x86_sse3")
set(SIMDPP_X86_SSE3_TEST_CODE
    "#include <pmmintrin.h>
    int main()
    {
        union {
            volatile char a[16];
            __m128 align;
        };
        __m128 one = _mm_load_ps((float*)(a));
        one = _mm_hadd_ps(one, one);
        _mm_store_ps((float*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_SSSE3")
if(NOT MSVC)
    set(SIMDPP_X86_SSSE3_CXX_FLAGS "-mssse3 -DSIMDPP_ARCH_X86_SSSE3")
else()
    set(SIMDPP_X86_SSSE3_CXX_FLAGS "/arch:SSE2 -DSIMDPP_ARCH_X86_SSSE3")
endif()
set(SIMDPP_X86_SSSE3_SUFFIX "-x86_ssse3")
set(SIMDPP_X86_SSSE3_TEST_CODE
    "#include <tmmintrin.h>
    int main()
    {
        union {
            volatile char a[16];
            __m128i align;
        };
        __m128i one = _mm_load_si128((__m128i*)(a));
        one = _mm_abs_epi8(one);
        _mm_store_si128((__m128i*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_SSE4_1")
if(NOT MSVC)
    set(SIMDPP_X86_SSE4_1_CXX_FLAGS "-msse4.1 -DSIMDPP_ARCH_X86_SSE4_1")
else()
    set(SIMDPP_X86_SSE4_1_CXX_FLAGS "/arch:SSE2 -DSIMDPP_ARCH_X86_SSE4_1")
endif()
set(SIMDPP_X86_SSE4_1_SUFFIX "-x86_sse4_1")
set(SIMDPP_X86_SSE4_1_TEST_CODE
    "#include <smmintrin.h>
    int main()
    {
        union {
            volatile char a[16];
            __m128i align;
        };
        __m128i one = _mm_load_si128((__m128i*)(a));
        one = _mm_cvtepi16_epi32(one);
        _mm_store_si128((__m128i*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_AVX")
if(NOT MSVC)
    set(SIMDPP_X86_AVX_CXX_FLAGS "-mavx -DSIMDPP_ARCH_X86_AVX")
else()
    set(SIMDPP_X86_AVX_CXX_FLAGS "/arch:AVX -DSIMDPP_ARCH_X86_AVX")
endif()
set(SIMDPP_X86_AVX_SUFFIX "-x86_avx")
set(SIMDPP_X86_AVX_TEST_CODE
    "#include <immintrin.h>
    int main()
    {
        union {
            volatile char a[32];
            __m256 align;
        };
        __m256 one = _mm256_load_ps((float*)a);
        one = _mm256_add_ps(one, one);
        _mm256_store_ps((float*)a, one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_AVX2")
if(NOT MSVC)
    set(SIMDPP_X86_AVX2_CXX_FLAGS "-mavx2 -DSIMDPP_ARCH_X86_AVX2")
else()
    set(SIMDPP_X86_AVX2_CXX_FLAGS "/arch:AVX -DSIMDPP_ARCH_X86_AVX2")
endif()
set(SIMDPP_X86_AVX2_SUFFIX "-x86_avx2")
set(SIMDPP_X86_AVX2_TEST_CODE
    "#include <immintrin.h>
    int main()
    {
        union {
            volatile char a[32];
            __m256 align;
        };
        __m256i one = _mm256_load_si256((__m256i*)(a));
        one = _mm256_or_si256(one, one);
        _mm256_store_si256((__m256i*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_FMA3")
if(NOT MSVC)
    set(SIMDPP_X86_FMA3_CXX_FLAGS "-mfma -DSIMDPP_ARCH_X86_FMA3")
else()
    set(SIMDPP_X86_FMA3_CXX_FLAGS "/arch:AVX -DSIMDPP_ARCH_X86_FMA3")
endif()
set(SIMDPP_X86_FMA3_SUFFIX "-x86_fma3")
set(SIMDPP_X86_FMA3_TEST_CODE
    "#include <immintrin.h>
    int main()
    {
        union {
            volatile float a[4];
            __m128 align;
        };
        __m128 one = _mm_load_ps((float*)(a));
        one = _mm_fmadd_ps(one, one, one);
        _mm_store_ps((float*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_FMA4")
if(NOT MSVC)
    set(SIMDPP_X86_FMA4_CXX_FLAGS "-mfma4 -DSIMDPP_ARCH_X86_FMA4")
else()
    set(SIMDPP_X86_FMA4_CXX_FLAGS "/arch:AVX -DSIMDPP_ARCH_X86_FMA4")
endif()
set(SIMDPP_X86_FMA4_SUFFIX "-x86_fma4")
set(SIMDPP_X86_FMA4_TEST_CODE
    "#include <x86intrin.h>
    int main()
    {
        union {
            volatile float a[4];
            __m128 align;
        };
        __m128 one = _mm_load_ps((float*)(a));
        one = _mm_macc_ps(one, one, one);
        _mm_store_ps((float*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_PRI "X86_XOP")
set(SIMDPP_X86_XOP_CXX_FLAGS "-mxop -DSIMDPP_ARCH_X86_XOP")
set(SIMDPP_X86_XOP_SUFFIX "-x86_xop")
set(SIMDPP_X86_XOP_TEST_CODE
    "#include <x86intrin.h>
    int main()
    {
        union {
            volatile char a[16];
            __m128i align;
        };
        __m128i one = _mm_load_si128((__m128i*)(a));
        one = _mm_cmov_si128(one, one, one);
        _mm_store_si128((__m128i*)(a), one);
    }"
)


list(APPEND SIMDPP_ARCHS_PRI "ARM_NEON")
set(SIMDPP_ARM_NEON_CXX_FLAGS "-mfpu=neon -DSIMDPP_ARCH_ARM_NEON")
set(SIMDPP_ARM_NEON_SUFFIX "-arm_neon")
set(SIMDPP_ARM_NEON_TEST_CODE
    "#include <arm_neon.h>
    int main()
    {
        volatile long long a[4];
        uint32x4_t one = vld1q_u32((uint32_t*)(a));
        one = vaddq_u32(one, one);
        vst1q_u32((uint32_t*)(a), one);
    }"
)

list(APPEND SIMDPP_ARCHS_SEC "ARM_NEON_FLT_SP")
set(SIMDPP_ARM_NEON_FLT_SP_CXX_FLAGS "-mfpu=neon -DSIMDPP_ARCH_ARM_NEON_FLT_SP")
set(SIMDPP_ARM_NEON_FLT_SP_SUFFIX "-arm_neon_flt_sp")

list(APPEND SIMDPP_ARCHS_PRI "POWER_ALTIVEC")
set(SIMDPP_POWER_ALTIVEC_CXX_FLAGS "-maltivec -DSIMDPP_ARCH_POWER_ALTIVEC")
set(SIMDPP_POWER_ALTIVEC_SUFFIX "-power_altivec")
set(SIMDPP_POWER_ALTIVEC_TEST_CODE
    "#include <altivec.h>
    int main()
    {
        volatile unsigned char a[16];
        vector unsigned char v = vec_ld(a);
        v = vec_add(v, v);
        vec_st(a, v);
    }"
)
set(SIMDPP_ARCHS "${SIMDPP_ARCHS_PRI};${SIMDPP_ARCHS_SEC}")

# ------------------------------------------------------------------------------
# Given one arch, returns compilation flags and an unique identifier (internal)
# If the given architecture does not exist, sets both result variables to ""
#
# Arguments:
#
# - CXX_FLAGS_VAR: the name of a variable to store the compilation flags to
#
# - UNIQUE_ID_VAR: the name of a variable to store the unique identifier to
#
# - ARCH: an architecture
#
function(simdpp_get_arch_info CXX_FLAGS_VAR UNIQUE_ID_VAR ARCH)
    set(UNIQUE_ID "")
    set(CXX_FLAGS "")

    string(REPLACE "," ";" ARCH_IDS "${ARCH}")
    list(SORT ARCH_IDS)
    foreach(ID ${ARCH_IDS})
        if(${ID} STREQUAL "NONE_NULL")
            set(UNIQUE_ID "${UNIQUE_ID}-null")
        else()
            list(FIND SIMDPP_ARCHS "${ID}" FOUND)
            if(NOT ${FOUND} EQUAL -1)
                set(CXX_FLAGS "${CXX_FLAGS} ${SIMDPP_${ID}_CXX_FLAGS}")
                set(UNIQUE_ID "${UNIQUE_ID}${SIMDPP_${ID}_SUFFIX}")
            endif()
        endif()
    endforeach()
    set(${CXX_FLAGS_VAR} "${CXX_FLAGS}" PARENT_SCOPE)
    set(${UNIQUE_ID_VAR} "${UNIQUE_ID}" PARENT_SCOPE)
endfunction()

# ------------------------------------------------------------------------------
#
# simdpp_multiarch(FILE_LIST_VAR SRC_FILE [ARCH...])
#
# A function that encapsulates the generation of build rules for libsimdpp
# multi-architecture source files. The function creates a copy of @a SRC_FILE
# for each supplied architecture definition. Each of these files is configured
# with appropriate compile flags for the given architecture. The list of copied
# files is appended to the variable supplied by @a FILE_LIST_VAR which can then
# be used in add_library or add_executable calls.
#
# All copied files are placed in the build directory. The directory of
# @a SRC_FILE is added to the default include paths.
#
# Arguments:
#
# * FILE_LIST_VAR: the name of the variable to append the list of generated
#   files to
#
# * SRC_FILE: the name of the source file relative to the @a
#   CMAKE_CURRENT_SOURCE_DIR
#
# * ARCH...: a list of architecture definitions. Each architecture definitions
#   consist of comma separated list of identifiers directly corresponding to
#   macros defined in simdpp/simd.h, which ultimately identify instruction set
#   features. The user of the function must ensure that sensible combination of
#   identifiers is supplied.
#
#   The following identifiers are currently supported:
#   X86_SSE2, X86_SSE3, X86_SSSE3, X86_SSE4_1, X86_AVX, X86_AVX2, X86_FMA3,
#   X86_FMA4, X86_XOP, ARM_NEON, ARM_NEON_FLT_SP
#
function(simdpp_multiarch FILE_LIST_VAR SRC_FILE)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}")
        message(FATAL_ERROR "File \"${SRC_FILE}\" does not exist")
    endif()
    get_filename_component(SRC_PATH "${SRC_FILE}" PATH)
    get_filename_component(SRC_NAME "${SRC_FILE}" NAME_WE)
    get_filename_component(SRC_EXT "${SRC_FILE}" EXT)

    set(FILE_LIST "")
    list(APPEND ARCHS ${ARGV})
    list(REMOVE_AT ARCHS 0 1)
    foreach(ARCH ${ARCHS})
        simdpp_get_arch_info(CXX_FLAGS SUFFIX ${ARCH})

        set(CXX_FLAGS "-I\"${CMAKE_CURRENT_SOURCE_DIR}/${SRC_PATH}\" ${CXX_FLAGS}")
        if(NOT "${SUFFIX}" STREQUAL "")
            set(DST_ABS_FILE "${CMAKE_CURRENT_BINARY_DIR}/${SRC_PATH}/${SRC_NAME}_simdpp_${SUFFIX}${SRC_EXT}")
            set(SRC_ABS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}")
            configure_file("${SRC_ABS_FILE}" "${DST_ABS_FILE}" COPYONLY)
            list(APPEND FILE_LIST "${DST_ABS_FILE}")
            set_source_files_properties("${DST_ABS_FILE}" PROPERTIES COMPILE_FLAGS ${CXX_FLAGS})
        endif()
    endforeach()

    set(RECV_FILE_LIST ${${FILE_LIST_VAR}})
    list(APPEND RECV_FILE_LIST ${FILE_LIST})
    set(${FILE_LIST_VAR} ${RECV_FILE_LIST} PARENT_SCOPE)
endfunction()

# ------------------------------------------------------------------------------
# Given a list of archs, return all possible permutations of them (internal)
#
# Arguments:
#
# - ALL_ARCHS_VAL: the name of the variable to store the permutation to
#
# - ARCH...: a list of supported architectures
function(simdpp_get_arch_perm ALL_ARCHS_VAR)
    list(APPEND ARCHS ${ARGV})
    list(REMOVE_AT ARCHS 0)

    foreach(ARCH ${ARCHS})
        set(ARCH_SUPPORTED_${ARCH} "1")
    endforeach()

    set(ALL_ARCHS "NONE_NULL")
    if(DEFINED ARCH_SUPPORTED_X86_SSE2)
        list(APPEND ALL_ARCHS "X86_SSE2")
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_SSE3)
        list(APPEND ALL_ARCHS "X86_SSE3")
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_SSSE3)
        list(APPEND ALL_ARCHS "X86_SSSE3")
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_SSE4_1)
        list(APPEND ALL_ARCHS "X86_SSE4_1")
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_AVX)
        list(APPEND ALL_ARCHS "X86_AVX")
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_AVX2)
        list(APPEND ALL_ARCHS "X86_AVX2")
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_FMA3)
        list(APPEND ALL_ARCHS "X86_FMA3")
        if(DEFINED ARCH_SUPPORTED_X86_AVX)
            list(APPEND ALL_ARCHS "X86_AVX,X86_FMA3")
        endif()
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_FMA4)
        list(APPEND ALL_ARCHS "X86_FMA4")
        if(DEFINED ARCH_SUPPORTED_X86_AVX)
            list(APPEND ALL_ARCHS "X86_AVX,X86_FMA4")
        endif()
    endif()
    if(DEFINED ARCH_SUPPORTED_X86_XOP)
        list(APPEND ALL_ARCHS "X86_XOP")
        if(DEFINED ARCH_SUPPORTED_X86_AVX)
            list(APPEND ALL_ARCHS "X86_AVX,X86_XOP")
        endif()
    endif()
    if(DEFINED ARCH_SUPPORTED_ARM_NEON)
        list(APPEND ALL_ARCHS "ARM_NEON")
        list(APPEND ALL_ARCHS "ARM_NEON_FLT_SP")
    endif()
    if(DEFINED ARCH_SUPPORTED_POWER_ALTIVEC)
        list(APPEND ALL_ARCHS "POWER_ALTIVEC")
    endif()
    set(${ALL_ARCHS_VAR} "${ALL_ARCHS}" PARENT_SCOPE)
endfunction()

# ------------------------------------------------------------------------------
#
# simdpp_get_compilable_archs(ARCH_LIST_VAR)
#
# Returns a list of architectures that are supported by the current build
# system. The generated list may be used as an argument to simdpp_multiarch.
#
# Arguments:
#
# * ARCH_LIST_VAR: the name of the variable to put the architecture list to
#
function(simdpp_get_compilable_archs ARCH_LIST_VAR)

    foreach(ARCH ${SIMDPP_ARCHS_PRI})
        set(CMAKE_REQUIRED_FLAGS "${SIMDPP_${ARCH}_CXX_FLAGS}")
        check_cxx_source_compiles("${SIMDPP_${ARCH}_TEST_CODE}" CAN_COMPILE_${ARCH})
        if(CAN_COMPILE_${ARCH})
            list(APPEND ARCHS ${ARCH})
        endif()
    endforeach()

    simdpp_get_arch_perm(ALL_ARCHS "${ARCHS}")
    set(${ARCH_LIST_VAR} "${ALL_ARCHS}" PARENT_SCOPE)

endfunction()

# ------------------------------------------------------------------------------
#
# simdpp_get_compilable_archs(ARCH_LIST_VAR)
#
# Returns a list of architectures that are supported by the current build
# system and the processor. The generated list may be used as an argument to
# simdpp_multiarch.
#
# Arguments:
#
# * ARCH_LIST_VAR: the name of the variable to put the architecture list to
#
function(simdpp_get_runnable_archs ARCH_LIST_VAR)

    foreach(ARCH ${SIMDPP_ARCHS_PRI})
        set(CMAKE_REQUIRED_FLAGS "${SIMDPP_${ARCH}_CXX_FLAGS}")
        check_cxx_source_runs("${SIMDPP_${ARCH}_TEST_CODE}" CAN_RUN_${ARCH})
        if(CAN_RUN_${ARCH})
            list(APPEND ARCHS ${ARCH})
        endif()
    endforeach()

    simdpp_get_arch_perm(ALL_ARCHS "${ARCHS}")
    set(${ARCH_LIST_VAR} "${ALL_ARCHS}" PARENT_SCOPE)

endfunction()

