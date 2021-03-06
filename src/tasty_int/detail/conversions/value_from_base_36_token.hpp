#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_VALUE_FROM_BASE_36_TOKEN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_VALUE_FROM_BASE_36_TOKEN_HPP

namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Convert an ASCII character token into its Base36 value.
 *
 * @param[in] base_36_token an ASCII character token
 * @return the Base36 value associated with @p base_36_token or a value greater
 *     than or equal to 36 if @p base_36_token is not a Base36 token
 */
unsigned int
value_from_base_36_token(char base_36_token);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_VALUE_FROM_BASE_36_TOKEN_HPP
