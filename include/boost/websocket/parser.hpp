//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_PARSER_HPP
#define BOOST_WEBSOCKET_PARSER_HPP

#include <boost/websocket/detail/config.hpp>
#include <stdexcept>

namespace boost {
namespace websocket {

class parser
{
public:
    BOOST_WEBSOCKET_DECL
    explicit
    parser(
        std::size_t n);

    BOOST_WEBSOCKET_DECL
    ~parser();


};

} // websocket
} // boost

#endif
