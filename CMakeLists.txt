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

cmake_minimum_required(VERSION 2.8.0)
project(libsimdpp)
set(PROJECT_VERSION "1.0")
set(SIMDPP_API_VERSION "1.0")

set(PKG_NAME "${CMAKE_PROJECT_NAME}")
set(PKG_FULL_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# ------------------------------------------------------------------------------
# Custom make dist target. Assumes source directory is a git repository.

set(ARCHIVE_NAME "${PKG_FULL_NAME}")
set(ARCHIVE_DIR "${PKG_FULL_NAME}")

add_custom_target(dist
    COMMAND cd "${CMAKE_SOURCE_DIR}" && ./make_dist.sh "${ARCHIVE_DIR}" "${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz"
    # we may append to the archive now if needed
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ------------------------------------------------------------------------------
# Check what instruction sets the current host supports. Use them for testing
include(SimdppMultiarch)
simdpp_get_runnable_archs(NATIVE_ARCHS)
# ------------------------------------------------------------------------------

set(SIMDPP_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include/${PKG_NAME}-${SIMDPP_API_VERSION}")
set(SIMDPP_DOCDIR "${CMAKE_INSTALL_PREFIX}/share/doc/${PKG_NAME}")
set(SIMDPP_PKGCONFIGDIR "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/${PKG_FULL_NAME}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/libsimdpp.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PKF_FULL_NAME}.pc" @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PKF_FULL_NAME}.pc"
    DESTINATION "${SIMDPP_PKGCONFIGDIR}"
)


enable_testing()

add_subdirectory(simdpp)
add_subdirectory(test)
add_subdirectory(doc)
