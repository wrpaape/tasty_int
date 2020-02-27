#include "tasty_int/detail/conversions/integral_from_digits.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::integral_from_digits;
using tasty_int::detail::conversions::digits_from_integral;


class IntegralFromDigitsTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class IntegralFromDigitsTest

TEST_P(IntegralFromDigitsTest, InitialValuePreserved)
{
    std::uintmax_t initial_value = GetParam();
    auto digits = digits_from_integral(initial_value);

    std::uintmax_t result = integral_from_digits(digits);

    EXPECT_EQ(initial_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntegralFromDigitsTest,
    IntegralFromDigitsTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

} // namespace
