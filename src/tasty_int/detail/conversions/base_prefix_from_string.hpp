#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_PREFIX_FROM_STRING_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_PREFIX_FROM_STRING_HPP

#include <string_view>


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * The class contains numeric base/radix information for parsing purposes.
 */
struct BasePrefix
{
    std::string_view::size_type prefix_length; ///< the length of the prefix
    unsigned int                base;          ///< the interpretted base
}; // struct BasePrefix

/**
 * @brief Attempts to extract information about the numeric base/radix of
 *     interpretation from the leading characters of @p tokens.
 *
 * @detail A leading "0b" or "0B" is considered binary. A leading '0' with at
 * least one other token is considered octal.  A leading "0x" or "0X" is
 * considered hexidecimal.  All other @p tokens are considered decimal.
 *
 * @param[in] tokens a string of ASCII tokens
 *
 * @return the interpretted BasePrefix
 */
BasePrefix
base_prefix_from_string(std::string_view tokens);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_PREFIX_FROM_STRING_HPP
