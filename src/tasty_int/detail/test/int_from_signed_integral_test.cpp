#include "tasty_int/detail/int_from_signed_integral.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/int_from_integral_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::Int;
using tasty_int::detail::Sign;
using tasty_int::detail::int_from_signed_integral;
using int_from_integral_test_common::expect_digits_equal;
using int_from_integral_test_common::expect_int_equals_zero;
using int_from_integral_test_common::expect_positive_int_equals;


class NegativeValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class NegativeValuesTest

void
expect_negative_int_equals(std::intmax_t expected, const Int &actual)
{
    EXPECT_EQ(Sign::NEGATIVE, actual.sign);

    expect_digits_equal(-expected, actual.digits);
}

TEST_P(NegativeValuesTest, NegativeValuesProduceNegativeInt)
{
    expect_negative_int_equals(GetParam(),
                               int_from_signed_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromSignedIntegralTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::min(), 2
    )
);


TEST(IntFromSignedIntegralTest, ZeroValueProducesZeroInt)
{
    expect_int_equals_zero(int_from_signed_integral(0));
}


class PositiveValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class PositiveValuesTest

TEST_P(PositiveValuesTest, PositiveValuesProducePositiveInt)
{
    expect_positive_int_equals(GetParam(),
                               int_from_signed_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromSignedIntegralTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        1, std::numeric_limits<std::intmax_t>::max(), 2
    )
);

} // namespace
