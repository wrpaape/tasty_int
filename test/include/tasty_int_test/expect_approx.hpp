#ifndef TASTY_INT_TEST_EXPECT_APPROX_HPP
#define TASTY_INT_TEST_EXPECT_APPROX_HPP

#include "tasty_int_test/approximately_equal.hpp"

#include <cmath>

#include <iomanip>
#include <limits>
#include <type_traits>

#include "gtest/gtest.h"


/**
 * @brief Generates a nonfatal google test failure and diagnostic error message
 *     unless any of the following are true:
 *     
 *     1. @p expected and @p actual are both infinity and have the same sign
 *     2. @p expected and @p actual are both nans
 *     3. tasty_int_test::approximately_equal(expected, actual)
 *
 * @param[in] expected the expected floating point value
 * @param[in] actual   the actual floating point value
 */
#define EXPECT_APPROX(expected, actual)                               \
do {                                                                  \
    auto &&_expected = (expected);                                    \
    auto &&_actual   = (actual);                                      \
    auto _both_nan = std::isnan(_expected) && std::isnan(_actual);    \
    auto _both_same_sign_infinity =                                   \
        (std::signbit(_expected) == std::signbit(_actual)) &&         \
        std::isinf(_expected) &&                                      \
        std::isinf(_actual);                                          \
    EXPECT_TRUE(                                                      \
        _both_nan ||                                                  \
        _both_same_sign_infinity ||                                   \
        tasty_int_test::approximately_equal(_expected, _actual)       \
    )                                                                 \
        << "    Expected: "                                           \
        << std::setprecision(                                         \
               std::numeric_limits<decltype(_expected)>::max_digits10 \
            ) << _expected << " (" #expected ")\n"                    \
        << "      Actual: "                                           \
        << std::setprecision(                                         \
               std::numeric_limits<decltype(_actual)>::max_digits10   \
           ) << _actual << " (" #actual ")\n";                        \
} while (0)

#endif // ifndef TASTY_INT_TEST_EXPECT_APPROX_HPP
