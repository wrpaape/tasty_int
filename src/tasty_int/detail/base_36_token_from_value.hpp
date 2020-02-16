#ifndef TASTY_INT_TASTY_INT_DETAIL_BASE_36_TOKEN_FROM_VALUE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_BASE_36_TOKEN_FROM_VALUE_HPP

namespace tasty_int {
namespace detail {

/**
 * @brief Convert a Base36 value into its associated ASCII character.
 *
 * @param[in] value an integer in the range [0, 36)
 * @return the ASCII character token associated with @p value.
 *
 * @pre `0 <= value < 36`
 */
char
base_36_token_from_value(unsigned int value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_BASE_36_TOKEN_FROM_VALUE_HPP
