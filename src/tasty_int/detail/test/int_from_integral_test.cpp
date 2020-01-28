#include "tasty_int/detail/test/int_from_integral_test.hpp"

#include "gtest/gtest.h"


using namespace tasty_int::detail;

namespace int_from_integral_test {

void
expect_digits_equal(std::uintmax_t                 expected,
                    const std::vector<digit_type> &digits)
{
    EXPECT_EQ(static_cast<digit_type>(expected), digits.at(0));

    if (expected <= DIGIT_TYPE_MAX) {
        EXPECT_EQ(1, digits.size());

    } else {
        EXPECT_EQ(static_cast<digit_type>(expected >> DIGIT_TYPE_BITS),
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


} // namespace int_from_integral_test
