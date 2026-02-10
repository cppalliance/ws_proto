//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/websocket
//

#ifndef BOOST_WEBSOCKET_IMPL_ERROR_HPP
#define BOOST_WEBSOCKET_IMPL_ERROR_HPP

#include <boost/system/error_category.hpp>
#include <boost/system/is_error_code_enum.hpp>
#include <type_traits>

namespace boost {

//-----------------------------------------------
namespace system {
template<>
struct is_error_code_enum<::boost::websocket::error>
{
    static bool const value = true;
};
} // system
//-----------------------------------------------

namespace websocket {

namespace detail {

struct BOOST_SYMBOL_VISIBLE
    error_cat_type
    : system::error_category
{
    BOOST_WEBSOCKET_DECL
    const char* name(
        ) const noexcept override;

    BOOST_WEBSOCKET_DECL
    std::string message(
        int) const override;

    BOOST_WEBSOCKET_DECL
    char const* message(
        int, char*, std::size_t
            ) const noexcept override;

    BOOST_WEBSOCKET_DECL
    system::error_condition
        default_error_condition(
            int code) const noexcept override;

    BOOST_SYSTEM_CONSTEXPR error_cat_type() noexcept
        : error_category(0xdfd293d97e2afb40)
    {
    }
};

BOOST_WEBSOCKET_DECL extern
    error_cat_type error_cat;

} // detail

inline
BOOST_SYSTEM_CONSTEXPR
system::error_code
make_error_code(
    error ev) noexcept
{
    return system::error_code{
        static_cast<std::underlying_type<
            error>::type>(ev),
        detail::error_cat};
}

} // websocket
} // boost

#endif