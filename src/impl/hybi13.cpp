//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#include "src/impl/hybi13.hpp"
#include "src/impl/base64.hpp"
#include "src/impl/prng.hpp"
#include "src/impl/sha1.hpp"
#include <boost/assert.hpp>

#include <cstdint>
#include <string>

namespace boost {
namespace websocket {
namespace detail {

void
make_request_key(
    request_key& key)
{
    auto g = make_prng(true);
    std::uint32_t a[4];
    for (auto& v : a)
        v = g();
    key.size = base64_encode(
        key.data, &a[0], sizeof(a));
}

void
make_response_key(
    response_key& out,
    core::string_view in)
{
    BOOST_ASSERT(in.size() <= request_key::capacity);
    core::string_view const guid(
        "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    sha1::context ctx;
    sha1::init(ctx);
    sha1::update(ctx, in.data(), in.size());
    sha1::update(ctx, guid.data(), guid.size());
    char digest[sha1::context::digest_size];
    sha1::finish(ctx, &digest[0]);
    out.size = base64_encode(
        out.data, &digest[0], sizeof(digest));
}

} // detail
} // websocket
} // boost

