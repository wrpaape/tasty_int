#ifndef TASTY_INT_TASTY_INT_DETAIL_INT_FROM_FLOATING_POINT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INT_FROM_FLOATING_POINT_HPP

#include "tasty_int/detail/int.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief constructs a new tasty_int::detail::Int from @p value
 *
 * @param[in] value a floating point value
 * @return the tasty_int::detail:Int representation of @p value
 */
Int
int_from_floating_point(long double value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INT_FROM_FLOATING_POINT_HPP
