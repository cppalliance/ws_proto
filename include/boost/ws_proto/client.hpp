//
// Copyright (c) 2025 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_WS_PROTO_CLIENT_HPP
#define BOOST_WS_PROTO_CLIENT_HPP

#include <boost/ws_proto/detail/config.hpp>

namespace boost {
namespace ws_proto {

enum class frame_type
{
    ping,
    pong,
    close,
    cont,
    data
};

/** A WebSocket client
*/
class client
{
public:
    /** Add an outgoing frame
    */
    template<class ConstBufferSequence>
    bool
    write(
        frame_type kind,
        ConstBufferSequence const& payload);
};

} // ws_proto
} // boost

#endif
