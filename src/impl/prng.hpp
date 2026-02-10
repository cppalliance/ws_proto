//
// Copyright (c) 2016-2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_SRC_IMPL_PRNG_HPP
#define BOOST_WEBSOCKET_SRC_IMPL_PRNG_HPP

#include <boost/config.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace websocket {
namespace detail {

using generator = std::uint32_t(*)();

//------------------------------------------------------------------------------

// Manually seed the prngs, must be called
// before acquiring a prng for the first time.
//
std::uint32_t const*
prng_seed(std::seed_seq* ss = nullptr);

// Acquire a PRNG using the TLS implementation if it
// is available, otherwise using the no-TLS implementation.
//
generator
make_prng(bool secure);

} // detail
} // websocket
} // boost

#endif
