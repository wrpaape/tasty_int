#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/conversions/digits_from_string.hpp"

#include "gtest/gtest.h"

#include "tasty_int_test/base_10_integer_string_from_arithmetic.hpp"
#include "tasty_int_test/floating_point_integral_limits.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::digits_from_floating_point;
using tasty_int::detail::conversions::digits_from_string;
using tasty_int_test::base_10_integer_string_from_arithmetic;
using tasty_int_test::FloatingPointIntegralLimits;


class SameIntegralValueTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class SameIntegralValueTest

TEST_P(SameIntegralValueTest, SameDigitsFromIntegralAndFloatingPoint)
{
    std::uintmax_t integral_value = GetParam();
    auto floating_point_value     = static_cast<long double>(integral_value);

    EXPECT_EQ(digits_from_integral(integral_value),
              digits_from_floating_point(floating_point_value));
}

TEST_P(SameIntegralValueTest, SameDigitsFromIntegralAndString)
{
    std::uintmax_t integral_value    = GetParam();
    std::string base_10_string_value =
        base_10_integer_string_from_arithmetic(integral_value);

    EXPECT_EQ(digits_from_integral(integral_value),
              digits_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromUserTypeIntegrationTest,
    SameIntegralValueTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0,
        FloatingPointIntegralLimits<long double, std::uintmax_t>::maximum(),
        2
    )
);


class SameFloatingPointValueTest : public ::testing::TestWithParam<long double>
{}; // class SameFloatingPointValueTest

TEST_P(SameFloatingPointValueTest, SameDigitsFromFloatingPointAndString)
{
    long double floating_point_value = GetParam();
    std::string base_10_string_value =
        base_10_integer_string_from_arithmetic(floating_point_value);

    EXPECT_EQ(digits_from_floating_point(floating_point_value),
              digits_from_string(base_10_string_value, 10));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromUserTypeIntegrationTest,
    SameFloatingPointValueTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0, std::numeric_limits<long double>::max(), 1.0e80L
    )
);

} // namespace
