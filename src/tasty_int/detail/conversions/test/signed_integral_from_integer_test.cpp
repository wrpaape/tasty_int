#include "tasty_int/detail/conversions/signed_integral_from_integer.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::signed_integral_from_integer;
using tasty_int::detail::conversions::integer_from_signed_integral;


class NonnegativeValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class NonnegativeValuesTest

TEST_P(NonnegativeValuesTest, InitialValuePreserved)
{
    std::intmax_t initial_value = GetParam();
    auto integer = integer_from_signed_integral(initial_value);

    std::intmax_t result = signed_integral_from_integer(integer);

    EXPECT_EQ(initial_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    UnsignedIntegralFromIntegerTest,
    NonnegativeValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        0, std::numeric_limits<std::intmax_t>::max(), 2
    )
);


class NegativeValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class NegativeValuesTest

TEST_P(NegativeValuesTest, InitialValuePreserved)
{
    std::intmax_t initial_value = GetParam();
    auto integer = integer_from_signed_integral(initial_value);

    std::intmax_t result = signed_integral_from_integer(integer);

    EXPECT_EQ(initial_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    UnsignedIntegralFromIntegerTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::lowest(), 2
    )
);

} // namespace
