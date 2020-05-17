#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_FLOATING_POINT_FROM_INTEGER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_FLOATING_POINT_FROM_INTEGER_HPP

#include "tasty_int/detail/integer.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Retrieves the floating-point value of @p integer.
 *
 * @details If the value of @p integer is larger than what can be represented by
 *    long double, the result is +/- infinity.
 *
 * @param[in] integer an arbitrary-precision integer
 * @return the floating-point value of @p integer
 *
 * @pre @p integer has a valid sign and at least one digit
 */
long double
floating_point_from_integer(const Integer &integer);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_FLOATING_POINT_FROM_INTEGER_HPP
