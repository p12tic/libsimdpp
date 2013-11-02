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

include_directories(${libsimdpp98_SOURCE_DIR})

set(PERF_SOURCES
    neon.cc
    neon_flt_sp.cc
    null.cc
    sse2.cc
    sse3.cc
    sse4_1.cc
    ssse3.cc
)

set(PERF_HEADERS
    perf.h
)

add_custom_target(perf)

if(DEFINED HAS_SSE2)
    add_executable(sse2 EXCLUDE_FROM_ALL sse2.cc)
    set_target_properties(sse2 PROPERTIES COMPILE_FLAGS "-msse2")
    add_dependencies(perf sse2)
endif()
if(DEFINED HAS_SSE3)
    add_executable(sse3 EXCLUDE_FROM_ALL sse3.cc)
    set_target_properties(sse3 PROPERTIES COMPILE_FLAGS "-msse3")
    add_dependencies(perf sse3)
endif()
if(DEFINED HAS_SSSE3)
    add_executable(ssse3 EXCLUDE_FROM_ALL ssse3.cc)
    set_target_properties(ssse3 PROPERTIES COMPILE_FLAGS "-mssse3")
    add_dependencies(perf ssse3)
endif()
if(DEFINED HAS_SSE4_1)
    add_executable(sse4_1 EXCLUDE_FROM_ALL sse4_1.cc)
    set_target_properties(sse4_1 PROPERTIES COMPILE_FLAGS "-msse4.1")
    add_dependencies(perf sse4_1)
endif()
if(DEFINED HAS_NEON)
    add_executable(neon EXCLUDE_FROM_ALL neon.cc)
    add_executable(neon_flt_sp EXCLUDE_FROM_ALL neon_flt_sp.cc)
    set_target_properties(neon neon_flt_sp PROPERTIES COMPILE_FLAGS "-mfpu=neon")
    add_dependencies(perf neon neon_flt_sp)
endif()


