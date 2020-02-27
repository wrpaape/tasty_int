#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_unsigned_integral.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::unsigned_integral_from_integer;
using tasty_int::detail::conversions::integer_from_unsigned_integral;
using tasty_int::detail::conversions::integer_from_signed_integral;


class NonnegativeValuesTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class NonnegativeValuesTest

TEST_P(NonnegativeValuesTest, InitialValuePreserved)
{
    std::uintmax_t initial_value = GetParam();
    auto integer = integer_from_unsigned_integral(initial_value);

    std::uintmax_t result = unsigned_integral_from_integer(integer);

    EXPECT_EQ(initial_value, result);
}

INSTANTIATE_TEST_SUITE_P(
    UnsignedIntegralFromIntegerTest,
    NonnegativeValuesTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);


class NegativeValuesTest : public ::testing::TestWithParam<std::intmax_t>
{}; // class NegativeValuesTest

TEST_P(NegativeValuesTest, InitialValuePreserved)
{
    std::intmax_t initial_value = GetParam();
    auto unsigned_initial_value = static_cast<std::uintmax_t>(initial_value);
    auto integer = integer_from_signed_integral(initial_value);

    std::uintmax_t unsigned_result = unsigned_integral_from_integer(integer);

    EXPECT_EQ(unsigned_initial_value, unsigned_result);
}

INSTANTIATE_TEST_SUITE_P(
    UnsignedIntegralFromIntegerTest,
    NegativeValuesTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::lowest(), 2
    )
);

} // namespace
