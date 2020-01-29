#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_INT_FROM_INTEGRAL_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_INT_FROM_INTEGRAL_TEST_COMMON_HPP

#include <cstdint>

#include <vector>

#include "tasty_int/detail/digit_type.hpp"
#include "tasty_int/detail/int.hpp"


namespace int_from_integral_test_common {

/**
 * @brief testing utility for checking that @p digits are equivalent @p
 *     expected.
 *
 * @param[in] expected the expected unsigned integer value
 * @param[in] digits   the little-endian positional notation representation of
 *     an unsigned integer
 */
void
expect_digits_equal(std::uintmax_t                                    expected,
                    const std::vector<tasty_int::detail::digit_type> &digits);

/**
 * @brief testing utility for checking that @p actual is equivalent to zero.
 *
 * @param[in] actual the tasty_int::detail::Int instance under test
 */
void
expect_int_equals_zero(const tasty_int::detail::Int &actual);

/**
 * @brief testing utility for checking that @p actual is equivalent to @p
 *     expected.
 *
 * @param[in] expected the expected unsigned integer value
 * @param[in] actual   the tasty_int::detail::Int instance under test
 */
void
expect_positive_int_equals(std::uintmax_t                expected,
                           const tasty_int::detail::Int &actual);

} // namespace int_from_integral_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_INT_FROM_INTEGRAL_TEST_COMMON_HPP
