#include "tasty_int/detail/int_from_floating_point.hpp"

#include <limits>
#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/from_floating_point_test_common.hpp"
#include "tasty_int/detail/test/int_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"



namespace {

using tasty_int::detail::Int;
using tasty_int::detail::Sign;
using tasty_int::detail::int_from_floating_point;
using from_floating_point_test_common::expect_digits_equal;


class NegativeValuesTest : public ::testing::TestWithParam<long double>
{}; // class NegativeValuesTest

void
expect_negative_int_equals(long double expected, const Int &actual)
{
    EXPECT_EQ(Sign::NEGATIVE, actual.sign);

    expect_digits_equal(-expected, actual.digits);
}

TEST_P(NegativeValuesTest,
       NegativeValuesLessThanOrEqualToNegativeOneProducesNegativeInt)
{
    expect_negative_int_equals(GetParam(),
                               int_from_floating_point(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromFloatingPointTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<long double>(
        -1.0,
        std::numeric_limits<long double>::lowest(),
        1.0e20
    )
);


class ZeroValueTest : public ::testing::TestWithParam<long double>
{}; // class ZeroValueTest

TEST_P(ZeroValueTest, AbsoluteValuesLessThanOneProduceZeroInt)
{
    const Int ZERO = { .sign = Sign::ZERO, .digits = { 0 } };
    long double zero_value = GetParam();


    EXPECT_EQ(ZERO, int_from_floating_point(zero_value));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromFloatingPointTest,
    ZeroValueTest,
    ::testing::Values(
      -1.0 + std::numeric_limits<long double>::epsilon(),
      -0.5L,
      -std::numeric_limits<long double>::epsilon(),
      0.0L,
      +std::numeric_limits<long double>::epsilon(),
      +0.5L,
      +1.0 - std::numeric_limits<long double>::epsilon()
    )
);


class PositiveValuesTest : public ::testing::TestWithParam<long double>
{}; // class PositiveValuesTest

void
expect_positive_int_equals(long double expected, const Int &actual)
{
    EXPECT_EQ(Sign::POSITIVE, actual.sign);

    expect_digits_equal(expected, actual.digits);
}

TEST_P(PositiveValuesTest,
       PositiveValuesGreaterThanOrEqualToOneProducePositiveInt)
{
    expect_positive_int_equals(GetParam(),
                               int_from_floating_point(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromFloatingPointTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<long double>(
        1.0,
        std::numeric_limits<long double>::max(),
        1.0e20
    )
);

} // namespace
