#   Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>
#
#   Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(PACKAGE_TAGNAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}")
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/reference/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/reference/Doxyfile @ONLY
    )
    add_custom_target(doc ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/reference/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/reference
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()

install(DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/reference/"
    DESTINATION "${SIMDPP_DOCDIR}/"
)
