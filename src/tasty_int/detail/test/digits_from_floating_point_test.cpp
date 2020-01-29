#include "tasty_int/detail/digits_from_floating_point.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/from_floating_point_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


using namespace tasty_int::detail;
using namespace from_floating_point_test_common;

namespace {

class DigitsFromFloatingPointTest : public ::testing::TestWithParam<long double>
{}; // class DigitsFromFloatingPointTest

TEST_P(DigitsFromFloatingPointTest, TwoDigitsForValuesGreaterThanDigitTypeMax)
{
    expect_digits_equal(GetParam(), digits_from_floating_point(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsFromFloatingPointTest,
    DigitsFromFloatingPointTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0,
        std::numeric_limits<long double>::max(),
        1.0e20
    )
);

} // namespace
