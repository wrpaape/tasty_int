#ifndef TASTY_INT_TASTY_INT_DETAIL_SIZE_DIGITS_FROM_NONNEGATIVE_FLOATING_POINT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_SIZE_DIGITS_FROM_NONNEGATIVE_FLOATING_POINT_HPP

#include<cstddef>


namespace tasty_int {
namespace detail {

/**
 * @brief Estimates the number of `digit_type`s required to represent @p value
 *     in base `DIGIT_BASE`.
 *
 * @param[in] value a nonnegative floating point value
 * @return the number of digits required to represent @p value
 *
 * @pre `std::isfinite(value) && (value >= 0.0)`
 */
std::size_t
size_digits_from_nonnegative_floating_point(long double value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_SIZE_DIGITS_FROM_NONNEGATIVE_FLOATING_POINT_HPP
