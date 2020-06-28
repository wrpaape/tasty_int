#ifndef TASTY_INT_TASTY_INT_TEST_CHECK_INTEGER_RESULT_HPP
#define TASTY_INT_TASTY_INT_TEST_CHECK_INTEGER_RESULT_HPP

#include <cmath>

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/expect_approx.hpp"


namespace tasty_int_test {

/**
 * @defgroup CheckIntegerResult Check Integer Result
 *
 * These assertions check the integer @p result of an arithmetic operation for
 * integer-equality with @p expected_result.  A nonfatal google test failure
 * and diagnostic error message is emitted if the input parameters do not
 * compare equal.
 *
 * @param[in] expected_result the expected operation result
 * @param[in] result          the actual operation result
 * @param[in] operation       a name that identifies the operation under test
 */
/// @{
template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
void
check_integer_result(FloatingPointType  expected_result,
                     FloatingPointType  result,
                     const char        *operation)
{
    EXPECT_APPROX(
        std::trunc(expected_result),
        std::trunc(result),
        << operation << " did not produce expected result"
    );
}

template<typename ExpectedResultType,
         typename ResultType>
void
check_integer_result(const ExpectedResultType &expected_result,
                     const ResultType         &result,
                     const char               *operation)
{
    EXPECT_EQ(expected_result, result)
        << operation << " did not produce expected result";
}
/// @}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_CHECK_INTEGER_RESULT_HPP
