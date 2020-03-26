#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_INTEGER_FROM_FLOATING_POINT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_INTEGER_FROM_FLOATING_POINT_HPP

#include "tasty_int/detail/integer.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief constructs a new tasty_int::detail::Integer from @p value
 *
 * @param[in] value a floating point value
 * @return the tasty_int::detail::Integer representation of @p value
 *
 * @pre `std::isfinite(value) && (value >= 0.0)`
 */
Integer
integer_from_floating_point(long double value);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_INTEGER_FROM_FLOATING_POINT_HPP
