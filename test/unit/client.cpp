//
// Copyright (c) 2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

// Test that header file is self-contained.
#include <boost/ws_proto/client.hpp>

#include "test_suite.hpp"

namespace boost {
namespace ws_proto {

struct client_test
{
    void
    run()
    {
    }
};

TEST_SUITE(
    client_test,
    "boost.ws_proto.client");

} // ws_proto
} // boost
