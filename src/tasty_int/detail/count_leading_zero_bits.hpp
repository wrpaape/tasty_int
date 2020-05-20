#ifndef TASTY_INT_TASTY_INT_DETAIL_COUNT_LEADING_ZERO_BITS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_COUNT_LEADING_ZERO_BITS_HPP

#include <cstdint>


namespace tasty_int {
namespace detail {

/**
 * @brief Counts the number of 0-bits beyond the most-significant 1-bit:
 *      
 *      3 == count_leading_zero_bits(000101...0b)
 *      0 == count_leading_zero_bits(100101...0b)
 *
 * @param[in] value a positive integer
 * @return the number of leading 0-bits in @p value
 *
 * @pre `value > 0`
 */
std::uintmax_t
count_leading_zero_bits(std::uintmax_t value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_COUNT_LEADING_ZERO_BITS_HPP
