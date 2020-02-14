#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_USER_TYPE_INTEGRATION_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_USER_TYPE_INTEGRATION_TEST_COMMON_HPP

#include <iomanip>
#include <sstream>
#include <type_traits>


namespace from_user_type_integration_test_common {

/**
 * @brief Converts an arithmetic value to its base 10 integer string
 *     representation.
 *
 * @tparam ArithmeticType an arithmetic type
 * @param[in] value an arithmetic value
 * @return the base 10 integer string representation of value truncated to the
 *     nearest integer
 */
template<typename ArithmeticType>
    requires std::is_arithmetic_v<ArithmeticType>
std::string
base_10_integer_string_from_arithmetic(ArithmeticType value)
{
    std::ostringstream base_10_string;

    base_10_string << std::setbase(10)
                   << std::fixed
                   << std::setprecision(0)
                   << value;

    return base_10_string.str();
}

} // namespace from_user_type_integration_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_USER_TYPE_INTEGRATION_TEST_COMMON_HPP
