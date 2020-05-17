#ifndef TASTY_INT_TASTY_INT_DETAIL_NEXT_POWER_OF_TWO_HPP
#define TASTY_INT_TASTY_INT_DETAIL_NEXT_POWER_OF_TWO_HPP

#include <cstdint>


namespace tasty_int {
namespace detail {

/**
 * @brief Advances @p value to the next power of two, `next_power`, s.t.
 *      
 *      next_power == 2^K
 *      2^(K-1) <= value < next_power
 *
 * @param[in] value a positive integer
 * @return the first power of two greater than @p value
 *
 * @pre `value > 0`
 * @pre `value < (1 << (std::numeric_limits<std::uintmax_t>::digits - 1))`
 */
std::uintmax_t
next_power_of_two(std::uintmax_t value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_NEXT_POWER_OF_TWO_HPP
