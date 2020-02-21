#include "tasty_int/detail/integer_from_unsigned_integral.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/integer_from_integral_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::integer_from_unsigned_integral;
using integer_from_integral_test_common::expect_integer_equals_zero;
using integer_from_integral_test_common::expect_positive_integer_equals;


TEST(IntegerFromUnsignedIntegralTest, ZeroValueProducesZeroInteger)
{
    Integer result = integer_from_unsigned_integral(0);

    expect_integer_equals_zero(result);
}


class PositiveValuesTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class PositiveValuesTest

TEST_P(PositiveValuesTest, PositiveValuesProducePositiveInteger)
{
    std::uintmax_t positive_value = GetParam();

    Integer result =integer_from_unsigned_integral(positive_value);

    expect_positive_integer_equals(positive_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerFromUnsignedIntegralTest,
    PositiveValuesTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        1, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

} // namespace
