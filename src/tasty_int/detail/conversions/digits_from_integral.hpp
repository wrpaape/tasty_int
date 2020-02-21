#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_INTEGRAL_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_INTEGRAL_HPP

#include <cstdint>

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Converts @p value to a little-endian sequence of digits.
 *
 * @param[in] value an unsigned integer value
 * @return little-endian representation of @p value in `digit_type`s
 */
std::vector<digit_type>
digits_from_integral(std::uintmax_t value);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_DIGITS_FROM_INTEGRAL_HPP
