#include "tasty_int/detail/int_from_floating_point.hpp"

#include <limits>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/from_floating_point_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


using namespace tasty_int::detail;
using namespace from_floating_point_test_common;

namespace {

class NegativeValuesTest : public ::testing::TestWithParam<long double>
{}; // class NegativeValuesTest

void
expect_negative_int_equals(long double expected, const Int &actual)
{
    EXPECT_EQ(Sign::NEGATIVE, actual.sign);

    expect_digits_equal(-expected, actual.digits);
}

TEST_P(NegativeValuesTest, NegativeValuesProduceNegativeInt)
{
    expect_negative_int_equals(GetParam(),
                               int_from_floating_point(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromFloatingPointTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<long double>(
        -std::numeric_limits<long double>::epsilon(),
        std::numeric_limits<long double>::lowest(),
        1.0e20
    )
);


void
expect_int_equals_zero(const Int &actual)
{
    EXPECT_EQ(Sign::ZERO, actual.sign);

    expect_digits_equal(0.0, actual.digits);
}

TEST(IntFromFloatingPointTest, ZeroValueProducesZeroInt)
{
    expect_int_equals_zero(int_from_floating_point(0.0));
}


class PositiveValuesTest : public ::testing::TestWithParam<long double>
{}; // class PositiveValuesTest

void
expect_positive_int_equals(long double expected, const Int &actual)
{
    EXPECT_EQ(Sign::POSITIVE, actual.sign);

    expect_digits_equal(expected, actual.digits);
}

TEST_P(PositiveValuesTest, PositiveValuesProducePositiveInt)
{
    expect_positive_int_equals(GetParam(),
                               int_from_floating_point(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromFloatingPointTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<long double>(
        std::numeric_limits<long double>::epsilon(),
        std::numeric_limits<long double>::max(),
        1.0e20
    )
);

} // namespace
