#include "tasty_int/detail/integral_digits_view.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::IntegralDigitsView;
using tasty_int::detail::digit_from_nonnegative_value;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_TYPE_BITS;


class IntegralDigitsViewTest : public :: testing::TestWithParam<std::uintmax_t>
{}; // class IntegralDigitsViewTest

TEST_P(IntegralDigitsViewTest, LowDigit)
{
    std::uintmax_t value = GetParam();

    IntegralDigitsView view(value);

    EXPECT_EQ(digit_from_nonnegative_value(value), view.low_digit());
}

TEST_P(IntegralDigitsViewTest, HighDigit)
{
    std::uintmax_t value = GetParam();

    IntegralDigitsView view(value);

    EXPECT_EQ(digit_from_nonnegative_value(value >> DIGIT_TYPE_BITS),
              view.high_digit());
}

TEST_P(IntegralDigitsViewTest, DigitsSize)
{
    std::uintmax_t value                = GetParam();
    std::size_t    expected_digits_size = (value <= DIGIT_TYPE_MAX) ? 1 : 2;

    IntegralDigitsView view(value);

    EXPECT_EQ(expected_digits_size, view.digits_size());
}

INSTANTIATE_TEST_SUITE_P(
    IntegralDigitsViewTest,
    IntegralDigitsViewTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

} // namespace
