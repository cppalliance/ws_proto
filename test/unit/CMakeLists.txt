#
# Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/ws_proto
#

set(EXTRAFILES
    ../../../url/extra/test_main.cpp
    ../../../url/extra/test_suite.hpp
    )

set(PFILES
    CMakeLists.txt
    Jamfile
    close_code.cpp
    error.cpp
    handshake.cpp
    parser.cpp
    serializer.cpp
    )

set(UNIT_TEST_LINK_LIBRARIES boost_ws_proto)
if (ZLIB_FOUND)
    set(UNIT_TEST_LINK_LIBRARIES ${UNIT_TEST_LINK_LIBRARIES} boost_ws_proto_zlib)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "" FILES ${PFILES})
source_group("_extra" FILES ${EXTRAFILES})
add_executable(boost_ws_proto_tests ${PFILES} ${EXTRAFILES})
target_include_directories(boost_ws_proto_tests PRIVATE . ../../../url/extra)
target_link_libraries(
    boost_ws_proto_tests PRIVATE
    ${UNIT_TEST_LINK_LIBRARIES}
    Boost::filesystem)
if (ZLIB_FOUND)
    target_link_libraries(boost_ws_proto_tests PRIVATE ZLIB::ZLIB)
endif()
add_test(NAME boost_ws_proto_tests COMMAND boost_ws_proto_tests)
