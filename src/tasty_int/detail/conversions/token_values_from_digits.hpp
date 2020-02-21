#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_STRING_FROM_DIGITS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_STRING_FROM_DIGITS_HPP

#include <string>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * Converts @p digits to base @p base token values
 *
 * @param[in]  digits       a little-endian sequence of digits
 * @param[in]  base         the desired numeric base/radix of the output
 * @param[out] token_values @p digits converted to base @base
 *
 * @pre @p digits is not empty
 * @pre `(base >= 2) && (base <= (std::numeric_limits<char>::max() + 1))`
 * @pre @p token_values is empty
 */
void
token_values_from_digits(const std::vector<digit_type> &digits,
                         unsigned int                   base,
                         std::string                   &token_values);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_STRING_FROM_DIGITS_HPP
