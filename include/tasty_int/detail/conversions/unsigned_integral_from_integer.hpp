#ifndef TASTY_INT_TASTY_INT_DETAIL_UNSIGNED_INTEGRAL_FROM_INTEGER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_UNSIGNED_INTEGRAL_FROM_INTEGER_HPP

#include <cstdint>

#include "tasty_int/detail/integer.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Retrieve the integral value of @p integer.
 *
 * @brief If the value of @p integer lies outside the bounds of what can be
 *    represented by std::uintmax_t, the result is truncated to the
 *    least-significant `sizeof(std::uintmax_t)` bytes.
 *
 * @param[in] integer an arbitrary-precision integer
 * @return the integral value of @p integer
 *
 * @pre @p digits is not empty
 */
std::uintmax_t
unsigned_integral_from_integer(const Integer &integer);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_UNSIGNED_INTEGRAL_FROM_INTEGER_HPP
