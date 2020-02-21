#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_FLOATING_POINT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_FLOATING_POINT_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Converts @p value to a little-endian sequence of digits.
 *
 * @param[in] value a non-negative, finite floating point value
 * @return little-endian representation of @p value in `digit_type`s
 *
 * @pre `std::isfinite(value) && (value >= 0.0)`
 */
std::vector<digit_type>
digits_from_floating_point(long double value);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_FLOATING_POINT_HPP
