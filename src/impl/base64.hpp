//
// Copyright (c) 2016-2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_SRC_IMPL_BASE64_HPP
#define BOOST_WEBSOCKET_SRC_IMPL_BASE64_HPP

#include <cctype>
#include <utility>

namespace boost {
namespace websocket {

char const*
base64_alphabet() noexcept;

signed char const*
base64_inverse() noexcept;

/// Returns max chars needed to encode a base64 string
std::size_t
constexpr
base64_encoded_size(std::size_t n)
{
    return 4 * ((n + 2) / 3);
}

/// Returns max bytes needed to decode a base64 string
std::size_t
constexpr
base64_decoded_size(std::size_t n)
{
    return n / 4 * 3; // requires n&3==0, smaller
}

/** Encode a series of octets as a padded, base64 string.

    The resulting string will not be null terminated.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `encoded_size(len)` bytes.

    @return The number of characters written to `out`. This
    will exclude any null termination.
*/
std::size_t
base64_encode(void* dest, void const* src, std::size_t len);

/** Decode a padded base64 string into a series of octets.

    @par Requires

    The memory pointed to by `out` points to valid memory
    of at least `decoded_size(len)` bytes.

    @return The number of octets written to `out`, and
    the number of characters read from the input string,
    expressed as a pair.
*/
std::pair<std::size_t, std::size_t>
base64_decode(void* dest, char const* src, std::size_t len);

} // websocket
} // boost

#endif
