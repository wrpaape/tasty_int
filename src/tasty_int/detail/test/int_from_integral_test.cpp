#include "tasty_int/detail/int_from_integral.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range.hpp"


using namespace tasty_int::detail;

namespace {

void
ExpectDigitsEqualNonnegativeValue(std::uintmax_t                 expected,
                                  const std::vector<digit_type> &digits)
{
    ASSERT_GE(digits.size(), 1);

    EXPECT_EQ(static_cast<digit_type>(expected), digits.front());

    if (expected <= DIGIT_TYPE_MAX) {
        EXPECT_EQ(1, digits.size());

    } else {
        ASSERT_GE(digits.size(), 2);

        EXPECT_EQ(static_cast<digit_type>(expected >> DIGIT_TYPE_BITS),
                  digits.back());
        EXPECT_EQ(2, digits.size());
    }
}


void
ExpectNegativeIntEquals(std::intmax_t expected, const Int &actual)
{
    EXPECT_EQ(Sign::NEGATIVE, actual.sign);

    ExpectDigitsEqualNonnegativeValue(-expected, actual.digits);
}

class NegativeValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class NegativeValuesTest

TEST_P(NegativeValuesTest, NegativeValuesProduceNegativeInt)
{
    ExpectNegativeIntEquals(GetParam(), int_from_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromIntegralTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::min(), 2
    )
);


void
ExpectZeroIntEquals(const Int &actual)
{
    EXPECT_EQ(Sign::ZERO, actual.sign);

    ExpectDigitsEqualNonnegativeValue(0, actual.digits);
}

TEST(IntFromIntegralTest, ZeroValueProducesZeroInt)
{
    ExpectZeroIntEquals(int_from_integral(0));
}


void
ExpectPositiveIntEquals(std::intmax_t expected, const Int &actual)
{
    EXPECT_EQ(Sign::POSITIVE, actual.sign);

    ExpectDigitsEqualNonnegativeValue(expected, actual.digits);
}

class PositiveValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class PositiveValuesTest

TEST_P(PositiveValuesTest, PositiveValuesProducePositiveInt)
{
    ExpectPositiveIntEquals(GetParam(), int_from_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromIntegralTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        1, std::numeric_limits<std::intmax_t>::max(), 2
    )
);

} // namespace
