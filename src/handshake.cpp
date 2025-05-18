//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#include <boost/ws_proto/handshake.hpp>
#include "src/impl/hybi13.hpp"

namespace boost {
namespace ws_proto {

system::result<bool>
is_upgrade(
    http_proto::request_view const& /*req*/) noexcept
{
    return false;
}

http_proto::request
make_upgrade(
    urls::url_view target)
{
    http_proto::request req;
    req.set_start_line(
        http_proto::method::get,
        target.buffer(),
        http_proto::version::http_1_1);
    req.set(http_proto::field::host, "host");
    req.set(http_proto::field::connection, "Upgrade");
    req.set(http_proto::field::upgrade, "websocket");

    detail::request_key key;
    detail::make_request_key(key);
    req.set(http_proto::field::sec_websocket_key,
        core::string_view(key.data, key.size));
    req.set(http_proto::field::sec_websocket_version, "13");

    /*
    this->build_request_pmd(req);
    decorator_opt(req);
    decorator(req);
    */

    return req;
}

} // ws_proto
} // boost
