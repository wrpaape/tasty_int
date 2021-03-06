#ifndef TASTY_INT_TASTY_INT_DETAIL_SIGNED_INTEGRAL_FROM_INTEGER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_SIGNED_INTEGRAL_FROM_INTEGER_HPP

#include <cstdint>

#include "tasty_int/detail/integer.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Retrieves the integral value of @p integer.
 *
 * @details If the value of @p integer lies outside the bounds of what can be
 *    represented by std::intmax_t, the result is truncated to the
 *    least-significant `sizeof(std::uintmax_t)` bytes.
 *
 * @param[in] integer an arbitrary-precision integer
 * @return the integral value of @p integer
 *
 * @pre @p integer has a valid sign and at least one digit
 */
std::intmax_t
signed_integral_from_integer(const Integer &integer);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_SIGNED_INTEGRAL_FROM_INTEGER_HPP
