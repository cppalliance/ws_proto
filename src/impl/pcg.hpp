//
// Copyright (c) 2016-2025 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_SRC_IMPL_PCG_HPP
#define BOOST_WEBSOCKET_SRC_IMPL_PCG_HPP

#include <boost/core/ignore_unused.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace websocket {
namespace detail {

class pcg
{
    std::uint64_t state_ = 0;
    std::uint64_t increment_;

public:
    using result_type = std::uint32_t;

    // Initialize the generator.
    // There are no restrictions on the input values.
    pcg(
        std::uint64_t seed,
        std::uint64_t stream)
    {
        // increment must be odd
        increment_ = 2 * stream + 1;
        boost::ignore_unused((*this)());
        state_ += seed;
        boost::ignore_unused((*this)());
    }

    std::uint32_t
    operator()()
    {
        std::uint64_t const p = state_;
        state_ = p *
            6364136223846793005ULL +
            increment_;
        std::uint32_t const x =
            static_cast<std::uint32_t>(
            ((p >> 18) ^ p) >> 27);
        std::uint32_t const r = p >> 59;
    #ifdef BOOST_MSVC
        return _rotr(x, r);
    #else
        return (x >> r) | (x << ((1 + ~r) & 31));
    #endif
    }
};

} // detail
} // websocket
} // boost

#endif
