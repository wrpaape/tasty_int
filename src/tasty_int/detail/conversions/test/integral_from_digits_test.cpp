#include "tasty_int/detail/conversions/integral_from_digits.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::conversions::integral_from_digits;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_TYPE_BITS;


class SingleDigitTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class SingleDigitTest

TEST_P(SingleDigitTest, InitialValuePreserved)
{
    std::uintmax_t initial_value = GetParam();
    std::vector<digit_type> single_digit = {
        static_cast<digit_type>(initial_value)
    };

    EXPECT_EQ(initial_value, integral_from_digits(single_digit));
}

INSTANTIATE_TEST_SUITE_P(
    IntegralFromDigitsTest,
    SingleDigitTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(0, DIGIT_TYPE_MAX, 2)
);


class MultiDigitTest : public ::testing::TestWithParam<std::uintmax_t>
{}; // class MultiDigitTest

TEST_P(MultiDigitTest, InitialValuePreserved)
{
    std::uintmax_t initial_value = GetParam();
    digit_type lower_digit = static_cast<digit_type>(initial_value);
    digit_type upper_digit =
        static_cast<digit_type>(initial_value >> DIGIT_TYPE_BITS);
    std::vector<digit_type> multiple_digits = { lower_digit, upper_digit };

    EXPECT_EQ(initial_value, integral_from_digits(multiple_digits));
}

INSTANTIATE_TEST_SUITE_P(
    IntegralFromDigitsTest,
    MultiDigitTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        DIGIT_TYPE_MAX + 1, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

} // namespace
