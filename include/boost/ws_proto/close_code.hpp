//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_WS_PROTO_CLOSE_CODE_HPP
#define BOOST_WS_PROTO_CLOSE_CODE_HPP

#include <boost/ws_proto/detail/config.hpp>
#include <cstdint>

namespace boost {
namespace ws_proto {

/** Close status codes.

    These codes accompany close frames.

    @see <a href="https://tools.ietf.org/html/rfc6455#section-7.4.1">RFC 6455 7.4.1 Defined Status Codes</a>
*/
enum close_code : std::uint16_t
{
    /// Normal closure; the connection successfully completed whatever purpose for which it was created.
    normal          = 1000,

    /// The endpoint is going away, either because of a server failure or because the browser is navigating away from the page that opened the connection.
    going_away      = 1001,

    /// The endpoint is terminating the connection due to a protocol error.
    protocol_error  = 1002,

    /// The connection is being terminated because the endpoint received data of a type it cannot accept (for example, a text-only endpoint received binary data).
    unknown_data    = 1003,

    /// The endpoint is terminating the connection because a message was received that contained inconsistent data (e.g., non-UTF-8 data within a text message).
    bad_payload     = 1007,

    /// The endpoint is terminating the connection because it received a message that violates its policy. This is a generic status code, used when codes 1003 and 1009 are not suitable.
    policy_error    = 1008,

    /// The endpoint is terminating the connection because a data frame was received that is too large.
    too_big         = 1009,

    /// The client is terminating the connection because it expected the server to negotiate one or more extension, but the server didn't.
    needs_extension = 1010,

    /// The server is terminating the connection because it encountered an unexpected condition that prevented it from fulfilling the request.
    internal_error  = 1011,

    /// The server is terminating the connection because it is restarting.
    service_restart = 1012,

    /// The server is terminating the connection due to a temporary condition, e.g. it is overloaded and is casting off some of its clients.
    try_again_later = 1013,

    //----
    //
    // The following are illegal on the wire
    //

    /** Used internally to mean "no error"

        This code is reserved and may not be sent.
    */
    none            = 0,

    /** Reserved for future use by the WebSocket standard.

        This code is reserved and may not be sent.
    */
    reserved1       = 1004,

    /** No status code was provided even though one was expected.

        This code is reserved and may not be sent.
    */
    no_status       = 1005,

    /** Connection was closed without receiving a close frame
        
        This code is reserved and may not be sent.
    */
    abnormal        = 1006,

    /** Reserved for future use by the WebSocket standard.
        
        This code is reserved and may not be sent.
    */
    reserved2       = 1014,

    /** Reserved for future use by the WebSocket standard.
       
        This code is reserved and may not be sent.
    */
    reserved3       = 1015

    //
    //----

    //last = 5000 // satisfy warnings
};

} // ws_proto
} // boost

#endif
