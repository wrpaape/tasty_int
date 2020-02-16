#ifndef TASTY_INT_TASTY_INT_DETAIL_STRING_FROM_DIGITS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_STRING_FROM_DIGITS_HPP

#include <string>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * Converts @p digits to string representation.
 *
 * @param[in] digits the little-endian sequence of digits
 * @param[in] base   the desired numeric base/radix of the output
 * @return the string representation of @p digits in base @p base
 */
std::string
string_from_digits(const std::vector<digit_type> &digits,
                   unsigned int                   base);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_STRING_FROM_DIGITS_HPP
