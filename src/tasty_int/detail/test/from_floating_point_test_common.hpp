#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_FLOATING_POINT_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_FLOATING_POINT_TEST_COMMON_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace from_floating_point_test_common {

/**
 * @brief testing utility for checking that @p digits are equivalent @p
 *     expected.
 *
 * @param[in] expected the expected nonnegative floating point value
 * @param[in] digits   the little-endian positional notation representation of
 *     a floating point number
 */
void
expect_digits_equal(long double                                       expected,
                    const std::vector<tasty_int::detail::digit_type> &digits);

} // namespace from_floating_point_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_FROM_FLOATING_POINT_TEST_COMMON_HPP
