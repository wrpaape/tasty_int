#include "tasty_int/detail/conversions/test/from_floating_point_test_common.hpp"

#include <cmath>

#include "gtest/gtest.h"


namespace from_floating_point_test_common {

using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_BASE;


void
expect_digits_equal(long double                    expected,
                    const std::vector<digit_type> &digits)
{
    std::size_t index = 0;

    do {
        digit_type next_digit =
            static_cast<digit_type>(std::fmod(expected, DIGIT_BASE));
        EXPECT_EQ(next_digit, digits.at(index++));
        expected /= DIGIT_BASE;
    } while (expected >= 1.0L);

    EXPECT_EQ(index, digits.size());
}

} // namespace from_floating_point_test_common
