#ifndef TASTY_INT_TASTY_INT_DETAIL_VALUE_FROM_BASE_64_TOKEN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_VALUE_FROM_BASE_64_TOKEN_HPP

namespace tasty_int {
namespace detail {

/**
 * @brief Convert an ASCII character token into its Base36 value.
 *
 * @param[in] base_36_token an ASCII character token
 * @return the Base36 value associated with @p base_36_token or a negative
 *     value if @p base_36_token is not a Base36 token.
 */
int
value_from_base_64_token(char base_64_token);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_VALUE_FROM_BASE_64_TOKEN_HPP
