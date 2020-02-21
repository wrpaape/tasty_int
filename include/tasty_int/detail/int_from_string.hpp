#ifndef TASTY_INT_TASTY_INT_DETAIL_INT_FROM_STRING_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INT_FROM_STRING_HPP

#include <string_view>

#include "tasty_int/detail/int.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Constructs a new tasty_int::detail::Int from @p tokens.
 *
 * @detail Leading whitespace is ignored.  If @p base is zero, the correct
 *     base is determined from the leading characters a la
 *     tasty_int::detail::base_prefix_from_string().  If @p tokens has a prefix
 *     associated with @p base, then it will be ignored (i.e. `base=16
 *     tokens=0xdead` is interpretted as `base=16 tokens=dead`).
 *
 * @param[in] tokens a string of ASCII tokens representing sign, numerical
 *     digits, and an optional prefix.
 * @param[in] base   the numeric base/radix in which @p tokens is interpretted
 * @return the tasty_int::detail:Int representation of @p tokens
 *
 * @throw std::invalid_argument if @p tokens contains no digits
 * @throw std::invalid_argument if @p base is not a supported numerical base or
 *     zero.
 * @throw std::invalid_argument if input contains an out-of-bounds token for
 *     the provided (or interpretted) base
 */
Int
int_from_string(std::string_view tokens,
                unsigned int     base);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INT_FROM_STRING_HPP