#ifndef TASTY_INT_TASTY_INT_DETAIL_FLOATING_POINT_FROM_DIGITS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FLOATING_POINT_FROM_DIGITS_HPP

#include <cstdint>

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Retrieve the floating-point value of @p digits.
 *
 * @brief If the value of @p digits is larger than what can be represented by
 *    long double, the result is positive infinity.
 *
 * @param[in] digits a little-endian sequence of digits
 * @return the floating-point value of @p digits
 *
 * @pre @p digits is not empty
 */
long double
floating_point_from_digits(const std::vector<digit_type> &digits);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FLOATING_POINT_FROM_DIGITS_HPP
