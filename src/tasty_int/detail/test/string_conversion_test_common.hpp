#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_STRING_CONVERSION_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_STRING_CONVERSION_TEST_COMMON_HPP

#include <iosfwd>
#include <string>
#include <string_view>
#include <utility>


namespace string_conversion_test_common {

/**
 * @defgroup TestParameters Test Parameters
 *
 * These structs bundle the arguments of the
 * tasty_int::detail::<result>_from_string() routines under test into a single
 * instance.
 */
/// @{
struct StringViewConversionTestParam
{
    unsigned int     base;   ///< the base of the test case tokens
    std::string_view tokens; ///< the test case string of ASCII digits
}; // struct StringViewConversionTestParam

struct StringConversionTestParam
{
    unsigned int base;   ///< the base of the test case tokens
    std::string  tokens; ///< the test case string of ASCII digits
}; // struct StringConversionTestParam
/// @}

/**
 * @defgroup TestParameterOutputOperators Test Parameter Output Operators
 *
 * @brief Outputs FromString(View)TestParam for diagnostic purposes.
 *
 * @param[in,out] output the output stream
 * @param[in]     test_param the StringViewConversionTestParam
 * @return a reference to @p output
 */
/// @{
std::ostream &
operator<<(std::ostream                        &output,
           const StringViewConversionTestParam &test_param);

std::ostream &
operator<<(std::ostream                    &output,
           const StringConversionTestParam &test_param);
/// @}

} // namespace string_conversion_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_STRING_CONVERSION_TEST_COMMON_HPP
