#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_FROM_STRING_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_FROM_STRING_HPP

#include <string_view>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief constructs a little-endian sequence of digits from @p tokens.
 *
 * @param[in] tokens a string of unsigned ASCII digits
 * @param[in] base   the numeric base/radix in which @p tokens is interpretted
 * @return the little-endian representation of @p tokens
 */
std::vector<digit_type>
digits_from_string(std::string_view tokens,
                   unsigned int     base);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_FROM_STRING_HPP
