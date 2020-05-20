#ifndef TASTY_INT_TASTY_INT_TEST_NONNEGATIVE_ARITHMETIC_VALUES_HPP
#define TASTY_INT_TASTY_INT_TEST_NONNEGATIVE_ARITHMETIC_VALUES_HPP

#include <array>
#include <limits>
#include <type_traits>


namespace tasty_int_test {

/**
 * A collection of desirable test values for functions that take arithmetic
 * types of arbitrary nonnegative value as input.
 */
template<typename ArithmeticType>
    requires std::is_arithmetic_v<ArithmeticType>
const std::array<ArithmeticType, 5> NONNEGATIVE_ARITHMETIC_VALUES = {
    ArithmeticType(0),
    std::numeric_limits<ArithmeticType>::min(),
    ArithmeticType(1), 
    std::numeric_limits<ArithmeticType>::max() / ArithmeticType(2),
    std::numeric_limits<ArithmeticType>::max()
};

} // tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_NONNEGATIVE_ARITHMETIC_VALUES_HPP
