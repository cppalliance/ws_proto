//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_WS_PROTO_HANDSHAKE_HPP
#define BOOST_WS_PROTO_HANDSHAKE_HPP

#include <boost/ws_proto/detail/config.hpp>
#include <boost/http_proto/request.hpp>
#include <boost/http_proto/request_view.hpp>
#include <boost/url/url_view.hpp>
#include <boost/system/result.hpp>

namespace boost {
namespace ws_proto {

/** Return true if the request is a valid Websocket Upgrade handshake.
*/
BOOST_WS_PROTO_DECL
system::result<bool>
is_upgrade(
    http_proto::request_view const& req) noexcept;

BOOST_WS_PROTO_DECL
http_proto::request
make_upgrade(
    urls::url_view target);

} // ws_proto
} // boost

#endif
