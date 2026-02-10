//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_HANDSHAKE_HPP
#define BOOST_WEBSOCKET_HANDSHAKE_HPP

#include <boost/websocket/detail/config.hpp>
#include <boost/http/request.hpp>
#include <boost/http/request.hpp>
#include <boost/url/url_view.hpp>
#include <boost/system/result.hpp>

namespace boost {
namespace websocket {

/** Return true if the request is a valid Websocket Upgrade handshake.
*/
BOOST_WEBSOCKET_DECL
system::result<bool>
is_upgrade(
    http::request const& req) noexcept;

/** Return a Websocket Upgrade HTTP request
*/
BOOST_WEBSOCKET_DECL
http::request
make_upgrade(
    urls::url_view target);

} // websocket
} // boost

#endif
