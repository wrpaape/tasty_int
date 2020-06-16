#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_INTEGER_ARITHMETIC_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_INTEGER_ARITHMETIC_TEST_COMMON_HPP

#include <cstdint>

#include "tasty_int/detail/integer.hpp"

/**
 * This namespace encapsulates utilities common to tests involving integer
 * arithmetic.
 */
namespace integer_arithmetic_test_common {

/**
 * @defgroup CheckExpectedIntegerResult Check Expected Integer Result
 *
 * These assertions check an arithmetic operation @p result for equality with
 * @p expected_result.  A nonfatal google test failure and diagnostic error
 * message is emitted if the input parameters do not compare equal.
 */
/// @{
void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              const tasty_int::detail::Integer &result);
void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              std::uintmax_t                    result);
void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              std::intmax_t                     result);
void
check_expected_integer_result(const tasty_int::detail::Integer &expected_result,
                              long double                       result);
/// @}

} // namespace integer_arithmetic_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_INTEGER_ARITHMETIC_TEST_COMMON_HPP
