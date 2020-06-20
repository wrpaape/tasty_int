#ifndef TASTY_INT_TASTY_INT_TEST_TASTY_INT_ARITHMETIC_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_TEST_TASTY_INT_ARITHMETIC_TEST_COMMON_HPP

#include <cmath>

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/concepts.hpp"
#include "tasty_int_test/expect_approx.hpp"


/**
 * This namespace encapsulates utilities common to tests involving TastyInt
 * arithmetic.
 */
namespace tasty_int_arithmetic_test_common {

/**
 * @defgroup CheckTastyIntResult Check TastyInt Result
 *
 * These assertions check an arithmetic operation @p result for equality with
 * @p expected_result.  A nonfatal google test failure and diagnostic error
 * message is emitted if the input parameters do not compare equal.
 */
/// @{
template<tasty_int::FloatingPoint FloatingPointType>
void
check_tasty_int_result(FloatingPointType  expected_result,
                       FloatingPointType  result,
                       const char        *operation)
{
    EXPECT_APPROX(
        std::trunc(expected_result),
        std::trunc(result),
        operation << " did not produce expected result"
    );
}

template<typename ExpectedResultType,
         typename ResultType>
void
check_tasty_int_result(const ExpectedResultType &expected_result,
                       const ResultType         &result,
                       const char               *operation)
{
    EXPECT_EQ(expected_result, result)
        << operation << " did not produce expected result";
}
/// @}

} // namespace tasty_int_arithmetic_test_common

#endif // ifndef TASTY_INT_TASTY_INT_TEST_TASTY_INT_ARITHMETIC_TEST_COMMON_HPP
