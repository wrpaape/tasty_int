#include "tasty_int/detail/digits_from_integral.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"


using namespace tasty_int::detail;

namespace {

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
    ::testing::Values(0,
                      DIGIT_TYPE_MAX / 4,
                      DIGIT_TYPE_MAX / 2,
                      DIGIT_TYPE_MAX)
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
    ::testing::Values(DIGIT_TYPE_MAX + 1,
                      std::numeric_limits<std::uintmax_t>::max() / 4,
                      std::numeric_limits<std::uintmax_t>::max() / 2,
                      std::numeric_limits<std::uintmax_t>::max())
);

} // namespace
