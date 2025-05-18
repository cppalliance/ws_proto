//
// Copyright (c) 2016-2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_WS_PROTO_SRC_IMPL_HYBI13_HPP
#define BOOST_WS_PROTO_SRC_IMPL_HYBI13_HPP

#include <boost/core/detail/string_view.hpp>
#include "src/impl/base64.hpp"
#include <cstdint>

namespace boost {
namespace ws_proto {
namespace detail {

struct request_key
{
    static constexpr std::size_t capacity =
        base64_encoded_size(16);
    std::size_t size = 0;
    char data[capacity];
};

struct response_key
{
    static constexpr std::size_t capacity =
        base64_encoded_size(20);
    std::size_t size = 0;
    char data[capacity];
};

void make_request_key(
    request_key& out);

void make_response_key(
    response_key& out,
    core::string_view in);

} // detail
} // ws_proto
} // boost

#endif
