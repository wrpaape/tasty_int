#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"

#include <cmath>

#include <limits>
#include <string>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_floating_point.hpp"
#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int_test/base_10_integer_string_from_arithmetic.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::floating_point_from_integer;
using tasty_int::detail::conversions::integer_from_floating_point;
using tasty_int::detail::conversions::integer_from_string;
using tasty_int_test::base_10_integer_string_from_arithmetic;


class FiniteFloatingPointFromIntegerTest
    : public ::testing::TestWithParam<long double>
{}; // class FiniteFloatingPointFromIntegerTest

TEST_P(FiniteFloatingPointFromIntegerTest, InitialValuePreserved)
{
    long double initial_value = GetParam();
    auto integer = integer_from_floating_point(initial_value);

    EXPECT_EQ(std::trunc(initial_value), floating_point_from_integer(integer));
}

INSTANTIATE_TEST_SUITE_P(
    NonnegativeFloatingPointFromIntegerTest,
    FiniteFloatingPointFromIntegerTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0, std::numeric_limits<long double>::max(), 1.0e20
    )
);

INSTANTIATE_TEST_SUITE_P(
    NegativeFloatingPointFromIntegerTest,
    FiniteFloatingPointFromIntegerTest,
    tasty_int_test::logarithmic_range<long double>(
        -std::numeric_limits<long double>::min(),
        std::numeric_limits<long double>::lowest(),
        1.0e20
    )
);


class InfiniteFloatingPointFromIntegerTest : public ::testing::Test
{
protected:
    void
    expect_overflow(long double expected_infinity,
                    long double limit);
}; // class InfiniteFloatingPointFromIntegerTest

void
InfiniteFloatingPointFromIntegerTest::expect_overflow(
    long double expected_infinity,
    long double limit
)
{
    std::string overflow_string =
        base_10_integer_string_from_arithmetic(limit) + '0';
    auto overflow_integer = integer_from_string(overflow_string, 10);

    EXPECT_EQ(expected_infinity, floating_point_from_integer(overflow_integer));
}

TEST_F(InfiniteFloatingPointFromIntegerTest,
       PositiveOverflowProducesPositiveInfinity)
{
    expect_overflow(+std::numeric_limits<long double>::infinity(),
                    std::numeric_limits<long double>::max());
}

TEST_F(InfiniteFloatingPointFromIntegerTest,
       NegativeOverflowProducesNegativeInfinity)
{
    expect_overflow(-std::numeric_limits<long double>::infinity(),
                    std::numeric_limits<long double>::lowest());
}

} // namespace
