#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_STRING_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_STRING_HPP

#include <string_view>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Converts @p tokens to a little-endian sequence of digits.
 *
 * @param[in] tokens a string of unsigned ASCII digits
 * @param[in] base   the numeric base/radix in which @p tokens is interpretted
 * @return the little-endian representation of @p tokens
 *
 * @throw std::invalid_argument if @p base is not a supported numeric
 *     base/radix
 * @throw std::invalid_argument if @p tokens contains an out-of-bounds token
 *     for @p base
 *
 * @pre @p base is a supported numeric base/radix
 * @pre @p tokens is not empty
 */
std::vector<digit_type>
digits_from_string(std::string_view tokens,
                   unsigned int     base);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_STRING_HPP
