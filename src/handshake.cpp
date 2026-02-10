//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#include <boost/websocket/handshake.hpp>
#include "src/impl/hybi13.hpp"

namespace boost {
namespace websocket {

system::result<bool>
is_upgrade(
    http::request const& /*req*/) noexcept
{
    return false;
}

http::request
make_upgrade(
    urls::url_view target)
{
    http::request req;
    req.set_start_line(
        http::method::get,
        target.buffer(),
        http::version::http_1_1);
    req.set(http::field::host, "host");
    req.set(http::field::connection, "Upgrade");
    req.set(http::field::upgrade, "websocket");

    detail::request_key key;
    detail::make_request_key(key);
    req.set(http::field::sec_websocket_key,
        core::string_view(key.data, key.size));
    req.set(http::field::sec_websocket_version, "13");

    /*
    this->build_request_pmd(req);
    decorator_opt(req);
    decorator(req);
    */

    return req;
}

} // websocket
} // boost
