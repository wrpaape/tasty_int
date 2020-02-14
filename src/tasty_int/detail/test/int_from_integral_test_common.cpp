#include "tasty_int/detail/test/int_from_integral_test_common.hpp"

#include "gtest/gtest.h"


namespace int_from_integral_test_common {

using tasty_int::detail::Int;
using tasty_int::detail::Sign;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::DIGIT_TYPE_MAX;


void
expect_digits_equal(std::uintmax_t                 expected,
                    const std::vector<digit_type> &digits)
{
    EXPECT_EQ(static_cast<digit_type>(expected), digits.at(0));

    if (expected <= DIGIT_TYPE_MAX) {
        EXPECT_EQ(1, digits.size());

    } else {
        EXPECT_EQ(static_cast<digit_type>(expected / DIGIT_BASE),
                  digits.at(1));
        EXPECT_EQ(2, digits.size());
    }
}

void
expect_int_equals_zero(const Int &actual)
{
    EXPECT_EQ(Sign::ZERO, actual.sign);

    expect_digits_equal(0, actual.digits);
}

void
expect_positive_int_equals(std::uintmax_t expected, const Int &actual)
{
    EXPECT_EQ(Sign::POSITIVE, actual.sign);

    expect_digits_equal(expected, actual.digits);
}

} // namespace int_from_integral_test_common
