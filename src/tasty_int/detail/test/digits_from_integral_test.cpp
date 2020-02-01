#include "tasty_int/detail/digits_from_integral.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::digit_type;
using tasty_int::detail::digits_from_integral;


class SmallValuesTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class SmallValuesTest

TEST_P(SmallValuesTest, SingleDigitForValuesLessThanOrEqualToDigitTypeMax)
{
    std::vector<digit_type> expected = {
        static_cast<digit_type>(GetParam())
    };

    EXPECT_EQ(expected, digits_from_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromIntegralTest,
    SmallValuesTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(0, DIGIT_TYPE_MAX, 2)
);


class LargeValuesTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class LargeValuesTest

TEST_P(LargeValuesTest, TwoDigitsForValuesGreaterThanDigitTypeMax)
{
    std::vector<digit_type> expected = {
        static_cast<digit_type>(GetParam()),
        static_cast<digit_type>(GetParam() >> DIGIT_TYPE_BITS)
    };

    EXPECT_EQ(expected, digits_from_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromIntegralTest,
    LargeValuesTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        DIGIT_TYPE_MAX + 1,
        std::numeric_limits<std::uintmax_t>::max(),
        2
    )
);

} // namespace
