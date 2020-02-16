#ifndef TASTY_INT_TASTY_INT_DETAIL_VALUE_FROM_BASE_64_TOKEN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_VALUE_FROM_BASE_64_TOKEN_HPP

namespace tasty_int {
namespace detail {

/**
 * @brief Convert an ASCII character token into its Base64 value.
 *
 * @param[in] base_64_token an ASCII character token
 * @return the Base64 value associated with @p base_64_token or a value greater
 *     than or equal to 64 if @p base_64_token is not a Base64 token
 */
unsigned int
value_from_base_64_token(char base_64_token);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_VALUE_FROM_BASE_64_TOKEN_HPP
