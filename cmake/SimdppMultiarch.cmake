#   libsimdpp
#   Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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
#

include(CheckCXXSourceRuns)
include(CheckCXXSourceCompiles)

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
#   X86_SSE2, X86_SSE3, X86_SSSE3, X86_SSE4_1, X86_AVX, X86_AVX2, ARM_NEON,
#   ARM_NEON_FLT_SP
#
function(simdpp_multiarch FILE_LIST_VAR SRC_FILE)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILE}")
        message(FATAL_ERROR "File \"${SRC_FILE}\" does not exist")
    endif()
    get_filename_component(SRC_PATH "${SRC_FILE}" PATH)
    get_filename_component(SRC_NAME "${SRC_FILE}" NAME_WE)
    get_filename_component(SRC_EXT "${SRC_FILE}" EXT)

    set(CXX_FLAG_X86_SSE2 "-msse2 -DSIMDPP_ARCH_X86_SSE2")
    set(CXX_FLAG_X86_SSE3 "-msse3 -DSIMDPP_ARCH_X86_SSE3")
    set(CXX_FLAG_X86_SSSE3 "-mssse3 -DSIMDPP_ARCH_X86_SSSE3")
    set(CXX_FLAG_X86_SSE4_1 "-msse4.1 -DSIMDPP_ARCH_X86_SSE4_1")
    set(CXX_FLAG_X86_AVX "-mavx -DSIMDPP_ARCH_X86_AVX")
    set(CXX_FLAG_X86_AVX2 "-mavx2 -DSIMDPP_ARCH_X86_AVX2")
    set(CXX_FLAG_ARM_NEON "-mfpu=neon -DSIMDPP_ARCH_ARM_NEON")
    set(CXX_FLAG_ARM_NEON_FLT_SP "-mfpu=neon -DSIMDPP_ARCH_ARM_NEON_FLT_SP")
    set(CXX_FLAG_POWER_ALTIVEC "-maltivec -DSIMDPP_ARCH_POWER_ALTIVEC")

    set(FILE_LIST "")
    list(APPEND ARCHS ${ARGV})
    list(REMOVE_AT ARCHS 0 1)
    foreach(ARCH ${ARCHS})
        set(CXX_FLAGS "-I${CMAKE_CURRENT_SOURCE_DIR}/${SRC_PATH}")
        set(SUFFIX "simdpp")

        string(REGEX MATCHALL "[^,]+,|[^,]+$" ARCH_IDS "${ARCH}")
        list(SORT ARCH_IDS)
        foreach(ID ${ARCH_IDS})
            if(${ID} STREQUAL "NONE_NULL")
                set(SUFFIX "${SUFFIX}-null")
            elseif(${ID} STREQUAL "X86_SSE2")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_X86_SSE2}")
                set(SUFFIX "${SUFFIX}-x86_sse2")
            elseif(${ID} STREQUAL "X86_SSE3")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_X86_SSE3}")
                set(SUFFIX "${SUFFIX}-x86_sse3")
            elseif(${ID} STREQUAL "X86_SSSE3")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_X86_SSSE3}")
                set(SUFFIX "${SUFFIX}-x86_ssse3")
            elseif(${ID} STREQUAL "X86_SSE4_1")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_X86_SSE4_1}")
                set(SUFFIX "${SUFFIX}-x86_sse4_1")
            elseif(${ID} STREQUAL "X86_AVX")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_X86_AVX}")
                set(SUFFIX "${SUFFIX}-x86_avx")
            elseif(${ID} STREQUAL "X86_AVX2")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_X86_AVX2}")
                set(SUFFIX "${SUFFIX}-x86_avx2")
            elseif(${ID} STREQUAL "ARM_NEON")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_ARM_NEON}")
                set(SUFFIX "${SUFFIX}-arm_neon")
            elseif(${ID} STREQUAL "ARM_NEON_FLT_SP")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_ARM_NEON_FLT_SP}")
                set(SUFFIX "${SUFFIX}-arm_neon_flt_sp")
            elseif(${ID} STREQUAL "POWER_ALTIVEC")
                set(CXX_FLAGS "${CXX_FLAGS} ${CXX_FLAG_POWER_ALTIVEC}")
                set(SUFFIX "${SUFFIX}-power_altivec")
            endif()
        endforeach()

        if(NOT "${SUFFIX}" STREQUAL "simdpp")
            set(DST_ABS_FILE "${CMAKE_CURRENT_BINARY_DIR}/${SRC_PATH}/${SRC_NAME}_${SUFFIX}${SRC_EXT}")
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
# some support code
set(SIMDPP_ARCH_TEST_SSE2_CODE
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
set(SIMDPP_ARCH_TEST_SSE3_CODE
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
set(SIMDPP_ARCH_TEST_SSSE3_CODE
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
set(SIMDPP_ARCH_TEST_SSE4_1_CODE
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
set(SIMDPP_ARCH_TEST_AVX_CODE
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
set(SIMDPP_ARCH_TEST_AVX2_CODE
    "#include <immintrin.h>
    int main()
    {
        union {
            volatile char a[32];
            __m256 align;
        };
        __m256i one = _mm256_load_si256((__m256i*)(a));
        one = _mm256_or_si256(one, one);
        _mm_store_si256((__m256i*)(a), one);
    }"
)
set(SIMDPP_ARCH_TEST_NEON_CODE
    "#include <arm_neon.h>
    int main()
    {
        volatile long long a[4];
        uint32x4_t one = vld1q_u32((uint32_t*)(a));
        one = vaddq_u32(one, one);
        vst1q_u32((uint32_t*)(a), one);
    }"
)
set(SIMDPP_ARCH_TEST_ALTIVEC_CODE
    "#include <altivec.h>
    int main()
    {
        volatile unsigned char a[16];
        vector unsigned char v = vec_ld(a);
        v = vec_add(v, v);
        vec_st(a, v);
    }"
)

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

    set(CMAKE_REQUIRED_FLAGS "-msse2")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_SSE2_CODE}" CAN_COMPILE_SSE2)

    set(CMAKE_REQUIRED_FLAGS "-msse3")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_SSE3_CODE}" CAN_COMPILE_SSE3)

    set(CMAKE_REQUIRED_FLAGS "-mssse3")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_SSSE3_CODE}" CAN_COMPILE_SSSE3)

    set(CMAKE_REQUIRED_FLAGS "-msse4.1")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_SSE4_1_CODE}" CAN_COMPILE_SSE4_1)

    set(CMAKE_REQUIRED_FLAGS "-mavx")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_AVX_CODE}" CAN_COMPILE_AVX)

    set(CMAKE_REQUIRED_FLAGS "-mavx2")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_AVX2_CODE}" CAN_COMPILE_AVX2)

    set(CMAKE_REQUIRED_FLAGS "-mfpu=neon")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_NEON_CODE}" CAN_COMPILE_NEON)

    set(CMAKE_REQUIRED_FLAGS "-maltivec")
    check_cxx_source_compiles("${SIMDPP_ARCH_TEST_ALTIVEC_CODE}" CAN_COMPILE_ALTIVEC)

    set(ARCHS "NONE_NULL")
    if(CAN_COMPILE_SSE2)
        list(APPEND ARCHS "X86_SSE2")
    endif()
    if(CAN_COMPILE_SSE3)
        list(APPEND ARCHS "X86_SSE3")
    endif()
    if(CAN_COMPILE_SSSE3)
        list(APPEND ARCHS "X86_SSSE3")
    endif()
    if(CAN_COMPILE_SSE4_1)
        list(APPEND ARCHS "X86_SSE4_1")
    endif()
    if(CAN_COMPILE_AVX)
        list(APPEND ARCHS "X86_AVX")
    endif()
    if(CAN_COMPILE_AVX2)
        list(APPEND ARCHS "X86_AVX2")
    endif()
    if(CAN_COMPILE_NEON)
        list(APPEND ARCHS "ARM_NEON")
        list(APPEND ARCHS "ARM_NEON_FLT_SP")
    endif()
    if(CAN_COMPILE_ALTIVEC)
        list(APPEND ARCHS "POWER_ALTIVEC")
    endif()
    set(${ARCH_LIST_VAR} ${ARCHS} PARENT_SCOPE)
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

    set(CMAKE_REQUIRED_FLAGS "-msse2")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_SSE2_CODE}" CAN_RUN_SSE2)

    set(CMAKE_REQUIRED_FLAGS "-msse3")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_SSE3_CODE}" CAN_RUN_SSE3)

    set(CMAKE_REQUIRED_FLAGS "-mssse3")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_SSSE3_CODE}" CAN_RUN_SSSE3)

    set(CMAKE_REQUIRED_FLAGS "-msse4.1")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_SSE4_1_CODE}" CAN_RUN_SSE4_1)

    set(CMAKE_REQUIRED_FLAGS "-mavx")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_AVX_CODE}" CAN_RUN_AVX)

    set(CMAKE_REQUIRED_FLAGS "-mavx2")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_AVX2_CODE}" CAN_RUN_AVX2)

    set(CMAKE_REQUIRED_FLAGS "-mfpu=neon")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_NEON_CODE}" CAN_RUN_NEON)

    set(CMAKE_REQUIRED_FLAGS "-maltivec")
    check_cxx_source_runs("${SIMDPP_ARCH_TEST_ALTIVEC_CODE}" CAN_RUN_ALTIVEC)

    set(ARCHS "NONE_NULL")
    if(CAN_RUN_SSE2)
        list(APPEND ARCHS "X86_SSE2")
    endif()
    if(CAN_RUN_SSE3)
        list(APPEND ARCHS "X86_SSE3")
    endif()
    if(CAN_RUN_SSSE3)
        list(APPEND ARCHS "X86_SSSE3")
    endif()
    if(CAN_RUN_SSE4_1)
        list(APPEND ARCHS "X86_SSE4_1")
    endif()
    if(CAN_RUN_AVX)
        list(APPEND ARCHS "X86_AVX")
    endif()
    if(CAN_RUN_AVX2)
        list(APPEND ARCHS "X86_AVX2")
    endif()
    if(CAN_RUN_NEON)
        list(APPEND ARCHS "ARM_NEON")
        list(APPEND ARCHS "ARM_NEON_FLT_SP")
    endif()
    if(CAN_RUN_ALTIVEC)
        list(APPEND ARCHS "POWER_ALTIVEC")
    endif()
    set(${ARCH_LIST_VAR} ${ARCHS} PARENT_SCOPE)
endfunction()

