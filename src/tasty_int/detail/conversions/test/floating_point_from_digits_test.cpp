#include "tasty_int/detail/conversions/floating_point_from_digits.hpp"

#include <limits>
#include <string>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/conversions/digits_from_string.hpp"
#include "tasty_int_test/base_10_integer_string_from_arithmetic.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::floating_point_from_digits;
using tasty_int::detail::conversions::digits_from_floating_point;
using tasty_int::detail::conversions::digits_from_string;
using tasty_int_test::base_10_integer_string_from_arithmetic;


class FloatingPointFromDigitsTest : public ::testing::TestWithParam<long double>
{}; // class FloatingPointFromDigitsTest

TEST_P(FloatingPointFromDigitsTest, InitialValuePreserved)
{
    long double initial_value = GetParam();
    auto digits = digits_from_floating_point(initial_value);

    EXPECT_EQ(initial_value, floating_point_from_digits(digits));
}

INSTANTIATE_TEST_SUITE_P(
    FloatingPointFromDigitsTest,
    FloatingPointFromDigitsTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0, std::numeric_limits<long double>::max(), 1.0e20
    )
);


TEST(FloatingPointFromDigitsTest, OverflowProducesPositiveInfinity)
{
    std::string overflow_string =
        base_10_integer_string_from_arithmetic(
            std::numeric_limits<long double>::max()
        ) + '0';
    auto overflow_digits = digits_from_string(overflow_string, 10);

    EXPECT_EQ(std::numeric_limits<long double>::infinity(),
              floating_point_from_digits(overflow_digits));
}

} // namespace
