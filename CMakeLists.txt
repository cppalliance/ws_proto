#
# Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
# Copyright (c) 2021 Dmitry Arkhipov (grisumbras@gmail.com)
# Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
# Copyright (c) 2025 Mohammad Nejati
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/ws_proto
#

#-------------------------------------------------
#
# Project
#
#-------------------------------------------------
cmake_minimum_required(VERSION 3.8...3.20)
set(BOOST_WS_PROTO_VERSION 1)
if (BOOST_SUPERPROJECT_VERSION)
    set(BOOST_WS_PROTO_VERSION ${BOOST_SUPERPROJECT_VERSION})
endif ()
project(boost_ws_proto VERSION "${BOOST_WS_PROTO_VERSION}" LANGUAGES CXX)
set(BOOST_WS_PROTO_IS_ROOT OFF)
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(BOOST_WS_PROTO_IS_ROOT ON)
endif ()
set(__ignore__ ${CMAKE_C_COMPILER})

#-------------------------------------------------
#
# Options
#
#-------------------------------------------------
if (BOOST_WS_PROTO_IS_ROOT)
    include(CTest)
endif ()
option(BOOST_WS_PROTO_BUILD_TESTS "Build boost::ws_proto tests" ${BUILD_TESTING})
option(BOOST_WS_PROTO_BUILD_EXAMPLES "Build boost::ws_proto examples" ${BOOST_WS_PROTO_IS_ROOT})


# Check if environment variable BOOST_SRC_DIR is set
if (NOT DEFINED BOOST_SRC_DIR AND DEFINED ENV{BOOST_SRC_DIR})
    set(DEFAULT_BOOST_SRC_DIR "$ENV{BOOST_SRC_DIR}")
else ()
    set(DEFAULT_BOOST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif ()
set(BOOST_SRC_DIR ${DEFAULT_BOOST_SRC_DIR} CACHE STRING "Boost source dir to use when running CMake from this directory")

#-------------------------------------------------
#
# Boost modules
#
#-------------------------------------------------
# The boost super-project requires one explicit dependency per-line.
set(BOOST_WS_PROTO_DEPENDENCIES
    Boost::http_proto
    Boost::url
    )

foreach (BOOST_WS_PROTO_DEPENDENCY ${BOOST_WS_PROTO_DEPENDENCIES})
    if (BOOST_WS_PROTO_DEPENDENCY MATCHES "^[ ]*Boost::([A-Za-z0-9_]+)[ ]*$")
        list(APPEND BOOST_WS_PROTO_INCLUDE_LIBRARIES ${CMAKE_MATCH_1})
    endif ()
endforeach ()
# Conditional dependencies
if (BOOST_WS_PROTO_BUILD_TESTS)
    # set(BOOST_WS_PROTO_UNIT_TEST_LIBRARIES filesystem)
endif ()
if (BOOST_WS_PROTO_BUILD_EXAMPLES)
    # set(BOOST_WS_PROTO_EXAMPLE_LIBRARIES json)
endif ()
# Complete dependency list
set(BOOST_INCLUDE_LIBRARIES ${BOOST_WS_PROTO_INCLUDE_LIBRARIES} ${BOOST_WS_PROTO_UNIT_TEST_LIBRARIES} ${BOOST_WS_PROTO_EXAMPLE_LIBRARIES})
set(BOOST_EXCLUDE_LIBRARIES ws_proto)

#-------------------------------------------------
#
# Add Boost Subdirectory
#
#-------------------------------------------------
if (BOOST_WS_PROTO_IS_ROOT)
    set(CMAKE_FOLDER Dependencies)
    # Find absolute BOOST_SRC_DIR
    if (NOT IS_ABSOLUTE ${BOOST_SRC_DIR})
        set(BOOST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${BOOST_SRC_DIR}")
    endif ()

    # Validate BOOST_SRC_DIR
    set(BOOST_SRC_DIR_IS_VALID ON)
    foreach (F "CMakeLists.txt" "Jamroot" "boost-build.jam" "bootstrap.sh" "libs")
        if (NOT EXISTS "${BOOST_SRC_DIR}/${F}")
            message(STATUS "${BOOST_SRC_DIR}/${F} does not exist. Fallback to find_package.")
            set(BOOST_SRC_DIR_IS_VALID OFF)
            break()
        endif ()
    endforeach ()

    # Create Boost interface targets
    if (BOOST_SRC_DIR_IS_VALID)
        # From BOOST_SRC_DIR
        if (BUILD_SHARED_LIBS)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
        endif ()
        set(BOOST_EXCLUDE_LIBRARIES ${PROJECT_NAME})
        set(PREV_BUILD_TESTING ${BUILD_TESTING})
        set(BUILD_TESTING OFF CACHE BOOL "Build the tests." FORCE)
        add_subdirectory(${BOOST_SRC_DIR} Dependencies/boost EXCLUDE_FROM_ALL)
        set(BUILD_TESTING ${PREV_BUILD_TESTING} CACHE BOOL "Build the tests." FORCE)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BOOST_SRC_DIR}/tools/cmake/include")
    else ()
        # From Boost Package
        find_package(Boost REQUIRED COMPONENTS http_proto)
        foreach (BOOST_INCLUDE_LIBRARY ${BOOST_INCLUDE_LIBRARIES})
            if (NOT TARGET Boost::${BOOST_INCLUDE_LIBRARY})
                add_library(Boost::${BOOST_INCLUDE_LIBRARY} ALIAS Boost::headers)
            endif ()
        endforeach ()
    endif ()
    unset(CMAKE_FOLDER)
endif ()

#-------------------------------------------------
#
# Library
#
#-------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE BOOST_WS_PROTO_HEADERS CONFIGURE_DEPENDS include/boost/ws_proto/*.hpp include/boost/ws_proto/*.natvis)
file(GLOB_RECURSE BOOST_WS_PROTO_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

source_group("" FILES "include/boost/ws_proto.hpp" "build/Jamfile")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/boost/ws_proto PREFIX "include" FILES ${BOOST_WS_PROTO_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${BOOST_WS_PROTO_SOURCES})

add_library(boost_ws_proto include/boost/ws_proto.hpp build/Jamfile ${BOOST_WS_PROTO_HEADERS} ${BOOST_WS_PROTO_SOURCES})
add_library(Boost::ws_proto ALIAS boost_ws_proto)
target_compile_features(boost_ws_proto PUBLIC cxx_constexpr)
target_include_directories(boost_ws_proto PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(boost_ws_proto PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(boost_ws_proto PUBLIC ${BOOST_WS_PROTO_DEPENDENCIES})
target_compile_definitions(boost_ws_proto PUBLIC BOOST_WS_PROTO_NO_LIB)
target_compile_definitions(boost_ws_proto PRIVATE BOOST_WS_PROTO_SOURCE)
if (BUILD_SHARED_LIBS)
    target_compile_definitions(boost_ws_proto PUBLIC BOOST_WS_PROTO_DYN_LINK)
else ()
    target_compile_definitions(boost_ws_proto PUBLIC BOOST_WS_PROTO_STATIC_LINK)
endif ()

#-------------------------------------------------
#
# Tests
#
#-------------------------------------------------
if (BOOST_WS_PROTO_BUILD_TESTS)
    add_subdirectory(test)
endif ()

#-------------------------------------------------
#
# Examples
#
#-------------------------------------------------
if (BOOST_WS_PROTO_BUILD_EXAMPLES)
    # add_subdirectory(example)
endif ()
