#ifndef TASTY_INT_DETAIL_TRIM_TRAILING_ZERO_HPP
#define TASTY_INT_DETAIL_TRIM_TRAILING_ZERO_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Remove the most-significant digit from @p digits if it is zero.
 *
 * @details This operation is common for routines that build digits from
 *     floating-point values, which may result in an (invalid) digits sequence
 *     with a zero in the most-significant position due to truncation.
 *
 * @param[in] digits a little-endian sequence of digits
 */
void
trim_trailing_zero(std::vector<digit_type> &digits);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_DETAIL_TRIM_TRAILING_ZERO_HPP
