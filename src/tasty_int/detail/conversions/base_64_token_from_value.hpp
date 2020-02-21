#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_64_TOKEN_FROM_VALUE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_64_TOKEN_FROM_VALUE_HPP

namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Convert a Base64 value into its associated ASCII character.
 *
 * @param[in] value an integer in the range [0, 64)
 * @return the ASCII character token associated with @p value.
 *
 * @pre `0 <= value < 64`
 */
char
base_64_token_from_value(unsigned int value);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_64_TOKEN_FROM_VALUE_HPP
