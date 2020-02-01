#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_STRING_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_STRING_TEST_COMMON_HPP

#include <iosfwd>
#include <string_view>
#include <utility>


namespace from_string_test_common {

/**
 * This struct bundles the arguments of the
 * tasty_int::detail::<result>_from_string() routines under test into a single
 * instance.
 */
struct FromStringTestParam
{
    unsigned int     base;   ///< the base of the test case tokens
    std::string_view tokens; ///< the test case string of ASCII digits
}; // struct FromStringTestParam

/**
 * Outputs the FromStringTestParam for diagnostic purposes.
 */
std::ostream &
operator<<(std::ostream              &output,
           const FromStringTestParam &test_param);
/// @}

} // namespace from_string_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_STRING_TEST_COMMON_HPP
