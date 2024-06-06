//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#include <boost/ws_proto/handshake.hpp>

namespace boost {
namespace ws_proto {

system::result<bool>
is_upgrade(
    http_proto::request_view const& /*req*/) noexcept
{
    return false;
}

} // ws_proto
} // boost
