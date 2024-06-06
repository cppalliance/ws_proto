//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/ws_proto
//

#ifndef BOOST_WS_PROTO_DETAIL_CONFIG_HPP
#define BOOST_WS_PROTO_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#include <stdint.h>

namespace boost {

namespace ws_proto {

//------------------------------------------------

# if (defined(BOOST_WS_PROTO_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_WS_PROTO_STATIC_LINK)
#  if defined(BOOST_WS_PROTO_SOURCE)
#   define BOOST_WS_PROTO_DECL        BOOST_SYMBOL_EXPORT
#   define BOOST_WS_PROTO_BUILD_DLL
#  else
#   define BOOST_WS_PROTO_DECL        BOOST_SYMBOL_IMPORT
#  endif

#  if defined(BOOST_WS_PROTO_ZLIB_SOURCE)
#   define BOOST_WS_PROTO_ZLIB_DECL   BOOST_SYMBOL_EXPORT
#   define BOOST_WS_PROTO_ZLIB_BUILD_DLL
#  else
#   define BOOST_WS_PROTO_ZLIB_DECL   BOOST_SYMBOL_IMPORT
#  endif

#  if defined(BOOST_WS_PROTO_EXT_SOURCE)
#   define BOOST_WS_PROTO_EXT_DECL   BOOST_SYMBOL_EXPORT
#   define BOOST_WS_PROTO_EXT_BUILD_DLL
#  else
#   define BOOST_WS_PROTO_EXT_DECL   BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib

# ifndef  BOOST_WS_PROTO_DECL
#  define BOOST_WS_PROTO_DECL
# endif

# ifndef  BOOST_WS_PROTO_ZLIB_DECL
#  define BOOST_WS_PROTO_ZLIB_DECL
# endif

# ifndef  BOOST_WS_PROTO_EXT_DECL
#  define BOOST_WS_PROTO_EXT_DECL
# endif

# if !defined(BOOST_WS_PROTO_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_WS_PROTO_NO_LIB)
#  define BOOST_LIB_NAME boost_ws_proto
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_WS_PROTO_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif

//------------------------------------------------

// Add source location to error codes
#ifdef BOOST_WS_PROTO_NO_SOURCE_LOCATION
# define BOOST_WS_PROTO_ERR(ev) (::boost::system::error_code(ev))
# define BOOST_WS_PROTO_RETURN_EC(ev) return (ev)
#else
# define BOOST_WS_PROTO_ERR(ev) ( \
    ::boost::system::error_code( (ev), [] { \
    static constexpr auto loc((BOOST_CURRENT_LOCATION)); \
    return &loc; }()))
# define BOOST_WS_PROTO_RETURN_EC(ev)                                  \
    do {                                                                 \
        static constexpr auto loc ## __LINE__((BOOST_CURRENT_LOCATION)); \
        return ::boost::system::error_code((ev), &loc ## __LINE__);      \
    } while(0)
#endif

} // ws_proto

} // boost

#endif
