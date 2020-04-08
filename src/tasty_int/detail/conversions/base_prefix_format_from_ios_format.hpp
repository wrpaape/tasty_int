#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_PREFIX_FORMAT_FROM_IOS_FORMAT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_PREFIX_FORMAT_FROM_IOS_FORMAT_HPP

#include <ios>
#include <string_view>


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * The class contains numeric base/radix format information for outputting
 * purposes.
 */
struct BasePrefixFormat
{
    unsigned int     base;             ///< the output base
    std::string_view nonnegative_sign; ///< the representation of Sign::POSITIVE
    std::string_view prefix;           ///< the prefix
}; // struct BasePrefixFormat

/**
 * @brief Extracts information about the numeric base/radix of interpretation
 *     and corresponding prefix string from a set of ios format flags.
 *
 * @param[in] format the result of std::ios_base::format()
 *
 * @return the associated BasePrefixFormat
 */
BasePrefixFormat
base_prefix_format_from_ios_format(std::ios_base::fmtflags format);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_BASE_PREFIX_FORMAT_FROM_IOS_FORMAT_HPP
