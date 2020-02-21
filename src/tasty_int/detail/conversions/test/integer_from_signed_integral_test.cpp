#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/test/integer_from_integral_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::conversions::integer_from_signed_integral;
using integer_from_integral_test_common::expect_digits_equal;
using integer_from_integral_test_common::expect_integer_equals_zero;
using integer_from_integral_test_common::expect_positive_integer_equals;


class NegativeValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class NegativeValuesTest

void
expect_negative_integer_equals(std::intmax_t  expected,
                               const Integer &actual)
{
    EXPECT_EQ(Sign::NEGATIVE, actual.sign);

    expect_digits_equal(-expected, actual.digits);
}

TEST_P(NegativeValuesTest, NegativeValuesProduceNegativeInteger)
{
    std::intmax_t negative_value = GetParam();

    Integer result = integer_from_signed_integral(negative_value);

    expect_negative_integer_equals(negative_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromSignedIntegralTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::min(), 2
    )
);


TEST(IntegerFromSignedIntegralTest, ZeroValueProducesZeroInteger)
{
    Integer result = integer_from_signed_integral(0);

    expect_integer_equals_zero(result);
}


class PositiveValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class PositiveValuesTest

TEST_P(PositiveValuesTest, PositiveValuesProducePositiveInteger)
{
    std::intmax_t positive_value = GetParam();

    Integer result = integer_from_signed_integral(positive_value);

    expect_positive_integer_equals(positive_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromSignedIntegralTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        1, std::numeric_limits<std::intmax_t>::max(), 2
    )
);

} // namespace
