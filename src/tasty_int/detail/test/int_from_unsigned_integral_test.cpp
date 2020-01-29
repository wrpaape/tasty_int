#include "tasty_int/detail/int_from_unsigned_integral.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/int_from_integral_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


using namespace tasty_int::detail;
using namespace int_from_integral_test_common;

namespace {

TEST(IntFromUnsignedIntegralTest, ZeroValueProducesZeroInt)
{
    expect_int_equals_zero(int_from_unsigned_integral(0));
}


class PositiveValuesTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class PositiveValuesTest

TEST_P(PositiveValuesTest, PositiveValuesProducePositiveInt)
{
    expect_positive_int_equals(GetParam(),
                               int_from_unsigned_integral(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    IntFromUnsignedIntegralTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        1, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

} // namespace
