#ifndef TASTY_INT_TASTY_INT_TEST_BASE_10_INTEGER_STRING_FROM_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_TEST_BASE_10_INTEGER_STRING_FROM_ARITHMETIC_HPP

#include <iomanip>
#include <sstream>
#include <type_traits>

#include "tasty_int_test/make_arithmetic_printable.hpp"


namespace tasty_int_test {

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
                   << make_arithmetic_printable(value);

    return base_10_string.str();
}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_BASE_10_INTEGER_STRING_FROM_ARITHMETIC_HPP
