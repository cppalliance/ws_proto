//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_DETAIL_CONFIG_HPP
#define BOOST_WEBSOCKET_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#include <stdint.h>

namespace boost {

namespace websocket {

//------------------------------------------------

# if (defined(BOOST_WEBSOCKET_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_WEBSOCKET_STATIC_LINK)
#  if defined(BOOST_WEBSOCKET_SOURCE)
#   define BOOST_WEBSOCKET_DECL        BOOST_SYMBOL_EXPORT
#   define BOOST_WEBSOCKET_BUILD_DLL
#  else
#   define BOOST_WEBSOCKET_DECL        BOOST_SYMBOL_IMPORT
#  endif

#  if defined(BOOST_WEBSOCKET_ZLIB_SOURCE)
#   define BOOST_WEBSOCKET_ZLIB_DECL   BOOST_SYMBOL_EXPORT
#   define BOOST_WEBSOCKET_ZLIB_BUILD_DLL
#  else
#   define BOOST_WEBSOCKET_ZLIB_DECL   BOOST_SYMBOL_IMPORT
#  endif

#  if defined(BOOST_WEBSOCKET_EXT_SOURCE)
#   define BOOST_WEBSOCKET_EXT_DECL   BOOST_SYMBOL_EXPORT
#   define BOOST_WEBSOCKET_EXT_BUILD_DLL
#  else
#   define BOOST_WEBSOCKET_EXT_DECL   BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib

# ifndef  BOOST_WEBSOCKET_DECL
#  define BOOST_WEBSOCKET_DECL
# endif

# ifndef  BOOST_WEBSOCKET_ZLIB_DECL
#  define BOOST_WEBSOCKET_ZLIB_DECL
# endif

# ifndef  BOOST_WEBSOCKET_EXT_DECL
#  define BOOST_WEBSOCKET_EXT_DECL
# endif

# if !defined(BOOST_WEBSOCKET_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_WEBSOCKET_NO_LIB)
#  define BOOST_LIB_NAME boost_websocket
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_WEBSOCKET_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif

//------------------------------------------------

// Add source location to error codes
#ifdef BOOST_WEBSOCKET_NO_SOURCE_LOCATION
# define BOOST_WEBSOCKET_ERR(ev) (::boost::system::error_code(ev))
# define BOOST_WEBSOCKET_RETURN_EC(ev) return (ev)
#else
# define BOOST_WEBSOCKET_ERR(ev) ( \
    ::boost::system::error_code( (ev), [] { \
    static constexpr auto loc((BOOST_CURRENT_LOCATION)); \
    return &loc; }()))
# define BOOST_WEBSOCKET_RETURN_EC(ev)                                  \
    do {                                                                 \
        static constexpr auto loc ## __LINE__((BOOST_CURRENT_LOCATION)); \
        return ::boost::system::error_code((ev), &loc ## __LINE__);      \
    } while(0)
#endif

} // websocket

} // boost

#endif
